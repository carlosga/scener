// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef KEYSTATE_HPP
#define KEYSTATE_HPP

#include <cstdint>

namespace SceneR
{
    namespace Input
    {
        // Identifies the state of a keyboard key.
        enum class KeyState : std::uint32_t
        {
            // Key is pressed.
            Down
            // Key is released.
          , Up
        };
    }
}

#endif // KEYSTATE_HPP
