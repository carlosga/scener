// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//---------------------------------------------------------------------------------------------------
// Ported from Microsoft XNA Community Game Platform Stock Effects
//---------------------------------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//---------------------------------------------------------------------------------------------------

#ifndef EFFECTDIRTYFLAGS_HPP
#define EFFECTDIRTYFLAGS_HPP

#include <stdint.h>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * @brief Track which effect parameters need to be recomputed during the next OnApply.
         */
        enum class EffectDirtyFlags : uint32_t
        {
            WorldViewProj   = 1,
            World           = 2,
            EyePosition     = 4,
            MaterialColor   = 8,
            Fog             = 16,
            FogEnable       = 32,
            AlphaTest       = 64,
            ShaderIndex     = 128,
            All             = WorldViewProj | World | EyePosition | MaterialColor | Fog | FogEnable | AlphaTest | ShaderIndex
        };

        inline constexpr EffectDirtyFlags operator&(const EffectDirtyFlags& left, const EffectDirtyFlags& right)
        {
            return static_cast<EffectDirtyFlags>(static_cast<uint32_t>(left) & static_cast<uint32_t>(right));
        }

        inline constexpr EffectDirtyFlags operator|(const EffectDirtyFlags& left, const EffectDirtyFlags& right)
        {
            return static_cast<EffectDirtyFlags>(static_cast<uint32_t>(left) | static_cast<uint32_t>(right));
        }

        inline constexpr EffectDirtyFlags operator~(const EffectDirtyFlags& value)
        {
            return static_cast<EffectDirtyFlags>(~static_cast<uint32_t>(value));
        }

        inline constexpr bool operator==(const EffectDirtyFlags& left, const uint32_t& right)
        {
            return (static_cast<uint32_t>(left) == right);
        }

        inline constexpr bool operator!=(const EffectDirtyFlags& left, const uint32_t& right)
        {
            return (static_cast<uint32_t>(left) != right);
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
    }
}

#endif /* EFFECTDIRTYFLAGS_HPP */
