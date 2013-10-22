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

#ifndef INDEXELEMENTSIZE_HPP
#define INDEXELEMENTSIZE_HPP

#include "Core/Core.hpp"

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines the element size for IndexBuffer instances
         */
        enum class IndexElementSize : GLenum
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