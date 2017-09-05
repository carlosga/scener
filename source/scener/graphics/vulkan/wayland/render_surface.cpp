// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#ifdef VK_USE_PLATFORM_WAYLAND_KHR

#include "scener/graphics/vulkan/wayland/render_surface.hpp"

#include "scener/graphics/vulkan/connection.hpp"
#include "scener/graphics/vulkan/vulkan_result.hpp"
#include "scener/math/basic_rect.hpp"

namespace scener::graphics::vulkan
{
    render_surface::render_surface(const connection&      connection
                                 , const display_surface& display_surface) noexcept
        : _connection      { connection }
        , _display_surface { display_surface }
        , _render_surface  { }
    {
        // Create vulkan surface
        auto create_info = vk::WaylandSurfaceCreateInfoKHR()
            .setDisplay(display_surface.display())
            .setSurface(display_surface.surface());

        auto result = _connection.vulkan().createWaylandSurfaceKHR(&create_info, nullptr, &_render_surface);

        check_result(result);
    }

    render_surface::~render_surface()
    {
        _connection.vulkan().destroySurfaceKHR(_render_surface, nullptr);
    }

    const vk::SurfaceKHR& render_surface::surface() const noexcept
    {
        return _render_surface;
    }

    vk::Extent2D render_surface::extent(const vk::SurfaceCapabilitiesKHR& capabilities) const noexcept
    {
        vk::Extent2D extent;

        // The extent is typically the size of the window we created the surface from.
        // However if Vulkan returns -1 then simply substitute the window size.
        if (capabilities.currentExtent.width == UINT32_MAX)
        {
            const auto& rect = _display_surface.rect();

            extent.width  = rect.width();
            extent.height = rect.height();
        }
        else
        {
            extent = vk::Extent2D(capabilities.currentExtent);
        }

        return extent;
    }
}

#endif
