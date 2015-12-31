// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_OPENGL_TEXTURETARGET_HPP
#define SCENER_GRAPHICS_OPENGL_TEXTURETARGET_HPP

#include <cstdint>

#include "SceneR/Graphics/OpenGL/Platform.hpp"

namespace SceneR { namespace Graphics { namespace OpenGL {

/**
 * Declares OpenGL texture targets
 */
enum class TextureTarget : std::uint32_t
{
    /**
     * One-dimensional texture image.
     */
    texture_1d = GL_TEXTURE_1D,
    /**
     * Two-dimensional texture image.
     */
    texture_2d = GL_TEXTURE_2D,
    /**
     * Three-dimensional texture image
     */
    texture_3d = GL_TEXTURE_3D,
    /**
     * Array of one-dimensional texture images.
     */
    texture_1d_Array = GL_TEXTURE_1D_ARRAY,
    /**
     * Array of two-dimensional texture images.
     */
    texture_2d_array = GL_TEXTURE_2D_ARRAY,
    /**
     * Two-dimensional texture image without mipmapping.
     * Texture coordinates used for these textures are not normalized.
     */
    texture_rect = GL_TEXTURE_RECTANGLE,
    /**
     * A set of, exactly, 6 distinct sets of 2D images, all of the same size.
     * They act as 6 faces of a cube.
     */
    texture_cube_map = GL_TEXTURE_CUBE_MAP,
    /**
     * Array of multiple sets of cube maps, all within one texture.
     * The array length * 6 (number of cube faces) is part of the texture size.
     */
    texture_cube_map_array = GL_TEXTURE_CUBE_MAP_ARRAY,
    /**
     * One-dimensional texture image without mipmapping.
     * The storage for this data comes from a Buffer Object.
     */
    texture_buffer = GL_TEXTURE_BUFFER,
    /**
     * Two-dimensional texture image without mipmapping.
     * Each pixel in these images contains multiple samples instead of just one value.
     */
    texture_2d_multi_sample = GL_TEXTURE_2D_MULTISAMPLE,
    /**
     * Combines 2D array and 2D multisample types. No mipmapping.
     */
    texture_2d_multi_sample_array = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
};

}}}

#endif // SCENER_GRAPHICS_OPENGL_TEXTURETARGET_HPP
