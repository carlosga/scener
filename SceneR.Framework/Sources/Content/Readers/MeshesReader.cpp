// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/MeshesReader.hpp>

#include <System/IO/BinaryReader.hpp>
#include <GLTF/Model.hpp>
#include <Content/json11.hpp>

namespace SceneR
{
    namespace Content
    {
        using System::IO::BinaryReader;
        using SceneR::GLTF::Accessor;
        using SceneR::GLTF::Buffer;
        using SceneR::GLTF::BufferView;
        using SceneR::GLTF::BufferViewTarget;
        using SceneR::GLTF::ModelMesh;
        using SceneR::GLTF::ModelMeshPart;
        using SceneR::Graphics::PrimitiveType;
        using json11::Json;

        MeshesReader::MeshesReader()
        {
        }

        MeshesReader::~MeshesReader()
        {
        }

        void MeshesReader::Read(const json11::Json&       value
                              , System::IO::BinaryReader& reader
                              , SceneR::GLTF::Model*      root)
        {
            for (const auto& item : value["meshes"].object_items())
            {
                auto mesh = std::make_shared<ModelMesh>();

                for (const auto& primitiveItem : item.second["primitives"].array_items())
                {
                    auto meshPart = std::make_shared<ModelMeshPart>();

                    for (const auto& primitiveAttribute : primitiveItem["attributes"].object_items())
                    {
                        auto accessor = root->accessors[primitiveAttribute.second.string_value()];

                        meshPart->attributes[primitiveAttribute.first] = accessor;
                    }

                    meshPart->indices  = root->accessors[primitiveItem["indices"].string_value()];
                    meshPart->material = root->materials[primitiveItem["material"].string_value()];

                    int primitiveType = primitiveItem["primitive"].int_value();

                    if (primitiveType == 0)         // 0 (POINTS)
                    {
                        meshPart->type = PrimitiveType::PointList;
                    }
                    else if (primitiveType == 1)    // 1 (LINES)
                    {
                        meshPart->type = PrimitiveType::LineList;
                    }
                    else if (primitiveType == 2)    // 2 (LINE_LOOP)
                    {
                        meshPart->type = PrimitiveType::LineLoop;
                    }
                    else if (primitiveType == 3)    // 3 (LINE_STRIP)
                    {
                        meshPart->type = PrimitiveType::LineStrip;
                    }
                    else if (primitiveType == 5)    // 5 (TRIANGLE_STRIP)
                    {
                        meshPart->type = PrimitiveType::TriangleStrip;
                    }
                    else if (primitiveType == 6)    // 6 (TRIANGLE_FAN)
                    {
                        meshPart->type = PrimitiveType::TriangleStrip;
                    }
                    else                            // 4 (TRIANGLES)
                    {
                        meshPart->type = PrimitiveType::LineStrip;
                    }

                    mesh->meshParts.push_back(meshPart);
                }

                root->meshes[item.first] = mesh;
            }
        }
    }
}