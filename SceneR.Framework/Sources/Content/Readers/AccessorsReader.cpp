// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/AccessorsReader.hpp>

#include <Content/ContentReader.hpp>
#include <Content/json11.hpp>
#include <Graphics/Accessor.hpp>
#include <Graphics/AttributeType.hpp>
#include <Graphics/BufferView.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/ComponentType.hpp>
#include <Graphics/Model.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Graphics::Accessor;
        using SceneR::Graphics::AttributeType;
        using SceneR::Graphics::ComponentType;
        using SceneR::Graphics::GraphicsDevice;
        using SceneR::Graphics::Model;

        AccessorsReader::AccessorsReader()
        {
        }

        AccessorsReader::~AccessorsReader()
        {

        }

        void AccessorsReader::read(const json11::Json&               value
                                 , SceneR::Graphics::GraphicsDevice& graphicsDevice
                                 , SceneR::Graphics::Model*          root)
        {
            for (const auto& item : value["accessors"].object_items())
            {
                auto accessor = std::make_shared<Accessor>();

                accessor->_buffer_view    = root->_bufferViews[item.second["bufferView"].string_value()];
                accessor->_byte_offset    = item.second["byteOffset"].int_value();
                accessor->_byte_stride    = item.second["byteStride"].int_value();
                accessor->_component_type = static_cast<ComponentType>(item.second["componentType"].int_value());
                accessor->_count          = item.second["count"].int_value();

                std::string attType = item.second["type"].string_value();

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

                for (const auto& item : item.second["max"].array_items())
                {
                    accessor->_max.push_back(item.number_value());
                }
                for (const auto& item : item.second["min"].array_items())
                {
                    accessor->_min.push_back(item.number_value());
                }

                root->_accessors.emplace(item.first, accessor);
            }
        }
    }
}
