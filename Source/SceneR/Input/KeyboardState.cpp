// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "KeyboardState.hpp"

#include "Keys.hpp"
#include "KeyState.hpp"
#include "../Graphics/OpenGL/DisplaySurface.hpp"

namespace SceneR
{
    namespace Input
    {
        using SceneR::Graphics::DisplaySurface;

        // Initializes a new instance of the KeyboardState class.
        // Array or parameter list of Keys to initialize as pressed.
        //KeyboardState(Keys[] keys);

        KeyboardState::KeyboardState(DisplaySurface* surface) noexcept
            : _surface(surface)
        {
        }

        KeyState KeyboardState::get_key_state(const Keys& key) noexcept
        {
            return (is_key_down(key) ? KeyState::Down : KeyState::Up);
        }

        std::vector<Keys> KeyboardState::get_pressed_keys() noexcept
        {
            return { };
        }

        bool KeyboardState::is_key_down(const Keys& key) noexcept
        {
            return false;
            // return (glfwGetKey(_window_handle, static_cast<int>(key)) == GLFW_PRESS);
        }

        bool KeyboardState::is_key_up(const Keys& key) noexcept
        {
            return false;
            // return (glfwGetKey(_window_handle, static_cast<int>(key)) == GLFW_RELEASE);
        }
    }
}
