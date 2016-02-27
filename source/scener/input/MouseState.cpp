// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/input/MouseState.hpp"

#include "scener/input/Buttons.hpp"
#include "scener/input/ButtonState.hpp"

namespace scener { namespace input {

mouse_state::mouse_state() noexcept
{
}

mouse_state::mouse_state(std::uint32_t x
                     , std::uint32_t y
                     , std::uint32_t scrollWheel
                     , button_state   leftButton
                     , button_state   middleButton
                     , button_state   rightButton
                     , button_state   xButton1
                     , button_state   xButton2) noexcept
    : _x             { x            }
    , _y             { y            }
    , _scroll_wheel  { scrollWheel  }
    , _left_button   { leftButton   }
    , _middle_button { middleButton }
    , _right_button  { rightButton  }
    , _xbutton_1     { xButton1     }
    , _xbutton_2     { xButton2     }
{
}

// Returns the state of the left mouse button.
button_state mouse_state::left_button() const noexcept
{
    return _left_button;
}

// Returns the state of the middle mouse button.
button_state mouse_state::middle_button() const noexcept
{
    return _middle_button;
}

// Returns the state of the right mouse button.
button_state mouse_state::right_button() const noexcept
{
    return _right_button;
}

// Gets the cumulative mouse scroll wheel value since the game was started.
std::uint32_t mouse_state::scroll_wheel_value() const noexcept
{
    return _scroll_wheel;
}

// Specifies the horizontal position of the mouse cursor.
std::uint32_t mouse_state::x() const noexcept
{
    return _x;
}

// Returns the state of XBUTTON1.
button_state mouse_state::xbutton_1() const noexcept
{
    return _xbutton_1;
}

// Returns the state of XBUTTON2.
button_state mouse_state::xbutton_2() const noexcept
{
    return _xbutton_2;
}

// Specifies the vertical position of the mouse cursor.
std::uint32_t mouse_state::y() const noexcept
{
    return _y;
}

}}
