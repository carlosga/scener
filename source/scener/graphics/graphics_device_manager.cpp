// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/graphics_device_manager.hpp"

#include "scener/graphics/graphics_device.hpp"
#include "scener/graphics/renderer.hpp"
#include "scener/graphics/service_container.hpp"

namespace scener::graphics
{
    graphics_device_manager::graphics_device_manager(gsl::not_null<renderer*> renderer) noexcept
        : _graphics_device                { nullptr }
        , _renderer                       { renderer }
        , _prepare_device_settings_signal { }
    {
        _renderer->services()->add_service<igraphics_device_service>(*this);
    }

    void graphics_device_manager::create_device() noexcept
    {
        graphics_device_information device_info;

        device_info.presentation_params.back_buffer_width  = preferred_back_buffer_width;
        device_info.presentation_params.back_buffer_height = preferred_back_buffer_height;
        device_info.presentation_params.full_screen        = full_screen;

        _prepare_device_settings_signal(&device_info);

        _graphics_device = std::make_unique<graphics_device>(device_info.adapter, device_info.presentation_params);
    }


    void graphics_device_manager::begin_prepare() noexcept
    {
        Expects(_graphics_device.get() != nullptr);

        return _graphics_device->begin_prepare();
    }

    void graphics_device_manager::end_prepare() noexcept
    {
        Expects(_graphics_device.get() != nullptr);

        _graphics_device->end_prepare();
    }

    void graphics_device_manager::draw() noexcept
    {
        Expects(_graphics_device.get() != nullptr);

        _graphics_device->draw();
        _graphics_device->present();
    }

    graphics_device* graphics_device_manager::device() const noexcept
    {
        return _graphics_device.get();
    }

    nod::connection graphics_device_manager::prepare_device_settings(std::function<void(graphics_device_information*)>&& slot) noexcept
    {
        return _prepare_device_settings_signal.connect(std::move(slot));
    }
}
