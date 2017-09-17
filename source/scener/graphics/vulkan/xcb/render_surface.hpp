// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#ifndef SCENER_GRAPHICS_VULKAN_RENDER_SURFACE_XCB_HPP
#define SCENER_GRAPHICS_VULKAN_RENDER_SURFACE_XCB_HPP

#include <vulkan/vulkan.hpp>

#include "scener/graphics/vulkan/xcb/display_surface.hpp"

namespace scener::graphics::vulkan
{
    class adapter;

    class render_surface final
    {
    public:
        render_surface(gsl::not_null<adapter*>         adapter
                     , gsl::not_null<display_surface*> display_surface) noexcept;

        ~render_surface() noexcept;

    public:
        const vk::SurfaceKHR& surface() const noexcept;

    public:
        vk::Extent2D extent(const vk::SurfaceCapabilitiesKHR& capabilities) const noexcept;

    private:
        adapter*         _adapter;
        display_surface* _display_surface;
        vk::SurfaceKHR   _render_surface;
    };
}

#endif
