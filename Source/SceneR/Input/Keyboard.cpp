// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Input/Keyboard.hpp>

#include <Graphics/OpenGL/Platform.hpp>
#include <Input/KeyboardState.hpp>

namespace SceneR
{
    namespace Input
    {
        using SceneR::Graphics::DisplaySurface;

        // Returns the current keyboard state.
        KeyboardState Keyboard::get_state() noexcept
        {
            return KeyboardState(Keyboard::surface);
        }

        // Gets or sets the window used for mouse processing.
        void Keyboard::initialize(DisplaySurface* surface) noexcept
        {
            Keyboard::surface = surface;

            // Enable sticky keys
            // glfwSetInputMode(window_handle, GLFW_STICKY_KEYS, 1);

            // initialize key callback
            // glfwSetKeyCallback(window_handle, Keyboard::key_callback);
        }

        void Keyboard::key_callback(DisplaySurface* surface, int key, int scancode, int action, int mods) noexcept
        {
        }

        DisplaySurface* Keyboard::surface;
    }
}
