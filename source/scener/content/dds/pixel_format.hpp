// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_DDS_PIXEL_FORMAT_HPP
#define SCENER_CONTENT_DDS_PIXEL_FORMAT_HPP

#include <cstdint>

#include "scener/content/dds/pixel_format_flags.hpp"
#include "scener/content/dds/fourcc.hpp"

namespace scener::content::dds
{
    /// Surface pixel format.
    struct pixel_format
    {
        std::uint32_t      size;            ///< Structure size; set to 32 (bytes).
        pixel_format_flags flags;           ///< Values which indicate what type of data is in the surface.
        fourcc             fourcc;          ///< Possible values include: DXT1, DXT2, DXT3, DXT4, or DXT5.
        std::uint32_t      rgb_bit_count;   ///< Number of bits in an RGB (possibly including alpha) format.
        std::uint32_t      red_mask;        ///< Red (or lumiannce or Y) mask for reading color data.
        std::uint32_t      green_mask;      ///< Green (or U) mask for reading color data.
        std::uint32_t      blue_mask;       ///< Blue (or V) mask for reading color data.
        std::uint32_t      alpha_mask;      ///< Alpha mask for reading alpha data.
    };
}

#endif  // SCENER_CONTENT_DDS_PIXEL_FORMAT_HPP
