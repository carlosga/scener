// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/MeshesReader.hpp>

#include <iostream>

#include <System/IO/BinaryReader.hpp>
#include <Content/json11.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/ModelMeshPart.hpp>
#include <Graphics/PrimitiveType.hpp>

namespace SceneR
{
    namespace Content
    {
        using System::IO::BinaryReader;
        using SceneR::Graphics::Model;
        using SceneR::Graphics::ModelMesh;
        using SceneR::Graphics::ModelMeshPart;
        using SceneR::Graphics::PrimitiveType;
        using json11::Json;

        MeshesReader::MeshesReader()
        {
        }

        MeshesReader::~MeshesReader()
        {
        }

        void MeshesReader::Read(const json11::Json& value, SceneR::Graphics::Model* root)
        {
            for (const auto& item : value["meshes"].object_items())
            {
                auto mesh = std::make_shared<ModelMesh>();

                for (const auto& primitiveItem : item.second["primitives"].array_items())
                {
                    auto meshPart = std::make_shared<ModelMeshPart>();

                    meshPart->indices  = root->accessors[primitiveItem["indices"].string_value()];
                    meshPart->material = root->materials[primitiveItem["material"].string_value()];
                    meshPart->type     = static_cast<PrimitiveType>(primitiveItem["primitive"].int_value());

                    for (const auto& attribute : primitiveItem["attributes"].object_items())
                    {
                        auto accessor = root->accessors[attribute.second.string_value()];

                        if (attribute.first == "JOINT")
                        {
                            meshPart->joint = accessor;
                        }
                        else if (attribute.first == "NORMAL")
                        {
                            meshPart->normal = accessor;
                        }
                        else if (attribute.first == "POSITION")
                        {
                            meshPart->position = accessor;
                        }
                        else if (attribute.first == "TEXBINORMAL")
                        {
                            meshPart->textureBinormal = accessor;
                        }
                        else if (attribute.first == "TEXCOORD_0")
                        {
                            meshPart->textureCoordinates = accessor;
                        }
                        else if (attribute.first == "TEXCOORD_0")
                        {
                            meshPart->textureCoordinates = accessor;
                        }
                        else if (attribute.first == "TEXTANGENT")
                        {
                            meshPart->textureTangent = accessor;
                        }
                        else if (attribute.first == "WEIGHT")
                        {
                            meshPart->weight = accessor;
                        }
                        else
                        {
                            std::cout << "unknown attribute [" << attribute.first << "]" << std::endl;
                        }
                    }

                    mesh->meshParts.push_back(meshPart);
                }

                root->meshes[item.first] = mesh;
            }
        }
    }
}
