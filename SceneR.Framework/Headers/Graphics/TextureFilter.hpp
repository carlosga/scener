// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_TEXTUREFILTER_HPP
#define GRAPHICS_TEXTUREFILTER_HPP

#include <cstdint>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines filtering types during texture sampling.
         */
        enum class TextureFilter : std::uint32_t
        {
            /**
             * Use linear filtering.
             */
            Linear = 0,
            /**
             * Use point filtering.
             */
            Point = 1,
            /**
             * Use anisotropic filtering.
             */
            Anisotropic = 2,
            /**
             * Use linear filtering to shrink or expand, and point filtering between mipmap levels (mip).
             */
            LinearMipPoint = 3,
            /**
             * Use point filtering to shrink (minify) or expand (magnify), and linear filtering between mipmap levels.
             */
            PointMipLinear = 4,
            /**
             * Use linear filtering to shrink, point filtering to expand, and linear filtering between mipmap levels.
             */
            MinLinearMagPointMipLinear = 5,
            /**
             * Use linear filtering to shrink, point filtering to expand, and point filtering between mipmap levels.
             */
            MinLinearMagPointMipPoint = 6,
            /**
             * Use point filtering to shrink, linear filtering to expand, and linear filtering between mipmap levels.
             */
            MinPointMagLinearMipLinear = 7,
            /**
             * Use point filtering to shrink, linear filtering to expand, and point filtering between mipmap levels.
             */
            MinPointMagLinearMipPoint = 8
        };
    }
}

#endif  // GRAPHICS_TEXTUREFILTER_HPP
