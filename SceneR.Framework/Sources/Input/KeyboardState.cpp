// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Input/KeyboardState.hpp>
#include <System/Graphics/Platform.hpp>

namespace SceneR
{
    namespace Input
    {
        // Initializes a new instance of the KeyboardState class.
        // Array or parameter list of Keys to initialize as pressed.
        //KeyboardState(Keys[] keys);

        KeyboardState::KeyboardState(GLFWwindow* windowHandle)
            : _window_handle(windowHandle)
        {
        }

        KeyboardState::~KeyboardState()
        {
        }

        KeyState KeyboardState::get_key_state(const Keys &key)
        {
            return (is_key_down(key) ? KeyState::Down : KeyState::Up);
        }

        std::vector<Keys> KeyboardState::get_pressed_keys()
        {
            return { };
        }

        bool KeyboardState::is_key_down(const Keys &key)
        {
            return (glfwGetKey(_window_handle, static_cast<int>(key)) == GLFW_PRESS);
        }

        bool KeyboardState::is_key_up(const Keys &key)
        {
            return (glfwGetKey(_window_handle, static_cast<int>(key)) == GLFW_RELEASE);
        }
    }
}
