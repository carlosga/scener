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

#include <Framework/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines vertex element formats.
         */
        enum class VertexElementFormat : UInt32
        {
            Single           = 1,
            Vector2          = 2,
            Vector3          = 3,
            Vector4          = 4,
            HalfVector2      = 5,
            HalfVector4      = 6,
            Color            = 7,
            NormalizedShort2 = 8,
            NormalizedShort4 = 9,
            Short2           = 10,
            Short4           = 11,
            Byte4            = 12
        };
    }
}

#endif  /* VERTEXELEMENTFORMAT_HPP */
