// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/SamplerState.hpp>

#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/Texture.hpp>

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

SamplerState::SamplerState(const SamplerState& samplerState)
    : GraphicsResource        { samplerState.graphicsDevice }
    , addressU                { samplerState.addressU }
    , addressV                { samplerState.addressV }
    , addressW                { samplerState.addressW }
    , filter                  { samplerState.filter }
    , maxAnisotropy           { samplerState.maxAnisotropy }
    , maxMipLevel             { samplerState.maxMipLevel }
    , mipMapLevelOfDetailBias { samplerState.mipMapLevelOfDetailBias }
{
}

SamplerState::~SamplerState()
{
}

void SamplerState::Dispose()
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

const int32_t& SamplerState::MaxAnisotropy() const
{
    return this->maxAnisotropy;
}

void SamplerState::MaxAnisotropy(const int32_t& maxAnisotropy)
{
    this->maxAnisotropy = maxAnisotropy;
}

uint32_t SamplerState::MaxMipLevel() const
{
    return this->maxMipLevel;
}

void SamplerState::MaxMipLevel(const uint32_t& maxMipLevel)
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

SamplerState&SamplerState::operator=(const SamplerState& samplerState)
{
    if (this != &samplerState)
    {
        this->graphicsDevice          = samplerState.graphicsDevice;
        this->addressU                = samplerState.addressU;
        this->addressV                = samplerState.addressV;
        this->addressW                = samplerState.addressW;
        this->filter                  = samplerState.filter;
        this->maxAnisotropy           = samplerState.maxAnisotropy;
        this->maxMipLevel             = samplerState.maxMipLevel;
        this->mipMapLevelOfDetailBias = samplerState.mipMapLevelOfDetailBias;
    }

    return *this;
}

void SamplerState::OnApply(const TextureTarget& target) const
{
    auto   glTarget  = static_cast<GLenum>(target);
    GLenum minfilter;
    GLenum magfilter;

    this->GetMinMaxFilters(minfilter, magfilter);

    glTexParameteri(glTarget, GL_TEXTURE_WRAP_S    , static_cast<GLint>(this->addressU));
    glTexParameteri(glTarget, GL_TEXTURE_WRAP_T    , static_cast<GLint>(this->addressV));
    glTexParameteri(glTarget, GL_TEXTURE_WRAP_R    , static_cast<GLint>(this->addressW));
    glTexParameterf(glTarget, GL_TEXTURE_LOD_BIAS  , this->mipMapLevelOfDetailBias);
    glTexParameteri(glTarget, GL_TEXTURE_MAX_LEVEL , static_cast<GLint>(this->maxMipLevel));
    glTexParameteri(glTarget, GL_TEXTURE_MIN_FILTER, minfilter);
    glTexParameteri(glTarget, GL_TEXTURE_MAG_FILTER, magfilter);

    if (this->filter == TextureFilter::Anisotropic)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, this->maxAnisotropy);
    }
}

void SamplerState::GetMinMaxFilters(GLenum& minfilter, GLenum& magfilter) const
{
    switch (this->filter)
    {
    case TextureFilter::Point:
        minfilter = ((this->maxMipLevel != 0) ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST);
        magfilter = GL_NEAREST;
        break;

    case TextureFilter::Linear:
    case TextureFilter::Anisotropic:
        minfilter = ((this->maxMipLevel != 0) ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
        magfilter = GL_LINEAR;
        break;

    case TextureFilter::PointMipLinear:
        minfilter = ((this->maxMipLevel != 0) ? GL_NEAREST_MIPMAP_LINEAR : GL_NEAREST);
        magfilter = GL_NEAREST;
        break;

    case TextureFilter::LinearMipPoint:
        minfilter = ((this->maxMipLevel != 0) ? GL_LINEAR_MIPMAP_NEAREST : GL_LINEAR);
        magfilter = GL_LINEAR;
        break;

    case TextureFilter::MinLinearMagPointMipLinear:
        minfilter = ((this->maxMipLevel != 0) ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
        magfilter = GL_NEAREST;

    case TextureFilter::MinLinearMagPointMipPoint:
        minfilter = ((this->maxMipLevel != 0) ? GL_LINEAR_MIPMAP_NEAREST : GL_LINEAR);
        magfilter = GL_NEAREST;
        break;

    case TextureFilter::MinPointMagLinearMipLinear:
        minfilter = ((this->maxMipLevel != 0) ? GL_NEAREST_MIPMAP_LINEAR : GL_NEAREST);
        magfilter = GL_LINEAR;
        break;

    case TextureFilter::MinPointMagLinearMipPoint:
        minfilter = ((this->maxMipLevel != 0) ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST);
        magfilter = GL_LINEAR;
        break;
    }
}
