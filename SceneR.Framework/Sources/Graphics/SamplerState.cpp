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

#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/SamplerState.hpp>

using namespace SceneR::Graphics;

SamplerState::SamplerState(GraphicsDevice& graphicsDevice)
    : GraphicsResource(graphicsDevice),
      addressU(TextureAddressMode::Wrap),
      addressV(TextureAddressMode::Wrap),
      addressW(TextureAddressMode::Wrap),
      filter(TextureFilter::Linear),
      maxAnisotropy(0),
      maxMipLevel(0),
      mipMapLevelOfDetailBias(0)
{
}

SamplerState::~SamplerState()
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
