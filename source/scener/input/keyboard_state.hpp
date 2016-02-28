// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_INPUT_KEYBOARD_STATE
#define SCENER_INPUT_KEYBOARD_STATE

#include <vector>

#include "scener/input/keys.hpp"
#include "scener/input/key_state.hpp"

namespace scener { namespace graphics { namespace opengl { class display_surface; } } }

namespace scener { namespace input {

/// Represents a state of keystrokes recorded by a keyboard input device.
class keyboard_state
{
public:
    ///Initializes a new instance of the KeyboardState class.
    keyboard_state(scener::graphics::opengl::display_surface* surface) noexcept;

    //KeyboardState(Keys[] keys);

public:
    /// Returns the state of a particular key.
    key_state get_key_state(keys key) noexcept;

    /// Gets an array of values that correspond to the keyboard keys that are currently being pressed
    /// \returns the keys that are currently pressed.
    std::vector<keys> get_pressed_keys() noexcept;

    /// Returns whether a specified key is currently being pressed.
    /// \param key specifies the key to query.
    /// \returns true if the key specified by key is being held down; false otherwise.
    bool is_key_down(keys key) noexcept;

    /// Returns whether a specified key is currently not pressed.
    /// \param key specifies the key to query.
    /// \returns true if the key specified by key is not pressed; false otherwise.
    bool is_key_up(keys key) noexcept;

private:
    scener::graphics::opengl::display_surface* _surface;
};

}}

#endif // SCENER_INPUT_KEYBOARD_STATE
