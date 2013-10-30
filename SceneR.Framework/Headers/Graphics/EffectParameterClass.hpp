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
        enum class EffectParameterClass : UInt32
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
