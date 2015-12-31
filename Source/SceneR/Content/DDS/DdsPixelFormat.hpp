// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_DDS_DDSPIXELFORMAT_HPP
#define SCENER_CONTENT_DDS_DDSPIXELFORMAT_HPP

#include <cstdint>

#include "SceneR/Content/DDS/DdsPixelFormatFlags.hpp"
#include "SceneR/Content/DDS/DdsFourCC.hpp"

namespace SceneR { namespace Content { namespace DDS {

struct DDS_PIXELFORMAT
{
    /// Structure size; set to 32 (bytes).
    std::uint32_t dwSize;
    /// Values which indicate what type of data is in the surface.
    DDS_PIXELFORMAT_FLAGS dwFlags;
    /// Four-character codes for specifying compressed or custom formats.
    /// Possible values include: DXT1, DXT2, DXT3, DXT4, or DXT5.
    /// A FourCC of DX10 indicates the prescense of the DDS_HEADER_DXT10 extended header,
    /// and the dxgiFormat member of that structure indicates the true format.
    /// When using a four-character code, dwFlags must include DDPF_FOURCC.
    DDS_FOURCC dwFourCC;
    /// Number of bits in an RGB (possibly including alpha) format.
    /// Valid when dwFlags includes DDPF_RGB, DDPF_LUMINANCE, or DDPF_YUV.
    std::uint32_t dwRGBBitCount;
    /// Red (or lumiannce or Y) mask for reading color data.
    /// For instance, given the A8R8G8B8 format, the red mask would be 0x00ff0000.
    std::uint32_t dwRBitMask;
    /// Green (or U) mask for reading color data. For instance, given the A8R8G8B8 format, the green mask would be 0x0000ff00.
    std::uint32_t dwGBitMask;
    /// Blue (or V) mask for reading color data. For instance, given the A8R8G8B8 format, the blue mask would be 0x000000ff.
    std::uint32_t dwBBitMask;
    /// Alpha mask for reading alpha data. dwFlags must include DDPF_ALPHAPIXELS or DDPF_ALPHA.
    /// For instance, given the A8R8G8B8 format, the alpha mask would be 0xff000000.
    std::uint32_t dwABitMask;
};

}}}

#endif  // SCENER_CONTENT_DDS_DDSPIXELFORMAT_HPP
