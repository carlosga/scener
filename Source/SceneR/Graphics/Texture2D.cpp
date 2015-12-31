// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/Texture2D.hpp"

#include "SceneR/Graphics/GraphicsDevice.hpp"
#include "SceneR/Graphics/SamplerState.hpp"
#include "SceneR/Graphics/OpenGL/TextureTarget.hpp"

namespace SceneR { namespace Graphics {

using SceneR::Graphics::OpenGL::TextureTarget;
using SceneR::Graphics::OpenGL::TextureStorage;

Texture2D::Texture2D(gsl::not_null<GraphicsDevice*> graphicsDevice
                   , const std::size_t&             width
                   , const std::size_t&             height) noexcept
    : Texture2D(graphicsDevice, width, height, false, SurfaceFormat::color)
{
}

Texture2D::Texture2D(gsl::not_null<GraphicsDevice*> graphicsDevice
                   , const std::size_t&             width
                   , const std::size_t&             height
                   , const bool&                    mipmap
                   , const SurfaceFormat&           format) noexcept
    : Texture        { graphicsDevice }
    , _format        { format }
    , _mipmap        { mipmap }
    , _mipmap_levels { 0 }
    , _height        { height }
    , _width         { width }
    , _storage       { TextureTarget::texture_2d }
{
}

void Texture2D::dispose()
{
    _storage.dispose();
}

std::uint32_t Texture2D::id() const noexcept
{
    return _storage.id();
}

const SurfaceFormat& Texture2D::format() const noexcept
{
    return _format;
}

std::size_t Texture2D::height() const noexcept
{
    return _height;
}

std::size_t Texture2D::level_count() const noexcept
{
    return _mipmap_levels;
}

std::size_t Texture2D::width() const noexcept
{
    return _width;
}

SamplerState* Texture2D::sampler_state() const noexcept
{
    return _sampler_state.get();
}

void Texture2D::set_data(const std::size_t&               level
                       , const std::size_t&               width
                       , const std::size_t&               height
                       , const std::vector<std::uint8_t>& data) const
{
    _storage.set_data(_format, level, width, height, data);
}

void Texture2D::declare_storage(const std::size_t& mipMapLevels)
{
    _storage.declare_storage(_format, mipMapLevels, _width, _height);
    _mipmap_levels = mipMapLevels;
}

void Texture2D::bind() const
{
    _storage.bind();
}

void Texture2D::unbind() const
{
    _storage.unbind();
}

}}
