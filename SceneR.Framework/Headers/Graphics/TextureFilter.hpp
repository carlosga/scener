/*
 * TextureFilter.hpp
 *
 *  Created on: Dec 28, 2013
 *      Author: carlos
 */

#ifndef TEXTUREFILTER_HPP
#define TEXTUREFILTER_HPP

#include <System/Core.hpp>
#include <System/Graphics/Platform.hpp>

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
            LinearMipPoint = GL_NEAREST_MIPMAP_LINEAR,
            /**
             * Use point filtering to shrink (minify) or expand (magnify), and linear filtering between mipmap levels.
             */
            PointMipLinear = GL_LINEAR_MIPMAP_NEAREST,
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
