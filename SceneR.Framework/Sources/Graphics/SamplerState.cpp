// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/SamplerState.hpp>

#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/Texture.hpp>

namespace SceneR
{
    namespace Graphics
    {
        SamplerState::SamplerState(GraphicsDevice& graphicsDevice)
            : GraphicsResource              { graphicsDevice }
            , address_U                     { TextureAddressMode::Wrap }
            , address_V                     { TextureAddressMode::Wrap }
            , address_W                     { TextureAddressMode::Wrap }
            , mag_filter                    { TextureFilter::Linear }
            , min_filter                    { TextureFilter::Linear }
            , max_anisotropy                { 4 }
            , max_mip_level                 { 0 }
            , mip_map_level_of_detail_bias  { 0 }
        {
        }

        SamplerState::SamplerState(const SamplerState& samplerState)
            : GraphicsResource              { samplerState._graphics_device }
            , address_U                     { samplerState.address_U }
            , address_V                     { samplerState.address_V }
            , address_W                     { samplerState.address_W }
            , mag_filter                    { samplerState.mag_filter }
            , min_filter                    { samplerState.min_filter }
            , max_anisotropy                { samplerState.max_anisotropy }
            , max_mip_level                 { samplerState.max_mip_level }
            , mip_map_level_of_detail_bias  { samplerState.mip_map_level_of_detail_bias }
        {
        }

        SamplerState::~SamplerState()
        {
        }

        void SamplerState::dispose()
        {
        }

        SamplerState&SamplerState::operator=(const SamplerState& samplerState)
        {
            if (this != &samplerState)
            {
                _graphics_device             = samplerState._graphics_device;
                address_U                    = samplerState.address_U;
                address_V                    = samplerState.address_V;
                address_W                    = samplerState.address_W;
                min_filter                   = samplerState.min_filter;
                mag_filter                   = samplerState.mag_filter;
                max_anisotropy               = samplerState.max_anisotropy;
                max_mip_level                = samplerState.max_mip_level;
                mip_map_level_of_detail_bias = samplerState.mip_map_level_of_detail_bias;
            }

            return *this;
        }

        void SamplerState::apply(const std::uint32_t& textureId) const
        {
            glTextureParameteri(textureId, GL_TEXTURE_WRAP_S    , static_cast<GLint>(address_U));
            glTextureParameteri(textureId, GL_TEXTURE_WRAP_T    , static_cast<GLint>(address_V));
            glTextureParameteri(textureId, GL_TEXTURE_WRAP_R    , static_cast<GLint>(address_W));
            glTextureParameteri(textureId, GL_TEXTURE_LOD_BIAS  , mip_map_level_of_detail_bias);
            glTextureParameteri(textureId, GL_TEXTURE_MAX_LEVEL , static_cast<GLint>(max_mip_level));
            glTextureParameteri(textureId, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(min_filter));
            glTextureParameteri(textureId, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(mag_filter));

//            if (this->filter == TextureFilter::Anisotropic)
//            {
//                glTextureParameteri(textureId, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);
//            }
        }
    }
}
