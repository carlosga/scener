//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#ifndef COMPAREFUNCTION_HPP
#define COMPAREFUNCTION_HPP

#include <Framework/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Specifies the functions used to compare each incoming pixel depth value
         * with the depth value present in the depth buffer.
         */
        enum class CompareFunction : GLenum
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
