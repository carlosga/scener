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
    using scener::math::matrix::create_scale;
    using scener::math::matrix::create_from_quaternion;
    using scener::math::matrix::create_translation;

    using namespace scener::content::gltf;

    auto content_type_reader<node>::read(content_reader* input, const std::string& key, const json& value) const noexcept
    {
        auto instance = std::make_shared<node>();

        instance->name        = key;
        instance->matrix      = matrix4::identity();
        instance->rotation    = quaternion::identity();
        instance->scale       = vector3::one();
        instance->translation = vector3::zero();

        if (value.count(k_camera) != 0)
        {
            instance->camera = value[k_camera].get<std::string>();
        }
        if (value.count(k_light) != 0)
        {
            instance->light = value[k_light].get<std::string>();
        }

        // transforms

        if (value.count(k_matrix) != 0)
        {
            instance->matrix = input->convert<matrix4>(value[k_matrix].get<json::array_t>());
        }
        else
        {
            if (value.count(k_rotation) != 0)
            {
                instance->rotation = input->convert<quaternion>(value[k_rotation].get<json::array_t>());
            }
            if (value.count(k_scale) != 0)
            {
                instance->scale = input->convert<vector3>(value[k_scale].get<json::array_t>());
            }
            if (value.count(k_translation) != 0)
            {
                instance->translation = input->convert<vector3>(value[k_translation].get<json::array_t>());
            }
        }

        // node children's

        const auto& children = value[k_children].get<json::array_t>();

        instance->children.reserve(children.size());

        if (value.count(k_joint_name) != 0)
        {
            instance->joint        = std::make_shared<bone>();
            instance->joint->_name = value[k_joint_name].get<std::string>();

            if (value.count(k_matrix) != 0)
            {
                instance->joint->_transform = instance->matrix;
            }
            else
            {
                instance->joint->_transform = create_scale(instance->scale)
                                            * create_from_quaternion(instance->rotation)
                                            * create_translation(instance->translation);
            }

            instance->joint->_children.reserve(children.size());

            for (const auto& child : children)
            {
                auto childNode = input->read_object<gltf::node>(child.get<std::string>());

                childNode->joint->_parent = instance->joint;

                instance->joint->_children.push_back(childNode->joint);
                instance->children.push_back(childNode);
            }
        }
        else
        {
            for (const auto& child : children)
            {
                instance->children.push_back(input->read_object<gltf::node>(child.get<std::string>()));
            }
        }

        // meshes

        if (value.count(k_meshes) != 0)
        {
            const auto& meshes = value[k_meshes].get<json::array_t>();

            instance->meshes.reserve(meshes.size());

            for (const auto& meshRef : meshes)
            {
                auto mesh = input->read_object<model_mesh>(meshRef.get<std::string>());

                Ensures(mesh.get() != nullptr);

                instance->meshes.push_back(mesh);
            }
        }

        // skin

        if (value.count(k_skin) != 0)
        {
            const auto& skin = value[k_skin].get<std::string>();

            instance->instance_skin = input->read_object_instance<skeleton>(skin, input->_root[k_skins][skin]);

            // The meshes for the skin instance
            std::for_each(instance->meshes.begin(), instance->meshes.end()
                        , [&instance](const auto& mesh) { mesh->_skeleton = instance->instance_skin; });
        }

        return instance;
    }
}
