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
        keep                 = 0    ///< Does not update the stencil-buffer entry. This is the default value.
      , zero                 = 1    ///< Sets the stencil-buffer entry to 0.
      , replace              = 2    ///< Replaces the stencil-buffer entry with a reference value.
      , increment_saturation = 3    ///< Increments the stencil-buffer entry, clamping to the maximum value.
      , decrement_saturation = 4    ///< Decrements the stencil-buffer entry, clamping to 0.
      , invert               = 5    ///< Inverts the bits in the stencil-buffer entry.
      , increment            = 6    ///< Increments the stencil-buffer entry, wrapping to 0
                                    ///< if the new value exceeds the maximum value.
      , decrement            = 7    ///< Decrements the stencil-buffer entry, wrapping to the maximum value
                                    ///< if the new value is less than 0.
    };
}

#endif // SCENER_GRAPHICS_STENCIL_OPERATION_HPP
