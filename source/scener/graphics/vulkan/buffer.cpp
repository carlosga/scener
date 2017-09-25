// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/vulkan/buffer.hpp"

namespace scener::graphics::vulkan
{
    buffer::buffer(buffer_usage      usage
                 , std::size_t       size
                 , const vk::Buffer& buffer
                 , const std::any&   allocation) noexcept
        : _usage      { usage }
        , _size       { size }
        , _buffer     { buffer }
        , _allocation { allocation }
    {
    }

    const vk::Buffer& buffer::handle() const noexcept
    {
        return _buffer;
    }

    const std::any& buffer::allocation() const noexcept
    {
        return _allocation;
    }

    buffer_usage buffer::usage() const noexcept
    {
        return _usage;
    }

    std::vector<std::uint8_t> buffer::get_data(std::size_t offset, std::size_t count) const noexcept
    {
        auto data = std::vector<std::uint8_t>(count, 0);

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
