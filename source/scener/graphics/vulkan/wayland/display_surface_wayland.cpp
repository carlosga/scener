// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================
// Based on https://github.com/gamedevtech/X11OpenGLWindow
// ==================================================================================================

#ifdef VK_USE_PLATFORM_WAYLAND_KHR

#include "scener/graphics/vulkan/display_surface.hpp"
#include "scener/graphics/vulkan/vulkan_result.hpp"

namespace scener::graphics::vulkan
{
    void display_surface::global_registry_handler_callback(void *data, struct wl_registry *registry, std::uint32_t id, const char *interface, std::uint32_t version)
    {
        display_surface* self = reinterpret_cast<display_surface*>(data);
        self->registry_handler(registry, id, interface, version);
    }

    void display_surface::global_registry_remover_callback(void *data, struct wl_registry *registry, std::uint32_t id)
    {
        display_surface* self = reinterpret_cast<display_surface*>(data);
        self->registry_remover(registry, id);
    }

    void display_surface::global_shell_surface_ping_callback(void *data, struct wl_shell_surface *shell_surface, std::uint32_t serial)
    {
        wl_shell_surface_pong(shell_surface, serial);
    }

    void display_surface::global_shell_surface_configure_callback(void *data, struct wl_shell_surface *shell_surface, std::uint32_t edges, std::int32_t width, std::int32_t height)
    {
    }

    void display_surface::global_shell_surface_popup_done_PopupDoneCb(void *data, struct wl_shell_surface *shell_surface)
    {
    }

    void display_surface::global_seat_capabilities_callback(void *data, wl_seat *seat, std::uint32_t caps)
    {
        display_surface* self = reinterpret_cast<display_surface *>(data);
        self->seat_capabilities(seat, caps);
    }
    
    display_surface::display_surface(gsl::not_null<vk::Instance*> vk_instance) noexcept
        : _wl_display   { nullptr }
        , _wl_surface   { nullptr }
        , _vk_instance  { vk_instance }
        , _vk_surface   { }
    {
    }

    display_surface::~display_surface() noexcept
    {
        destroy();
    }

    void display_surface::title(const std::string& title) noexcept
    {
        wl_shell_surface_set_title(_wl_shell_surface, title.c_str());
    }

    void display_surface::create(std::uint32_t width, std::uint32_t height) noexcept
    {
        static const struct wl_registry_listener registry_listener =
        {
            global_registry_handler_callback
          , global_registry_remover_callback
        };
        static const struct wl_shell_surface_listener shell_surface_listener =
        {
            global_shell_surface_ping_callback
          , global_shell_surface_configure_callback
          , global_shell_surface_popup_done_PopupDoneCb
        };

        _wl_display = wl_display_connect(nullptr);

        Ensures(_wl_display != nullptr);

        _wl_registry = wl_display_get_registry(_wl_display);

        Ensures(_wl_registry != nullptr);

        wl_registry_add_listener(_wl_registry, &registry_listener, this);

        wl_display_dispatch(_wl_display);
        wl_display_roundtrip(_wl_display);

        Ensures(_wl_compositor != nullptr);

        _wl_surface = wl_compositor_create_surface(_wl_compositor);

        Ensures(_wl_surface != nullptr);

        _wl_shell_surface = wl_shell_get_shell_surface(_wl_shell, _wl_surface);

        Ensures(_wl_shell_surface != nullptr);

        wl_shell_surface_add_listener(_wl_shell_surface, &shell_surface_listener, this);
        wl_shell_surface_set_toplevel(_wl_shell_surface);

        wl_shell_surface_set_title(_wl_shell_surface, "scener");

        // Create vulkan surface
        auto create_info = vk::WaylandSurfaceCreateInfoKHR()
            .setDisplay(_wl_display)
            .setSurface(_wl_surface);

        auto result = _vk_instance->createWaylandSurfaceKHR(&create_info, nullptr, &_vk_surface);
        
        check_result(result);
    }

    void display_surface::destroy() noexcept
    {
        if (_wl_shell_surface != nullptr)
        {
            wl_shell_surface_destroy(_wl_shell_surface);
            _wl_shell_surface = nullptr;
        }

        if (_wl_surface != nullptr)
        {
            wl_surface_destroy(_wl_surface);
            _wl_surface = nullptr;
        }

        if (_wl_seat != nullptr)
        {
            wl_seat_destroy(_wl_seat);
            _wl_seat = nullptr;
        }

        if (_wl_shell != nullptr)
        {
            wl_shell_destroy(_wl_shell);
            _wl_shell = nullptr;
        }

        if (_wl_compositor != nullptr)
        {
            wl_compositor_destroy(_wl_compositor);
            _wl_compositor = nullptr;
        }

        if (_wl_registry != nullptr)
        {
            wl_registry_destroy(_wl_registry);
            _wl_registry = nullptr;
        }

        if (_wl_display != nullptr)
        {
            wl_display_disconnect(_wl_display);
            _wl_display = nullptr;
        }
    }

    void display_surface::clear() noexcept
    {
    }

    void display_surface::show() noexcept
    {
    }

    vk::Extent2D display_surface::get_extent(const vk::SurfaceCapabilitiesKHR& capabilities) const noexcept
    {
        VkExtent2D extent;
        
        // The extent is typically the size of the window we created the surface from.
        // However if Vulkan returns -1 then simply substitute the window size.
        if (capabilities.currentExtent.width == UINT32_MAX) 
        {
            extent.width  = 1600;
            extent.height = 900;
        }
        else
        {
            extent = capabilities.currentExtent;
        }
    
        return extent;
    }

    void display_surface::pool_events() noexcept
    {
    }

    void display_surface::registry_handler(struct wl_registry *registry, std::uint32_t id, const char *interface, std::uint32_t version)
    {
        if (strcmp(interface, "wl_compositor") == 0)
        {
            _wl_compositor = reinterpret_cast<wl_compositor*>(wl_registry_bind(registry, id, &wl_compositor_interface, 1));
        }
        else if (strcmp(interface, "wl_shell") == 0)
        {
            _wl_shell = reinterpret_cast<wl_shell*>(wl_registry_bind(registry, id, &wl_shell_interface, 1));
        }
        else if (strcmp(interface, "wl_seat") == 0)
        {
            _wl_seat = reinterpret_cast<wl_seat*>(wl_registry_bind(registry, id, &wl_seat_interface, 1));

            static const struct wl_seat_listener seat_listener = { global_seat_capabilities_callback, nullptr };
            wl_seat_add_listener(_wl_seat, &seat_listener, this);
        }
    }
   
    void display_surface::registry_remover(struct wl_registry *registry, std::uint32_t id)
    {
    }

    void display_surface::seat_capabilities(wl_seat *seat, std::uint32_t caps)
    {
    }
}

#endif
