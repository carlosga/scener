// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_SURFACE_FORMAT_HPP
#define SCENER_GRAPHICS_SURFACE_FORMAT_HPP

#include <cstdint>

namespace scener::graphics
{
    /// Defines various types of surface formats.
    enum class surface_format : std::uint32_t
    {
        color            = 0x8058   ///< (Unsigned format) 32-bit ARGB pixel format with alpha,
                                    ///< using 8 bits per channel.
      , bgr565           = 0x8D62   ///< (Unsigned format) 16-bit BGR pixel format with 5 bits for blue,
                                    ///< 6 bits for green, and 5 bits for red.
      , bgra5551         = 0x8057   ///< (Unsigned format) 16-bit BGRA pixel format where 5 bits are
                                    ///< reserved for each color and 1 bit is reserved for alpha.
      , bgra4444         = 0x8056   ///< (Unsigned format) 16-bit BGRA pixel format with 4 bits for each
                                    ///< channel.
      , dxt1             = 0x83F1   ///< DXT1 compression texture format.
      , dxt3             = 0x83F2   ///< DXT3 compression texture format.
      , dxt5             = 0x83F3   ///< DXT5 compression texture format.
      , normalized_byte2 = 0x8F95   ///< (Signed format) 16-bit bump-map format using 8 bits each for u and v data.
      , normalized_byte4 = 0x8F97   ///< (Signed format) 32-bit bump-map format using 8 bits for each channel.
      , rgba1010102      = 0x8059   ///< 32-bit RGBA pixel format using 10 bits for each color and 2 bits for alpha.
      , rg32             = 0x822C   ///< 32-bit pixel format using 16 bits each for red and green.
      , rgba64           = 0x805B   ///< 64-bit RGBA pixel format using 16 bits for each component.
    };
}

#endif // SCENER_GRAPHICS_SURFACE_FORMAT_HPP
