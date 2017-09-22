// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/vulkan/shader_module.hpp"

namespace scener::graphics::vulkan
{
    shader_module::shader_module()
    {
    }

    vulkan::constant_buffer* shader_module::constant_buffer() const noexcept
    {
        return _constant_buffer.get();
    }

    void shader_module::add_shader(const std::shared_ptr<shader> shader) noexcept
    {
    }

    std::map<std::string, std::size_t> shader_module::query_uniform_offsets() const noexcept
    {
        std::map<std::string, std::size_t> uniforms;

        return uniforms;
    }
}
