// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/Texture2D.hpp"

#include "scener/graphics/GraphicsDevice.hpp"
#include "scener/graphics/SamplerState.hpp"

namespace scener { namespace graphics {

texture2d::texture2d(gsl::not_null<graphics_device*> device, std::size_t width, std::size_t height) noexcept
    : texture2d(device, width, height, surface_format::color)
{
}

texture2d::texture2d(gsl::not_null<graphics_device*> device
                   , std::size_t                     width
                   , std::size_t                     height
                   , surface_format                  format) noexcept
    : texture        { device }
    , _format        { format }
    , _mipmap_levels { 0 }
    , _height        { height }
    , _width         { width }
    , _sampler_state { nullptr }
    , _storage       { opengl::texture_target::texture_2d }
{
}

std::uint32_t texture2d::id() const noexcept
{
    return _storage.id();
}

surface_format texture2d::format() const noexcept
{
    return _format;
}

std::size_t texture2d::height() const noexcept
{
    return _height;
}

std::size_t texture2d::level_count() const noexcept
{
    return _mipmap_levels;
}

std::size_t texture2d::width() const noexcept
{
    return _width;
}

sampler_state* texture2d::sampler_state() const noexcept
{
    return _sampler_state.get();
}

void texture2d::set_data(std::size_t                          level
                       , std::size_t                          width
                       , std::size_t                          height
                       , const gsl::span<const std::uint8_t>& data) const noexcept
{
    _storage.set_data(_format, level, width, height, data);
}

void texture2d::declare_storage(std::size_t mipMapLevels) noexcept
{
    _storage.declare_storage(_format, mipMapLevels, _width, _height);
    _mipmap_levels = mipMapLevels;
}

void texture2d::bind() const noexcept
{
    _storage.bind();
}

void texture2d::unbind() const noexcept
{
    _storage.unbind();
}

}}
