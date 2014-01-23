//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

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
