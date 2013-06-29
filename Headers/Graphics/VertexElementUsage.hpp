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

#include "Core/Core.hpp"

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines usage for vertex elements.
         */
        enum class VertexElementUsage : UInt32
        {
            /**
             * Vertex binormal data.
             */
            Binormal = 0,
            /**
             * Blending indices data. (BlendIndices with UsageIndex = 0) specifies matrix indices for fixed-function vertex processing using indexed paletted skinning.
             */
            BlendIndices = 1,
            /**
             * Blending weight data. (BlendWeight with UsageIndex = 0) specifies the blend weights in fixed-function vertex processing.
             */
            BlendWeight = 2,
            /**
             * Vertex data contains diffuse or specular color. (Color with UsageIndex = 0) specifies the diffuse color in the fixed-function vertex shader and in pixel shaders prior to ps_3_0. (Color with UsageIndex = 1) specifies the specular color in the fixed-function vertex shader and in pixel shaders prior to ps_3_0.
             */
            Color = 3,
            /**
             * Vertex data contains depth data.
             */
            Depth = 4,
            /**
             * Vertex normal data. (Normal with UsageIndex = 0) specifies vertex normals for fixed-function vertex processing and the N-patch tessellator.
             * (Normal with UsageIndex = 1) specifies vertex normals for fixed-function vertex processing for skinning.
             */
            Normal = 5,
            /**
             * Point size data. (PointSize with UsageIndex = 0) specifies the point-size attribute used by
             * the setup engine of the rasterizer to expand a point into a quad for the point-sprite functionality.
             */
            PointSize = 6,
            /**
             * Position data. (Position with UsageIndex = 0 ) specifies the nontransformed position in fixed-function
             * vertex processing and the N-patch tessellator. (Position with UsageIndex = 1) specifies the nontransformed
             * position in the fixed-function vertex shader for skinning.
             */
            Position = 7,
            /**
             * Vertex data contains sampler data. (Sample with UsageIndex = 0) specifies the displacement value to look up.
             */
            Sample = 8,
            /**
             * Vertex tangent data.
             */
            Tangent = 9,
            /**
             * Single, positive floating-point value. (TessellateFactor with UsageIndex = 0) specifies a
             * tessellation factor used in the tessellation unit to control the rate of tessellation.
             */
            TessellateFactor = 10,
            /**
             * Texture coordinate data. (TextureCoordinate, n) specifies texture coordinates in fixed-function vertex processing and in pixel shaders prior to ps_3_0. These coordinates can be used to pass user-defined data.
             */
            TextureCoordinate = 11
        };
    }
}

#endif  /* VERTEXELEMENTUSAGE_HPP */
