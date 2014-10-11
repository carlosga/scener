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

#ifndef TEXTUREFILTER_HPP
#define TEXTUREFILTER_HPP

#include <System/Graphics/Platform.hpp>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines filtering types during texture sampling.
         */
        enum class TextureFilter : System::UInt32
        {
            /**
             * Use linear filtering.
             */
            Linear = GL_LINEAR,
            /**
             * Use point filtering.
             */
            Point = GL_NEAREST,
            /**
             * Use anisotropic filtering.
             */
            Anisotropic = 2,
            /**
             * Use linear filtering to shrink or expand, and point filtering between mipmap levels (mip).
             */
            LinearMipPoint = GL_LINEAR_MIPMAP_NEAREST,
            /**
             * Use point filtering to shrink (minify) or expand (magnify), and linear filtering between mipmap levels.
             */
            PointMipLinear = GL_NEAREST_MIPMAP_LINEAR,
            /**
             * Use linear filtering to shrink, point filtering to expand, and linear filtering between mipmap levels.
             */
            MinLinearMagPointMipLinear = GL_LINEAR_MIPMAP_LINEAR,
            /**
             * Use linear filtering to shrink, point filtering to expand, and point filtering between mipmap levels.
             */
            MinLinearMagPointMipPoint = GL_LINEAR_MIPMAP_NEAREST,
            /**
             * Use point filtering to shrink, linear filtering to expand, and linear filtering between mipmap levels.
             */
            MinPointMagLinearMipLinear = GL_NEAREST_MIPMAP_LINEAR,
            /**
             * Use point filtering to shrink, linear filtering to expand, and point filtering between mipmap levels.
             */
            MinPointMagLinearMipPoint = GL_NEAREST_MIPMAP_NEAREST
        };
    }
}

#endif /* TEXTUREFILTER_HPP */
