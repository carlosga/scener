// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#ifndef SCENER_GRAPHICS_VULKAN_DISPLAY_SURFACE_XCB_HPP
#define SCENER_GRAPHICS_VULKAN_DISPLAY_SURFACE_XCB_HPP

#include <cstdint>
#include <queue>
#include <string>

#include <gsl/gsl>
#include <xcb/xcb.h>
#include <vulkan/vulkan.hpp>

namespace vk { class Instance; }

namespace scener::graphics::vulkan
{
    class physical_device;
    class logical_device;

    /// Represents a XCB display surface.
    class display_surface final
    {
    public:
        /// Initializes a new instance of the display_surface class.
        display_surface(gsl::not_null<vk::Instance*> vk_instance) noexcept;

        /// Releases all resources being used by this DisplaySurface instance.
        ~display_surface() noexcept;

    public:
        /// Sets the display surface title ( for window surfaces ).
        void title(const std::string& title) noexcept;

    public:
        /// Creates the display surface with the given width and height.
        /// \param width the display surface width.
        /// \param height the display surface width.
        void create(std::uint32_t width, std::uint32_t height) noexcept;

        /// Destroys this DisplaySurface instance.
        void destroy() noexcept;

        /// Clears the entire area of this display surface.
        void clear() noexcept;

        /// Shows the display surface.
        void show() noexcept;
        
        /// Process all the events that have been received from the X server.
        void pool_events() noexcept;

    private:
        /// Get the vulkan surface extent
        vk::Extent2D get_extent(const vk::SurfaceCapabilitiesKHR& capabilities) const noexcept;
        
    private:
        xcb_window_t             _xcb_window;
        xcb_screen_t*            _screen;
        xcb_connection_t*        _connection;
        xcb_intern_atom_reply_t* _atom_wm_delete_window;
        vk::Instance*            _vk_instance;
        vk::SurfaceKHR           _vk_surface;

        friend class vulkan::physical_device;
        friend class vulkan::logical_device;
    };
}

#endif
