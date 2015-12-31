// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/Readers/AccessorReader.hpp"

#include <json11.hpp>

#include "SceneR/Content/ContentReader.hpp"
#include "SceneR/Content/GLTF/Accessor.hpp"
#include "SceneR/Content/GLTF/AttributeType.hpp"
#include "SceneR/Graphics/ComponentType.hpp"

namespace SceneR { namespace Content { namespace Readers {

using json11::Json;
using SceneR::Content::GLTF::Accessor;
using SceneR::Content::GLTF::AttributeType;
using SceneR::Content::GLTF::BufferView;
using SceneR::Graphics::ComponentType;

auto ContentTypeReader<Accessor>::read(ContentReader* input, const std::string& key, const Json& source) const
{
    auto accessor = std::make_shared<Accessor>();
    auto attType  = source["type"].string_value();

    if (attType == "SCALAR")
    {
        accessor->_attribute_type = AttributeType::Scalar;
    }
    else if (attType == "VEC2")
    {
        accessor->_attribute_type = AttributeType::Vector2;
    }
    else if (attType == "VEC3")
    {
        accessor->_attribute_type = AttributeType::Vector3;
    }
    else if (attType == "VEC4")
    {
        accessor->_attribute_type = AttributeType::Vector4;
    }
    else if (attType == "MAT2")
    {
        accessor->_attribute_type = AttributeType::Matrix2;
    }
    else if (attType == "MAT3")
    {
        accessor->_attribute_type = AttributeType::Matrix3;
    }
    else if (attType == "MAT4")
    {
        accessor->_attribute_type = AttributeType::Matrix4;
    }

    accessor->_name            = key;
    accessor->_component_type  = static_cast<ComponentType>(source["componentType"].int_value());
    accessor->_byte_offset     = source["byteOffset"].int_value();
    accessor->_byte_stride     = source["byteStride"].int_value();
    accessor->_attribute_count = source["count"].int_value();
    accessor->_buffer_view     = input->read_object<BufferView>(source["bufferView"].string_value());
    accessor->_byte_length     = accessor->_attribute_count
                               * accessor->get_attribute_type_count()
                               * accessor->get_component_size_in_bytes();

    for (const auto& item : source["max"].array_items())
    {
        accessor->_max.push_back(item.number_value());
    }
    for (const auto& item : source["min"].array_items())
    {
        accessor->_min.push_back(item.number_value());
    }

    return accessor;
}

}}}
