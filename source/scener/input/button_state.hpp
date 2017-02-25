// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_INPUT_BUTTON_STATE_HPP
#define SCENER_INPUT_BUTTON_STATE_HPP

#include <cstdint>

namespace scener::input
{
    /// Identifies the state of a controller button.
    enum class button_state : std::uint32_t
    {
        pressed     ///< The button is pressed.
      , released    ///< The button is released.
    };
}

#endif  // SCENER_INPUT_BUTTON_STATE_HPP
