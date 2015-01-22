// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for full license information.

#ifndef EFFECTPARAMETERCLASS_HPP
#define EFFECTPARAMETERCLASS_HPP

#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines classes that can be used for effect parameters or shader constants.
         */
        enum class EffectParameterClass : System::UInt32
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

#endif  /* EFFECTPARAMETERCLASS_HPP */
