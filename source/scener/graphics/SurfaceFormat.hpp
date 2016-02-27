// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_SURFACEFORMAT_HPP
#define SCENER_GRAPHICS_SURFACEFORMAT_HPP

#include <cstdint>

#include "scener/graphics/opengl/Platform.hpp"

namespace scener { namespace graphics {

/// Defines various types of surface formats.
enum class surface_format : std::uint32_t
{
    color            = GL_RGBA8                         ///< (Unsigned format) 32-bit ARGB pixel format with alpha,
                                                        ///< using 8 bits per channel.
  , bgr565           = GL_RGB565                        ///< (Unsigned format) 16-bit BGR pixel format with 5 bits for blue,
                                                        ///< 6 bits for green, and 5 bits for red.
  , bgra5551         = GL_RGB5_A1                       ///< (Unsigned format) 16-bit BGRA pixel format where 5 bits are
                                                        ///< reserved for each color and 1 bit is reserved for alpha.
  , bgra4444         = GL_RGBA4                         ///< (Unsigned format) 16-bit BGRA pixel format with 4 bits for each
                                                        ///< channel.
  , dxt1             = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ///< DXT1 compression texture format.
  , dxt3             = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT ///< DXT3 compression texture format.
  , dxt5             = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT ///< DXT5 compression texture format.
  , normalized_byte2 = GL_RG8_SNORM                     ///< (Signed format) 16-bit bump-map format using 8 bits each for u and v data.
  , normalized_byte4 = GL_RGBA8_SNORM                   ///< (Signed format) 32-bit bump-map format using 8 bits for each channel.
  , rgba1010102      = GL_RGB10_A2                      ///< 32-bit RGBA pixel format using 10 bits for each color and 2 bits for alpha.
  , rg32             = GL_RG16                          ///< 32-bit pixel format using 16 bits each for red and green.
  , rgba64           = GL_RGBA16                        ///< 64-bit RGBA pixel format using 16 bits for each component.
};

}}

#endif // SCENER_GRAPHICS_SURFACEFORMAT_HPP
