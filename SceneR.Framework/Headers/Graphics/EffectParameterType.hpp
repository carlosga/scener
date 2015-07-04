// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef EFFECTPARAMETERTYPE_HPP
#define EFFECTPARAMETERTYPE_HPP

#include <stdint.h>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines types that can be used for effect parameters or shader constants.
         */
        enum class EffectParameterType : uint32_t
        {
            /**
             * Parameter is a Boolean. Any nonzero value passed in will be mapped to 1 (TRUE)
             * before being written into the constant table; otherwise, the value will be set to 0 in the constant
             * table.
             */
            Bool = 1,
            /**
             * Parameter is an integer. Any floating-point values passed in will be rounded off
             * (to zero decimal places) before being written into the constant table.
             */
            Int32 = 2,
            /**
             * Parameter is a floating-point number.
             */
            Single = 3,
            /**
             * Parameter is a string.
             */
            String = 4,
            /**
             * Parameter is a texture.
             */
            Texture = 5,
            /**
             * Parameter is a 1D texture.
             */
            Texture1D = 6,
            /**
             * Parameter is a 2D texture.
             */
            Texture2D = 7,
            /**
             * Parameter is a 3D texture.
             */
            Texture3D = 8,
            /**
             * Parameter is a cube texture.
             */
            TextureCube = 9,
            /**
             * Parameter is a void pointer.
             */
            Void = 10
        };
    }
}

#endif  /* EFFECTPARAMETERTYPE_HPP */
