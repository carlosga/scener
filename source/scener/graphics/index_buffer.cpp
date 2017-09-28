// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/index_buffer.hpp"

#include "scener/graphics/graphics_device.hpp"

namespace scener::graphics
{
    index_buffer::index_buffer(gsl::not_null<graphics_device*> device
                             , component_type                  index_element_type
                             , std::size_t                     index_count) noexcept
        : graphics_resource   { device }
        , _index_element_type { index_element_type }
        , _index_count        { index_count }
        , _buffer             { nullptr }
    {
    }

    std::size_t index_buffer::index_count() const noexcept
    {
        return _index_count;
    }

    component_type index_buffer::index_element_type() const noexcept
    {
        return _index_element_type;
    }

    std::size_t index_buffer::element_size_in_bytes() const noexcept
    {
        switch (_index_element_type)
        {
        case component_type::byte:
        case component_type::ubyte:
            return sizeof(std::uint8_t);
        case component_type::int16:
        case component_type::uint16:
            return sizeof(std::uint16_t);
        case component_type::single:
            return sizeof(float);
        default:
            throw std::runtime_error("Unknown component type.");
        }
    }

    std::vector<std::uint8_t> index_buffer::get_data() const noexcept
    {
        return get_data(0, _index_count);
    }

    std::vector<std::uint8_t> index_buffer::get_data(std::size_t start_index, std::size_t element_count) const noexcept
    {
        if (_buffer.get() == nullptr)
        {
            return { };
        }

        auto offset = (start_index * element_size_in_bytes());
        auto size   = (element_count * element_size_in_bytes());

        return _buffer->get_data(offset, size);
    }

    void index_buffer::set_data(const gsl::span<const std::uint8_t>& data) noexcept
    {
        if (_buffer.get() == nullptr)
        {
            _buffer = device()->create_index_buffer(data);
        }
        else
        {
            _buffer->set_data(data);
        }
    }
}
