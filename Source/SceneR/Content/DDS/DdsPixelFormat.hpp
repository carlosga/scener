// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_DDS_DDSPIXELFORMAT_HPP
#define SCENER_CONTENT_DDS_DDSPIXELFORMAT_HPP

#include <cstdint>

#include "SceneR/Content/DDS/DdsPixelFormatFlags.hpp"
#include "SceneR/Content/DDS/DdsFourCC.hpp"

namespace SceneR { namespace Content { namespace DDS {

/// Surface pixel format.
struct DDS_PIXELFORMAT
{
    std::uint32_t         dwSize;        ///< Structure size; set to 32 (bytes).
    DDS_PIXELFORMAT_FLAGS dwFlags;       ///< Values which indicate what type of data is in the surface.
    DDS_FOURCC            dwFourCC;      ///< Possible values include: DXT1, DXT2, DXT3, DXT4, or DXT5.
    std::uint32_t         dwRGBBitCount; ///< Number of bits in an RGB (possibly including alpha) format.
    std::uint32_t         dwRBitMask;    ///< Red (or lumiannce or Y) mask for reading color data.
    std::uint32_t         dwGBitMask;    ///< Green (or U) mask for reading color data.
    std::uint32_t         dwBBitMask;    ///< Blue (or V) mask for reading color data.
    std::uint32_t         dwABitMask;    ///< Alpha mask for reading alpha data.
};

}}}

#endif  // SCENER_CONTENT_DDS_DDSPIXELFORMAT_HPP
