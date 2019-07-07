// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#ifdef VK_USE_PLATFORM_XCB_KHR

#include "scener/graphics/vulkan/xcb/render_surface.hpp"

#include <scener/math/basic_rect.hpp>

#include "scener/graphics/vulkan/adapter.hpp"
#include "scener/graphics/vulkan/vulkan_result.hpp"

namespace scener::graphics::vulkan
{
    render_surface::render_surface(gsl::not_null<adapter*>         adapter
                                 , gsl::not_null<display_surface*> display_surface) noexcept
        : _adapter         { adapter }
        , _display_surface { display_surface }
        , _render_surface  { }
    {
        // Create vulkan surface
        auto create_info = vk::XcbSurfaceCreateInfoKHR()
            .setConnection(display_surface->connection())
            .setWindow(display_surface->window());

        auto result = _adapter->instance().createXcbSurfaceKHR(&create_info, nullptr, &_render_surface);

        check_result(result);
    }

    render_surface::~render_surface() noexcept
    {
        if (_adapter)
        {
            _adapter->instance().destroySurfaceKHR(_render_surface, nullptr);
            _adapter = nullptr;
        }
        _display_surface = nullptr;
    }

    const vk::SurfaceKHR& render_surface::surface() const noexcept
    {
        return _render_surface;
    }

    vk::Extent2D render_surface::extent(const vk::SurfaceCapabilitiesKHR& capabilities) const noexcept
    {        
        // The extent is typically the size of the window we created the surface from.
        // However if Vulkan returns -1 then simply substitute the window size.
        if (capabilities.currentExtent.width == UINT32_MAX)
        {
            return vk::Extent2D()
                .setWidth(_display_surface->rect().width())
                .setHeight(_display_surface->rect().height());
        }

        return capabilities.currentExtent;
    }
}

#endif
