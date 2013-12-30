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
            /**
             * Single-component, 32-bit floating-point, expanded to (float, 0, 0, 1).
             */
            Single = 0,
            /**
             * Two-component, 32-bit floating-point, expanded to (float, float, 0, 1).
             */
            Vector2 = 1,
            /**
             * Three-component, 32-bit floating point, expanded to (float, float, float, 1).
             */
            Vector3 = 2,
            /**
             * Four-component, 32-bit floating point, expanded to (float, float, float, float).
             */
            Vector4 = 3,
            /**
             * Four-component, packed, unsigned byte, mapped to 0 to 1 range.
             * Input is in Int32 format (ARGB) expanded to (R, G, B, A).
             */
            Color = 4,
            /**
             * Four-component, unsigned byte.
             */
            Byte4 = 5,
            /**
             * Two-component, signed short expanded to (value, value, 0, 1).
             */
            Short2 = 6,
            /**
             * Four-component, signed short expanded to (value, value, value, value).
             */
            Short4 = 7,
            /**
             * Normalized, two-component, signed short, expanded to (first short/32767.0, second short/32767.0, 0, 1).
             */
            NormalizedShort2 = 8,
            /**
             * Normalized, four-component, signed short, expanded to (first short/32767.0, second short/32767.0,
             * third short/32767.0, fourth short/32767.0).
             */
            NormalizedShort4 = 9,
            /**
             * Two-component, 16-bit floating point expanded to (value, value, value, value).
             */
            HalfVector2 = 10,
            /**
             * Four-component, 16-bit floating-point expanded to (value, value, value, value).
             */
            HalfVector4 = 11
        };
    }
}

#endif  /* VERTEXELEMENTFORMAT_HPP */
