// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_INPUT_KEYBOARD_STATE
#define SCENER_INPUT_KEYBOARD_STATE

#include <vector>

namespace scener { namespace graphics { namespace opengl { class display_surface; } } }

namespace scener { namespace input {

enum class Keys     : std::uint32_t;
enum class KeyState : std::uint32_t;

/// Represents a state of keystrokes recorded by a keyboard input device.
class KeyboardState
{
public:
    ///Initializes a new instance of the KeyboardState class.
    KeyboardState(scener::graphics::opengl::display_surface* surface) noexcept;

    //KeyboardState(Keys[] keys);

public:
    /// Returns the state of a particular key.
    KeyState get_key_state(Keys key) noexcept;

    /// Gets an array of values that correspond to the keyboard keys that are currently being pressed
    /// \returns the keys that are currently pressed.
    std::vector<Keys> get_pressed_keys() noexcept;

    /// Returns whether a specified key is currently being pressed.
    /// \param key specifies the key to query.
    /// \returns true if the key specified by key is being held down; false otherwise.
    bool is_key_down(Keys key) noexcept;

    /// Returns whether a specified key is currently not pressed.
    /// \param key specifies the key to query.
    /// \returns true if the key specified by key is not pressed; false otherwise.
    bool is_key_up(Keys key) noexcept;

private:
    scener::graphics::opengl::display_surface* _surface;
};

}}

#endif // SCENER_INPUT_KEYBOARD_STATE
