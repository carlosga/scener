// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/node_reader.hpp"

#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/accessor.hpp"
#include "scener/content/gltf/node.hpp"
#include "scener/graphics/model_mesh.hpp"
#include "scener/graphics/skeleton.hpp"
#include "scener/math/matrix.hpp"

namespace scener::content::readers
{
    using nlohmann::json;
    using scener::content::gltf::accessor;
    using scener::graphics::bone;
    using scener::graphics::model_mesh;
    using scener::graphics::skeleton;
    using scener::math::matrix4;
    using scener::math::quaternion;
    using scener::math::vector3;
    using scener::math::vector4;

    auto content_type_reader<gltf::node>::read(content_reader* input, const std::string& key, const json& source) const noexcept
    {
        auto node = std::make_shared<gltf::node>();

        node->name        = key;
        node->matrix      = matrix4::identity();
        node->rotation    = quaternion::identity();
        node->scale       = vector3::one();
        node->translation = vector3::zero();

        if (source.count("camera") != 0)
        {
            node->camera = source["camera"].get<std::string>();
        }
        if (source.count("light") != 0)
        {
            node->light = source["light"].get<std::string>();
        }

        // transforms

        if (source.count("matrix") != 0)
        {
            node->matrix = input->convert<matrix4>(source["matrix"].get<json::array_t>());
        }
        else
        {
            if (source.count("rotation") != 0)
            {
                node->rotation = input->convert<quaternion>(source["rotation"].get<json::array_t>());
            }
            if (source.count("scale") != 0)
            {
                node->scale = input->convert<vector3>(source["scale"].get<json::array_t>());
            }
            if (source.count("translation") != 0)
            {
                node->translation = input->convert<vector3>(source["translation"].get<json::array_t>());
            }
        }

        // node children's

        const auto& children = source["children"].get<json::array_t>();

        node->children.reserve(children.size());

        if (source.count("jointName") != 0)
        {
            node->joint        = std::make_shared<bone>();
            node->joint->_name = source["jointName"].get<std::string>();

            if (source.count("matrix") != 0)
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

        if (source.count("meshes") != 0)
        {
            const auto& meshes = source["meshes"].get<json::array_t>();

            node->meshes.reserve(meshes.size());

            for (const auto& meshRef : meshes)
            {
                auto mesh = input->read_object<model_mesh>(meshRef.get<std::string>());

                Ensures(mesh.get() != nullptr);

                node->meshes.push_back(mesh);
            }
        }

        // skin

        if (source.count("skin") != 0)
        {
            const auto& skin = source["skin"].get<std::string>();

            node->instance_skin = input->read_object_instance<skeleton>(skin, input->_root["skins"][skin]);

            // The meshes for the skin instance
            std::for_each(node->meshes.begin(), node->meshes.end()
                        , [&node](const auto& mesh) { mesh->_skeleton = node->instance_skin; });
        }

        return node;
    }
}
