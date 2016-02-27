// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/accessor_reader.hpp"

#include <json11.hpp>

#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/accessor.hpp"

namespace scener { namespace content { namespace readers {

using json11::Json;
using scener::content::gltf::attribute_type;
using scener::content::gltf::buffer_view;
using scener::graphics::component_type;

auto content_type_reader<gltf::accessor>::read(content_reader* input, const std::string& key, const Json& source) const noexcept
{
    auto        accessor = std::make_shared<gltf::accessor>();
    const auto& type     = source["type"].string_value();

    if (type == "SCALAR")
    {
        accessor->_attribute_type = attribute_type::scalar;
    }
    else if (type == "VEC2")
    {
        accessor->_attribute_type = attribute_type::vector2;
    }
    else if (type == "VEC3")
    {
        accessor->_attribute_type = attribute_type::vector3;
    }
    else if (type == "VEC4")
    {
        accessor->_attribute_type = attribute_type::vector4;
    }
    else if (type == "MAT2")
    {
        accessor->_attribute_type = attribute_type::matrix2;
    }
    else if (type == "MAT3")
    {
        accessor->_attribute_type = attribute_type::matrix3;
    }
    else if (type == "MAT4")
    {
        accessor->_attribute_type = attribute_type::matrix4;
    }

    accessor->_name            = key;
    accessor->_component_type  = static_cast<component_type>(source["componentType"].int_value());
    accessor->_byte_offset     = static_cast<std::size_t>(source["byteOffset"].int_value());
    accessor->_byte_stride     = static_cast<std::size_t>(source["byteStride"].int_value());
    accessor->_attribute_count = static_cast<std::size_t>(source["count"].int_value());
    accessor->_buffer_view     = input->read_object<buffer_view>(source["bufferView"].string_value());
    accessor->_byte_length     = accessor->_attribute_count
                               * accessor->get_attribute_type_count()
                               * accessor->get_component_size_in_bytes();

    for (const auto& item : source["max"].array_items())
    {
        accessor->_max.push_back(static_cast<float>(item.number_value()));
    }
    for (const auto& item : source["min"].array_items())
    {
        accessor->_min.push_back(static_cast<float>(item.number_value()));
    }

    return accessor;
}

}}}
