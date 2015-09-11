// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/ContentReader.hpp>

#include <cassert>

#include <Content/ContentLoadException.hpp>
#include <Content/ContentManager.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
#include <System/IO/BinaryReader.hpp>
#include <System/IO/File.hpp>
#include <System/IO/Path.hpp>
#include <System/Text/Encoding.hpp>

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
        using System::Text::Encoding;

        ContentReader::ContentReader(const std::u16string& assetName, ContentManager* contentManager, Stream& stream)
            : _asset_name      { assetName }
            , _asset_reader    { stream }
            , _content_manager { contentManager }
        {
        }

        ContentReader::~ContentReader()
        {
            _asset_reader.close();
        }

        const std::u16string& ContentReader::asset_name() const
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

            // Buffers
            for (const auto& buffer : _root["buffers"].object_items())
            {
                _buffers.push_back(read_object<SceneR::Graphics::Buffer>(buffer));
            }
            // Buffer Views
            for (const auto& bufferView : _root["bufferViews"].object_items())
            {
                _buffer_views.push_back(read_object<SceneR::Graphics::BufferView>(bufferView));
            }
            // Accessors
            for (const auto& accessor : _root["accessors"].object_items())
            {
                _accessors.push_back(read_object<SceneR::Graphics::Accessor>(accessor));
            }
            // Meshes
            for (const auto& mesh : _root["meshes"].object_items())
            {
                _meshes.push_back(read_object<SceneR::Graphics::ModelMesh>(mesh));
            }

            // read_object("buffers"    , json, context);
            // read_object("bufferViews", json, context);
            // read_object("accessors"  , json, context);
            // read_object("meshes"     , json, context);
            // read_object("lights"     , json, context);
            // read_object("cameras"    , json, context);
            // read_object("nodes"      , json, context);
            // read_object("images"     , json, context);
            // read_object("textures"   , json, context);
            // read_object("shaders"    , json, context);
            // read_object("programs"   , json, context);
            // read_object("samplers"   , json, context);
            // read_object("techniques" , json, context);
            // read_object("materials"  , json, context);
            // read_object("animations" , json, context);
            // read_object("skins"      , json, context);

            return model;
        }

        bool ContentReader::read_header()
        {
            return true;
        }

        std::vector<std::uint8_t> ContentReader::read_external_reference(const std::string& assetName) const
        {
            return read_external_reference(Encoding::convert(assetName));
        }

        std::vector<std::uint8_t> ContentReader::read_external_reference(const std::u16string& assetName) const
        {
            auto assetRoot = Path::combine(Path::get_directory_name(_asset_name), assetName);
            auto assetPath = Path::combine(_content_manager->root_directory(), assetRoot);

            assert(File::exists(assetPath));

            return File::read_all_bytes(assetPath);
        }
    }
}
