// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_STENCILOPERATION_HPP
#define SCENER_GRAPHICS_STENCILOPERATION_HPP

#include <cstdint>

#include "SceneR/Graphics/OpenGL/Platform.hpp"

namespace SceneR { namespace Graphics {

/**
 * Defines stencil buffer operations.
 */
enum class StencilOperation : std::uint32_t
{
    /**
     * Decrements the stencil-buffer entry, wrapping to the maximum value if the new value is less than 0.
     */
    decrement = GL_DECR,
    /**
     * Decrements the stencil-buffer entry, clamping to 0.
     */
    decrement_saturation = GL_DECR_WRAP,
    /**
     * Increments the stencil-buffer entry, wrapping to 0 if the new value exceeds the maximum value.
     */
    increment = GL_INCR,
    /**
     * Increments the stencil-buffer entry, clamping to the maximum value.
     */
    increment_saturation = GL_INCR_WRAP,
    /**
     * Inverts the bits in the stencil-buffer entry.
     */
    invert = GL_INVERT,
    /**
     * Does not update the stencil-buffer entry. This is the default value.
     */
    keep = GL_KEEP,
    /**
     * Replaces the stencil-buffer entry with a reference value.
     */
    replace = GL_REPLACE,
    /**
     * Sets the stencil-buffer entry to 0.
     */
    zero = GL_ZERO
};

}}

#endif // SCENER_GRAPHICS_STENCILOPERATION_HPP
