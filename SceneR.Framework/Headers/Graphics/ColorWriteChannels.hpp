// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef COLORWRITECHANNELS_HPP
#define COLORWRITECHANNELS_HPP

#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines the color channels that can be chosen for a per-channel write to a render target color buffer
         */
        enum class ColorWriteChannels : System::UInt32
        {
            /**
             * No channel selected.
             */
            None = 0,
            /**
             * Alpha channel of a buffer.
             */
            Alpha = 1,
            /**
             * Blue channel of a buffer.
             */
            Blue = 2,
            /**
             * Green channel of a buffer.
             */
            Green = 4,
            /**
             * Red channel of a buffer.
             */
            Red = 8,
            /**
             * All buffer channels.
             */
            All = Red | Green | Blue | Alpha
        };

        inline constexpr ColorWriteChannels
        operator&(ColorWriteChannels left, ColorWriteChannels right)
        {
            return static_cast<ColorWriteChannels>(static_cast<int>(left) & static_cast<int>(right));
        };

        inline constexpr ColorWriteChannels
        operator|(ColorWriteChannels left, ColorWriteChannels right)
        {
            return static_cast<ColorWriteChannels>(static_cast<int>(left) | static_cast<int>(right));
        };
    }
}

#endif /* COLORWRITECHANNELS_HPP */
