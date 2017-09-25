// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_COLOR_WRITE_CHANNELS_HPP
#define SCENER_GRAPHICS_COLOR_WRITE_CHANNELS_HPP

#include <cstdint>

namespace scener::graphics
{
    /// Defines the color channels that can be chosen for a per-channel write to a render target color buffer
    enum class color_write_channels : std::uint32_t
    {
        red   = 0x00000001                 ///< Red channel of a buffer.
      , green = 0x00000002                 ///< Green channel of a buffer.
      , blue  = 0x00000004                 ///< Blue channel of a buffer.
      , alpha = 0x00000008                 ///< Alpha channel of a buffer.
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

    inline color_write_channels& operator|=(color_write_channels& lhs, const color_write_channels& rhs)
    {
        lhs = lhs | rhs;

        return lhs;
    }
}

#endif // SCENER_GRAPHICS_COLOR_WRITE_CHANNELS_HPP
