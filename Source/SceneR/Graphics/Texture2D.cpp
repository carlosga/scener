// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/Texture2D.hpp"

#include "SceneR/Graphics/GraphicsDevice.hpp"
#include "SceneR/Graphics/SamplerState.hpp"

namespace scener { namespace graphics {

Texture2D::Texture2D(gsl::not_null<GraphicsDevice*> graphicsDevice, std::size_t width, std::size_t height) noexcept
    : Texture2D(graphicsDevice, width, height, SurfaceFormat::color)
{
}

Texture2D::Texture2D(gsl::not_null<GraphicsDevice*> graphicsDevice
                   , std::size_t                    width
                   , std::size_t                    height
                   , SurfaceFormat                  format) noexcept
    : Texture        { graphicsDevice }
    , _format        { format }
    , _mipmap_levels { 0 }
    , _height        { height }
    , _width         { width }
    , _sampler_state { nullptr }
    , _storage       { scener::graphics::opengl::TextureTarget::texture_2d }
{
}

std::uint32_t Texture2D::id() const noexcept
{
    return _storage.id();
}

SurfaceFormat Texture2D::format() const noexcept
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

void Texture2D::set_data(std::size_t                          level
                       , std::size_t                          width
                       , std::size_t                          height
                       , const gsl::span<const std::uint8_t>& data) const noexcept
{
    _storage.set_data(_format, level, width, height, data);
}

void Texture2D::declare_storage(std::size_t mipMapLevels) noexcept
{
    _storage.declare_storage(_format, mipMapLevels, _width, _height);
    _mipmap_levels = mipMapLevels;
}

void Texture2D::bind() const noexcept
{
    _storage.bind();
}

void Texture2D::unbind() const noexcept
{
    _storage.unbind();
}

}}
