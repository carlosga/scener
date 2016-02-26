// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_DDS_DDS_HPP
#define SCENER_CONTENT_DDS_DDS_HPP

#include "SceneR/Content/DDS/DdsCaps.hpp"
#include "SceneR/Content/DDS/DdsCaps2.hpp"
#include "SceneR/Content/DDS/DdsHeaderFlags.hpp"
#include "SceneR/Content/DDS/DdsPixelFormat.hpp"

namespace scener { namespace content { namespace dds {

/// Describes a DDS file header.
///
/// Programming Guide for DDS (DirectDraw Surface):
///     http://msdn.microsoft.com/en-us/library/bb943991.aspx
/// Reference for DDS:
///     http://msdn.microsoft.com/en-us/library/bb943992.aspx
/// Compressed Texture Resources (Direct3D 9):
///     http://msdn.microsoft.com/en-us/library/bb204843.aspx
/// Block Compression (Direct3D 10):
///     http://msdn.microsoft.com/en-us/library/bb694531.aspx
///
/// The OpenGL extensions also document the block compression formats:
/// DXT1, DXT3 and DXT5 (equivalent to BC1, BC2 and BC3):
///     http://www.opengl.org/registry/specs/EXT/texture_compression_s3tc.txt
/// LATC and RGTC (equivalent to BC4 and BC5):
///     http://www.opengl.org/registry/specs/EXT/texture_compression_latc.txt
///     http://www.opengl.org/registry/specs/EXT/texture_compression_rgtc.txt
/// BPTC (equivalent to BC6 and BC7):
///     http://www.opengl.org/registry/specs/ARB/texture_compression_bptc.txt
struct DDS_HEADER
{
    std::uint32_t    dwMagic;             ///< (magic number) containing the four character code value 'DDS ' (0x20534444).
    std::uint32_t    dwSize;              ///< Size of structure. This member must be set to 124.
    DDS_HEADER_FLAGS dwFlags;             ///< Flags to indicate which members contain valid data.
    std::uint32_t    dwHeight;            ///< Surface height (in pixels).
    std::uint32_t    dwWidth;             ///< Surface width (in pixels).
    std::uint32_t    dwPitchOrLinearSize; ///< The pitch or number of bytes per scan line in an uncompressed texture;
                                          ///< The total number of bytes in the top level texture for a compressed texture.
    std::uint32_t    dwDepth;             ///< Depth of a volume texture (in pixels), otherwise unused.
    std::uint32_t    dwMipMapCount;       ///< Number of mipmap levels, otherwise unused.
    std::uint32_t    dwReserved1[11];     ///< Unused.
    DDS_PIXELFORMAT  ddspf;               ///< The pixel format (see DDS_PIXELFORMAT).
    DDS_CAPS         dwCaps;              ///< Specifies the complexity of the surfaces stored.
    std::uint32_t    dwCaps2;             ///< Additional detail about the surfaces stored.
    std::uint32_t    dwCaps3;             ///< Unused.
    std::uint32_t    dwCaps4;             ///< Unused.
    std::uint32_t    dwReserved2;         ///< Unused.
};

}}}

#endif // SCENER_CONTENT_DDS_DDS_HPP
