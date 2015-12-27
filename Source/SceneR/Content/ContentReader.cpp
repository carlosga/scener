// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "ContentReader.hpp"

#include "ContentLoadException.hpp"
#include "ContentManager.hpp"
#include "../IO/File.hpp"
#include "../IO/Path.hpp"
#include "../Graphics/IGraphicsDeviceService.hpp"
#include "../Graphics/Animation.hpp"
#include "../Graphics/Model.hpp"
#include "../Graphics/ModelMesh.hpp"
#include "../Graphics/Shader.hpp"

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Math::Matrix;
        using SceneR::Graphics::GraphicsDevice;
        using SceneR::Graphics::IGraphicsDeviceService;
        using SceneR::Graphics::Model;
        using SceneR::IO::File;
        using SceneR::IO::Path;
        using SceneR::IO::Stream;

        ContentReader::ContentReader(const std::string&             assetName
                                   , gsl::not_null<ContentManager*> contentManager
                                   , Stream&                        stream)
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

        std::shared_ptr<Model> ContentReader::read_asset()
        {
            auto buffer = _asset_reader.read_bytes(_asset_reader.base_stream().length());
            auto errors = std::string();
            auto model  = std::make_shared<Model>();

            _root = json11::Json::parse(reinterpret_cast<char*>(buffer.data()), errors);

            Expects(errors.empty());

            // Meshes
            for (const auto& mesh : _root["meshes"].object_items())
            {
                model->_meshes.push_back(read_object<SceneR::Graphics::ModelMesh>(mesh));
            }
            // Nodes ( joints )
            for (const auto& node : _root["nodes"].object_items())
            {
                if (!node.second["jointName"].is_null())
                {
                    read_object<Node>(node);
                }
            }
            // Nodes ( not joints )
            for (const auto& node : _root["nodes"].object_items())
            {
                if (node.second["jointName"].is_null())
                {
                    read_object<Node>(node);
                }
            }
            // Animations
            for (const auto& node : _root["animations"].object_items())
            {
                read_object_instance<SceneR::Graphics::Animation>(node);
            }

            // cleanup
            for (auto shader : _shaders)
            {
                shader.second->dispose();
            }

            return model;
        }

        bool ContentReader::read_header()
        {
            return true;
        }

        std::string ContentReader::get_asset_path(const std::string& assetName) const noexcept
        {
            auto assetRoot = Path::combine(Path::get_directory_name(_asset_name), assetName);

            return Path::combine(_content_manager->root_directory(), assetRoot);
        }

        std::vector<std::uint8_t> ContentReader::read_external_reference(const std::string& assetName) const
        {
            auto assetPath = get_asset_path(assetName);

            Ensures(File::exists(assetPath));

            return File::read_all_bytes(assetPath);
        }
    }
}
