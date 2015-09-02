// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/AccessorsReader.hpp>

#include <System/IO/BinaryReader.hpp>
#include <Content/ContentReader.hpp>
#include <Content/json11.hpp>
#include <GLTF/Model.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::GLTF::Model;
        using SceneR::GLTF::Accessor;
        using SceneR::GLTF::AttributeType;
        using SceneR::GLTF::ComponentType;

        AccessorsReader::AccessorsReader()
        {
        }

        AccessorsReader::~AccessorsReader()
        {

        }

        void AccessorsReader::Read(const json11::Json&       value
                                 , System::IO::BinaryReader& reader
                                 , SceneR::GLTF::Model*      root)
        {
            for (const auto& item : value["accessors"].object_items())
            {
                auto accessor = std::make_shared<Accessor>();

                accessor->bufferView    = root->bufferViews[item.second["bufferView"].string_value()];
                accessor->byteOffset    = item.second["byteOffset"].int_value();
                accessor->byteStride    = item.second["byteStride"].int_value();
                accessor->componentType = static_cast<ComponentType>(item.second["componentType"].int_value());
                accessor->count         = item.second["count"].int_value();

                std::string attType = item.second["type"].string_value();

                if (attType == "SCALAR")
                {
                    accessor->type = AttributeType::Scalar;
                }
                else if (attType == "VEC2")
                {
                    accessor->type = AttributeType::Vector2;
                }
                else if (attType == "VEC3")
                {
                    accessor->type = AttributeType::Vector3;
                }
                else if (attType == "VEC4")
                {
                    accessor->type = AttributeType::Vector4;
                }
                else if (attType == "MAT2")
                {
                    accessor->type = AttributeType::Matrix2;
                }
                else if (attType == "MAT3")
                {
                    accessor->type = AttributeType::Matrix3;
                }
                else if (attType == "MAT4")
                {
                    accessor->type = AttributeType::Matrix4;
                }

                for (const auto& item : item.second["max"].array_items())
                {
                    accessor->max.push_back(item.number_value());
                }
                for (const auto& item : item.second["min"].array_items())
                {
                    accessor->min.push_back(item.number_value());
                }

                root->accessors.emplace(item.first, accessor);
            }
        }
    }
}
