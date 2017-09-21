// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_STENCIL_OPERATION_HPP
#define SCENER_GRAPHICS_STENCIL_OPERATION_HPP

#include <cstdint>

namespace scener::graphics
{
    /// Defines stencil buffer operations.
    enum class stencil_operation : std::uint32_t
    {
        decrement            = 0x1E03   ///< Decrements the stencil-buffer entry, wrapping to the maximum value
                                        ///< if the new value is less than 0.
      , decrement_saturation = 0x8508   ///< Decrements the stencil-buffer entry, clamping to 0.
      , increment            = 0x1E02   ///< Increments the stencil-buffer entry, wrapping to 0
                                        ///< if the new value exceeds the maximum value.
      , increment_saturation = 0x8507   ///< Increments the stencil-buffer entry, clamping to the maximum value.
      , invert               = 0x150A   ///< Inverts the bits in the stencil-buffer entry.
      , keep                 = 0x1E00   ///< Does not update the stencil-buffer entry. This is the default value.
      , replace              = 0x1E01   ///< Replaces the stencil-buffer entry with a reference value.
      , zero                 = 0        ///< Sets the stencil-buffer entry to 0.
    };
}

#endif // SCENER_GRAPHICS_STENCIL_OPERATION_HPP
