// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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
        enum class TextureTarget : uint32_t
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
