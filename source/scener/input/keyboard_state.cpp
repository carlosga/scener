// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/input/keyboard_state.hpp"

#include "scener/input/keys.hpp"
#include "scener/input/key_state.hpp"
#include "scener/graphics/opengl/display_surface.hpp"

namespace scener { namespace input {

using scener::graphics::opengl::display_surface;

// Initializes a new instance of the KeyboardState class.
// Array or parameter list of Keys to initialize as pressed.
//KeyboardState(Keys[] keys);

keyboard_state::keyboard_state(display_surface* surface) noexcept
    : _surface(surface)
{
}

key_state keyboard_state::get_key_state(keys key) noexcept
{
    return (is_key_down(key) ? key_state::down : key_state::up);
}

std::vector<keys> keyboard_state::get_pressed_keys() noexcept
{
    return { };
}

bool keyboard_state::is_key_down(keys key) noexcept
{
    return false;
    // return (glfwGetKey(_window_handle, static_cast<int>(key)) == GLFW_PRESS);
}

bool keyboard_state::is_key_up(keys key) noexcept
{
    return false;
    // return (glfwGetKey(_window_handle, static_cast<int>(key)) == GLFW_RELEASE);
}

}}
