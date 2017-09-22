// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/vulkan/buffer.hpp"

namespace scener::graphics::vulkan
{
    buffer::buffer(buffer_target target) noexcept
        : _id     { 0 }
        , _target { target }
    {
    }

    std::uint32_t buffer::id() const noexcept
    {
        return _id;
    }

    buffer_target buffer::target() const noexcept
    {
        return _target;
    }

    std::vector<std::uint8_t> buffer::get_data(std::size_t offset, std::size_t count) const noexcept
    {
        auto data = std::vector<std::uint8_t>(count, 0);

        // glGetNamedBufferSubData(_id, static_cast<GLintptr>(offset), static_cast<GLintptr>(count), data.data());

        return data;
    }

    void buffer::set_data(std::size_t count, gsl::not_null<const void*> data) const noexcept
    {
    }

    void buffer::set_data(std::size_t offset, std::size_t count, gsl::not_null<const void*> data) const noexcept
    {
    }

    void buffer::invalidate() const noexcept
    {
    }

    void buffer::invalidate(std::size_t offset, const std::size_t count) const noexcept
    {
    }
}
