// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_INDEX_TYPE_HPP
#define SCENER_GRAPHICS_INDEX_TYPE_HPP

#include <cstdint>

namespace scener::graphics
{
    /// Defines the type of an index of an index buffer.
    enum class index_type : std::uint32_t
    {
        uint16 = 0   ///< Sixteen bits (unsigned).
      , uint32 = 1   ///< Sixteen bits (unsigned).
    };
}

#endif // SCENER_GRAPHICS_INDEX_TYPE_HPP
