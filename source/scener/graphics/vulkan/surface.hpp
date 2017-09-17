// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#ifndef SCENER_GRAPHICS_VULKAN_SURFACE_HPP
#define SCENER_GRAPHICS_VULKAN_SURFACE_HPP

#if defined(VK_USE_PLATFORM_WIN32_KHR)
#elif defined(VK_USE_PLATFORM_XLIB_KHR)
#elif defined(VK_USE_PLATFORM_XCB_KHR)
    #include "scener/graphics/vulkan/xcb/display_surface.hpp"
    #include "scener/graphics/vulkan/xcb/render_surface.hpp"
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
    #include "scener/graphics/vulkan/wayland/display_surface.hpp"
    #include "scener/graphics/vulkan/wayland/render_surface.hpp"
#elif defined(VK_USE_PLATFORM_MIR_KHR)
#elif defined(VK_USE_PLATFORM_DISPLAY_KHR)
#endif

#endif
