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
        KeyboardState Keyboard::get_state()
        {
            return KeyboardState(Keyboard::window_handle);
        }

        // Gets or sets the window used for mouse processing.
        void Keyboard::initialize(GLFWwindow *window)
        {
            window_handle = window;

            // Enable sticky keys
            glfwSetInputMode(window_handle, GLFW_STICKY_KEYS, 1);

            // initialize key callback
            // glfwSetKeyCallback(window_handle, Keyboard::key_callback);
        }

        void Keyboard::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
        {
        }

        GLFWwindow* Keyboard::window_handle;
    }
}
