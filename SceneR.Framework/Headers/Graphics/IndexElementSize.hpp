// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef INDEXELEMENTSIZE_HPP
#define INDEXELEMENTSIZE_HPP

#include <cstdint>

#include <System/Graphics/Platform.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines the element size for IndexBuffer instances
         */
        enum class IndexElementSize : std::uint32_t
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
