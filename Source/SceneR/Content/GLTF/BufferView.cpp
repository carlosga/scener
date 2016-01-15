// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/GLTF/BufferView.hpp"

#include "SceneR/Content/GLTF/Buffer.hpp"

namespace SceneR { namespace Content { namespace GLTF {

std::size_t BufferView::byte_offset() const noexcept
{
    return _byte_offset;
}

std::size_t BufferView::byte_length() const noexcept
{
    return _byte_length;
}

const std::string& BufferView::name() const noexcept
{
    return _name;
}

gsl::span<const std::uint8_t> BufferView::get_data() const noexcept
{
    return get_data(0, _byte_length);
}

gsl::span<const std::uint8_t> BufferView::get_data(std::size_t offset, std::size_t count) const noexcept
{
    return _buffer->get_data(_byte_offset + offset, count);
}

}}}
