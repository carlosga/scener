// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/drawable_component.hpp"

#include "scener/graphics/graphics_device.hpp"
#include "scener/graphics/graphics_device_manager.hpp"
#include "scener/graphics/renderer.hpp"
#include "scener/graphics/window.hpp"

namespace scener::graphics
{
    drawable_component::drawable_component(gsl::not_null<graphics::renderer*> renderer) noexcept
        : component { renderer }
    {
    }

    graphics_device* drawable_component::device() noexcept
    {
        return _renderer->device();
    }

    void drawable_component::draw() noexcept
    {
    }

    bool drawable_component::visible() const noexcept
    {
        return _visible;
    }

    void drawable_component::visible(bool visible) noexcept
    {
        _visible = visible;
    }

    std::uint32_t drawable_component::draw_order() const noexcept
    {
        return _draw_order;
    }

    void drawable_component::draw_order(std::uint32_t order) noexcept
    {
        _draw_order = order;
    }

    void drawable_component::initialize() noexcept
    {
        this->load_content();
    }

    void drawable_component::load_content() noexcept
    {
    }

    void drawable_component::unload_content() noexcept
    {
    }
}
