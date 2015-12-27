// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "AccessorReader.hpp"

#include <json11.hpp>

#include "SceneR/Content/ContentReader.hpp"
#include "SceneR/Content/Readers/AttributeType.hpp"
#include "SceneR/Graphics/ComponentType.hpp"

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Content::Accessor;
        using SceneR::Content::AttributeType;
        using SceneR::Content::BufferView;
        using SceneR::Graphics::ComponentType;

        std::shared_ptr<Accessor> ContentTypeReader<Accessor>::read(gsl::not_null<ContentReader*>       input
                                                                  , const std::pair<std::string, Json>& source) const
        {
            auto accessor = std::make_shared<Accessor>();
            auto attType  = source.second["type"].string_value();

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

            accessor->_name            = source.first;
            accessor->_component_type  = static_cast<ComponentType>(source.second["componentType"].int_value());
            accessor->_byte_offset     = source.second["byteOffset"].int_value();
            accessor->_byte_stride     = source.second["byteStride"].int_value();
            accessor->_attribute_count = source.second["count"].int_value();
            accessor->_buffer_view     = input->read_object<BufferView>(source.second["bufferView"].string_value());
            accessor->_byte_length     = accessor->_attribute_count
                                       * accessor->get_attribute_type_count()
                                       * accessor->get_component_size_in_bytes();

            for (const auto& item : source.second["max"].array_items())
            {
                accessor->_max.push_back(item.number_value());
            }
            for (const auto& item : source.second["min"].array_items())
            {
                accessor->_min.push_back(item.number_value());
            }

            return accessor;
        }
    }
}
