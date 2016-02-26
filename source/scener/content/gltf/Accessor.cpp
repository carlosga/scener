// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/GLTF/Accessor.hpp"

#include "SceneR/Content/GLTF/BufferView.hpp"

namespace scener { namespace content { namespace gltf {

using scener::graphics::ComponentType;

AttributeType Accessor::attribute_type() const noexcept
{
    return _attribute_type;
}

ComponentType Accessor::component_type() const noexcept
{
    return _component_type;
}

std::size_t Accessor::byte_offset() const noexcept
{
    return _byte_offset;
}

std::size_t Accessor::byte_length() const noexcept
{
    return _byte_length;
}

std::size_t Accessor::byte_stride() const noexcept
{
    return ((_byte_stride > 0) ? _byte_stride : get_attribute_type_count() * get_component_size_in_bytes());
}

std::size_t Accessor::attribute_count() const noexcept
{
    return _attribute_count;
}

const std::vector<float>& Accessor::max() const noexcept
{
    return _max;
}

const std::vector<float>& Accessor::min() const noexcept
{
    return _min;
}

const std::string& Accessor::name() const noexcept
{
    return _name;
}

gsl::span<const std::uint8_t> Accessor::get_data() const noexcept
{
    return get_data(0, _attribute_count);
}

gsl::span<const std::uint8_t> Accessor::get_data(std::size_t offset, std::size_t count) const noexcept
{
    return _buffer_view->get_data(_byte_offset + (offset * byte_stride()), count * byte_stride());
}

}}}
