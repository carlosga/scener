// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_DDS_DDSHEADERFLAGS_HPP
#define SCENER_CONTENT_DDS_DDSHEADERFLAGS_HPP

#include <cstdint>

namespace SceneR { namespace Content { namespace DDS {

/// DDS file header flags, indicates which members contain valid data.
enum class DDS_HEADER_FLAGS : std::uint32_t
{
    DDSD_CAPS        = 0x1      ///< Required in every .dds file.
  , DDSD_HEIGHT      = 0x2      ///< Required in every .dds file
  , DDSD_WIDTH       = 0x4      ///< Required in every .dds file.
  , DDSD_PITCH       = 0x8      ///< Required when pitch is provided for an uncompressed texture.
  , DDSD_PIXELFORMAT = 0x1000   ///< Required in every .dds file.
  , DDSD_MIPMAPCOUNT = 0x20000  ///< Required in a mipmapped texture.
  , DDSD_LINEARSIZE  = 0x80000  ///< Required when pitch is provided for a compressed texture.
  , DDSD_DEPTH       = 0x800000 ///< Required in a depth texture.
};

/// Bitwise AND operator for DDS_HEADER_FLAGS.
inline constexpr DDS_HEADER_FLAGS operator&(const DDS_HEADER_FLAGS& left, const DDS_HEADER_FLAGS& right)
{
    return static_cast<DDS_HEADER_FLAGS>(static_cast<std::uint32_t>(left) & static_cast<std::uint32_t>(right));
}

/// Bitwise OR operator for DDS_HEADER_FLAGS.
inline constexpr DDS_HEADER_FLAGS operator|(const DDS_HEADER_FLAGS& left, const DDS_HEADER_FLAGS& right)
{
    return static_cast<DDS_HEADER_FLAGS>(static_cast<std::uint32_t>(left) | static_cast<std::uint32_t>(right));
}

/// Unary complement operator for DDS_DDS_HEADER_FLAGS.
inline constexpr DDS_HEADER_FLAGS operator~(const DDS_HEADER_FLAGS& value)
{
    return static_cast<DDS_HEADER_FLAGS>(~static_cast<std::uint32_t>(value));
}

/// Equality operator for comparing a DDS_HEADER_FLAGS value against an unsigned int32.
inline constexpr bool operator==(const DDS_HEADER_FLAGS& left, const std::uint32_t& right)
{
    return (static_cast<std::uint32_t>(left) == right);
}

/// Inequality operator for comparing a DDS_HEADER_FLAGS value against an unsigned int32.
inline constexpr bool operator!=(const DDS_HEADER_FLAGS& left, const std::uint32_t& right)
{
    return (static_cast<std::uint32_t>(left) != right);
}

/// Equality operator for comparing DDS_HEADER_FLAGS values.
inline DDS_HEADER_FLAGS& operator&=(DDS_HEADER_FLAGS& left, const DDS_HEADER_FLAGS& right)
{
    left = left & right;

    return left;
}

/// Equality operator for comparing DDS_HEADER_FLAGS values.
inline DDS_HEADER_FLAGS& operator|=(DDS_HEADER_FLAGS& left, const DDS_HEADER_FLAGS& right)
{
    left = left | right;

    return left;
}

}}}

#endif // SCENER_CONTENT_DDS_DDSHEADERFLAGS_HPP
