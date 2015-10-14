// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/NodeReader.hpp>

#include <json11.hpp>
#include <Content/ContentReader.hpp>
#include <Graphics/Accessor.hpp>
#include <Graphics/ModelBone.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/Skeleton.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Framework::Matrix;
        using SceneR::Framework::Quaternion;
        using SceneR::Framework::Vector3;
        using SceneR::Framework::Vector4;
        using SceneR::Graphics::Accessor;
        using SceneR::Graphics::ModelBone;
        using SceneR::Graphics::ModelMesh;
        using SceneR::Graphics::Skeleton;
        using SceneR::Graphics::Node;

        std::shared_ptr<Node> ContentTypeReader<Node>::read(gsl::not_null<ContentReader*>       input
                                                          , const std::pair<std::string, Json>& source) const
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
                node->joint        = std::make_shared<ModelBone>();
                node->joint->_name = source.second["jointName"].string_value();

                if (!source.second["matrix"].is_null())
                {
                    node->joint->_transform = node->matrix;
                }
                else
                {
                    node->joint->_transform = Matrix::create_scale(node->scale)
                                            * Matrix::create_from_quaternion(node->rotation)
                                            * Matrix::create_translation(node->translation);
                }

                for (const auto& child : source.second["children"].array_items())
                {
                    auto childNode = input->read_object<Node>(child.string_value());

                    childNode->joint->_parent = node->joint;

                    node->joint->_children.push_back(childNode->joint);
                    node->children.push_back(childNode);
                }
            }
            else
            {
                for (const auto& child : source.second["children"].array_items())
                {
                    node->children.push_back(input->read_object<Node>(child.string_value()));
                }
            }

            for (const auto& mesh : source.second["meshes"].array_items())
            {
                node->meshes.push_back(input->read_object<ModelMesh>(mesh.string_value()));
            }

            if (!source.second["skin"].is_null())
            {
                node->instance_skin = read_skeleton(input, source.second);
            }

            return node;
        }

        std::shared_ptr<Skeleton> ContentTypeReader<Node>::read_skeleton(gsl::not_null<ContentReader*> input
                                                                       , const Json&                   source) const
        {
            auto skeleton = std::make_shared<Skeleton>();
            auto skin     = input->_root["skins"][source["skin"].string_value()];
            auto accessor = input->read_object<Accessor>(skin["inverseBindMatrices"].string_value());

            // Name
            skeleton->_name = source["skin"].string_value();

            // Bind shape matrix
            skeleton->_bind_shape_matrix = input->convert<Matrix>(skin["bindShapeMatrix"].array_items());

            // Inverse bind matrices
            for (std::size_t i = 0; i < accessor->attribute_count(); i++)
            {
                skeleton->_inverse_bind_matrices.push_back(accessor->get_element<Matrix>(i));
            }

            // Joints
            std::size_t boneIndex = 0;

            for (const auto& jointName : skin["jointNames"].array_items())
            {
                auto node = input->find_joint_node(jointName.string_value());

                Ensures(node.get() != nullptr && node->joint.get() != nullptr);

                node->joint->_index = boneIndex++;

                skeleton->_joints.push_back(node->joint);
                skeleton->_bone_transforms.push_back(node->joint->transform());
            }

            skeleton->_world_transforms = std::vector<Matrix>(skeleton->_bone_transforms.size());
            skeleton->_skin_transforms  = std::vector<Matrix>(skeleton->_bone_transforms.size());

            // The meshes for the skin instance
            for (const auto& meshRef : source["meshes"].array_items())
            {
                auto mesh = input->read_object<ModelMesh>(meshRef.string_value());

                Ensures(mesh.get() != nullptr);

                mesh->_skeleton = skeleton;
            }

            return skeleton;
        }
    }
}
