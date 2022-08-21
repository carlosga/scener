// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/gltf/buffer.hpp"

namespace scener::content::gltf
{
    const std::string& buffer::name() const noexcept
    {
        return _name;
    }

    const std::string& buffer::uri() const noexcept
    {
        return _uri;
    }

    std::uint32_t buffer::byte_length() const noexcept
    {
        return _byte_length;
    }

    gsl::span<const std::uint8_t> buffer::get_data(std::uint32_t offset, std::uint32_t count) const noexcept
    {
        return _span.subspan(offset, count);
    }

    void buffer::set_data(const std::vector<std::uint8_t>& data) noexcept
    {
        Expects(data.size() == _byte_length);

        _data = data;
        _span = gsl::span<const std::uint8_t>(_data);
    }
}
