// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#ifndef SCENER_GRAPHICS_VULKAN_DISPLAY_SURFACE_WAYLAND_HPP
#define SCENER_GRAPHICS_VULKAN_DISPLAY_SURFACE_WAYLAND_HPP

#include <cstdint>
#include <queue>
#include <string>

#include <gsl/gsl>
#include <wayland-client.h>
#include <vulkan/vulkan.hpp>

namespace vk { class Instance; }

namespace scener::graphics::vulkan
{
    class physical_device;
    class logical_device;

    /// Represents a XCB display surface.
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
        void registry_handler(struct wl_registry *registry, std::uint32_t id, const char *interface, std::uint32_t version);
        void registry_remover(struct wl_registry *registry, std::uint32_t id);
        void seat_capabilities(wl_seat *seat, std::uint32_t caps);

    private:
        /// Get the vulkan surface extent
        vk::Extent2D get_extent(const vk::SurfaceCapabilitiesKHR& capabilities) const noexcept;
        
    private:
        struct wl_registry*      _wl_registry;
        struct wl_display*       _wl_display;
        struct wl_compositor*    _wl_compositor;
        struct wl_surface*       _wl_surface;
        struct wl_shell*         _wl_shell;
        struct wl_shell_surface* _wl_shell_surface;
        struct wl_seat*          _wl_seat;
        vk::Instance*            _vk_instance;
        vk::SurfaceKHR           _vk_surface;

        friend class vulkan::physical_device;
        friend class vulkan::logical_device;
    };
}

#endif
