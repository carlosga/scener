// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_FILL_MODE_HPP
#define SCENER_GRAPHICS_FILL_MODE_HPP

#include <cstdint>

namespace scener::graphics
{
    /// Describes options for filling the vertices and lines that define a primitive.
    enum class fill_mode : std::uint32_t
    {
        solid      = 1  ///< draw solid faces for each primitive.
      , wire_frame = 2  ///< draw lines connecting the vertices that define a primitive face.
    };
}

#endif // SCENER_GRAPHICS_FILL_MODE_HPP
