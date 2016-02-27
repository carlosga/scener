// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/input/keyboard.hpp"

#include "scener/input/keyboard_state.hpp"
#include "scener/graphics/opengl/Platform.hpp"

namespace scener { namespace input {

using scener::graphics::opengl::display_surface;

// Returns the current keyboard state.
keyboard_state keyboard::get_state() noexcept
{
    return keyboard_state(keyboard::surface);
}

// Gets or sets the window used for mouse processing.
void keyboard::initialize(display_surface* s) noexcept
{
    keyboard::surface = s;

    // Enable sticky keys
    // glfwSetInputMode(window_handle, GLFW_STICKY_KEYS, 1);

    // initialize key callback
    // glfwSetKeyCallback(window_handle, Keyboard::key_callback);
}

void keyboard::key_callback(display_surface* s, int key, int scancode, int action, int mods) noexcept
{
}

display_surface* keyboard::surface;

}}
