// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/ContentReader.hpp"

#include "SceneR/Content/ContentManager.hpp"
#include "SceneR/Graphics/Animation.hpp"
#include "SceneR/Graphics/Model.hpp"
#include "SceneR/Graphics/ModelMesh.hpp"
#include "SceneR/IO/File.hpp"
#include "SceneR/IO/Path.hpp"

namespace SceneR { namespace Content {

using json11::Json;
using SceneR::Content::GLTF::Node;
using SceneR::Graphics::Animation;
using SceneR::Graphics::Model;
using SceneR::Graphics::ModelMesh;
using SceneR::IO::File;
using SceneR::IO::Path;
using SceneR::IO::Stream;

ContentReader::ContentReader(const std::string& assetName, ContentManager* contentManager, Stream& stream) noexcept
    : _asset_name      { assetName }
    , _asset_reader    { stream }
    , _content_manager { contentManager }
    , _root            { }
{
}

const std::string& ContentReader::asset_name() const noexcept
{
    return _asset_name;
}

ContentManager* ContentReader::content_manager() const noexcept
{
    return _content_manager;
}

std::shared_ptr<Model> ContentReader::read_asset() noexcept
{
    auto buffer = _asset_reader.read_bytes(_asset_reader.base_stream().length());
    auto errors = std::string();
    auto model  = std::make_shared<Model>();

    _root = json11::Json::parse(reinterpret_cast<char*>(buffer.data()), errors);

    Expects(errors.empty());

    // Meshes
    const auto& meshes = _root["meshes"].object_items();

    model->_meshes.reserve(meshes.size());

    for (const auto& mesh : meshes)
    {
        model->_meshes.push_back(read_object<ModelMesh>(mesh.first, mesh.second));
    }

    // Nodes
    const auto& nodes = _root["nodes"].object_items();

    // Joints
    for (const auto& node : nodes)
    {
        if (!node.second["jointName"].is_null())
        {
            read_object<Node>(node.first, node.second);
        }
    }
    // Other nodes
    for (const auto& node : nodes)
    {
        if (node.second["jointName"].is_null())
        {
            read_object<Node>(node.first, node.second);
        }
    }

    // Animations
    for (const auto& animation : _root["animations"].object_items())
    {
        read_object_instance<Animation>(animation.first, animation.second);
    }

    return model;
}

bool ContentReader::read_header() noexcept
{
    return true;
}

std::string ContentReader::get_asset_path(const std::string& assetName) const noexcept
{
    auto assetRoot = Path::combine(Path::get_directory_name(_asset_name), assetName);

    return Path::combine(_content_manager->root_directory(), assetRoot);
}

std::vector<std::uint8_t> ContentReader::read_external_reference(const std::string& assetName) const noexcept
{
    auto assetPath = get_asset_path(assetName);

    Ensures(File::exists(assetPath));

    return File::read_all_bytes(assetPath);
}

std::shared_ptr<GLTF::Node> ContentReader::find_joint_node(const std::string& jointName) const noexcept
{
    for (const auto& node : _nodes)
    {
        if (node.second.get())
        {
            auto& joint = node.second->joint;

            if (joint.get() && joint->name() == jointName)
            {
                return node.second;
            }
        }
    }

    return nullptr;
}

}}
