// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/ContentReader.hpp>

#include <cassert>

#include <Content/json11.hpp>
#include <Content/ContentLoadException.hpp>
#include <Content/ContentManager.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
#include <Graphics/Model.hpp>
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

        ContentTypeReaderManager ContentReader::TypeReaderManager;

        ContentReader::ContentReader(const std::u16string& assetName
                                   , ContentManager*       contentManager
                                   , Stream&               stream)
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

        std::shared_ptr<SceneR::Graphics::Model> ContentReader::read_asset()
        {
            auto& gdService = _content_manager->service_provider().get_service<IGraphicsDeviceService>();
            auto  context   = ContentReaderContext(gdService.graphics_device());
            auto  buffer    = _asset_reader.read_bytes(_asset_reader.base_stream().length());
            auto  errors    = std::string();
            auto  json      = json11::Json::parse(reinterpret_cast<char*>(buffer.data()), errors);

            assert(errors.empty());

            context.content_reader = this;
            context.model          = std::make_shared<Model>();

            read_object("buffers"    , json, context);
            read_object("bufferViews", json, context);
            read_object("accessors"  , json, context);
            read_object("meshes"     , json, context);
            // read_object("lights"     , json, context);
            // read_object("cameras"    , json, context);
            read_object("nodes"      , json, context);
            read_object("images"     , json, context);
            read_object("textures"   , json, context);
            read_object("shaders"    , json, context);
            read_object("programs"   , json, context);
            read_object("samplers"   , json, context);
            read_object("techniques" , json, context);
            read_object("materials"  , json, context);
            // read_object("animations" , json, context);
            // read_object("skins"      , json, context);

            return context.model;
        }

        bool ContentReader::read_header()
        {
            return true;
        }

        void ContentReader::read_object(const std::string& key, const Json& value, ContentReaderContext& context)
        {
            auto typeReader = TypeReaderManager.get_by_reader_name(key);

            if (typeReader == nullptr)
            {
                throw ContentLoadException("Unknown type reader");
            }

            typeReader->read(value, context);
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
