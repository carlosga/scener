// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/AccessorsReader.hpp>

#include <algorithm>

#include <Content/json11.hpp>
#include <Graphics/Accessor.hpp>
#include <Graphics/AttributeType.hpp>
#include <Graphics/ComponentType.hpp>
#include <System/Text/Encoding.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Graphics::Accessor;
        using SceneR::Graphics::AttributeType;
        using SceneR::Graphics::ComponentType;
        using System::Text::Encoding;

        AccessorsReader::AccessorsReader()
        {
        }

        AccessorsReader::~AccessorsReader()
        {

        }

        void AccessorsReader::read(const Json& value, ContentReaderContext& context)
        {
            for (const auto& source : value["accessors"].object_items())
            {
                auto accessor = std::make_shared<Accessor>();
                auto viewName = Encoding::convert(source.second["bufferView"].string_value());
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

                accessor->_name            = Encoding::convert(source.first);
                accessor->_buffer_view     = context.find_buffer_view(viewName);
                accessor->_component_type  = static_cast<ComponentType>(source.second["componentType"].int_value());
                accessor->_byte_offset     = source.second["byteOffset"].int_value();
                accessor->_byte_stride     = source.second["byteStride"].int_value();
                accessor->_attribute_count = source.second["count"].int_value();
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

                context.accessors.push_back(accessor);
            }
        }
    }
}
