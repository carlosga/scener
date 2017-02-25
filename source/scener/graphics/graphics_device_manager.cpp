// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/graphics_device_manager.hpp"

#include "scener/graphics/graphics_device.hpp"
#include "scener/graphics/renderer.hpp"
#include "scener/graphics/service_container.hpp"
#include "scener/graphics/window.hpp"

namespace scener::graphics
{
    graphics_device_manager::graphics_device_manager(gsl::not_null<renderer*> renderer) noexcept
        : _renderer { renderer }
    {
        _renderer->services()->add_service<igraphics_device_service>(*this);
    }

    void graphics_device_manager::apply_changes() noexcept
    {
        _graphics_device->presentation_parameters().back_buffer_width  = preferred_back_buffer_width;
        _graphics_device->presentation_parameters().back_buffer_height = preferred_back_buffer_height;
        _graphics_device->presentation_parameters().full_screen        = full_screen;

        _renderer->window()->title(window_title);
        _renderer->window()->allow_user_resizing(allow_user_resizing);

        _graphics_device->blend_state().apply();
        _graphics_device->rasterizer_state().apply();
        _graphics_device->depth_stencil_state().apply();
    }

    bool graphics_device_manager::begin_draw() noexcept
    {
        return true;
    }

    void graphics_device_manager::end_draw() noexcept
    {
        _graphics_device->present();
    }

    void graphics_device_manager::create_device() noexcept
    {
        _graphics_device = std::make_unique<graphics_device>();
    }

    graphics_device* graphics_device_manager::device() const noexcept
    {
        return _graphics_device.get();
    }
}
