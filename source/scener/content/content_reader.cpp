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
    using json11::Json;

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
        auto errors = std::string { };
        auto model  = std::make_shared<graphics::model>();

        _root = json11::Json::parse(reinterpret_cast<char*>(buffer.data()), errors);

        Expects(errors.empty());

        // Meshes
        const auto& meshes = _root["meshes"].object_items();

        model->_meshes.reserve(meshes.size());

        std::for_each(meshes.begin(), meshes.end(), [&](const auto& mesh) -> void
        {
            model->_meshes.push_back(read_object<graphics::model_mesh>(mesh.first, mesh.second));
        });

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
            read_object_instance<graphics::animation>(animation.first, animation.second);
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
