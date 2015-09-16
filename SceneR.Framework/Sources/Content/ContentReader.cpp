// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/ContentReader.hpp>

#include <cassert>

#include <Content/ContentLoadException.hpp>
#include <Content/ContentManager.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Node.hpp>
#include <System/IO/File.hpp>
#include <System/IO/Path.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Graphics::GraphicsDevice;
        using SceneR::Graphics::IGraphicsDeviceService;
        using SceneR::Graphics::Model;
        using System::IO::File;
        using System::IO::Path;
        using System::IO::Stream;

        ContentReader::ContentReader(const std::string& assetName, ContentManager* contentManager, Stream& stream)
            : _asset_name      { assetName }
            , _asset_reader    { stream }
            , _content_manager { contentManager }
        {
        }

        ContentReader::~ContentReader()
        {
            _asset_reader.close();
        }

        const std::string& ContentReader::asset_name() const
        {
            return _asset_name;
        }

        ContentManager* ContentReader::content_manager() const
        {
            return _content_manager;
        }

        std::shared_ptr<Model> ContentReader::read_asset()
        {
            auto broot  = _asset_reader.read_bytes(_asset_reader.base_stream().length());
            auto errors = std::string();
            auto model  = std::make_shared<Model>();

            _root = json11::Json::parse(reinterpret_cast<char*>(broot.data()), errors);

            assert(errors.empty());

            // Meshes
            for (const auto& mesh : _root["meshes"].object_items())
            {
                model->_meshes.push_back(read_object<SceneR::Graphics::ModelMesh>(mesh));
            }
            // Nodes
            for (const auto& node : _root["nodes"].object_items())
            {
                read_object<SceneR::Graphics::Node>(node);
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

        std::string ContentReader::get_asset_path(const std::string& assetName) const
        {
            auto assetRoot = Path::combine(Path::get_directory_name(_asset_name), assetName);

            return Path::combine(_content_manager->root_directory(), assetRoot);
        }

        std::vector<std::uint8_t> ContentReader::read_external_reference(const std::string& assetName) const
        {
            auto assetPath = get_asset_path(assetName);

            assert(File::exists(assetPath));

            return File::read_all_bytes(assetPath);
        }
    }
}
