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

#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * @brief Track which effect parameters need to be recomputed during the next OnApply.
         */
        enum class EffectDirtyFlags : System::UInt32
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

        inline constexpr EffectDirtyFlags operator~(EffectDirtyFlags value)
        {
            return static_cast<EffectDirtyFlags>(static_cast<System::UInt32>(~value));
        }

        inline constexpr EffectDirtyFlags operator&(EffectDirtyFlags left, EffectDirtyFlags right)
        {
            return static_cast<EffectDirtyFlags>(static_cast<System::UInt32>(left) & static_cast<System::UInt32>(right));
        }

        inline constexpr EffectDirtyFlags operator|(EffectDirtyFlags left, EffectDirtyFlags right)
        {
            return static_cast<EffectDirtyFlags>(static_cast<System::UInt32>(left) | static_cast<System::UInt32>(right));
        }

        inline constexpr System::Boolean operator!=(EffectDirtyFlags left, System::UInt32 right)
        {
            return (static_cast<System::UInt32>(left) != right);
        }

        inline EffectDirtyFlags operator&=(EffectDirtyFlags left, EffectDirtyFlags right)
        {
            left = left & right;

            return left;
        }

        inline EffectDirtyFlags operator|=(EffectDirtyFlags left, EffectDirtyFlags right)
        {
            left = left | right;

            return left;
        }
    }
}

#endif /* EFFECTDIRTYFLAGS_HPP */