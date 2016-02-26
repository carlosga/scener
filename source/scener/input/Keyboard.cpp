// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/input/Keyboard.hpp"

#include "scener/input/KeyboardState.hpp"
#include "scener/graphics/opengl/Platform.hpp"

namespace scener { namespace input {

using scener::graphics::opengl::display_surface;

// Returns the current keyboard state.
KeyboardState Keyboard::get_state() noexcept
{
    return KeyboardState(Keyboard::surface);
}

// Gets or sets the window used for mouse processing.
void Keyboard::initialize(display_surface* s) noexcept
{
    Keyboard::surface = s;

    // Enable sticky keys
    // glfwSetInputMode(window_handle, GLFW_STICKY_KEYS, 1);

    // initialize key callback
    // glfwSetKeyCallback(window_handle, Keyboard::key_callback);
}

void Keyboard::key_callback(display_surface* s, int key, int scancode, int action, int mods) noexcept
{
}

display_surface* Keyboard::surface;

}}
