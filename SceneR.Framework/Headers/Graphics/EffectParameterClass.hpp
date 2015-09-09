// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_EFFECTPARAMETERCLASS_HPP
#define GRAPHICS_EFFECTPARAMETERCLASS_HPP

#include <cstdint>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines classes that can be used for effect parameters or shader constants.
         */
        enum class EffectParameterClass : std::uint32_t
        {
            /**
             * Constant is a matrix.
             */
            Matrix = 1,
            /**
             * Constant is either a texture, a shader, or a string.
             */
            Object = 2,
            /**
             * Constant is a scalar.
             */
            Scalar = 3,
            /**
             * Constant is a structure.
             */
            Struct = 4,
            /**
             * Constant is a vector.
             */
            Vector = 5
        };
    }
}

#endif  // GRAPHICS_EFFECTPARAMETERCLASS_HPP
