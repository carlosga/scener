// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef INPUT_KEYBOARD_STATE
#define INPUT_KEYBOARD_STATE

#include <vector>

#include <Input/Keys.hpp>
#include <Input/KeyState.hpp>

struct GLFWwindow;

namespace SceneR
{
    namespace Input
    {
        // Represents a state of keystrokes recorded by a keyboard input device.
        struct KeyboardState
        {
        public:
            KeyboardState(GLFWwindow* windowHandle);

            ~KeyboardState();

            // Initializes a new instance of the KeyboardState class.
            // Array or parameter list of Keys to initialize as pressed.
            //KeyboardState(Keys[] keys);

            // Returns the state of a particular key.
            KeyState get_key_state(const Keys &key);

            // Gets an array of values that correspond to the keyboard keys that are currently being pressed
            std::vector<Keys> get_pressed_keys();

            // Returns whether a specified key is currently being pressed.
            // Enumerated value that specifies the key to query.
            bool is_key_down(const Keys &key);

            // Returns whether a specified key is currently not pressed.
            // Enumerated value that specifies the key to query.
            // true if the key specified by key is not pressed; false otherwise.
            bool is_key_up(const Keys &key);

            // Compares two objects to determine whether they are the same.
            // static bool op_Equality (KeyboardState a,KeyboardState b)

            // Compares two objects to determine whether they are different.
            // static bool op_Inequality (KeyboardState a,KeyboardState b)
        private:
            GLFWwindow* _window_handle;
        };
    }
}

#endif  // INPUT_KEYBOARD_STATE
