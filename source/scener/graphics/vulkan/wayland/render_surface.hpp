// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#ifndef SCENER_GRAPHICS_VULKAN_RENDER_SURFACE_WAYLAND_HPP
#define SCENER_GRAPHICS_VULKAN_RENDER_SURFACE_WAYLAND_HPP

#include <gsl/gsl>
#include <vulkan/vulkan.hpp>

#include "scener/graphics/vulkan/wayland/display_surface.hpp"

namespace scener::graphics::vulkan
{
    class adapter;

    class render_surface final
    {
    public:
        render_surface(std::shared_ptr<adapter>        adapter
                     , gsl::not_null<display_surface*> display_surface) noexcept;

        ~render_surface() noexcept;

    public:
        const vk::SurfaceKHR& surface() const noexcept;

    public:
        vk::Extent2D extent(const vk::SurfaceCapabilitiesKHR& capabilities) const noexcept;

    private:
        std::shared_ptr<adapter> _adapter;
        display_surface*         _display_surface;
        vk::SurfaceKHR           _render_surface;
    };
}

#endif
