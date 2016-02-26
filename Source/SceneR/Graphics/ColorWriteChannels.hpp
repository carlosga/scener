// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_COLORWRITECHANNELS_HPP
#define SCENER_GRAPHICS_COLORWRITECHANNELS_HPP

#include <cstdint>

namespace scener { namespace graphics {

/// Defines the color channels that can be chosen for a per-channel write to a render target color buffer
enum class ColorWriteChannels : std::uint32_t
{
    none  = 0                          ///< No channel selected.
  , alpha = 1                          ///< Alpha channel of a buffer.
  , blue  = 2                          ///< Blue channel of a buffer.
  , green = 4                          ///< Green channel of a buffer.
  , red   = 8                          ///< Red channel of a buffer.
  , all   = red | green | blue | alpha ///< All buffer channels.
};

inline constexpr ColorWriteChannels operator&(const ColorWriteChannels& left, const ColorWriteChannels& right)
{
    return static_cast<ColorWriteChannels>(static_cast<std::uint32_t>(left) & static_cast<std::uint32_t>(right));
}

inline constexpr ColorWriteChannels operator|(const ColorWriteChannels& left, const ColorWriteChannels& right)
{
    return static_cast<ColorWriteChannels>(static_cast<std::uint32_t>(left) | static_cast<std::uint32_t>(right));
}

inline constexpr ColorWriteChannels operator~(const ColorWriteChannels& value)
{
    return static_cast<ColorWriteChannels>(~static_cast<std::uint32_t>(value));
}

inline constexpr bool operator==(const ColorWriteChannels& left, const std::uint32_t& right)
{
    return (static_cast<std::uint32_t>(left) == right);
}

inline constexpr bool operator!=(const ColorWriteChannels& left, const std::uint32_t& right)
{
    return (static_cast<std::uint32_t>(left) != right);
}

inline ColorWriteChannels& operator&=(ColorWriteChannels& left, const ColorWriteChannels& right)
{
    left = left & right;

    return left;
}

inline ColorWriteChannels& operator|=(ColorWriteChannels& left, const ColorWriteChannels& right)
{
    left = left | right;

    return left;
}

}}

#endif // SCENER_GRAPHICS_COLORWRITECHANNELS_HPP
