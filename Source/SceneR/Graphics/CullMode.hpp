// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_CULLMODE_HPP
#define GRAPHICS_CULLMODE_HPP

#include <cstdint>

#include "OpenGL/Platform.hpp"

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines winding orders that may be used for face culling.
         */
        enum class CullMode : std::uint32_t
        {
            /**
             * Cull back faces with clockwise vertices.
             */
            CullClockwiseFace = GL_CW,
            /**
             * Cull front faces with counterclockwise vertices.
             */
            CullCounterClockwiseFace = GL_CCW,
            /**
             * Do not perform culling
             */
            None = 0
        };
    }
}

#endif  // GRAPHICS_CULLMODE_HPP
