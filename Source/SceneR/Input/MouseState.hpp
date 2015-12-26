// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_INPUT_MOUSE_STATE_HPP
#define SCENER_INPUT_MOUSE_STATE_HPP

#include <cstdint>

#include <Input/Buttons.hpp>
#include <Input/ButtonState.hpp>

namespace SceneR
{
    namespace Input
    {
        // Represents the state of a mouse input device, including mouse cursor position and buttons pressed.
        struct MouseState
        {
        public:
            MouseState() noexcept;

            //Initializes a new instance of the MouseState class.
            MouseState(const std::uint32_t& x
                     , const std::uint32_t& y
                     , const std::uint32_t& scrollWheel
                     , const ButtonState&   leftButton
                     , const ButtonState&   middleButton
                     , const ButtonState&   rightButton
                     , const ButtonState&   xButton1
                     , const ButtonState&   xButton2) noexcept;

            ~MouseState() = default;

            // Returns the state of the left mouse button.
            const ButtonState& left_button() const noexcept;

            // Returns the state of the middle mouse button.
            const ButtonState& middle_button() const noexcept;

            // Returns the state of the right mouse button.
            const ButtonState& right_button() const noexcept;

            // Gets the cumulative mouse scroll wheel value since the game was started.
            std::uint32_t scroll_wheel_value() const noexcept;

            // Specifies the horizontal position of the mouse cursor.
            std::uint32_t x() const noexcept;

            // Returns the state of XBUTTON1.
            const ButtonState& xbutton_1() const noexcept;

            // Returns the state of XBUTTON2.
            const ButtonState& xbutton_2() const noexcept;

            // Specifies the vertical position of the mouse cursor.
            std::uint32_t y() const noexcept;

            // Determines whether two MouseState instances are equal.
            // public static bool op_Equality (MouseState left,MouseState right)

            // Determines whether two MouseState instances are not equal.
            // public static bool op_Inequality (MouseState left,MouseState right)

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
    }
}

#endif // SCENER_INPUT_MOUSE_HPP
