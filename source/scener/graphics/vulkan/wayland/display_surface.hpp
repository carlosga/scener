// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#ifndef SCENER_GRAPHICS_VULKAN_DISPLAY_SURFACE_WAYLAND_HPP
#define SCENER_GRAPHICS_VULKAN_DISPLAY_SURFACE_WAYLAND_HPP

#include <cstdint>
#include <string>

#include <gsl/gsl>
#include <scener/math/basic_rect.hpp>
#include <vulkan/vulkan.hpp>
#include <wayland-client.h>

namespace scener::graphics::vulkan
{
    class physical_device;
    class logical_device;

    /// Represents a Wayland display surface.
    class display_surface final
    {
        static void global_registry_handler_callback(void *data, struct wl_registry *registry, std::uint32_t id, const char *interface, std::uint32_t version);
        static void global_registry_remover_callback(void *data, struct wl_registry *registry, std::uint32_t id);

        static void global_shell_surface_ping_callback(void *data, struct wl_shell_surface *shell_surface, std::uint32_t serial);
        static void global_shell_surface_configure_callback(void *data, struct wl_shell_surface *shell_surface, std::uint32_t edges, int32_t width, int32_t height);
        static void global_shell_surface_popup_done_PopupDoneCb(void *data, struct wl_shell_surface *shell_surface);

        static void global_seat_capabilities_callback(void *data, wl_seat *seat, std::uint32_t caps);

    public:
        /// Initializes a new instance of the display_surface class.
        /// \param title the initial window title
        /// \param rect the initial window location & size
        display_surface(const std::string& title, const scener::math::basic_rect<std::uint32_t>& rect) noexcept;

        /// Releases all resources being used by this display_surface instance.
        ~display_surface() noexcept;

    public:
        struct wl_display* display() const noexcept;
        struct wl_surface* surface() const noexcept;
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
        void registry_handler(struct wl_registry *registry, std::uint32_t id, const char *interface, std::uint32_t version);
        void registry_remover(struct wl_registry *registry, std::uint32_t id);
        void seat_capabilities(wl_seat *seat, std::uint32_t caps);

    private:
        struct wl_display*       _wl_display;
        struct wl_compositor*    _wl_compositor;
        struct wl_surface*       _wl_surface;
        struct wl_shell*         _wl_shell;
        struct wl_shell_surface* _wl_shell_surface;
        struct wl_seat*          _wl_seat;

        scener::math::basic_rect<std::uint32_t> _rect;

        friend class vulkan::physical_device;
        friend class vulkan::logical_device;
    };
}

#endif
