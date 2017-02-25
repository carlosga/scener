// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_INPUT_MOUSE_STATE_HPP
#define SCENER_INPUT_MOUSE_STATE_HPP

#include <cstdint>

#include "scener/input/buttons.hpp"
#include "scener/input/button_state.hpp"

namespace scener::input
{
    /// Represents the state of a mouse input device, including mouse cursor position and buttons pressed.
    class mouse_state
    {
    public:
        ///Initializes a new instance of the MouseState class.
        mouse_state() noexcept;

        /// Initializes a new instance of the MouseState class.
        /// \param x Horizontal mouse position.
        /// \param y Vertical mouse position.
        /// \param scrollWheel Mouse scroll wheel value.
        /// \param leftButton Left mouse button state.
        /// \param middleButton Middle mouse button state.
        /// \param rightButton Right mouse button state.
        /// \param xButton1 XBUTTON1 state.
        /// \param xButton2 XBUTTON2 state.
        mouse_state(std::uint32_t x
                  , std::uint32_t y
                  , std::uint32_t scrollWheel
                  , button_state   leftButton
                  , button_state   middleButton
                  , button_state   rightButton
                  , button_state   xButton1
                  , button_state   xButton2) noexcept;

        /// Returns the state of the left mouse button.
        button_state left_button() const noexcept;

        /// Returns the state of the middle mouse button.
        button_state middle_button() const noexcept;

        /// Returns the state of the right mouse button.
        button_state right_button() const noexcept;

        /// Gets the cumulative mouse scroll wheel value since the game was started.
        std::uint32_t scroll_wheel_value() const noexcept;

        /// Specifies the horizontal position of the mouse cursor.
        std::uint32_t x() const noexcept;

        /// Returns the state of XBUTTON1.
        button_state xbutton_1() const noexcept;

        /// Returns the state of XBUTTON2.
        button_state xbutton_2() const noexcept;

        /// Specifies the vertical position of the mouse cursor.
        std::uint32_t y() const noexcept;

    private:
        std::uint32_t _x;
        std::uint32_t _y;
        std::uint32_t _scroll_wheel;
        button_state   _left_button;
        button_state   _middle_button;
        button_state   _right_button;
        button_state   _xbutton_1;
        button_state   _xbutton_2;
    };
}

#endif // SCENER_INPUT_MOUSE_STATE_HPP
