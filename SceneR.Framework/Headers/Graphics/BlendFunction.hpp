// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef BLENDFUNCTION_HPP
#define BLENDFUNCTION_HPP

#include <System/Graphics/Platform.hpp>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines how to combine a source color with the destination color already on the render target for color blending.
         */
        enum class BlendFunction : System::UInt32
        {
            /**
             * The result is the destination added to the source.
             * Result = (Source Color * Source Blend) + (Destination Color * Destination Blend)
             */
            Add = GL_FUNC_ADD,
            /**
             * The result is the maximum of the source and destination.
             * Result = max( (Source Color * Source Blend), (Destination Color * Destination Blend) )
             */
            Max = GL_MAX,
            /**
             * The result is the minimum of the source and destination.
             * Result = min( (Source Color * Source Blend), (Destination Color * Destination Blend) )
             */
            Min = GL_MIN,
            /**
             * The result is the source subtracted from the destination.
             * Result = (Destination Color * Destination Blend) − (Source Color * Source Blend)
             */
            ReverseSubtract = GL_FUNC_REVERSE_SUBTRACT,
            /**
             * The result is the destination subtracted from the source.
             * Result = (Source Color * Source Blend) − (Destination Color * Destination Blend)
             */
            Subtract = GL_FUNC_SUBTRACT
        };
    }
}

#endif /* BLENDFUNCTION_HPP */
