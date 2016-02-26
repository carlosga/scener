// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_DDS_PIXEL_FORMAT_FLAGS_HPP
#define SCENER_CONTENT_DDS_PIXEL_FORMAT_FLAGS_HPP

#include <cstdint>

namespace scener { namespace content { namespace dds {

/// Values which indicate what type of data is in the surface.
enum class pixel_format_flags : std::uint32_t
{
    alphapixels = 0x1      ///< Texture contains alpha data; dwRGBAlphaBitMask contains valid data.
  , alpha       = 0x2      ///< Used in some older DDS files for alpha channel only uncompressed data.
  , fourcc      = 0x4      ///< Texture contains compressed RGB data; dwFourCC contains valid data.
  , rgb         = 0x40     ///< Texture contains uncompressed RGB data; dwRGBBitCount and the RGB masks.
  , yuv         = 0x200    ///< Used in some older DDS files for YUV uncompressed data.
  , luminance   = 0x20000  ///< Used in some older DDS files for single channel color uncompressed data.
};

/// Bitwise AND operator for pixel_format_flags.
inline constexpr pixel_format_flags operator&(const pixel_format_flags& left, const pixel_format_flags& right)
{
    return static_cast<pixel_format_flags>(static_cast<std::uint32_t>(left) & static_cast<std::uint32_t>(right));
}

/// Bitwise OR operator for pixel_format_flags.
inline constexpr pixel_format_flags operator|(const pixel_format_flags& left, const pixel_format_flags& right)
{
    return static_cast<pixel_format_flags>(static_cast<std::uint32_t>(left) | static_cast<std::uint32_t>(right));
}

/// Unary complement operator for pixel_format_flags.
inline constexpr pixel_format_flags operator~(const pixel_format_flags& value)
{
    return static_cast<pixel_format_flags>(~static_cast<std::uint32_t>(value));
}

/// Equality operator for comparing a pixel_format_flags value against an unsigned int32.
inline constexpr bool operator==(const pixel_format_flags& left, const std::uint32_t& right)
{
    return (static_cast<std::uint32_t>(left) == right);
}

/// Inequality operator for comparing a pixel_format_flags value against an unsigned int32.
inline constexpr bool operator!=(const pixel_format_flags& left, const std::uint32_t& right)
{
    return (static_cast<std::uint32_t>(left) != right);
}

/// Equality operator for comparing pixel_format_flags values.
inline pixel_format_flags& operator&=(pixel_format_flags& left, const pixel_format_flags& right)
{
    left = left & right;

    return left;
}

/// Inequality operator for comparing pixel_format_flags values.
inline pixel_format_flags& operator|=(pixel_format_flags& left, const pixel_format_flags& right)
{
    left = left | right;

    return left;
}

}}}

#endif // SCENER_CONTENT_DDS_PIXEL_FORMAT_FLAGS_HPP
