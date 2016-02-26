// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_STENCILOPERATION_HPP
#define SCENER_GRAPHICS_STENCILOPERATION_HPP

#include <cstdint>

#include "scener/graphics/opengl/Platform.hpp"

namespace scener { namespace graphics {

/// Defines stencil buffer operations.
enum class stencil_operation : std::uint32_t
{
    decrement            = GL_DECR      ///< Decrements the stencil-buffer entry, wrapping to the maximum value
                                        ///< if the new value is less than 0.
  , decrement_saturation = GL_DECR_WRAP ///< Decrements the stencil-buffer entry, clamping to 0.
  , increment            = GL_INCR      ///< Increments the stencil-buffer entry, wrapping to 0
                                        ///< if the new value exceeds the maximum value.
  , increment_saturation = GL_INCR_WRAP ///< Increments the stencil-buffer entry, clamping to the maximum value.
  , invert               = GL_INVERT    ///< Inverts the bits in the stencil-buffer entry.
  , keep                 = GL_KEEP      ///< Does not update the stencil-buffer entry. This is the default value.
  , replace              = GL_REPLACE   ///< Replaces the stencil-buffer entry with a reference value.
  , zero                 = GL_ZERO      ///< Sets the stencil-buffer entry to 0.
};

}}

#endif // SCENER_GRAPHICS_STENCILOPERATION_HPP
