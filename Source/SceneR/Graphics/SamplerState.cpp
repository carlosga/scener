// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/SamplerState.hpp"

#include "SceneR/Graphics/GraphicsDevice.hpp"
#include "SceneR/Graphics/Texture.hpp"
#include "SceneR/Graphics/TextureFilter.hpp"
#include "SceneR/Graphics/TextureTarget.hpp"
#include "SceneR/Graphics/TextureAddressMode.hpp"

namespace SceneR
{
    namespace Graphics
    {
        SamplerState::SamplerState(gsl::not_null<GraphicsDevice*> graphicsDevice) noexcept
            : GraphicsResource { graphicsDevice }
        {
        }

        void SamplerState::dispose()
        {
        }

        void SamplerState::apply(const std::uint32_t& textureId) const
        {
            glTextureParameteri(textureId, GL_TEXTURE_WRAP_S    , static_cast<GLint>(address_u));
            glTextureParameteri(textureId, GL_TEXTURE_WRAP_T    , static_cast<GLint>(address_v));
            glTextureParameteri(textureId, GL_TEXTURE_WRAP_R    , static_cast<GLint>(address_w));
            glTextureParameteri(textureId, GL_TEXTURE_MAX_LEVEL , static_cast<GLint>(max_mip_level));
            glTextureParameteri(textureId, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(min_filter));
            glTextureParameteri(textureId, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(mag_filter));
            glTextureParameterf(textureId, GL_TEXTURE_LOD_BIAS  , mip_map_level_of_detail_bias);
        }
    }
}
