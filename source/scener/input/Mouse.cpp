// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/input/Mouse.hpp"

#include "scener/input/Buttons.hpp"
#include "scener/input/ButtonState.hpp"
#include "scener/input/MouseState.hpp"
#include "scener/graphics/opengl/DisplaySurface.hpp"

namespace scener { namespace input {

using scener::graphics::opengl::display_surface;

MouseState Mouse::get_state() noexcept
{
    return MouseState();
}

void Mouse::set_position(std::uint32_t x, std::uint32_t y) noexcept
{
}

void Mouse::initialize(display_surface* s) noexcept
{
    Mouse::surface = s;

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

void Mouse::cursor_position_callback(display_surface* s, double xpos, double ypos) noexcept
{
}

void Mouse::mouse_button_callback(display_surface* s
                                , std::uint32_t   button
                                , std::uint32_t   action
                                , std::uint32_t   mods) noexcept
{
//            if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
//                popup_menu();
}

void Mouse::scroll_wheel_callback(display_surface* s, double xoffset, double yoffset) noexcept
{
}

display_surface* Mouse::surface;

}}
