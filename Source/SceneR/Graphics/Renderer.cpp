// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/Renderer.hpp"

#include <algorithm>
#include <iostream>
#include <thread>

#include "SceneR/Content/ContentManager.hpp"
#include "SceneR/Graphics/GraphicsDevice.hpp"
#include "SceneR/Graphics/GraphicsDeviceManager.hpp"
#include "SceneR/Graphics/OpenGL/RenderContext.hpp"
#include "SceneR/Graphics/RendererServiceContainer.hpp"
#include "SceneR/Graphics/RendererWindow.hpp"

namespace SceneR { namespace Graphics {

using SceneR::TimeSpan;
using SceneR::Content::ContentManager;
using SceneR::Graphics::GraphicsDevice;
using SceneR::Graphics::OpenGL::RenderContext;

Renderer::Renderer(const std::string& rootDirectory) noexcept
    : _root_directory { rootDirectory }
{
}

Renderer::~Renderer()
{
}

GraphicsDevice* Renderer::graphics_device() const noexcept
{
    if (!_graphics_device_manager.get())
    {
        return nullptr;
    }

    return _graphics_device_manager->graphics_device();
}

RendererWindow* Renderer::window() const noexcept
{
    return _renderer_window.get();
}

ContentManager* Renderer::content_manager() const noexcept
{
    return _content_manager.get();
}

RendererServiceContainer* Renderer::services() const noexcept
{
    return _services.get();
}

std::vector<std::shared_ptr<IComponent>>& Renderer::components() noexcept
{
    return _components;
}

void Renderer::run() noexcept
{
    begin_run();
    create_device();
    load_content();
    initialize();
    post_process_components();
    start_event_loop();
    unload_content();
    end_run();
}

void Renderer::exit() noexcept
{
    _content_manager->unload();
    _graphics_device_manager->dispose();
    _services->clear();
    _render_context->destroy();
    _renderer_window->close();
}

bool Renderer::begin_draw() noexcept
{
    return true;
}

void Renderer::begin_run() noexcept
{
    _services                = std::make_unique<RendererServiceContainer>();
    _graphics_device_manager = std::make_unique<GraphicsDeviceManager>(this);
    _content_manager         = std::make_unique<ContentManager>(_services.get(), _root_directory);
    _renderer_window         = std::make_unique<RendererWindow>(this);
}

void Renderer::draw(const StepTime &renderTime) noexcept
{
    for (auto& component : _drawable_components)
    {
        if (component->visible())
        {
            component->draw(renderTime);
        }
    }
}

void Renderer::end_draw() noexcept
{
    _render_context->present();
    // _graphics_device_manager->graphics_device()->present();
}

void Renderer::end_run() noexcept
{
}

void Renderer::initialize() noexcept
{
    for (auto component : _components)
    {
        component->initialize();
    }
}

void Renderer::load_content() noexcept
{
}

void Renderer::unload_content() noexcept
{
    _drawable_components.clear();
    _updateable_components.clear();
    _components.clear();
}

void Renderer::update(const StepTime &renderTime) noexcept
{
    for (auto& component : _updateable_components)
    {
        if (component->enabled())
        {
            component->update(renderTime);
        }
    }
}

void Renderer::start_event_loop() noexcept
{
    _timer.reset();

    _renderer_window->show();

    do
    {
        _renderer_window->pool_events();

        time_step();

    } while (!_renderer_window->should_close());
}

/**
 * References:
 *      http://gafferongames.com/game-physics/fix-your-timestep/
 *      http://msdn.microsoft.com/en-us/library/bb203873.aspx
 */
void Renderer::time_step() noexcept
{
    if (is_fixed_time_step)
    {
        fixed_time_step();
    }
    else
    {
        variable_time_step();
    }
}

void Renderer::post_process_components() noexcept
{
    for (auto& component : _components)
    {
        auto drawable = std::dynamic_pointer_cast<IDrawable>(component);

        if (drawable != nullptr)
        {
            _drawable_components.push_back(drawable);
        }

        auto updateable = std::dynamic_pointer_cast<IUpdateable>(component);

        if (updateable != nullptr)
        {
            _updateable_components.push_back(updateable);
        }
    }

    std::sort(_drawable_components.begin(), _drawable_components.end(),
              [](const std::shared_ptr<IDrawable>& a, const std::shared_ptr<IDrawable>& b) -> bool
              {
                  return (a->draw_order() < b->draw_order());
              });

    std::sort(_updateable_components.begin(), _updateable_components.end(),
              [](const std::shared_ptr<IUpdateable>& a, const std::shared_ptr<IUpdateable>& b) -> bool
              {
                  return (a->update_order() < b->update_order());
              });
}

void Renderer::create_device() noexcept
{
    _graphics_device_manager->create_device();
    _renderer_window->allow_user_resizing(true);
    _renderer_window->open();
    _render_context = std::make_unique<RenderContext>(_renderer_window->display_device()
                                                    , _renderer_window->display_surface());
    _render_context->create();
    _graphics_device_manager->apply_changes();

    switch (graphics_device()->presentation_parameters().present_interval)
    {
        case PresentInterval::one:
            _render_context->present_interval(1);
            break;

        case PresentInterval::two:
            _render_context->present_interval(2);
            break;

        case PresentInterval::immediate:
            _render_context->present_interval(0);
            break;
    }
}

void Renderer::fixed_time_step() noexcept
{
    _render_time.elapsed_render_time = _timer.elapsed_time_step_time();
    _render_time.total_render_time   = _timer.elapsed_time();
    _render_time.is_running_slowly   = _is_running_slowly;

    _timer.update_time_step();

    update(_render_time);

    _is_running_slowly = (_timer.elapsed_time_step_time() > target_elapsed_time);

    if (!_is_running_slowly)
    {
        if (begin_draw())
        {
            draw(_render_time);
            end_draw();
        }

        auto interval = (target_elapsed_time - _timer.elapsed_time_step_time());

        std::this_thread::sleep_for(interval.to_duration<std::chrono::milliseconds>());
    }
    else
    {
        std::cout << "running slowly" << std::endl;
    }
}

void Renderer::variable_time_step() noexcept
{
}

}}
