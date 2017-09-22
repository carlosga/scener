// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/vulkan/constant_buffer.hpp"

#include "scener/graphics/vulkan/buffer_target.hpp"

namespace scener::graphics::vulkan
{
    constant_buffer::constant_buffer(const std::string& name, std::uint32_t program_id) noexcept
        : _buffer_object { buffer_target::uniform_buffer }
        , _index         { 0 }
        , _binding_point { 0 }
        , _size          { 0 }
        , _name          { name }
    {
    }

    std::uint32_t constant_buffer::binding_point() const noexcept
    {
        return _binding_point;
    }

    std::uint32_t constant_buffer::index() const noexcept
    {
        return _index;
    }

    std::size_t constant_buffer::size() const noexcept
    {
        return _size;
    }

    std::vector<std::uint8_t> constant_buffer::get_data() const noexcept
    {
        return get_data(0, _size);
    }

    std::vector<std::uint8_t> constant_buffer::get_data(std::size_t offset, std::size_t count) const noexcept
    {
        Ensures(count <= _size);

        return _buffer_object.get_data(offset, count);
    }

    void constant_buffer::set_data(gsl::not_null<const void*> data) const noexcept
    {
        set_data(0, _size, data);
    }

    void constant_buffer::set_data(std::size_t offset, std::size_t count, gsl::not_null<const void*> data) const noexcept
    {
        Ensures((offset + count) <= _size);

        _buffer_object.set_data(offset, count, data);
    }
}
