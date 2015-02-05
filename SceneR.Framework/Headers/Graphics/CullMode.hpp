// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CULLMODE_HPP
#define CULLMODE_HPP

#include <System/Graphics/Platform.hpp>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines winding orders that may be used for face culling.
         */
        enum class CullMode : System::UInt32
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

#endif  /* CULLMODE_HPP */
