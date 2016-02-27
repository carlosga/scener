// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_INPUT_KEYSTATE_HPP
#define SCENER_INPUT_KEYSTATE_HPP

#include <cstdint>

namespace scener { namespace input {

/// Identifies the state of a keyboard key.
enum class key_state : std::uint32_t
{
    down    ///< Key is pressed.
  , up      ///< Key is released.
};

}}

#endif // SCENER_INPUT_KEYSTATE_HPP
