// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/gltf/accessor.hpp"

#include "scener/content/gltf/buffer_view.hpp"

namespace scener::content::gltf
{
    using scener::content::gltf::attribute_type;
    using scener::content::gltf::component_type;

    accessor::accessor() noexcept
        : _attribute_type  { attribute_type::scalar }
        , _attribute_count { 0 }
        , _buffer_view     { nullptr }
        , _byte_offset     { 0 }
        , _byte_length     { 0 }
        , _byte_stride     { 0 }
        , _component_type  { component_type::single }
        , _max             { 0 }
        , _min             { 0 }
        , _name            { }
    {
    }

    attribute_type accessor::attribute_type() const noexcept
    {
        return _attribute_type;
    }

    component_type accessor::component_type() const noexcept
    {
        return _component_type;
    }

    std::size_t accessor::byte_offset() const noexcept
    {
        return _byte_offset;
    }

    std::size_t accessor::byte_length() const noexcept
    {
        return _byte_length;
    }

    std::size_t accessor::byte_stride() const noexcept
    {
        return ((_byte_stride > 0) ? _byte_stride : get_attribute_type_count() * get_component_size_in_bytes());
    }

    std::size_t accessor::attribute_count() const noexcept
    {
        return _attribute_count;
    }

    const std::vector<float>& accessor::max() const noexcept
    {
        return _max;
    }

    const std::vector<float>& accessor::min() const noexcept
    {
        return _min;
    }

    const std::string& accessor::name() const noexcept
    {
        return _name;
    }

    gsl::span<const std::uint8_t> accessor::get_data() const noexcept
    {
        return get_data(0, _attribute_count);
    }

    gsl::span<const std::uint8_t> accessor::get_data(std::size_t offset, std::size_t count) const noexcept
    {
        return _buffer_view->get_data(_byte_offset + (offset * byte_stride()), count * byte_stride());
    }
}
