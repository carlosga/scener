// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/GLTF/Buffer.hpp"

namespace SceneR { namespace Content { namespace GLTF {

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

gsl::span<std::uint8_t> Buffer::get_data(std::size_t offset, std::size_t count) const noexcept
{
    return _data_view.subspan(offset, count);
}

void Buffer::set_data(std::vector<std::uint8_t>&& buffer) noexcept
{
    _data      = std::move(buffer);
    _data_view = gsl::as_span(_data.data(), _data.size());
}

}}}
