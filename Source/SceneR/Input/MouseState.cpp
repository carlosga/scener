// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Input/MouseState.hpp"

#include "SceneR/Input/Buttons.hpp"
#include "SceneR/Input/ButtonState.hpp"

namespace SceneR
{
    namespace Input
    {
        MouseState::MouseState() noexcept
        {
        }

        MouseState::MouseState(const std::uint32_t& x
                             , const std::uint32_t& y
                             , const std::uint32_t& scrollWheel
                             , const ButtonState&   leftButton
                             , const ButtonState&   middleButton
                             , const ButtonState&   rightButton
                             , const ButtonState&   xButton1
                             , const ButtonState&   xButton2) noexcept
        {
            _x             = x;
            _y             = y;
            _scroll_wheel  = scrollWheel;
            _left_button   = leftButton;
            _middle_button = middleButton;
            _right_button  = rightButton;
            _xbutton_1     = xButton1;
            _xbutton_2     = xButton2;
        }

        // Returns the state of the left mouse button.
        const ButtonState& MouseState::left_button() const noexcept
        {
            return _left_button;
        }

        // Returns the state of the middle mouse button.
        const ButtonState& MouseState::middle_button() const noexcept
        {
            return _middle_button;
        }

        // Returns the state of the right mouse button.
        const ButtonState& MouseState::right_button() const noexcept
        {
            return _right_button;
        }

        // Gets the cumulative mouse scroll wheel value since the game was started.
        std::uint32_t MouseState::scroll_wheel_value() const noexcept
        {
            return _scroll_wheel;
        }

        // Specifies the horizontal position of the mouse cursor.
        std::uint32_t MouseState::x() const noexcept
        {
            return _x;
        }

        // Returns the state of XBUTTON1.
        const ButtonState& MouseState::xbutton_1() const noexcept
        {
            return _xbutton_1;
        }

        // Returns the state of XBUTTON2.
        const ButtonState& MouseState::xbutton_2() const noexcept
        {
            return _xbutton_2;
        }

        // Specifies the vertical position of the mouse cursor.
        std::uint32_t MouseState::y() const noexcept
        {
            return _y;
        }
    }
}
