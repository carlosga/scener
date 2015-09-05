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
            , filter                        { TextureFilter::Linear }
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
            , filter                        { samplerState.filter }
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
                filter                       = samplerState.filter;
                max_anisotropy               = samplerState.max_anisotropy;
                max_mip_level                = samplerState.max_mip_level;
                mip_map_level_of_detail_bias = samplerState.mip_map_level_of_detail_bias;
            }

            return *this;
        }

        void SamplerState::apply(const std::uint32_t& textureId) const
        {
            GLenum minfilter;
            GLenum magfilter;

            get_min_max_filters(minfilter, magfilter);

            glTextureParameteri(textureId, GL_TEXTURE_WRAP_S    , static_cast<GLint>(address_U));
            glTextureParameteri(textureId, GL_TEXTURE_WRAP_T    , static_cast<GLint>(address_V));
            glTextureParameteri(textureId, GL_TEXTURE_WRAP_R    , static_cast<GLint>(address_W));
            glTextureParameteri(textureId, GL_TEXTURE_LOD_BIAS  , mip_map_level_of_detail_bias);
            glTextureParameteri(textureId, GL_TEXTURE_MAX_LEVEL , static_cast<GLint>(max_mip_level));
            glTextureParameteri(textureId, GL_TEXTURE_MIN_FILTER, minfilter);
            glTextureParameteri(textureId, GL_TEXTURE_MAG_FILTER, magfilter);

            if (this->filter == TextureFilter::Anisotropic)
            {
                glTextureParameteri(textureId, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);
            }
        }

        void SamplerState::get_min_max_filters(GLenum& minfilter, GLenum& magfilter) const
        {
            switch (this->filter)
            {
            case TextureFilter::Point:
                minfilter = ((max_mip_level != 0) ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST);
                magfilter = GL_NEAREST;
                break;

            case TextureFilter::Linear:
            case TextureFilter::Anisotropic:
                minfilter = ((max_mip_level != 0) ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
                magfilter = GL_LINEAR;
                break;

            case TextureFilter::PointMipLinear:
                minfilter = ((max_mip_level != 0) ? GL_NEAREST_MIPMAP_LINEAR : GL_NEAREST);
                magfilter = GL_NEAREST;
                break;

            case TextureFilter::LinearMipPoint:
                minfilter = ((max_mip_level != 0) ? GL_LINEAR_MIPMAP_NEAREST : GL_LINEAR);
                magfilter = GL_LINEAR;
                break;

            case TextureFilter::MinLinearMagPointMipLinear:
                minfilter = ((max_mip_level != 0) ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
                magfilter = GL_NEAREST;
                break;

            case TextureFilter::MinLinearMagPointMipPoint:
                minfilter = ((max_mip_level != 0) ? GL_LINEAR_MIPMAP_NEAREST : GL_LINEAR);
                magfilter = GL_NEAREST;
                break;

            case TextureFilter::MinPointMagLinearMipLinear:
                minfilter = ((max_mip_level != 0) ? GL_NEAREST_MIPMAP_LINEAR : GL_NEAREST);
                magfilter = GL_LINEAR;
                break;

            case TextureFilter::MinPointMagLinearMipPoint:
                minfilter = ((max_mip_level != 0) ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST);
                magfilter = GL_LINEAR;
                break;
            }
        }
    }
}
