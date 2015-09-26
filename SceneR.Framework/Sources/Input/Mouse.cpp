// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Input/Mouse.hpp>

#include <System/Graphics/Platform.hpp>
#include <Input/MouseState.hpp>

namespace SceneR
{
    namespace Input
    {
        MouseState Mouse::get_state() noexcept
        {
            // glfwGetCursorPos(window, &xpos, &ypos);
            // int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

            return MouseState();
        }

        void Mouse::set_position(const std::uint32_t& x, const std::uint32_t& y) noexcept
        {
            glfwSetCursorPos(window_handle, x, y);
        }

        void Mouse::initialize(GLFWwindow* window) noexcept
        {
            window_handle = window;

            // Enable mouse cursor (only needed for fullscreen mode)
            glfwSetInputMode(window_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

            // Enable mouse sticky buttons
            glfwSetInputMode(window_handle, GLFW_STICKY_MOUSE_BUTTONS, 1);

            // Cursor position callback
            // glfwSetCursorPosCallback(window_handle, Mouse::cursor_position_callback);

            // Mouse buttons callback
            // glfwSetMouseButtonCallback(window_handle, Mouse::mouse_button_callback);

            // Mouse scrolling callback
            // glfwSetScrollCallback(window_handle, Mouse::scroll_wheel_callback);
        }

        void Mouse::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) noexcept
        {
        }

        void Mouse::mouse_button_callback(GLFWwindow*   window
                                        , std::uint32_t button
                                        , std::uint32_t action
                                        , std::uint32_t mods) noexcept
        {
//            if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
//                popup_menu();
        }

        void Mouse::scroll_wheel_callback(GLFWwindow* window, double xoffset, double yoffset) noexcept
        {
        }

        GLFWwindow* Mouse::window_handle;
    }
}
