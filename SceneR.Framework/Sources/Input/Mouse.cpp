// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Input/Mouse.hpp>

#include <System/Graphics/Platform.hpp>
#include <Input/MouseState.hpp>

namespace SceneR
{
    namespace Input
    {
        MouseState Mouse::GetState()
        {
            // glfwGetCursorPos(window, &xpos, &ypos);
            // int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

            return MouseState();
        }

        void Mouse::SetPosition(const int& x, const int& y)
        {
            glfwSetCursorPos(WindowHandle, x, y);
        }

        void Mouse::Initialize(GLFWwindow* window)
        {
            WindowHandle = window;

            // Enable mouse cursor (only needed for fullscreen mode)
            glfwSetInputMode(WindowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

            // Enable mouse sticky buttons
            glfwSetInputMode(WindowHandle, GLFW_STICKY_MOUSE_BUTTONS, 1);

            // Cursor position callback
            // glfwSetCursorPosCallback(WindowHandle, Mouse::CursorPositionCallback);

            // Mouse buttons callback
            // glfwSetMouseButtonCallback(WindowHandle, Mouse::MouseButtonCallback);

            // Mouse scrolling callback
            // glfwSetScrollCallback(WindowHandle, Mouse::ScrollCallback);
        }

        void Mouse::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
        {
        }

        void Mouse::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
        {
//            if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
//                popup_menu();
        }

        void Mouse::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
        {
        }

        GLFWwindow* Mouse::WindowHandle;
    }
}
