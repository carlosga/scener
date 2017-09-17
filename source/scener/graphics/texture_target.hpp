// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_TEXTURE_TYPE_HPP
#define SCENER_GRAPHICS_TEXTURE_TYPE_HPP

#include <cstdint>

namespace scener::graphics
{
    /// Declares texture targets.
    enum class texture_target : std::uint32_t
    {
        texture_1d                    = 1   ///< One-dimensional texture image.
      , texture_2d                    = 2   ///< Two-dimensional texture image.
      , texture_3d                    = 3   ///< Three-dimensional texture image
      , texture_1d_array              = 4   ///< Array of one-dimensional texture images.
      , texture_2d_array              = 5   ///< Array of two-dimensional texture images.
      , texture_rect                  = 6   ///< Two-dimensional texture image without mipmapping.
                                            ///< Texture coordinates used for these textures are not normalized.
      , texture_cube_map              = 7   ///< A set of, exactly, 6 distinct sets of 2D images, all of the same size.
                                            ///< They act as 6 faces of a cube.
      , texture_cube_map_array        = 8   ///< Array of multiple sets of cube maps, all within one texture.
                                            ///< The array length * 6 (number of cube faces) is part of the texture size.
      , texture_buffer                = 9   ///< One-dimensional texture image without mipmapping.
                                            ///< The storage for this data comes from a Buffer Object.
      , texture_2d_multi_sample       = 10  ///< Two-dimensional texture image without mipmapping.
                                            ///< Each pixel in these images contains multiple
                                            ///< samples instead of just one value.
      , texture_2d_multi_sample_array = 11  ///< Combines 2D array and 2D multisample types. No mipmapping.
    };
}

#endif // SCENER_GRAPHICS_TEXTURE_TYPE_HPP
