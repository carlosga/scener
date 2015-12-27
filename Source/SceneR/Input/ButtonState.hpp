// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_INPUT_BUTTON_STATE_HPP
#define SCENER_INPUT_BUTTON_STATE_HPP

#include <cstdint>

namespace SceneR
{
    namespace Input
    {
        enum class ButtonState : std::uint32_t
        {
            // The button is pressed.
            Pressed
            // The button is released.
          , Released
        };
    }
}

#endif  // SCENER_INPUT_BUTTON_STATE_HPP
