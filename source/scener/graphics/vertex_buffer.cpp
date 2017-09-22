// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/vertex_buffer.hpp"

#include "scener/graphics/graphics_device.hpp"
#include "scener/graphics/vulkan/buffer_target.hpp"

namespace scener::graphics
{
    using scener::graphics::vulkan::buffer;
    using scener::graphics::vulkan::buffer_target;

    vertex_buffer::vertex_buffer(gsl::not_null<graphics_device*>     device
                               , std::size_t                         vertex_count
                               , const graphics::vertex_declaration& vertex_declaration) noexcept
        : graphics_resource   { device }
        , _binding_index      { 0 }
        , _vertex_count       { vertex_count }
        , _vertex_declaration { vertex_declaration }
        , _buffer             { buffer_target::vertex_buffer }
    {
    }

    std::size_t vertex_buffer::vertex_count() const noexcept
    {
        return _vertex_count;
    }

    std::vector<std::uint8_t> vertex_buffer::get_data() const noexcept
    {
        return get_data(0, _vertex_count);
    }

    std::vector<std::uint8_t> vertex_buffer::get_data(std::size_t start_index, std::size_t element_count) const noexcept
    {
        auto offset = (start_index   * _vertex_declaration.vertex_stride());
        auto size   = (element_count * _vertex_declaration.vertex_stride());

        return _buffer.get_data(offset, size);
    }

    void vertex_buffer::set_data(const gsl::span<const std::uint8_t>& data) const noexcept
    {
        _buffer.set_data(_vertex_count * _vertex_declaration.vertex_stride(), data.data());
    }

    const vertex_declaration& vertex_buffer::vertex_declaration() const noexcept
    {
        return _vertex_declaration;
    }

    void vertex_buffer::bind() noexcept
    {
    }

    void vertex_buffer::unbind() noexcept
    {
    }
}
