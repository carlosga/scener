// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/node_reader.hpp"

#include <json11.hpp>

#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/accessor.hpp"
#include "scener/graphics/model_mesh.hpp"
#include "scener/graphics/skeleton.hpp"
#include "scener/math/matrix.hpp"

namespace scener { namespace content { namespace readers {

using json11::Json;
using scener::content::gltf::accessor;
using scener::graphics::bone;
using scener::graphics::model_mesh;
using scener::graphics::skeleton;
using scener::math::matrix4;
using scener::math::quaternion;
using scener::math::vector3;
using scener::math::vector4;

auto content_type_reader<gltf::node>::read(content_reader* input, const std::string& key, const Json& source) const noexcept
{
    auto node = std::make_shared<gltf::node>();

    node->name        = key;
    node->camera      = source["camera"].string_value();
    node->light       = source["light"].string_value();
    node->matrix      = matrix4::identity();
    node->rotation    = quaternion::identity();
    node->scale       = vector3::one();
    node->translation = vector3::zero();

    // transforms

    if (!source["matrix"].is_null())
    {
        node->matrix = input->convert<matrix4>(source["matrix"].array_items());
    }
    else
    {
        if (!source["rotation"].is_null())
        {
            node->rotation = input->convert<quaternion>(source["rotation"].array_items());
        }
        if (!source["scale"].is_null())
        {
            node->scale = input->convert<vector3>(source["scale"].array_items());
        }
        if (!source["translation"].is_null())
        {
            node->translation = input->convert<vector3>(source["translation"].array_items());
        }
    }

    // node children's

    const auto& children = source["children"].array_items();

    node->children.reserve(children.size());

    if (!source["jointName"].is_null())
    {
        node->joint        = std::make_shared<bone>();
        node->joint->_name = source["jointName"].string_value();

        if (!source["matrix"].is_null())
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
            auto childNode = input->read_object<gltf::node>(child.string_value());

            childNode->joint->_parent = node->joint;

            node->joint->_children.push_back(childNode->joint);
            node->children.push_back(childNode);
        }
    }
    else
    {
        for (const auto& child : children)
        {
            node->children.push_back(input->read_object<gltf::node>(child.string_value()));
        }
    }

    // meshes

    const auto& meshes = source["meshes"].array_items();

    node->meshes.reserve(meshes.size());

    for (const auto& meshRef : meshes)
    {
        auto mesh = input->read_object<model_mesh>(meshRef.string_value());

        Ensures(mesh.get() != nullptr);

        node->meshes.push_back(mesh);
    }

    // skin

    if (!source["skin"].is_null())
    {
        const auto& skin = source["skin"].string_value();

        node->instance_skin = input->read_object_instance<skeleton>(skin, input->_root["skins"][skin]);

        // The meshes for the skin instance
        std::for_each(node->meshes.begin(), node->meshes.end()
                    , [&node](const auto& mesh) { mesh->_skeleton = node->instance_skin; });
    }

    return node;
}

}}}
