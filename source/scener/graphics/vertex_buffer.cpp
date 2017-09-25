// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/vertex_buffer.hpp"

#include "scener/graphics/graphics_device.hpp"

namespace scener::graphics
{
    using scener::graphics::vulkan::buffer;

    vertex_buffer::vertex_buffer(gsl::not_null<graphics_device*>     device
                               , std::size_t                         vertex_count
                               , const graphics::vertex_declaration& vertex_declaration) noexcept
        : graphics_resource   { device }
        , _vertex_count       { vertex_count }
        , _vertex_declaration { vertex_declaration }
        , _buffer             { nullptr }
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
        if (_buffer.get() == nullptr)
        {
            return { };
        }

        auto offset = (start_index   * _vertex_declaration.vertex_stride());
        auto size   = (element_count * _vertex_declaration.vertex_stride());

        return _buffer->get_data(offset, size);
    }

    void vertex_buffer::set_data(const gsl::span<const std::uint8_t>& data) noexcept
    {
        auto size = _vertex_count * _vertex_declaration.vertex_stride();

        if (_buffer.get() == nullptr)
        {
            _buffer = device()->create_vertex_buffer(size);
        }

        _buffer->set_data(size, data.data());
    }

    const vertex_declaration& vertex_buffer::vertex_declaration() const noexcept
    {
        return _vertex_declaration;
    }
}
