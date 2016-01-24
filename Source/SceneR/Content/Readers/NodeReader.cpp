// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/Readers/NodeReader.hpp"

#include <json11.hpp>

#include "SceneR/Content/ContentReader.hpp"
#include "SceneR/Content/GLTF/Accessor.hpp"
#include "SceneR/Graphics/ModelMesh.hpp"
#include "SceneR/Graphics/Skeleton.hpp"

namespace SceneR { namespace Content { namespace Readers {

using json11::Json;
using SceneR::Content::GLTF::Accessor;
using SceneR::Content::GLTF::Node;
using SceneR::Graphics::ModelMesh;
using SceneR::Graphics::ModelBone;
using SceneR::Graphics::Skeleton;
using SceneR::Math::Matrix;
using SceneR::Math::Quaternion;
using SceneR::Math::Vector3;
using SceneR::Math::Vector4;

auto ContentTypeReader<Node>::read(ContentReader* input, const std::string& key, const Json& source) const noexcept
{
    auto node = std::make_shared<Node>();

    node->name        = key;
    node->camera      = source["camera"].string_value();
    node->light       = source["light"].string_value();
    node->matrix      = Matrix::identity;
    node->rotation    = Quaternion::identity;
    node->scale       = Vector3::one;
    node->translation = Vector3::zero;

    // transforms

    if (!source["matrix"].is_null())
    {
        node->matrix = input->convert<Matrix>(source["matrix"].array_items());
    }
    else
    {
        if (!source["rotation"].is_null())
        {
            node->rotation = input->convert<Quaternion>(source["rotation"].array_items());
        }
        if (!source["scale"].is_null())
        {
            node->scale = input->convert<Vector3>(source["scale"].array_items());
        }
        if (!source["translation"].is_null())
        {
            node->translation = input->convert<Vector3>(source["translation"].array_items());
        }
    }

    // node children's

    const auto& children = source["children"].array_items();

    node->children.reserve(children.size());

    if (!source["jointName"].is_null())
    {
        node->joint        = std::make_shared<ModelBone>();
        node->joint->_name = source["jointName"].string_value();

        if (!source["matrix"].is_null())
        {
            node->joint->_transform = node->matrix;
        }
        else
        {
            node->joint->_transform = Matrix::create_scale(node->scale)
                                    * Matrix::create_from_quaternion(node->rotation)
                                    * Matrix::create_translation(node->translation);
        }

        node->joint->_children.reserve(children.size());

        for (const auto& child : children)
        {
            auto childNode = input->read_object<Node>(child.string_value());

            childNode->joint->_parent = node->joint;

            node->joint->_children.push_back(childNode->joint);
            node->children.push_back(childNode);
        }
    }
    else
    {
        for (const auto& child : children)
        {
            node->children.push_back(input->read_object<Node>(child.string_value()));
        }
    }

    // meshes

    const auto& meshes = source["meshes"].array_items();

    node->meshes.reserve(meshes.size());

    for (const auto& meshRef : meshes)
    {
        auto mesh = input->read_object<ModelMesh>(meshRef.string_value());

        Ensures(mesh.get() != nullptr);

        node->meshes.push_back(mesh);
    }

    // skin

    if (!source["skin"].is_null())
    {
        const auto& skin = source["skin"].string_value();

        node->instance_skin = input->read_object_instance<Skeleton>(skin, input->_root["skins"][skin]);

        // The meshes for the skin instance
        std::for_each(node->meshes.begin(), node->meshes.end()
                    , [&node](const auto& mesh) { mesh->_skeleton = node->instance_skin; });
    }

    return node;
}

}}}
