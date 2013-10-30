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

#ifndef SURFACEFORMAT_HPP
#define SURFACEFORMAT_HPP

#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        enum class SurfaceFormat : UInt32
        {
            /**
             * (Unsigned format) 32-bit ARGB pixel format with alpha, using 8 bits per channel.
             */
            Color = 0,
            /**
             * (Unsigned format) 16-bit BGR pixel format with 5 bits for blue, 6 bits for green,
             * and 5 bits for red.
             */
            Bgr565 = 1,
            /**
             * (Unsigned format) 16-bit BGRA pixel format where 5 bits are reserved for each color
             * and 1 bit is reserved for alpha.
             */
            Bgra5551 = 2,
            /**
             * (Unsigned format) 16-bit BGRA pixel format with 4 bits for each channel.
             */
            Bgra4444 = 3,
            /**
             * (Signed format) 16-bit bump-map format using 8 bits each for u and v data.
             */
            NormalizedByte2 = 7,
            /**
             * (Signed format) 32-bit bump-map format using 8 bits for each channel.
             */
            NormalizedByte4 = 8
        };
    }
}

#endif /* SURFACEFORMAT_HPP */
