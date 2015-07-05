// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TEXTUREADDRESSMODE_HPP
#define TEXTUREADDRESSMODE_HPP

#include <cstdint>

#include <System/Graphics/Platform.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines modes for addressing texels using texture coordinates that are outside of the typical range of 0.0 to 1.0.
         */
        enum class TextureAddressMode : std::uint32_t
        {
            /**
             * Texture coordinates outside the range [0.0, 1.0] are set to the texture color at 0.0 or 1.0, respectively.
             */
            Clamp = GL_CLAMP_TO_EDGE,
            /**
             * Similar to Wrap, except that the texture is flipped at every integer junction.
             * For u values between 0 and 1, for example, the texture is addressed normally;
             * between 1 and 2, the texture is flipped (mirrored); between 2 and 3,
             * the texture is normal again, and so on.
             */
            Mirror = GL_MIRRORED_REPEAT,
            /**
             * Tile the texture at every integer junction. For example, for u values between 0 and 3,
             * the texture is repeated three times; no mirroring is performed.
             */
            Wrap = GL_REPEAT
        };
    }
}

#endif /* TEXTUREADDRESSMODE_HPP */
