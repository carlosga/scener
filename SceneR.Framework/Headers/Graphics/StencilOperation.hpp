// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef STENCILOPERATION_HPP
#define STENCILOPERATION_HPP

#include <System/Graphics/Platform.hpp>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines stencil buffer operations.
         */
        enum class StencilOperation : uint32_t
        {
            /**
             * Decrements the stencil-buffer entry, wrapping to the maximum value if the new value is less than 0.
             */
            Decrement = GL_DECR,
            /**
             * Decrements the stencil-buffer entry, clamping to 0.
             */
            DecrementSaturation = GL_DECR_WRAP,
            /**
             * Increments the stencil-buffer entry, wrapping to 0 if the new value exceeds the maximum value.
             */
            Increment = GL_INCR,
            /**
             * Increments the stencil-buffer entry, clamping to the maximum value.
             */
            IncrementSaturation = GL_INCR_WRAP,
            /**
             * Inverts the bits in the stencil-buffer entry.
             */
            Invert = GL_INVERT,
            /**
             * Does not update the stencil-buffer entry. This is the default value.
             */
            Keep = GL_KEEP,
            /**
             * Replaces the stencil-buffer entry with a reference value.
             */
            Replace = GL_REPLACE,
            /**
             * Sets the stencil-buffer entry to 0.
             */
            Zero = GL_ZERO
        };
    }
}

#endif /* STENCILOPERATION_HPP */
