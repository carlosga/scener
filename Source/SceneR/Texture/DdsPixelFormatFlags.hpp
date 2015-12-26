// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_TEXTURE_DDSPIXELFORMATFLAGS_HPP
#define SCENER_TEXTURE_DDSPIXELFORMATFLAGS_HPP

#include <cstdint>

namespace SceneR
{
    namespace DDS
    {
        enum class DDS_PIXELFORMAT_FLAGS : std::uint32_t
        {
            /// Texture contains alpha data; dwRGBAlphaBitMask contains valid data.
            DDPF_ALPHAPIXELS = 0x1
            /// Used in some older DDS files for alpha channel only uncompressed data (dwRGBBitCount contains the alpha
            /// channel bitcount; dwABitMask contains valid data)
          , DDPF_ALPHA       = 0x2
            /// Texture contains compressed RGB data; dwFourCC contains valid data.
          , DDPF_FOURCC      = 0x4
            /// Texture contains uncompressed RGB data; dwRGBBitCount and the RGB masks
            /// (dwRBitMask, dwGBitMask, dwBBitMask) contain valid data.
          , DDPF_RGB         = 0x40
            /// Used in some older DDS files for YUV uncompressed data (dwRGBBitCount contains the YUV bit count;
            /// dwRBitMask contains the Y mask, dwGBitMask contains the U mask, dwBBitMask contains the V mask)
          , DDPF_YUV         = 0x200
            /// Used in some older DDS files for single channel color uncompressed data (dwRGBBitCount contains the
            /// luminance channel bit count; dwRBitMask contains the channel mask).
            /// Can be combined with DDPF_ALPHAPIXELS for a two channel DDS file.
          , DDPF_LUMINANCE   = 0x20000
        };

        inline constexpr DDS_PIXELFORMAT_FLAGS operator&(const DDS_PIXELFORMAT_FLAGS& left, const DDS_PIXELFORMAT_FLAGS& right)
        {
            return static_cast<DDS_PIXELFORMAT_FLAGS>(static_cast<std::uint32_t>(left) & static_cast<std::uint32_t>(right));
        }

        inline constexpr DDS_PIXELFORMAT_FLAGS operator|(const DDS_PIXELFORMAT_FLAGS& left, const DDS_PIXELFORMAT_FLAGS& right)
        {
            return static_cast<DDS_PIXELFORMAT_FLAGS>(static_cast<std::uint32_t>(left) | static_cast<std::uint32_t>(right));
        }

        inline constexpr DDS_PIXELFORMAT_FLAGS operator~(const DDS_PIXELFORMAT_FLAGS& value)
        {
            return static_cast<DDS_PIXELFORMAT_FLAGS>(~static_cast<std::uint32_t>(value));
        }

        inline constexpr bool operator==(const DDS_PIXELFORMAT_FLAGS& left, const std::uint32_t& right)
        {
            return (static_cast<std::uint32_t>(left) == right);
        }

        inline constexpr bool operator!=(const DDS_PIXELFORMAT_FLAGS& left, const std::uint32_t& right)
        {
            return (static_cast<std::uint32_t>(left) != right);
        }

        inline DDS_PIXELFORMAT_FLAGS& operator&=(DDS_PIXELFORMAT_FLAGS& left, const DDS_PIXELFORMAT_FLAGS& right)
        {
            left = left & right;

            return left;
        }

        inline DDS_PIXELFORMAT_FLAGS& operator|=(DDS_PIXELFORMAT_FLAGS& left, const DDS_PIXELFORMAT_FLAGS& right)
        {
            left = left | right;

            return left;
        }
    }
}

#endif // SCENER_TEXTURE_DDSPIXELFORMATFLAGS_HPP
