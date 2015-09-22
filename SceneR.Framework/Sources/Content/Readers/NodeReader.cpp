// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/NodeReader.hpp>

#include <json11.hpp>
#include <Content/ContentReader.hpp>
#include <Graphics/Accessor.hpp>
#include <Graphics/ModelBone.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/ModelSkin.hpp>
#include <System/IO/MemoryStream.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Framework::Matrix;
        using SceneR::Framework::Quaternion;
        using SceneR::Framework::Vector3;
        using SceneR::Graphics::Accessor;
        using SceneR::Graphics::ModelBone;
        using SceneR::Graphics::ModelMesh;
        using SceneR::Graphics::ModelSkin;
        using SceneR::Graphics::Node;
        using System::IO::BinaryReader;
        using System::IO::MemoryStream;

        std::shared_ptr<Node> ContentTypeReader<Node>::read(ContentReader*                      input
                                                          , const std::pair<std::string, Json>& source)
        {
            auto node = std::make_shared<Node>();

            node->name        = source.first;
            node->camera      = source.second["camera"].string_value();
            node->light       = source.second["light"].string_value();
            node->matrix      = Matrix::identity;
            node->rotation    = Quaternion::identity;
            node->scale       = Vector3::one;
            node->translation = Vector3::zero;

            if (!source.second["matrix"].is_null())
            {
                node->matrix = input->convert<Matrix>(source.second["matrix"].array_items());
            }
            else
            {
                if (!source.second["rotation"].is_null())
                {
                    node->rotation = input->convert<Quaternion>(source.second["rotation"].array_items());
                }
                if (!source.second["scale"].is_null())
                {
                    node->scale = input->convert<Vector3>(source.second["scale"].array_items());
                }
                if (!source.second["translation"].is_null())
                {
                    node->translation = input->convert<Vector3>(source.second["translation"].array_items());
                }
            }

            if (!source.second["jointName"].is_null())
            {
                node->joint = std::make_shared<ModelBone>();

                node->joint->_name = source.second["jointName"].string_value();

                if (!source.second["matrix"].is_null())
                {
                    node->joint->_transform = node->matrix;
                }
                else
                {
                    // rotation * translation * scale
                    node->joint->_transform = Matrix::transform(node->matrix, node->rotation)
                                            * Matrix::create_translation(node->translation)
                                            * Matrix::create_scale(node->scale);
                }

                for (const auto& child : source.second["children"].array_items())
                {
                    auto childNode = input->read_object<Node>("nodes", child.string_value());

                    childNode->joint->_parent = node->joint;

                    node->joint->_children.push_back(childNode->joint);
                    node->children.push_back(childNode);
                }
            }
            else
            {
                for (const auto& child : source.second["children"].array_items())
                {
                    node->children.push_back(input->read_object<Node>("nodes", child.string_value()));
                }
            }

            for (const auto& mesh : source.second["meshes"].array_items())
            {
                node->meshes.push_back(input->read_object<ModelMesh>("meshes", mesh.string_value()));
            }

            if (!source.second["instanceSkin"].is_null())
            {
                node->instance_skin = read_instance_skin(input, source.second["instanceSkin"]);
            }

            return node;
        }

        std::shared_ptr<ModelSkin> ContentTypeReader<Node>::read_instance_skin(ContentReader* input, const Json& source)
        {
            auto skin     = std::make_shared<ModelSkin>();
            auto skinRef  = input->_root["skins"][source["skin"].string_value()];
            auto accessor = input->read_object<Accessor>("accessors", skinRef["inverseBindMatrices"].string_value());

            MemoryStream stream(accessor->get_data());
            BinaryReader reader(stream);

            // Bind shape matrix
            skin->_bindShapeMatrix = input->convert<Matrix>(skinRef["bindShapeMatrix"].array_items());

            // Inverse bind matrices
            for (std::size_t i = 0; i < accessor->attribute_count(); i++)
            {
                Matrix matrix = { reader.read<float>(), reader.read<float>(), reader.read<float>(), reader.read<float>()
                                , reader.read<float>(), reader.read<float>(), reader.read<float>(), reader.read<float>()
                                , reader.read<float>(), reader.read<float>(), reader.read<float>(), reader.read<float>()
                                , reader.read<float>(), reader.read<float>(), reader.read<float>(), reader.read<float>() };

                skin->_inverseBindMatrices.push_back(Matrix::transpose(matrix));
            }

            // Skeleton roots
            for (const auto& skeleton : source["skeletons"].array_items())
            {
                auto node = input->read_object<Node>("nodes", skeleton.string_value());

                skin->_skeletons.push_back(node->joint);
            }

            // Joints
            for (const auto& jointName : skinRef["jointNames"].array_items())
            {
                auto node = input->read_object<Node>("nodes", jointName.string_value());

                skin->_joints.push_back(node->joint);
            }

            // The meshes for the skin instance
            for (const auto& meshRef : source["meshes"].array_items())
            {
                auto mesh = input->read_object<ModelMesh>("meshes", meshRef.string_value());

                mesh->_skin = skin;
            }

            return skin;
        }
    }
}
