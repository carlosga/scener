// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/input/KeyboardState.hpp"

#include "scener/input/Keys.hpp"
#include "scener/input/KeyState.hpp"
#include "scener/graphics/opengl/DisplaySurface.hpp"

namespace scener { namespace input {

using scener::graphics::opengl::display_surface;

// Initializes a new instance of the KeyboardState class.
// Array or parameter list of Keys to initialize as pressed.
//KeyboardState(Keys[] keys);

KeyboardState::KeyboardState(display_surface* surface) noexcept
    : _surface(surface)
{
}

KeyState KeyboardState::get_key_state(Keys key) noexcept
{
    return (is_key_down(key) ? KeyState::down : KeyState::up);
}

std::vector<Keys> KeyboardState::get_pressed_keys() noexcept
{
    return { };
}

bool KeyboardState::is_key_down(Keys key) noexcept
{
    return false;
    // return (glfwGetKey(_window_handle, static_cast<int>(key)) == GLFW_PRESS);
}

bool KeyboardState::is_key_up(Keys key) noexcept
{
    return false;
    // return (glfwGetKey(_window_handle, static_cast<int>(key)) == GLFW_RELEASE);
}

}}
