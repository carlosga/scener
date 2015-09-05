// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Input/MouseState.hpp>

namespace SceneR
{
    namespace Input
    {
        MouseState::MouseState()
        {
        }

        MouseState::MouseState(const int&         x
                             , const int&         y
                             , const int&         scrollWheel
                             , const ButtonState& leftButton
                             , const ButtonState& middleButton
                             , const ButtonState& rightButton
                             , const ButtonState& xButton1
                             , const ButtonState& xButton2)
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

        MouseState::~MouseState()
        {
        }

        // Returns the state of the left mouse button.
        const ButtonState& MouseState::left_button() const
        {
            return _left_button;
        }

        // Returns the state of the middle mouse button.
        const ButtonState& MouseState::middle_button() const
        {
            return _middle_button;
        }

        // Returns the state of the right mouse button.
        const ButtonState& MouseState::right_button() const
        {
            return _right_button;
        }

        // Gets the cumulative mouse scroll wheel value since the game was started.
        int MouseState::scroll_wheel_value() const
        {
            return _scroll_wheel;
        }

        // Specifies the horizontal position of the mouse cursor.
        int MouseState::x() const
        {
            return _x;
        }

        // Returns the state of XBUTTON1.
        const ButtonState& MouseState::xbutton_1() const
        {
            return _xbutton_1;
        }

        // Returns the state of XBUTTON2.
        const ButtonState& MouseState::xbutton_2() const
        {
            return _xbutton_2;
        }

        // Specifies the vertical position of the mouse cursor.
        int MouseState::y() const
        {
            return _y;
        }
    }
}
