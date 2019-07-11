// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/texture2d.hpp"

#include "scener/graphics/graphics_device.hpp"
#include "scener/graphics/sampler_state.hpp"

namespace scener::graphics
{
    texture2d::texture2d(gsl::not_null<graphics_device*> device, std::uint32_t width, std::uint32_t height) noexcept
        : texture2d(device, width, height, surface_format::color)
    {
    }

    texture2d::texture2d(gsl::not_null<graphics_device*> device
                       , std::uint32_t                   width
                       , std::uint32_t                   height
                       , surface_format                  format) noexcept
        : texture        { device }
        , _format        { format }
        , _mipmap_levels { 0 }
        , _height        { height }
        , _width         { width }
        , _sampler       { }
    {
    }

    texture2d::~texture2d()
    {
        if (_graphics_device != nullptr)
        {
            _graphics_device->destroy(_sampler);
        }

        _graphics_device = nullptr;
    }

    std::uint32_t texture2d::id() const noexcept
    {
        return 0;
    }

    surface_format texture2d::format() const noexcept
    {
        return _format;
    }

    std::uint32_t texture2d::level_count() const noexcept
    {
        return _mipmap_levels;
    }

    std::uint32_t texture2d::width() const noexcept
    {
        return _width;
    }

    std::uint32_t texture2d::height() const noexcept
    {
        return _height;
    }

    const vk::Sampler& texture2d::sampler() const noexcept
    {
        return _sampler;
    }

//    void texture2d::set_data([[maybe_unused]] std::uint32_t level
//                           , [[maybe_unused]] std::uint32_t width
//                           , [[maybe_unused]] std::uint32_t height
//                           , [[maybe_unused]] const gsl::span<const std::uint8_t>& data) const noexcept
//    {
//    }
}
