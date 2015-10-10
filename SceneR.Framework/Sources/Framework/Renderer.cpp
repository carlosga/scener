// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/Renderer.hpp>

#include <algorithm>
#include <iostream>
#include <thread>

#include <Content/ContentManager.hpp>
#include <Framework/GraphicsDeviceManager.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Framework/RendererWindow.hpp>
#include <Graphics/GraphicsDevice.hpp>

namespace SceneR
{
    namespace Framework
    {
        using SceneR::Content::ContentManager;
        using SceneR::Graphics::GraphicsDevice;
        using System::TimeSpan;

        Renderer::Renderer(const std::string& rootDirectory)
            : is_fixed_time_step       { true }
            , target_elapsed_time      { 10000000L / 60L }
            , _components              ( 0 )
            , _services                { }
            , _graphics_device_manager { nullptr }
            , _content_manager         { nullptr }
            , _renderer_window         { nullptr }
            , _timer                   { }
            , _render_time             { }
            , _total_tender_time       { TimeSpan::zero }
            , _is_running_slowly       { false }
            , _drawable_components     ( 0 )
            , _updateable_components   ( 0 )
            , _root_directory          { rootDirectory }
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

        void Renderer::run()
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

        void Renderer::exit()
        {
            _content_manager->unload();
            _graphics_device_manager->dispose();
            _services->clear();
            _renderer_window->close();

            glfwTerminate();
        }

        bool Renderer::begin_draw()
        {
            return true;
        }

        void Renderer::begin_run()
        {
            _services                = std::make_unique<RendererServiceContainer>();
            _graphics_device_manager = std::make_unique<GraphicsDeviceManager>(this);
            _content_manager         = std::make_unique<ContentManager>(_services.get(), _root_directory);
            _renderer_window         = std::make_unique<RendererWindow>(this);
        }

        void Renderer::draw(const RenderTime &renderTime)
        {
            for (auto& component : _drawable_components)
            {
                if (component->visible())
                {
                    component->draw(renderTime);
                }
            }
        }

        void Renderer::end_draw()
        {
            _graphics_device_manager->graphics_device()->present();
        }

        void Renderer::end_run()
        {
        }

        void Renderer::initialize()
        {
            for (auto& component : _components)
            {
                component->initialize();
            }
        }

        void Renderer::load_content()
        {
        }

        void Renderer::unload_content()
        {
            _drawable_components.clear();
            _updateable_components.clear();
            _components.clear();
        }

        void Renderer::update(const RenderTime &renderTime)
        {
            glfwPollEvents();

            for (auto& component : _updateable_components)
            {
                if (component->enabled())
                {
                    component->update(renderTime);
                }
            }
        }

        void Renderer::start_event_loop()
        {
            _timer.reset();

            do
            {
                time_step();

            } while (!_renderer_window->should_close());
        }

        /**
         * References:
         *      http://gafferongames.com/game-physics/fix-your-timestep/
         *      http://msdn.microsoft.com/en-us/library/bb203873.aspx
         */
        void Renderer::time_step()
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

        void Renderer::post_process_components()
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

        void Renderer::create_device()
        {
            _graphics_device_manager->create_device();
            _renderer_window->allow_user_resizing(true);
            _renderer_window->open();
            _graphics_device_manager->apply_changes();
        }

        void Renderer::fixed_time_step()
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

                std::this_thread::sleep_for(interval.ToDuration<std::chrono::milliseconds>());
            }
            else
            {
                std::cout << "runnin slowly" << std::endl;
            }
        }

        void Renderer::variable_time_step()
        {
        }
    }
}
