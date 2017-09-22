// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/vulkan/shader.hpp"

namespace scener::graphics::vulkan
{
    shader::shader(const std::string& name, shader_stage stage, std::vector<std::uint8_t>&& buffer) noexcept
        : _name   { name }
        , _stage  { stage }
        , _buffer { std::move(buffer)}
    {
    }

    const std::string& shader::name() const noexcept
    {
        return _name;
    }

    shader_stage shader::stage() const noexcept
    {
        return _stage;
    }

    const std::vector<std::uint8_t>& shader::buffer() const noexcept
    {
        return _buffer;
    }
}
