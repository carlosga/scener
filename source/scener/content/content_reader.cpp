// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/content_reader.hpp"

#include "scener/content/content_manager.hpp"
#include "scener/graphics/Animation.hpp"
#include "scener/graphics/Model.hpp"
#include "scener/graphics/ModelMesh.hpp"
#include "scener/io/file.hpp"
#include "scener/io/path.hpp"

namespace scener { namespace content {

using json11::Json;
using scener::content::gltf::node;
using scener::graphics::Animation;
using scener::graphics::Model;
using scener::graphics::ModelMesh;
using scener::io::file;
using scener::io::path;
using scener::io::stream;

content_reader::content_reader(const std::string& assetName, content::content_manager* manager, io::stream& stream) noexcept
    : _asset_name      { assetName }
    , _asset_reader    { stream }
    , _content_manager { manager }
    , _root            { }
{
}

const std::string& content_reader::asset_name() const noexcept
{
    return _asset_name;
}

content::content_manager* content_reader::content_manager() const noexcept
{
    return _content_manager;
}

std::shared_ptr<Model> content_reader::read_asset() noexcept
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
            read_object<gltf::node>(node.first, node.second);
        }
    }
    // Other nodes
    for (const auto& node : nodes)
    {
        if (node.second["jointName"].is_null())
        {
            read_object<gltf::node>(node.first, node.second);
        }
    }

    // Animations
    for (const auto& animation : _root["animations"].object_items())
    {
        read_object_instance<Animation>(animation.first, animation.second);
    }

    return model;
}

bool content_reader::read_header() noexcept
{
    return true;
}

std::string content_reader::get_asset_path(const std::string& assetName) const noexcept
{
    auto assetRoot = path::combine(path::get_directory_name(_asset_name), assetName);

    return path::combine(_content_manager->root_directory(), assetRoot);
}

std::vector<std::uint8_t> content_reader::read_external_reference(const std::string& assetName) const noexcept
{
    auto asset_path = get_asset_path(assetName);

    Ensures(file::exists(asset_path));

    return file::read_all_bytes(asset_path);
}

std::shared_ptr<gltf::node> content_reader::find_joint_node(const std::string& jointName) const noexcept
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
