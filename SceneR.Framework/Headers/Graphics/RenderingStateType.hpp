// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef RENDERINGSTATETYPE_HPP
#define RENDERINGSTATETYPE_HPP

#include <cstdint>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Fixed-function rendering states.
         */
        enum class RenderingStateType : std::uint32_t
        {
            None                  = 0
          , Blend                 = 3042
          , CullFace              = 2884
          , DepthTest             = 2929
          , PolygonOffsetFill     = 32823
          , SampleAlphaToCoverage = 32926
          , ScissorTest           = 3089
        };

        inline constexpr RenderingStateType operator&(const RenderingStateType& left, const RenderingStateType& right)
        {
            return static_cast<RenderingStateType>(static_cast<std::uint32_t>(left) & static_cast<std::uint32_t>(right));
        }

        inline constexpr RenderingStateType operator|(const RenderingStateType& left, const RenderingStateType& right)
        {
            return static_cast<RenderingStateType>(static_cast<std::uint32_t>(left) | static_cast<std::uint32_t>(right));
        }

        inline constexpr RenderingStateType operator~(const RenderingStateType& value)
        {
            return static_cast<RenderingStateType>(~static_cast<std::uint32_t>(value));
        }

        inline constexpr bool operator==(const RenderingStateType& left, const std::uint32_t& right)
        {
            return (static_cast<std::uint32_t>(left) == right);
        }

        inline constexpr bool operator!=(const RenderingStateType& left, const std::uint32_t& right)
        {
            return (static_cast<std::uint32_t>(left) != right);
        }

        inline RenderingStateType& operator&=(RenderingStateType& left, const RenderingStateType& right)
        {
            left = left & right;

            return left;
        }

        inline RenderingStateType& operator|=(RenderingStateType& left, const RenderingStateType& right)
        {
            left = left | right;

            return left;
        }
    }
}

#endif // RENDERINGSTATETYPE_HPP
