// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/NodeReader.hpp>

#include <Content/json11.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/InstanceSkin.hpp>
#include <Graphics/ModelMesh.hpp>
#include <System/Text/Encoding.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Framework::Matrix;
        using SceneR::Framework::Quaternion;
        using SceneR::Framework::Vector3;
        using SceneR::Graphics::InstanceSkin;
        using SceneR::Graphics::ModelMesh;
        using SceneR::Graphics::Node;
        using System::Text::Encoding;

        ContentTypeReader<Node>::ContentTypeReader()
        {

        }

        ContentTypeReader<Node>::~ContentTypeReader()
        {

        }

        std::shared_ptr<Node> ContentTypeReader<Node>::read(const std::pair<std::string, Json>& source
                                                          , ContentReaderContext&               context)
        {
            auto node        = std::make_shared<Node>();
            auto matrix      = Matrix::identity;
            auto rotation    = Quaternion::identity;
            auto scale       = Vector3::one;
            auto translation = Vector3::zero;

            if (!source.second["matrix"].is_null())
            {
                matrix = context.convert<Matrix>(source.second["matrix"].array_items());
            }
            if (!source.second["rotation"].is_null())
            {
                rotation = context.convert<Quaternion>(source.second["rotation"].array_items());
            }
            if (!source.second["scale"].is_null())
            {
                scale = context.convert<Vector3>(source.second["scale"].array_items());
            }
            if (!source.second["translation"].is_null())
            {
                translation = context.convert<Vector3>(source.second["translation"].array_items());
            }

            node->name        = Encoding::convert(source.first);
            node->camera      = source.second["camera"].string_value();
            node->joint_name  = source.second["jointName"].string_value();
            node->light       = source.second["light"].string_value();
            node->matrix      = matrix;
            node->rotation    = rotation;
            node->scale       = scale;
            node->translation = translation;

            if (!source.second["instanceSkin"].is_null())
            {
                node->instance_skin = read_instance_skin(source.second["instanceSkin"], context);
            }

            for (const auto& mesh : source.second["meshes"].array_items())
            {
                node->meshes.push_back(context.find_object<ModelMesh>(mesh.string_value()));
            }

            for (const auto& child : source.second["children"].array_items())
            {
                node->children.push_back(child.string_value());
            }

            return node;
        }

        std::shared_ptr<InstanceSkin> ContentTypeReader<Node>::read_instance_skin(const Json&           source
                                                                                , ContentReaderContext& context)
        {
            auto instanceSkin = std::make_shared<InstanceSkin>();

            for (const auto& skeleton : source["skeletons"].array_items())
            {
                instanceSkin->skeletons.push_back(skeleton.string_value());
            }

            instanceSkin->skin = source["skin"].string_value();

            for (const auto& mesh : source["meshes"].array_items())
            {
                // instanceSkin->meshes.push_back(context.find_object<ModelMesh>(mesh.string_value()));
                instanceSkin->meshes.push_back(mesh.string_value());
            }

            return instanceSkin;
        }
    }
}