// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/input/mouse.hpp"

#include "scener/input/mouse_state.hpp"

namespace scener::input
{
    using scener::graphics::vulkan::display_surface;

    mouse_state mouse::get_state() noexcept
    {
        return mouse_state();
    }

    void mouse::set_position(std::uint32_t x, std::uint32_t y) noexcept
    {
    }

    void mouse::initialize(display_surface* s) noexcept
    {
        mouse::surface = s;

        // Enable mouse cursor (only needed for fullscreen mode)
        // glfwSetInputMode(window_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        // Enable mouse sticky buttons
        // glfwSetInputMode(window_handle, GLFW_STICKY_MOUSE_BUTTONS, 1);

        // Cursor position callback
        // glfwSetCursorPosCallback(window_handle, Mouse::cursor_position_callback);

        // Mouse buttons callback
        // glfwSetMouseButtonCallback(window_handle, Mouse::mouse_button_callback);

        // Mouse scrolling callback
        // glfwSetScrollCallback(window_handle, Mouse::scroll_wheel_callback);
    }

    void mouse::cursor_position_callback(display_surface* s, double xpos, double ypos) noexcept
    {
    }

    void mouse::mouse_button_callback(display_surface* s
                                    , std::uint32_t   button
                                    , std::uint32_t   action
                                    , std::uint32_t   mods) noexcept
    {
    //            if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    //                popup_menu();
    }

    void mouse::scroll_wheel_callback(display_surface* s, double xoffset, double yoffset) noexcept
    {
    }

    display_surface* mouse::surface;
}
