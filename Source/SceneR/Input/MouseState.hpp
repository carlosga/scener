// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_INPUT_MOUSE_STATE_HPP
#define SCENER_INPUT_MOUSE_STATE_HPP

#include <cstdint>

namespace SceneR { namespace Input {

enum class Buttons     : std::uint32_t;
enum class ButtonState : std::uint32_t;

/// Represents the state of a mouse input device, including mouse cursor position and buttons pressed.
class MouseState
{
public:
    ///Initializes a new instance of the MouseState class.
    MouseState() noexcept;

    /// Initializes a new instance of the MouseState class.
    /// \param x
    /// \param y
    /// \param scrollWheel
    /// \param leftButton
    /// \param middleButton
    /// \param rightButton
    /// \param xButton1
    /// \param xButton2
    MouseState(std::uint32_t x
             , std::uint32_t y
             , std::uint32_t scrollWheel
             , ButtonState   leftButton
             , ButtonState   middleButton
             , ButtonState   rightButton
             , ButtonState   xButton1
             , ButtonState   xButton2) noexcept;

    /// Returns the state of the left mouse button.
    ButtonState left_button() const noexcept;

    /// Returns the state of the middle mouse button.
    ButtonState middle_button() const noexcept;

    /// Returns the state of the right mouse button.
    ButtonState right_button() const noexcept;

    /// Gets the cumulative mouse scroll wheel value since the game was started.
    std::uint32_t scroll_wheel_value() const noexcept;

    /// Specifies the horizontal position of the mouse cursor.
    std::uint32_t x() const noexcept;

    /// Returns the state of XBUTTON1.
    ButtonState xbutton_1() const noexcept;

    /// Returns the state of XBUTTON2.
    ButtonState xbutton_2() const noexcept;

    /// Specifies the vertical position of the mouse cursor.
    std::uint32_t y() const noexcept;

private:
    std::uint32_t _x;
    std::uint32_t _y;
    std::uint32_t _scroll_wheel;
    ButtonState   _left_button;
    ButtonState   _middle_button;
    ButtonState   _right_button;
    ButtonState   _xbutton_1;
    ButtonState   _xbutton_2;
};

}}

#endif // SCENER_INPUT_MOUSE_HPP
