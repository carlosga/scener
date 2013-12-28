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

#ifndef BLEND_HPP
#define BLEND_HPP

#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines color blending factors.
         */
        enum class Blend : System::UInt32
        {
            /**
             * Each component of the color is multiplied by (0, 0, 0, 0).
             */
            Zero,
            /**
             * Each component of the color is multiplied by (1, 1, 1, 1).
             */
            One,
            /**
             * Each component of the color is multiplied by the source color.
             */
            SourceColor,
            /**
             * Each component of the color is multiplied by the inverse of the source color.
             */
            InverseSourceColor,
            /**
             * Each component of the color is multiplied by the alpha value of the source.
             */
            SourceAlpha,
            /**
             * Each component of the color is multiplied by the inverse of the alpha value of the source.
             */
            InverseSourceAlpha,
            /**
             * Each component of the color is multiplied by the alpha value of the destination.
             */
            DestinationAlpha,
            /**
             * Each component of the color is multiplied by the inverse of the alpha value of the destination.
             */
            InverseDestinationAlpha,
            /**
             * Each component color is multiplied by the destination color.
             */
            DestinationColor,
            /**
             * Each component of the color is multiplied by the inverse of the destination color.
             */
            InverseDestinationColor,
            /**
             * Each component of the color is multiplied by either the alpha of the source color,
             * or the inverse of the alpha of the source color, whichever is greater.
             */
            SourceAlphaSaturation,
            /**
             * Each component of the color is multiplied by a constant set in BlendFactor.
             */
            BlendFactor,
            /**
             * Each component of the color is multiplied by the inverse of a constant set in BlendFactor.
             */
            InverseBlendFactor
        };
    }
}

#endif /* BLEND_HPP */
