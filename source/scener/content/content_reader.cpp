// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/content_reader.hpp"

#include <experimental/algorithm>

#include "scener/content/content_manager.hpp"
#include "scener/graphics/animation.hpp"
#include "scener/graphics/model.hpp"
#include "scener/graphics/model_mesh.hpp"
#include "scener/io/file.hpp"
#include "scener/io/path.hpp"

namespace scener::content
{
    using nlohmann::json;

    content_reader::content_reader(const std::string& assetname, content::content_manager* manager, io::stream& stream) noexcept
        : _asset_name      { assetname }
        , _asset_reader    { stream    }
        , _content_manager { manager   }
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

    std::shared_ptr<graphics::model> content_reader::read_asset() noexcept
    {
        auto buffer = _asset_reader.read_bytes(_asset_reader.base_stream().length());
        auto model  = std::make_shared<graphics::model>();

        _root = json::parse(buffer.data());

        // Meshes
        const auto& meshes = _root["meshes"];

        model->_meshes.reserve(meshes.size());

        for (auto it = meshes.begin(); it != meshes.end(); ++it)
        {
            model->_meshes.push_back(read_object<graphics::model_mesh>(it.key(), it.value()));
        }

        // Nodes
        const auto& nodes = _root["nodes"];

        // Joints
        for (auto it = nodes.begin(); it != nodes.end(); ++it)
        {
            const auto& key = it.key();
            const auto& val = it.value();

            if (val.count("jointName") != 0)
            {
                read_object<gltf::node>(key, val);
            }
        }
        // Other nodes
        for (auto it = nodes.begin(); it != nodes.end(); ++it)
        {
            const auto& key = it.key();
            const auto& val = it.value();

            if (val.count("jointName") == 0)
            {
                read_object<gltf::node>(key, val);
            }
        }

        // Animations
        const auto& animations = _root["animations"];

        for (auto it = animations.begin(); it != animations.end(); ++it)
        {
            read_object_instance<graphics::animation>(it.key(), it.value());
        }

        return model;
    }

    bool content_reader::read_header() noexcept
    {
        return true;
    }

    std::string content_reader::get_asset_path(const std::string& assetname) const noexcept
    {
        auto root = io::path::combine(io::path::get_directory_name(_asset_name), assetname);

        return io::path::combine(_content_manager->root_directory(), root);
    }

    std::vector<std::uint8_t> content_reader::read_external_reference(const std::string& assetname) const noexcept
    {
        auto path = get_asset_path(assetname);

        Ensures(io::file::exists(path));

        return io::file::read_all_bytes(path);
    }

    std::shared_ptr<gltf::node> content_reader::find_joint_node(const std::string& jointname) const noexcept
    {
        for (const auto& node : _nodes)
        {
            if (node.second.get())
            {
                auto& joint = node.second->joint;

                if (joint.get() && joint->name() == jointname)
                {
                    return node.second;
                }
            }
        }

        return nullptr;
    }
}
