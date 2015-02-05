// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef INDEXELEMENTSIZE_HPP
#define INDEXELEMENTSIZE_HPP

#include <System/Graphics/Platform.hpp>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines the element size for IndexBuffer instances
         */
        enum class IndexElementSize : System::UInt32
        {
            /**
             * Sixteen bits
             */
            SixteenBits = GL_UNSIGNED_SHORT,
            /**
             * Thirty-two bits.
             */
            ThirtyTwoBits = GL_UNSIGNED_INT
        };
    }
}

#endif  /* INDEXELEMENTSIZE_HPP */
