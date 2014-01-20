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

#ifndef VERTEXELEMENTUSAGE_HPP
#define VERTEXELEMENTUSAGE_HPP

#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines usage for vertex elements.
         */
        enum class VertexElementUsage : System::UInt32
        {
            /**
             * Position data.
             */
            Position = 0,
            /**
             * Vertex data contains diffuse or specular color.
             */
            Color = 1,
            /**
             * Texture coordinate data.
             */
            TextureCoordinate = 2,
            /**
             * Vertex normal data.
             */
            Normal = 3,
            /**
             * Vertex binormal data.
             */
            Binormal = 4,
            /**
             * Vertex tangent data.
             */
            Tangent = 5,
            /**
             * Blending indices data.
             */
            BlendIndices = 6,
            /**
             * Blending weight data.
             */
            BlendWeight = 7,
            /**
             * Vertex data contains depth data.
             */
            Depth = 8,
            /**
             * Vertex data contains fog data.
             */
            Fog = 9,
            /**
             * Point size data.
             */
            PointSize = 10,
            /**
             * Vertex data contains sampler data.
             */
            Sample = 11,
            /**
             * Single, positive floating-point value.
             */
            TessellateFactor = 12
        };
    }
}

#endif  /* VERTEXELEMENTUSAGE_HPP */
