// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//---------------------------------------------------------------------------------------------------
// Ported from Microsoft XNA Community Game Platform Stock Effects
//---------------------------------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//---------------------------------------------------------------------------------------------------

#ifndef SCENER_GRAPHICS_EFFECTDIRTYFLAGS_HPP
#define SCENER_GRAPHICS_EFFECTDIRTYFLAGS_HPP

#include <cstdint>

namespace scener { namespace graphics {

///Tracks which effect parameters need to be recomputed during the next OnApply.
enum class EffectDirtyFlags : std::uint32_t
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

inline constexpr EffectDirtyFlags operator&(const EffectDirtyFlags& left, const EffectDirtyFlags& right)
{
    return static_cast<EffectDirtyFlags>(static_cast<std::uint32_t>(left) & static_cast<std::uint32_t>(right));
}

inline constexpr EffectDirtyFlags operator|(const EffectDirtyFlags& left, const EffectDirtyFlags& right)
{
    return static_cast<EffectDirtyFlags>(static_cast<std::uint32_t>(left) | static_cast<std::uint32_t>(right));
}

inline constexpr EffectDirtyFlags operator~(const EffectDirtyFlags& value)
{
    return static_cast<EffectDirtyFlags>(~static_cast<std::uint32_t>(value));
}

inline constexpr bool operator==(const EffectDirtyFlags& left, const std::uint32_t& right)
{
    return (static_cast<std::uint32_t>(left) == right);
}

inline constexpr bool operator!=(const EffectDirtyFlags& left, const std::uint32_t& right)
{
    return (static_cast<std::uint32_t>(left) != right);
}

inline EffectDirtyFlags& operator&=(EffectDirtyFlags& left, const EffectDirtyFlags& right)
{
    left = left & right;

    return left;
}

inline EffectDirtyFlags& operator|=(EffectDirtyFlags& left, const EffectDirtyFlags& right)
{
    left = left | right;

    return left;
}

}}

#endif // SCENER_GRAPHICS_EFFECTDIRTYFLAGS_HPP
