// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <cstdint>

#include <Input/Buttons.hpp>
#include <Input/ButtonState.hpp>

struct GLFWwindow;

namespace SceneR
{
    namespace Input
    {
        struct MouseState;

        // Allows retrieval of position and button clicks from a mouse input device.
        class Mouse
        {
        public:
            // Gets the current state of the mouse, including mouse position and buttons pressed.
            static MouseState GetState();

            // Sets the position of the mouse cursor relative to the upper-left corner of the window.
            static void SetPosition(const int& x, const int& y);

            // Gets or sets the window used for mouse processing.
            // Mouse coordinates returned by GetState are relative to the upper-left corner of this window.
            static void Initialize(GLFWwindow* window);

        private:
            static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
            static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
            static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

            static GLFWwindow* WindowHandle;

        private:
            Mouse() = delete;
            Mouse(const Mouse& mouse) = delete;
            Mouse& operator=(const Mouse& mouse) = delete;
        };
    }
}

#endif // MOUSE_HPP
