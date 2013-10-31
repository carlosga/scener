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

#ifndef CULLMODE_HPP
#define CULLMODE_HPP

#include <GL/glew.h>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines winding orders that may be used to identify back faces for culling.
         */
        enum class CullMode : UInt32
        {
            /**
             * Cull back faces with clockwise vertices.
             */
            CullClockwiseFace = GL_CW,
            /**
             * Cull back faces with counterclockwise vertices.
             */
            CullCounterClockwiseFace = GL_CCW,
            /**
             * Do not cull back faces.
             */
            None
        };
    }
}

#endif  /* CULLMODE_HPP */
