// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_TEXTURE_DDS_HPP
#define SCENER_TEXTURE_DDS_HPP

#include <cstdint>
#include <vector>
#include <string>

#include "SceneR/Texture/DdsCaps.hpp"
#include "SceneR/Texture/DdsCaps2.hpp"
#include "SceneR/Texture/DdsHeaderFlags.hpp"
#include "SceneR/Texture/DdsPixelFormat.hpp"

namespace SceneR
{
    namespace DDS
    {
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

        union DDS_HEADER
        {
            struct
            {
                /// (magic number) containing the four character code value 'DDS ' (0x20534444).
                std::uint32_t dwMagic;
                /// Size of structure. This member must be set to 124.
                std::uint32_t dwSize;
                /// Flags to indicate which members contain valid data.
                DDS_HEADER_FLAGS dwFlags;
                /// Surface height (in pixels).
                std::uint32_t dwHeight;
                /// Surface width (in pixels).
                std::uint32_t dwWidth;
                /// The pitch or number of bytes per scan line in an uncompressed texture;
                /// the total number of bytes in the top level texture for a compressed texture.
                /// For information about how to compute the pitch,
                /// see the DDS File Layout section of the Programming Guide for DDS.
                std::uint32_t dwPitchOrLinearSize;
                /// Depth of a volume texture (in pixels), otherwise unused.
                std::uint32_t dwDepth;
                /// Number of mipmap levels, otherwise unused.
                std::uint32_t dwMipMapCount;
                /// Unused.
                std::uint32_t dwReserved1[11];
                /// The pixel format (see DDS_PIXELFORMAT).
                DDS_PIXELFORMAT ddspf;
                /// Specifies the complexity of the surfaces stored.
                DDS_CAPS dwCaps;
                /// Additional detail about the surfaces stored.
                std::uint32_t dwCaps2;
                /// Unused.
                std::uint32_t dwCaps3;
                /// Unused.
                std::uint32_t dwCaps4;
                /// Unused.
                std::uint32_t dwReserved2;
            };

            std::uint8_t data[128];
        };
    }
}

#endif // SCENER_TEXURE_DDS_HPP
