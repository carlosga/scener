// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_INPUT_KEYBOARD_HPP
#define SCENER_INPUT_KEYBOARD_HPP

#include <cstdint>
#include <vector>

#include "scener/input/keyboard_state.hpp"
#include "scener/graphics/opengl/platform.hpp"
#include "scener/graphics/opengl/display_surface.hpp"

namespace scener { namespace graphics { namespace opengl { class display_surface; } } }

namespace scener { namespace input {

class keyboard_state;

/// Allows retrieval of keystrokes from a keyboard input device.
class keyboard
{
public:
    /// Returns the current keyboard state.
    /// \returns current keyboard state.
    static keyboard_state get_state() noexcept;

    /// Gets or sets the window used for mouse processing.
    static void initialize(graphics::opengl::display_surface* s) noexcept;

private:
    static void key_callback(graphics::opengl::display_surface* s, int key, int scancode, int action, int mods) noexcept;

private:
    keyboard() = delete;
    keyboard(const keyboard& keyboard) = delete;
    keyboard& operator=(const keyboard& keyboard) = delete;

private:
    static graphics::opengl::display_surface* surface;
};

}}

#endif // SCENER_INPUT_KEYBOARD_HPP
