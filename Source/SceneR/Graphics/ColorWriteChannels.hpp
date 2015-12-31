// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_COLORWRITECHANNELS_HPP
#define SCENER_GRAPHICS_COLORWRITECHANNELS_HPP

#include <cstdint>

namespace SceneR { namespace Graphics {

/**
 * Defines the color channels that can be chosen for a per-channel write to a render target color buffer
 */
enum class ColorWriteChannels : std::uint32_t
{
    /**
     * No channel selected.
     */
    none = 0,
    /**
     * Alpha channel of a buffer.
     */
    alpha = 1,
    /**
     * Blue channel of a buffer.
     */
    blue = 2,
    /**
     * Green channel of a buffer.
     */
    green = 4,
    /**
     * Red channel of a buffer.
     */
    red = 8,
    /**
     * All buffer channels.
     */
    all = red | green | blue | alpha
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
