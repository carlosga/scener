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

#ifndef EFFECTPARAMETERTYPE_HPP
#define EFFECTPARAMETERTYPE_HPP

#include <Framework/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines types that can be used for effect parameters or shader constants.
         */
        enum class EffectParameterType : UInt32
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
