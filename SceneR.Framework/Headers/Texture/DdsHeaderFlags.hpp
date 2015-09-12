// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TEXTURE_DDS_HEADER_FLAGS_HPP
#define TEXTURE_DDS_HEADER_FLAGS_HPP

#include <cstdint>

namespace SceneR
{
    namespace DDS
    {
        enum class DDS_HEADER_FLAGS : std::uint32_t
        {
            /// Required in every .dds file.
            DDSD_CAPS        = 0x1
            /// Required in every .dds file
          , DDSD_HEIGHT      = 0x2
            /// Required in every .dds file.
          , DDSD_WIDTH       = 0x4
            /// Required when pitch is provided for an uncompressed texture.
          , DDSD_PITCH       = 0x8
            /// Required in every .dds file.
          , DDSD_PIXELFORMAT = 0x1000
            /// Required in a mipmapped texture.
          , DDSD_MIPMAPCOUNT = 0x20000
            /// Required when pitch is provided for a compressed texture.
          , DDSD_LINEARSIZE	 = 0x80000
            /// Required in a depth texture.
          , DDSD_DEPTH       = 0x800000
        };

        inline constexpr DDS_HEADER_FLAGS operator&(const DDS_HEADER_FLAGS& left, const DDS_HEADER_FLAGS& right)
        {
            return static_cast<DDS_HEADER_FLAGS>(static_cast<std::uint32_t>(left) & static_cast<std::uint32_t>(right));
        }

        inline constexpr DDS_HEADER_FLAGS operator|(const DDS_HEADER_FLAGS& left, const DDS_HEADER_FLAGS& right)
        {
            return static_cast<DDS_HEADER_FLAGS>(static_cast<std::uint32_t>(left) | static_cast<std::uint32_t>(right));
        }

        inline constexpr DDS_HEADER_FLAGS operator~(const DDS_HEADER_FLAGS& value)
        {
            return static_cast<DDS_HEADER_FLAGS>(~static_cast<std::uint32_t>(value));
        }

        inline constexpr bool operator==(const DDS_HEADER_FLAGS& left, const std::uint32_t& right)
        {
            return (static_cast<std::uint32_t>(left) == right);
        }

        inline constexpr bool operator!=(const DDS_HEADER_FLAGS& left, const std::uint32_t& right)
        {
            return (static_cast<std::uint32_t>(left) != right);
        }

        inline DDS_HEADER_FLAGS& operator&=(DDS_HEADER_FLAGS& left, const DDS_HEADER_FLAGS& right)
        {
            left = left & right;

            return left;
        }

        inline DDS_HEADER_FLAGS& operator|=(DDS_HEADER_FLAGS& left, const DDS_HEADER_FLAGS& right)
        {
            left = left | right;

            return left;
        }
    }
}

#endif  // TEXTURE_DDS_HEADER_FLAGS_HPP
