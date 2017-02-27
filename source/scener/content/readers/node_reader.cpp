// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/node_reader.hpp"

#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/accessor.hpp"
#include "scener/content/gltf/node.hpp"
#include "scener/content/gltf/constants.hpp"
#include "scener/graphics/model_mesh.hpp"
#include "scener/graphics/skeleton.hpp"
#include "scener/math/matrix.hpp"

namespace scener::content::readers
{
    using nlohmann::json;
    using scener::graphics::bone;
    using scener::graphics::model_mesh;
    using scener::graphics::skeleton;
    using scener::math::matrix4;
    using scener::math::quaternion;
    using scener::math::vector3;
    using scener::math::vector4;

    using namespace scener::content::gltf;

    auto content_type_reader<gltf::node>::read(content_reader* input, const std::string& key, const json& source) const noexcept
    {
        auto node = std::make_shared<gltf::node>();

        node->name        = key;
        node->matrix      = matrix4::identity();
        node->rotation    = quaternion::identity();
        node->scale       = vector3::one();
        node->translation = vector3::zero();

        if (source.count(k_camera) != 0)
        {
            node->camera = source[k_camera].get<std::string>();
        }
        if (source.count(k_light) != 0)
        {
            node->light = source[k_light].get<std::string>();
        }

        // transforms

        if (source.count(k_matrix) != 0)
        {
            node->matrix = input->convert<matrix4>(source[k_matrix].get<json::array_t>());
        }
        else
        {
            if (source.count(k_rotation) != 0)
            {
                node->rotation = input->convert<quaternion>(source[k_rotation].get<json::array_t>());
            }
            if (source.count(k_scale) != 0)
            {
                node->scale = input->convert<vector3>(source[k_scale].get<json::array_t>());
            }
            if (source.count(k_translation) != 0)
            {
                node->translation = input->convert<vector3>(source[k_translation].get<json::array_t>());
            }
        }

        // node children's

        const auto& children = source[k_children].get<json::array_t>();

        node->children.reserve(children.size());

        if (source.count(k_joint_name) != 0)
        {
            node->joint        = std::make_shared<bone>();
            node->joint->_name = source[k_joint_name].get<std::string>();

            if (source.count(k_matrix) != 0)
            {
                node->joint->_transform = node->matrix;
            }
            else
            {
                node->joint->_transform = scener::math::matrix::create_scale(node->scale)
                                        * scener::math::matrix::create_from_quaternion(node->rotation)
                                        * scener::math::matrix::create_translation(node->translation);
            }

            node->joint->_children.reserve(children.size());

            for (const auto& child : children)
            {
                auto childNode = input->read_object<gltf::node>(child.get<std::string>());

                childNode->joint->_parent = node->joint;

                node->joint->_children.push_back(childNode->joint);
                node->children.push_back(childNode);
            }
        }
        else
        {
            for (const auto& child : children)
            {
                node->children.push_back(input->read_object<gltf::node>(child.get<std::string>()));
            }
        }

        // meshes

        if (source.count(k_meshes) != 0)
        {
            const auto& meshes = source[k_meshes].get<json::array_t>();

            node->meshes.reserve(meshes.size());

            for (const auto& meshRef : meshes)
            {
                auto mesh = input->read_object<model_mesh>(meshRef.get<std::string>());

                Ensures(mesh.get() != nullptr);

                node->meshes.push_back(mesh);
            }
        }

        // skin

        if (source.count(k_skin) != 0)
        {
            const auto& skin = source[k_skin].get<std::string>();

            node->instance_skin = input->read_object_instance<skeleton>(skin, input->_root[k_skins][skin]);

            // The meshes for the skin instance
            std::for_each(node->meshes.begin(), node->meshes.end()
                        , [&node](const auto& mesh) { mesh->_skeleton = node->instance_skin; });
        }

        return node;
    }
}
