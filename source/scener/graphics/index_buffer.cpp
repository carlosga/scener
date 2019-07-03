// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/index_buffer.hpp"

#include "scener/graphics/graphics_device.hpp"

namespace scener::graphics
{
    index_buffer::index_buffer(gsl::not_null<graphics_device*> device, std::uint32_t index_count) noexcept
        : index_buffer(device, index_type::uint16, index_count)
    {
    }

    index_buffer::index_buffer(gsl::not_null<graphics_device*> device
                             , index_type                      index_element_type
                             , std::uint32_t                   index_count) noexcept
        : graphics_resource   { device }
        , _index_element_type { index_element_type }
        , _index_count        { index_count }
        , _buffer             { nullptr }
    {
    }

    std::uint32_t index_buffer::index_count() const noexcept
    {
        return _index_count;
    }

    index_type index_buffer::index_element_type() const noexcept
    {
        return _index_element_type;
    }

    std::uint32_t index_buffer::element_size_in_bytes() const noexcept
    {
        switch (_index_element_type)
        {
        case index_type::uint16:
            return sizeof(std::uint16_t);
        case index_type::uint32:
            return sizeof(std::uint32_t);
        default:
            throw std::runtime_error("Unknown index element type.");
        }
    }

    std::vector<std::uint8_t> index_buffer::get_data() const noexcept
    {
        return get_data(0, _index_count);
    }

    std::vector<std::uint8_t> index_buffer::get_data(std::uint32_t start_index, std::uint32_t element_count) const noexcept
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
