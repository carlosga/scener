// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_DDS_FOURCC_HPP
#define SCENER_CONTENT_DDS_FOURCC_HPP

#include <cstdint>

namespace scener::content::dds 
{
    /// DirectDrawSurface resource formats.
    /// A FourCC of DX10 indicates the prescense of the DDS_HEADER_DXT10 extended header,
    /// and the dxgiFormat member of that structure indicates the true format.
    /// When using a four-character code, dwFlags must include DDPF_FOURCC.
    enum class fourcc : std::uint32_t
    {
        dxt1 = 0x31545844 ///< DXT1 (also known as Block Compression 1 or BC1).
    , dxt2 = 0x32545844 ///< DXT2 and DXT3 (collectively also known as Block Compression 2 or BC2).
    , dxt3 = 0x33545844 ///< DXT2 and DXT3 (collectively also known as Block Compression 2 or BC2).
    , dxt4 = 0x34545844 ///< DXT4 and DXT5 (collectively also known as Block Compression 3 or BC3).
    , dxt5 = 0x35545844 ///< DXT4 and DXT5 (collectively also known as Block Compression 3 or BC3).
    };
}

#endif // SCENER_CONTENT_DDS_FOURCC_HPP
