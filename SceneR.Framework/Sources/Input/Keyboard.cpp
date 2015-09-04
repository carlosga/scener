// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Input/Keyboard.hpp>

#include <System/Graphics/Platform.hpp>
#include <Input/KeyboardState.hpp>

namespace SceneR
{
    namespace Input
    {
        // Returns the current keyboard state.
        KeyboardState Keyboard::GetState()
        {
            return KeyboardState(Keyboard::WindowHandle);
        }

        // Gets or sets the window used for mouse processing.
        void Keyboard::Initialize(GLFWwindow* window)
        {
            WindowHandle = window;

            // Enable sticky keys
            glfwSetInputMode(WindowHandle, GLFW_STICKY_KEYS, 1);

            // initialize key callback
            // glfwSetKeyCallback(WindowHandle, Keyboard::KeyCallback);
        }

        void Keyboard::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
        }

        GLFWwindow* Keyboard::WindowHandle;
    }
}
