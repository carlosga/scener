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

#include "scener/math/basic_rect.hpp"

namespace vk { class Instance; }

namespace scener::graphics::vulkan
{
    /// Represents a XCB display surface.
    class display_surface final
    {
    public:
        /// Initializes a new instance of the display_surface class.
        /// \param title the initial window title
        /// \param rect the initial window location & size
        display_surface(const std::string& title, const scener::math::basic_rect<std::uint32_t>& rect) noexcept;

        /// Releases all resources being used by this DisplaySurface instance.
        ~display_surface() noexcept;

    public:
        xcb_connection_t*   connection() const noexcept;
        const xcb_window_t& window() const noexcept;
        scener::math::basic_rect<std::uint32_t> rect() const noexcept;
    
    public:       
        /// Clears the entire area of this display surface.
        void clear() noexcept;

        /// Shows the display surface.
        void show() noexcept;
        
        /// Process all the events that have been received from the X server.
        void pool_events() noexcept;
       
    private:        
        void create(const std::string& title, const scener::math::basic_rect<std::uint32_t>& rect) noexcept;
        void destroy() noexcept;
        
    private:
        xcb_window_t             _window;
        xcb_screen_t*            _screen;
        xcb_connection_t*        _connection;
        xcb_intern_atom_reply_t* _atom_wm_delete_window;
    };
}

#endif
