// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/MeshesReader.hpp>

#include <iostream>

#include <Content/json11.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/ModelMeshPart.hpp>
#include <Graphics/PrimitiveType.hpp>

namespace SceneR
{
    namespace Content
    {
        using SceneR::Graphics::GraphicsDevice;
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

        void MeshesReader::read(const json11::Json&               value
                              , SceneR::Graphics::GraphicsDevice& graphicsDevice
                              , SceneR::Graphics::Model*          root)
        {
            for (const auto& item : value["meshes"].object_items())
            {
                auto mesh = std::make_shared<ModelMesh>();

                for (const auto& primitiveItem : item.second["primitives"].array_items())
                {
                    auto meshPart = std::make_shared<ModelMeshPart>();

                    meshPart->_indices  = root->_accessors[primitiveItem["indices"].string_value()];
                    meshPart->_material = root->_materials[primitiveItem["material"].string_value()];
                    meshPart->_type     = static_cast<PrimitiveType>(primitiveItem["primitive"].int_value());

                    for (const auto& attribute : primitiveItem["attributes"].object_items())
                    {
                        auto accessor = root->_accessors[attribute.second.string_value()];

                        if (attribute.first == "JOINT")
                        {
                            meshPart->_joint = accessor;
                        }
                        else if (attribute.first == "NORMAL")
                        {
                            meshPart->_normal = accessor;
                        }
                        else if (attribute.first == "POSITION")
                        {
                            meshPart->_position = accessor;
                        }
                        else if (attribute.first == "TEXBINORMAL")
                        {
                            meshPart->_textureBinormal = accessor;
                        }
                        else if (attribute.first == "TEXCOORD_0")
                        {
                            meshPart->_textureCoordinates = accessor;
                        }
                        else if (attribute.first == "TEXCOORD_0")
                        {
                            meshPart->_textureCoordinates = accessor;
                        }
                        else if (attribute.first == "TEXTANGENT")
                        {
                            meshPart->_textureTangent = accessor;
                        }
                        else if (attribute.first == "WEIGHT")
                        {
                            meshPart->_weight = accessor;
                        }
                        else
                        {
                            std::cout << "unknown attribute [" << attribute.first << "]" << std::endl;
                        }
                    }

                    mesh->_mesh_parts.push_back(meshPart);
                }

                root->_meshes[item.first] = mesh;
            }
        }
    }
}
