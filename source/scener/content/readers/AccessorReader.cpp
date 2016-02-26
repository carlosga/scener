// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/AccessorReader.hpp"

#include <json11.hpp>

#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/accessor.hpp"

namespace scener { namespace content { namespace readers {

using json11::Json;
using scener::content::gltf::AttributeType;
using scener::content::gltf::buffer_view;
using scener::graphics::ComponentType;

auto ContentTypeReader<gltf::accessor>::read(content_reader* input, const std::string& key, const Json& source) const noexcept
{
    auto        accessor = std::make_shared<gltf::accessor>();
    const auto& attType  = source["type"].string_value();

    if (attType == "SCALAR")
    {
        accessor->_attribute_type = AttributeType::scalar;
    }
    else if (attType == "VEC2")
    {
        accessor->_attribute_type = AttributeType::vector2;
    }
    else if (attType == "VEC3")
    {
        accessor->_attribute_type = AttributeType::vector3;
    }
    else if (attType == "VEC4")
    {
        accessor->_attribute_type = AttributeType::vector4;
    }
    else if (attType == "MAT2")
    {
        accessor->_attribute_type = AttributeType::matrix2;
    }
    else if (attType == "MAT3")
    {
        accessor->_attribute_type = AttributeType::matrix3;
    }
    else if (attType == "MAT4")
    {
        accessor->_attribute_type = AttributeType::matrix4;
    }

    accessor->_name            = key;
    accessor->_component_type  = static_cast<ComponentType>(source["componentType"].int_value());
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
