// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/renderer.hpp"

#include <iostream>
#include <thread>

#include "scener/graphics/graphics_device.hpp"
#include "scener/graphics/graphics_device_manager.hpp"
#include "scener/graphics/window.hpp"
#include "scener/input/keyboard.hpp"
#include "scener/input/keyboard_state.hpp"
#include "scener/input/keys.hpp"
#include "scener/input/mouse.hpp"

namespace scener::graphics
{
    using scener::timespan;
    using scener::content::content_manager;
    using scener::graphics::graphics_device;
    using scener::input::keyboard;
    using scener::input::keyboard_state;
    using scener::input::keys;
    using scener::input::mouse;

    renderer::renderer(const std::string& root_directory) noexcept
        : _root_directory { root_directory }
    {
    }

    renderer::~renderer()
    {
    }

    graphics_device* renderer::device() const noexcept
    {
        if (!_device_manager.get())
        {
            return nullptr;
        }

        return _device_manager->device();
    }

    graphics::window* renderer::window() const noexcept
    {
        return _window.get();
    }

    content::content_manager* renderer::content_manager() const noexcept
    {
        return _content_manager.get();
    }

    service_container* renderer::services() const noexcept
    {
        return _services.get();
    }

    std::vector<std::shared_ptr<icomponent>>& renderer::components() noexcept
    {
        return _components;
    }

    void renderer::run() noexcept
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

    void renderer::exit() noexcept
    {
        _content_manager->unload();
        _services->clear();
    }

    bool renderer::begin_draw() noexcept
    {
        return true;
    }

    void renderer::begin_run() noexcept
    {
        _services        = std::make_unique<service_container>();
        _device_manager  = std::make_unique<graphics_device_manager>(this);
        _content_manager = std::make_unique<content::content_manager>(_services.get(), _root_directory);
        _window          = std::make_unique<graphics::window>(this);

        _device_manager->prepare_device_settings([&](presentation_parameters* params) -> void {
            prepare_device_settings(params);
        });
    }

    void renderer::draw(const steptime &time) noexcept
    {
        std::for_each(_drawable_components.begin(), _drawable_components.end(), [&time](const auto& component) -> void
        {
            if (component->visible())
            {
                component->draw(time);
            }
        });
    }

    void renderer::end_draw() noexcept
    {
        _device_manager->device()->present();
    }

    void renderer::end_run() noexcept
    {
    }

    void renderer::initialize() noexcept
    {
        std::for_each(_components.begin(), _components.end(), [](const auto& component) -> void {
            component->initialize();
        });

        keyboard::initialize(_window->display_surface());
        mouse::initialize(_window->display_surface());
    }

    void renderer::load_content() noexcept
    {
    }

    void renderer::unload_content() noexcept
    {
        _drawable_components.clear();
        _updateable_components.clear();
        _components.clear();
    }

    void renderer::update(const steptime& time) noexcept
    {
        std::for_each(_updateable_components.begin(), _updateable_components.end(), [&time](const auto& component) -> void
        {
            if (component->enabled())
            {
                component->update(time);
            }
        });
    }

    void renderer::start_event_loop() noexcept
    {
        _timer.reset();

        _window->show();

        do
        {
            _window->pool_events();

            time_step();

        } while (!_window->closed());
    }

    /**
    * References:
    *      http://gafferongames.com/game-physics/fix-your-timestep/
    *      http://msdn.microsoft.com/en-us/library/bb203873.aspx
    */
    void renderer::time_step() noexcept
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

    void renderer::post_process_components() noexcept
    {
        std::for_each(_components.begin(), _components.end(), [&] (const auto& component) -> void
        {
            auto drawable = std::dynamic_pointer_cast<idrawable>(component);

            if (drawable != nullptr)
            {
                _drawable_components.push_back(drawable);
            }

            auto updateable = std::dynamic_pointer_cast<iupdateable>(component);

            if (updateable != nullptr)
            {
                _updateable_components.push_back(updateable);
            }
        });

        std::sort(_drawable_components.begin(), _drawable_components.end(),
            [](const std::shared_ptr<idrawable>& a, const std::shared_ptr<idrawable>& b) -> bool
            {
                return (a->draw_order() < b->draw_order());
            }
        );

        std::sort(_updateable_components.begin(), _updateable_components.end(),
            [](const std::shared_ptr<iupdateable>& a, const std::shared_ptr<iupdateable>& b) -> bool
            {
                return (a->update_order() < b->update_order());
            }
        );
    }

    void renderer::create_device() noexcept
    {
        Ensures(_device_manager->preferred_back_buffer_width  > 0);
        Ensures(_device_manager->preferred_back_buffer_height > 0);

        _window->allow_user_resizing(true);
        _window->create({ 0u
                        , 0u
                        , _device_manager->preferred_back_buffer_width
                        , _device_manager->preferred_back_buffer_height });
        _window->title(_device_manager->window_title);
        _device_manager->create_device();
    }

    void renderer::fixed_time_step() noexcept
    {
        _time.elapsed_render_time = _timer.elapsed_time_step_time();
        _time.total_render_time   = _timer.elapsed_time();
        _time.is_running_slowly   = _is_running_slowly;

        _timer.update_time_step();

        update(_time);

        _is_running_slowly = (_timer.elapsed_time_step_time() > target_elapsed_time);

        if (!_is_running_slowly)
        {
            if (begin_draw())
            {
                draw(_time);
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

    void renderer::variable_time_step() noexcept
    {
    }

    graphics_device_manager* renderer::device_manager() const
    {
        return _device_manager.get();
    }

    void renderer::add_component(std::shared_ptr<icomponent> component)
    {
        _components.push_back(component);
    }

    void renderer::prepare_device_settings(presentation_parameters* params) const noexcept
    {
        params->device_window_handle = _window->display_surface();
    }
}
