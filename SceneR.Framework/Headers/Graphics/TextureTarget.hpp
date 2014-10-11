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

#ifndef TEXTURETARGET_HPP
#define TEXTURETARGET_HPP

#include <System/Graphics/Platform.hpp>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Declares OpenGL texture targets
         */
        enum class TextureTarget : System::UInt32
        {
            /**
             * One-dimensional texture image.
             */
            Texture1D = GL_TEXTURE_1D,
            /**
             * Two-dimensional texture image.
             */
            Texture2D = GL_TEXTURE_2D,
            /**
             * Three-dimensional texture image
             */
            Texture3D = GL_TEXTURE_3D,
            /**
             * Array of one-dimensional texture images.
             */
            Texture1DArray = GL_TEXTURE_1D_ARRAY,
            /**
             * Array of two-dimensional texture images.
             */
            Texture2DArray = GL_TEXTURE_2D_ARRAY,
            /**
             * Two-dimensional texture image without mipmapping.
             * Texture coordinates used for these textures are not normalized.
             */
            TextureRect = GL_TEXTURE_RECTANGLE,
            /**
             * A set of, exactly, 6 distinct sets of 2D images, all of the same size.
             * They act as 6 faces of a cube.
             */
            TextureCubeMap = GL_TEXTURE_CUBE_MAP,
            /**
             * Array of multiple sets of cube maps, all within one texture.
             * The array length * 6 (number of cube faces) is part of the texture size.
             */
            TextureCubeMapArray = GL_TEXTURE_CUBE_MAP_ARRAY,
            /**
             * One-dimensional texture image without mipmapping.
             * The storage for this data comes from a Buffer Object.
             */
            TextureBuffer = GL_TEXTURE_BUFFER,
            /**
             * Two-dimensional texture image without mipmapping.
             * Each pixel in these images contains multiple samples instead of just one value.
             */
            Texture2DMultiSample = GL_TEXTURE_2D_MULTISAMPLE,
            /**
             * Combines 2D array and 2D multisample types. No mipmapping.
             */
            Texture2DMultiSampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
        };
    }
}

#endif /* TEXTURETARGET_HPP */
