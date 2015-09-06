// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/MeshesReader.hpp>

#include <iostream>

#include <Content/json11.hpp>
#include <Graphics/Accessor.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/Material.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/ModelMeshPart.hpp>
#include <Graphics/PrimitiveType.hpp>
#include <System/Text/Encoding.hpp>

namespace SceneR
{
    namespace Content
    {
        using SceneR::Graphics::Accessor;
        using SceneR::Graphics::GraphicsDevice;
        using SceneR::Graphics::Material;
        using SceneR::Graphics::Model;
        using SceneR::Graphics::ModelMesh;
        using SceneR::Graphics::ModelMeshPart;
        using SceneR::Graphics::PrimitiveType;
        using System::Text::Encoding;
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

                for (const auto& source : item.second["primitives"].array_items())
                {
                    mesh->_mesh_parts.push_back(read_mesh_part(root, source));
                }

                mesh->_name = Encoding::convert(item.first);
                root->_meshes.push_back(mesh);
            }
        }

        std::shared_ptr<ModelMeshPart> MeshesReader::read_mesh_part(const Model* root, const Json& source) const
        {
            auto meshPart = std::__1::make_shared<ModelMeshPart>();
            auto indices  = Encoding::convert(source["indices"].string_value());
            auto material = Encoding::convert(source["material"].string_value());

            meshPart->_indices  = root->find_accessor(indices);
            meshPart->_material = root->find_material(material);
            meshPart->_type     = static_cast<PrimitiveType>(source["primitive"].int_value());

            for (const auto& attribute : source["attributes"].object_items())
            {
                read_mesh_part_attribute(attribute, root, meshPart);
            }

            return meshPart;
        }

        void MeshesReader::read_mesh_part_attribute(std::pair<std::string, json11::Json> attribute
                                                  , const Model*                         root
                                                  , std::shared_ptr<ModelMeshPart>       meshPart) const
        {
            auto name     = Encoding::convert(attribute.second.string_value());
            auto accessor = root->find_accessor(name);

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
                std::__1::cout << "unknown attribute [" << attribute.first << "]" << std::__1::endl;
            }
        }
    }
}
