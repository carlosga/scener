// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef INPUT_KEYBOARD_HPP
#define INPUT_KEYBOARD_HPP

#include <cstdint>
#include <vector>

#include <Input/Keys.hpp>
#include <Input/KeyState.hpp>

struct GLFWwindow;

namespace SceneR
{
    namespace Input
    {
        struct KeyboardState;

        // Allows retrieval of keystrokes from a keyboard input device.
        class Keyboard
        {
        public:
            // Returns the current keyboard state.
            static KeyboardState get_state();

            // Gets or sets the window used for mouse processing.
            static void initialize(GLFWwindow *window);

        private:
            static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

            static GLFWwindow* window_handle;

        private:
            Keyboard() = delete;
            Keyboard(const Keyboard& keyboard) = delete;
            Keyboard& operator=(const Keyboard& keyboard) = delete;
        };
    }
}

#endif  // INPUT_KEYBOARD_HPP
