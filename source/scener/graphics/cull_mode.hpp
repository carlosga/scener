// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_CULLMODE_HPP
#define SCENER_GRAPHICS_CULLMODE_HPP

#include <cstdint>

namespace scener::graphics
{
    /// Defines winding orders that may be used for face culling.
    enum class cull_mode : std::uint32_t
    {
        none                        = 0     ///< Do not perform culling
      , cull_clockwise_face         = 1     ///< Cull back faces with clockwise vertices.
      , cull_counter_clockwise_face = 2     ///< Cull front faces with counterclockwise vertices.
    };
}

#endif // SCENER_GRAPHICS_CULLMODE_HPP
