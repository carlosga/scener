// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/vulkan/shader.hpp"

#include <cmath>

namespace scener::graphics::vulkan
{
    shader::shader(const std::string& name, shader_stage stage, const std::vector<std::uint8_t>& buffer) noexcept
        : _name        { name }
        , _entry_point { "main" }
        , _stage       { stage }
        , _buffer      { buffer }
    {
    }

    const std::string& shader::name() const noexcept
    {
        return _name;
    }

    const std::string& shader::entry_point() const noexcept
    {
        return _entry_point;
    }

    shader_stage shader::stage() const noexcept
    {
        return _stage;
    }

    const std::vector<uint8_t>& shader::buffer() const noexcept
    {
        return _buffer;
    }
}
