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
            Nearest              = 9728,    // GL_NEAREST
            Linear               = 9729,    // GL_LINEAR,
            NearestMipMapNearest = 9984,    // GL_NEAREST_MIPMAP_NEAREST,
            LinearMipMapNearest  = 9985,    // GL_LINEAR_MIPMAP_NEAREST,
            NearestMipMapLinear  = 9986,    // GL_NEAREST_MIPMAP_LINEAR
            LinearMipMapLinear   = 9987     // GL_LINEAR_MIPMAP_LINEAR,
        };
    }
}

#endif  // GRAPHICS_TEXTUREFILTER_HPP
