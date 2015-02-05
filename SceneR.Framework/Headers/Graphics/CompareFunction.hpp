// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef COMPAREFUNCTION_HPP
#define COMPAREFUNCTION_HPP

#include <System/Graphics/Platform.hpp>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Specifies the functions used to compare each incoming pixel depth value
         * with the depth value present in the depth buffer.
         */
        enum class CompareFunction : System::UInt32
        {
            /**
             * Always passes.
             */
            Always = GL_ALWAYS,
            /**
             * Passes if the incoming depth value is equal to the stored depth value.
             */
            Equal = GL_EQUAL,
            /**
             * Passes if the incoming depth value is greater than the stored depth value.
             */
            Greater = GL_GREATER,
            /**
             * Passes if the incoming depth value is greater than or equal to the stored depth value.
             */
            GreaterEqual = GL_GEQUAL,
            /**
             * Passes if the incoming depth value is less than the stored depth value.
             */
            Less = GL_LESS,
            /**
             * Passes if the incoming depth value is less than or equal to the stored depth value.
             */
            LessEqual = GL_LEQUAL,
            /**
             * Never passes.
             */
            Never = GL_NEVER,
            /**
             * Passes if the incoming depth value is not equal to the stored depth value.
             */
            NotEqual = GL_NOTEQUAL
        };
    }
}

#endif  /* COMPAREFUNCTION_HPP */
