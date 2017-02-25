// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/gltf/buffer_view.hpp"

#include "scener/content/gltf/buffer.hpp"

namespace scener::content::gltf
{
    std::size_t buffer_view::byte_offset() const noexcept
    {
        return _byte_offset;
    }

    std::size_t buffer_view::byte_length() const noexcept
    {
        return _byte_length;
    }

    const std::string& buffer_view::name() const noexcept
    {
        return _name;
    }

    gsl::span<const std::uint8_t> buffer_view::get_data() const noexcept
    {
        return get_data(0, _byte_length);
    }

    gsl::span<const std::uint8_t> buffer_view::get_data(std::size_t offset, std::size_t count) const noexcept
    {
        return _buffer->get_data(_byte_offset + offset, count);
    }
}
