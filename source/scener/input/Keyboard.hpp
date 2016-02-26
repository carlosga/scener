// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_INPUT_KEYBOARD_HPP
#define SCENER_INPUT_KEYBOARD_HPP

#include <cstdint>
#include <vector>

#include "scener/graphics/opengl/DisplaySurface.hpp"

namespace scener { namespace graphics { namespace opengl { class display_surface; } } }

namespace scener { namespace input {

enum class Keys     : std::uint32_t;
enum class KeyState : std::uint32_t;

class KeyboardState;

/// Allows retrieval of keystrokes from a keyboard input device.
class Keyboard
{
public:
    /// Returns the current keyboard state.
    /// \returns current keyboard state.
    static KeyboardState get_state() noexcept;

    /// Gets or sets the window used for mouse processing.
    static void initialize(graphics::opengl::display_surface* s) noexcept;

private:
    static void key_callback(graphics::opengl::display_surface* s, int key, int scancode, int action, int mods) noexcept;

private:
    Keyboard() = delete;
    Keyboard(const Keyboard& keyboard) = delete;
    Keyboard& operator=(const Keyboard& keyboard) = delete;

private:
    static graphics::opengl::display_surface* surface;
};

}}

#endif // SCENER_INPUT_KEYBOARD_HPP
