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

#include <GL/glew.h>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        enum class SurfaceFormat : System::UInt32
        {
            /**
             * (Unsigned format) 32-bit ARGB pixel format with alpha, using 8 bits per channel.
             */
            Color = GL_RGBA8,
            /**
             * (Unsigned format) 16-bit BGR pixel format with 5 bits for blue, 6 bits for green,
             * and 5 bits for red.
             */
            Bgr565 = GL_RGB565,
            /**
             * (Unsigned format) 16-bit BGRA pixel format where 5 bits are reserved for each color
             * and 1 bit is reserved for alpha.
             */
            Bgra5551 = GL_RGB5_A1,
            /**
             * (Unsigned format) 16-bit BGRA pixel format with 4 bits for each channel.
             */
            Bgra4444 = GL_RGBA4,
            /**
             * DXT1 compression texture format. The runtime will not allow an application to create a
             * surface using a DXTn format unless the surface dimensions are multiples of 4.
             * This applies to offscreen-plain surfaces, render targets, 2D textures, cube textures, and volume textures.
             */
            Dxt1 = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,
            /**
             * DXT3 compression texture format. The runtime will not allow an application to create a surface using a DXTn
             * format unless the surface dimensions are multiples of 4. This applies to offscreen-plain surfaces,
             * render targets, 2D textures, cube textures, and volume textures.
             */
            Dxt3 = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
            /**
             * DXT5 compression texture format. The runtime will not allow an application to create a surface using a DXTn
             * format unless the surface dimensions are multiples of 4. This applies to offscreen-plain surfaces,
             * render targets, 2D textures, cube textures, and volume textures.
             */
            Dxt5 = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,
            /**
             * (Signed format) 16-bit bump-map format using 8 bits each for u and v data.
             */
            NormalizedByte2 = GL_RG8_SNORM,
            /**
             * (Signed format) 32-bit bump-map format using 8 bits for each channel.
             */
            NormalizedByte4 = GL_RGBA8_SNORM,
            /**
             * 32-bit RGBA pixel format using 10 bits for each color and 2 bits for alpha.
             */
            Rgba1010102 = GL_RGB10_A2,
            /**
             * 32-bit pixel format using 16 bits each for red and green.
             */
            Rg32 = GL_RG16,
            /**
             * 64-bit RGBA pixel format using 16 bits for each component.
             */
            Rgba64 = GL_RGBA16
        };
    }
}

#endif /* SURFACEFORMAT_HPP */
