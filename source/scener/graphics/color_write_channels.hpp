// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_COLORWRITECHANNELS_HPP
#define SCENER_GRAPHICS_COLORWRITECHANNELS_HPP

#include <cstdint>

namespace scener { namespace graphics {

/// Defines the color channels that can be chosen for a per-channel write to a render target color buffer
enum class color_write_channels : std::uint32_t
{
    none  = 0                          ///< No channel selected.
  , alpha = 1                          ///< Alpha channel of a buffer.
  , blue  = 2                          ///< Blue channel of a buffer.
  , green = 4                          ///< Green channel of a buffer.
  , red   = 8                          ///< Red channel of a buffer.
  , all   = red | green | blue | alpha ///< All buffer channels.
};

inline constexpr color_write_channels operator&(const color_write_channels& lhs, const color_write_channels& rhs)
{
    return static_cast<color_write_channels>(static_cast<std::uint32_t>(lhs) & static_cast<std::uint32_t>(rhs));
}

inline constexpr color_write_channels operator|(const color_write_channels& lhs, const color_write_channels& rhs)
{
    return static_cast<color_write_channels>(static_cast<std::uint32_t>(lhs) | static_cast<std::uint32_t>(rhs));
}

inline constexpr color_write_channels operator~(const color_write_channels& value)
{
    return static_cast<color_write_channels>(~static_cast<std::uint32_t>(value));
}

inline constexpr bool operator==(const color_write_channels& lhs, const std::uint32_t& rhs)
{
    return (static_cast<std::uint32_t>(lhs) == rhs);
}

inline constexpr bool operator!=(const color_write_channels& lhs, const std::uint32_t& rhs)
{
    return (static_cast<std::uint32_t>(lhs) != rhs);
}

inline color_write_channels& operator&=(color_write_channels& lhs, const color_write_channels& rhs)
{
    lhs = lhs & rhs;

    return lhs;
}

inline color_write_channels& operator|=(color_write_channels& lhss, const color_write_channels& rhs)
{
    lhss = lhss | rhs;

    return lhss;
}

}}

#endif // SCENER_GRAPHICS_COLORWRITECHANNELS_HPP