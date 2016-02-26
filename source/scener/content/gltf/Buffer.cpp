// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/gltf/Buffer.hpp"

namespace scener { namespace content { namespace gltf {

const std::string& Buffer::name() const noexcept
{
    return _name;
}

const std::string& Buffer::uri() const noexcept
{
    return _uri;
}

std::size_t Buffer::byte_length() const noexcept
{
    return _byte_length;
}

gsl::span<const std::uint8_t> Buffer::get_data(std::size_t offset, std::size_t count) const noexcept
{
    Expects(offset < _data.size() && (offset + count) <= _data.size());

    return gsl::span<const std::uint8_t>(_data.data() + offset, static_cast<std::ptrdiff_t>(count));
}

void Buffer::set_data(const std::vector<std::uint8_t>& buffer) noexcept
{
    Expects(buffer.size() == _byte_length);

    _data = buffer;
}

}}}
