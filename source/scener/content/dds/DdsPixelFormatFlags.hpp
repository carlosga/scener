// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_DDS_DDSPIXELFORMATFLAGS_HPP
#define SCENER_CONTENT_DDS_DDSPIXELFORMATFLAGS_HPP

#include <cstdint>

namespace scener { namespace content { namespace dds {

/// Values which indicate what type of data is in the surface.
enum class DDS_PIXELFORMAT_FLAGS : std::uint32_t
{
    DDPF_ALPHAPIXELS = 0x1      ///< Texture contains alpha data; dwRGBAlphaBitMask contains valid data.
  , DDPF_ALPHA       = 0x2      ///< Used in some older DDS files for alpha channel only uncompressed data.
  , DDPF_FOURCC      = 0x4      ///< Texture contains compressed RGB data; dwFourCC contains valid data.
  , DDPF_RGB         = 0x40     ///< Texture contains uncompressed RGB data; dwRGBBitCount and the RGB masks.
  , DDPF_YUV         = 0x200    ///< Used in some older DDS files for YUV uncompressed data.
  , DDPF_LUMINANCE   = 0x20000  ///< Used in some older DDS files for single channel color uncompressed data.
};

/// Bitwise AND operator for DDS_PIXELFORMAT_FLAGS.
inline constexpr DDS_PIXELFORMAT_FLAGS operator&(const DDS_PIXELFORMAT_FLAGS& left, const DDS_PIXELFORMAT_FLAGS& right)
{
    return static_cast<DDS_PIXELFORMAT_FLAGS>(static_cast<std::uint32_t>(left) & static_cast<std::uint32_t>(right));
}

/// Bitwise OR operator for DDS_PIXELFORMAT_FLAGS.
inline constexpr DDS_PIXELFORMAT_FLAGS operator|(const DDS_PIXELFORMAT_FLAGS& left, const DDS_PIXELFORMAT_FLAGS& right)
{
    return static_cast<DDS_PIXELFORMAT_FLAGS>(static_cast<std::uint32_t>(left) | static_cast<std::uint32_t>(right));
}

/// Unary complement operator for DDS_PIXELFORMAT_FLAGS.
inline constexpr DDS_PIXELFORMAT_FLAGS operator~(const DDS_PIXELFORMAT_FLAGS& value)
{
    return static_cast<DDS_PIXELFORMAT_FLAGS>(~static_cast<std::uint32_t>(value));
}

/// Equality operator for comparing a DDS_PIXELFORMAT_FLAGS value against an unsigned int32.
inline constexpr bool operator==(const DDS_PIXELFORMAT_FLAGS& left, const std::uint32_t& right)
{
    return (static_cast<std::uint32_t>(left) == right);
}

/// Inequality operator for comparing a DDS_PIXELFORMAT_FLAGS value against an unsigned int32.
inline constexpr bool operator!=(const DDS_PIXELFORMAT_FLAGS& left, const std::uint32_t& right)
{
    return (static_cast<std::uint32_t>(left) != right);
}

/// Equality operator for comparing DDS_PIXELFORMAT_FLAGS values.
inline DDS_PIXELFORMAT_FLAGS& operator&=(DDS_PIXELFORMAT_FLAGS& left, const DDS_PIXELFORMAT_FLAGS& right)
{
    left = left & right;

    return left;
}

/// Inequality operator for comparing DDS_PIXELFORMAT_FLAGS values.
inline DDS_PIXELFORMAT_FLAGS& operator|=(DDS_PIXELFORMAT_FLAGS& left, const DDS_PIXELFORMAT_FLAGS& right)
{
    left = left | right;

    return left;
}

}}}

#endif // SCENER_CONTENT_DDS_DDSPIXELFORMATFLAGS_HPP
