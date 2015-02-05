// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/SamplerState.hpp>

#include <Graphics/Texture.hpp>
#include <Graphics/GraphicsDevice.hpp>

using namespace System;
using namespace SceneR::Graphics;

SamplerState::SamplerState(GraphicsDevice& graphicsDevice)
    : GraphicsResource        { graphicsDevice }
    , addressU                { TextureAddressMode::Wrap }
    , addressV                { TextureAddressMode::Wrap }
    , addressW                { TextureAddressMode::Wrap }
    , filter                  { TextureFilter::Linear }
    , maxAnisotropy           { 4 }
    , maxMipLevel             { 0 }
    , mipMapLevelOfDetailBias { 0 }
{
}

const TextureAddressMode& SamplerState::AddressU() const
{
    return this->addressU;
}

void SamplerState::AddressU(const TextureAddressMode& addressU)
{
    this->addressU = addressU;
}

const TextureAddressMode& SamplerState::AddressV() const
{
    return this->addressV;
}

void SamplerState::AddressV(const TextureAddressMode& addressV)
{
    this->addressV = addressV;
}

const TextureAddressMode& SamplerState::AddressW() const
{
    return this->addressW;
}

void SamplerState::AddressW(const TextureAddressMode& addressW)
{
    this->addressW = addressW;
}

const TextureFilter& SamplerState::Filter() const
{
    return this->filter;
}

void SamplerState::Filter(const TextureFilter& filter)
{
    this->filter = filter;
}

const System::Int32& SamplerState::MaxAnisotropy() const
{
    return this->maxAnisotropy;
}

void SamplerState::MaxAnisotropy(const System::Int32& maxAnisotropy)
{
    this->maxAnisotropy = maxAnisotropy;
}

const System::Int32& SamplerState::MaxMipLevel() const
{
    return this->maxMipLevel;
}

void SamplerState::MaxMipLevel(const System::Int32& maxMipLevel)
{
    this->maxMipLevel = maxMipLevel;
}

const System::Single& SamplerState::MipMapLevelOfDetailBias() const
{
    return this->mipMapLevelOfDetailBias;
}

void SamplerState::MipMapLevelOfDetailBias(const System::Single& mipMapLevelOfDetailBias)
{
    this->mipMapLevelOfDetailBias = mipMapLevelOfDetailBias;
}

void SamplerState::OnApply(const TextureTarget& target, const Int32& mipmapLevels) const
{
    auto glTarget = static_cast<GLenum>(target);

    glTexParameteri(glTarget, GL_TEXTURE_SWIZZLE_R , GL_RED);
    glTexParameteri(glTarget, GL_TEXTURE_SWIZZLE_G , GL_GREEN);
    glTexParameteri(glTarget, GL_TEXTURE_SWIZZLE_B , GL_BLUE);
    glTexParameteri(glTarget, GL_TEXTURE_SWIZZLE_A , GL_ALPHA);
    glTexParameteri(glTarget, GL_TEXTURE_WRAP_S    , static_cast<GLenum>(this->addressU));
    glTexParameteri(glTarget, GL_TEXTURE_WRAP_T    , static_cast<GLenum>(this->addressV));
    glTexParameteri(glTarget, GL_TEXTURE_WRAP_R    , static_cast<GLenum>(this->addressW));
    glTexParameterf(glTarget, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(this->filter));
    glTexParameterf(glTarget, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(TextureFilter::Linear));
    glTexParameterf(glTarget, GL_TEXTURE_LOD_BIAS  , this->mipMapLevelOfDetailBias);
    glTexParameteri(glTarget, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(glTarget, GL_TEXTURE_MAX_LEVEL , mipmapLevels);

    if (this->filter == TextureFilter::Anisotropic)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, this->maxAnisotropy);
    }
}
