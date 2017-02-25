// Copyrhs (c) Carlos Guzmán Álvarez. All rhss reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//---------------------------------------------------------------------------------------------------
// Ported from Microsoft XNA Community Game Platform Stock Effects
//---------------------------------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyrhs (C) Microsoft Corporation. All rhss reserved.
//---------------------------------------------------------------------------------------------------

#ifndef SCENER_GRAPHICS_EFFECT_DIRTY_FLAGS_HPP
#define SCENER_GRAPHICS_EFFECT_DIRTY_FLAGS_HPP

#include <cstdint>

namespace scener::graphics
{
    ///Tracks which effect parameters need to be recomputed during the next OnApply.
    enum class effect_dirty_flags : std::uint32_t
    {
        world_view_proj = 1,
        world           = 2,
        eye_position    = 4,
        material_color  = 8,
        fog             = 16,
        fog_enable      = 32,
        alpha_test      = 64,
        shader_index    = 128,
        all             = world_view_proj | world | eye_position | material_color | fog | fog_enable | alpha_test | shader_index
    };

    inline constexpr effect_dirty_flags operator&(const effect_dirty_flags& lhs, const effect_dirty_flags& rhs)
    {
        return static_cast<effect_dirty_flags>(static_cast<std::uint32_t>(lhs) & static_cast<std::uint32_t>(rhs));
    }

    inline constexpr effect_dirty_flags operator|(const effect_dirty_flags& lhs, const effect_dirty_flags& rhs)
    {
        return static_cast<effect_dirty_flags>(static_cast<std::uint32_t>(lhs) | static_cast<std::uint32_t>(rhs));
    }

    inline constexpr effect_dirty_flags operator~(const effect_dirty_flags& value)
    {
        return static_cast<effect_dirty_flags>(~static_cast<std::uint32_t>(value));
    }

    inline constexpr bool operator==(const effect_dirty_flags& lhs, const std::uint32_t& rhs)
    {
        return (static_cast<std::uint32_t>(lhs) == rhs);
    }

    inline constexpr bool operator!=(const effect_dirty_flags& lhs, const std::uint32_t& rhs)
    {
        return (static_cast<std::uint32_t>(lhs) != rhs);
    }

    inline effect_dirty_flags& operator&=(effect_dirty_flags& lhs, const effect_dirty_flags& rhs)
    {
        lhs = lhs & rhs;

        return lhs;
    }

    inline effect_dirty_flags& operator|=(effect_dirty_flags& lhs, const effect_dirty_flags& rhs)
    {
        lhs = lhs | rhs;

        return lhs;
    }
}

#endif // SCENER_GRAPHICS_EFFECT_DIRTY_FLAGS_HPP
