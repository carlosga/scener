// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VULKAN_BUFFER_TARGET_HPP
#define SCENER_GRAPHICS_VULKAN_BUFFER_TARGET_HPP

#include <cstdint>

namespace scener::graphics::vulkan
{
    /// Defines buffer usages
    enum class buffer_usage : std::uint32_t
    {
        transfer_source       = 0x00000001
      , transfer_destination  = 0x00000002
      , uniform_texel         = 0x00000004
      , storage_texel         = 0x00000008
      , uniform_buffer        = 0x00000010
      , storage_buffer        = 0x00000020
      , index_buffer          = 0x00000040
      , vertex_buffer         = 0x00000080
      , indirect_buffer       = 0x00000100
    };

    inline constexpr buffer_usage operator&(const buffer_usage& lhs, const buffer_usage& rhs)
    {
        return static_cast<buffer_usage>(static_cast<std::uint32_t>(lhs) & static_cast<std::uint32_t>(rhs));
    }

    inline constexpr buffer_usage operator|(const buffer_usage& lhs, const buffer_usage& rhs)
    {
        return static_cast<buffer_usage>(static_cast<std::uint32_t>(lhs) | static_cast<std::uint32_t>(rhs));
    }

    inline constexpr buffer_usage operator~(const buffer_usage& value)
    {
        return static_cast<buffer_usage>(~static_cast<std::uint32_t>(value));
    }

    inline constexpr bool operator==(const buffer_usage& lhs, const std::uint32_t& rhs)
    {
        return (static_cast<std::uint32_t>(lhs) == rhs);
    }

    inline constexpr bool operator!=(const buffer_usage& lhs, const std::uint32_t& rhs)
    {
        return (static_cast<std::uint32_t>(lhs) != rhs);
    }

    inline buffer_usage& operator&=(buffer_usage& lhs, const buffer_usage& rhs)
    {
        lhs = lhs & rhs;

        return lhs;
    }

    inline buffer_usage& operator|=(buffer_usage& lhs, const buffer_usage& rhs)
    {
        lhs = lhs | rhs;

        return lhs;
    }
}

#endif // SCENER_GRAPHICS_VULKAN_BUFFER_TARGET_HPP
