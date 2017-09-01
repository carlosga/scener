#ifndef SCENER_GRAPHICS_VULKAN_RENDER_SURFACE_WAYLAND_HPP
#define SCENER_GRAPHICS_VULKAN_RENDER_SURFACE_WAYLAND_HPP

#include <vulkan/vulkan.hpp>

#include "scener/graphics/vulkan/wayland/display_surface.hpp"

namespace scener::graphics::vulkan
{
    class connection;    

    class render_surface final
    {
    public:
        render_surface(const connection&      connection
                     , const display_surface& display_surface) noexcept;

        ~render_surface() noexcept;

    public:
        const vk::SurfaceKHR& surface() const noexcept;

    public:
        vk::Extent2D extent(const vk::SurfaceCapabilitiesKHR& capabilities) const noexcept;

    private:
        display_surface _display_surface;
        vk::SurfaceKHR  _vk_surface;
    };
}

#endif
