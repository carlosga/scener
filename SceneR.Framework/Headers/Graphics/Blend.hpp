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
#include <System/Graphics/Platform.hpp>

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
            Zero = GL_ZERO,
            /**
             * Each component of the color is multiplied by (1, 1, 1, 1).
             */
            One = GL_ONE,
            /**
             * Each component of the color is multiplied by the source color.
             */
            SourceColor = GL_SRC_COLOR,
            /**
             * Each component of the color is multiplied by the inverse of the source color.
             */
            InverseSourceColor = GL_ONE_MINUS_SRC_COLOR,
            /**
             * Each component of the color is multiplied by the alpha value of the source.
             */
            SourceAlpha = GL_SRC_ALPHA,
            /**
             * Each component of the color is multiplied by the inverse of the alpha value of the source.
             */
            InverseSourceAlpha = GL_ONE_MINUS_SRC_ALPHA,
            /**
             * Each component of the color is multiplied by the alpha value of the destination.
             */
            DestinationAlpha = GL_DST_ALPHA,
            /**
             * Each component of the color is multiplied by the inverse of the alpha value of the destination.
             */
            InverseDestinationAlpha = GL_ONE_MINUS_DST_ALPHA,
            /**
             * Each component color is multiplied by the destination color.
             */
            DestinationColor = GL_DST_COLOR,
            /**
             * Each component of the color is multiplied by the inverse of the destination color.
             */
            InverseDestinationColor = GL_ONE_MINUS_DST_COLOR,
            /**
             * Each component of the color is multiplied by either the alpha of the source color,
             * or the inverse of the alpha of the source color, whichever is greater.
             */
            SourceAlphaSaturation = GL_SRC_ALPHA_SATURATE,
            /**
             * Each component of the color is multiplied by a constant set in BlendFactor.
             */
            BlendFactor = GL_CONSTANT_COLOR,
            /**
             * Each component of the color is multiplied by the inverse of a constant set in BlendFactor.
             */
            InverseBlendFactor = GL_ONE_MINUS_CONSTANT_COLOR
        };
    }
}

#endif /* BLEND_HPP */
