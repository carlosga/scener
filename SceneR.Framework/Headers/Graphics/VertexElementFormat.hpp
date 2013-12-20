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

#ifndef VERTEXELEMENTFORMAT_HPP
#define VERTEXELEMENTFORMAT_HPP

#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines vertex element formats.
         */
        enum class VertexElementFormat : System::UInt32
        {
            Single           = 0,
            Vector2          = 1,
            Vector3          = 2,
            Vector4          = 3,
            Color            = 4,
            Byte4            = 5,
            Short2           = 6,
            Short4           = 7,
            NormalizedShort2 = 8,
            NormalizedShort4 = 9,
            HalfVector2      = 10,
            HalfVector4      = 11
        };
    }
}

#endif  /* VERTEXELEMENTFORMAT_HPP */
