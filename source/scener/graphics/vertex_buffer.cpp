// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/vertex_buffer.hpp"

#include "scener/graphics/graphics_device.hpp"

namespace scener::graphics
{
    using scener::graphics::vulkan::buffer;

    vertex_buffer::vertex_buffer(gsl::not_null<graphics_device*>      device
                               , const graphics::vertex_declaration&  vertex_declaration
                               , std::uint32_t                        vertex_count
                               , const gsl::span<const std::uint8_t>& data) noexcept
        : graphics_resource   { device }
        , _vertex_count       { vertex_count }
        , _vertex_declaration { vertex_declaration }
        , _buffer             { device->create_vertex_buffer(data) }
    {
    }

    std::uint32_t vertex_buffer::vertex_count() const noexcept
    {
        return _vertex_count;
    }

    std::vector<std::uint8_t> vertex_buffer::get_data() const noexcept
    {
        return get_data(0, _vertex_count);
    }

    std::vector<std::uint8_t> vertex_buffer::get_data(std::uint32_t start_index, std::uint32_t element_count) const noexcept
    {
        auto offset = (start_index   * _vertex_declaration.vertex_stride());
        auto size   = (element_count * _vertex_declaration.vertex_stride());

        return _buffer.get_data(offset, size);
    }

    void vertex_buffer::set_data(const gsl::span<const std::uint8_t>& data) noexcept
    {
        // std::uint64_t size = _vertex_count * _vertex_declaration.vertex_stride();

        _buffer.set_data(0, static_cast<std::uint64_t>(data.size()), data.data());
    }

    const vertex_declaration& vertex_buffer::vertex_declaration() const noexcept
    {
        return _vertex_declaration;
    }
}
