// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/ContentReader.hpp>

#include <cassert>

#include <Content/json11.hpp>
#include <Content/ContentLoadException.hpp>
#include <Content/ContentManager.hpp>
#include <Content/TypeReaders.hpp>
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

        std::shared_ptr<Model> ContentReader::read_asset()
        {
            auto& gdService = _content_manager->service_provider().get_service<IGraphicsDeviceService>();
            auto  context   = ContentReaderContext(gdService.graphics_device());
            auto  buffer    = _asset_reader.read_bytes(_asset_reader.base_stream().length());
            auto  errors    = std::string();
            auto  json      = json11::Json::parse(reinterpret_cast<char*>(buffer.data()), errors);
            auto  model     = std::make_shared<Model>();

            assert(errors.empty());

            context.content_reader = this;
            context.root           = json;

            // Buffers
            for (const auto& buffer : json["buffers"].object_items())
            {
                context.buffers.push_back(read_object<SceneR::Graphics::Buffer>(buffer, context));
            }
            // Buffer Views
            for (const auto& bufferView : json["bufferViews"].object_items())
            {
                context.buffer_views.push_back(read_object<SceneR::Graphics::BufferView>(bufferView, context));
            }
            // Accessors
            for (const auto& accessor : json["accessors"].object_items())
            {
                context.accessors.push_back(read_object<SceneR::Graphics::Accessor>(accessor, context));
            }
            // Meshes
            for (const auto& mesh : json["meshes"].object_items())
            {
                context.meshes.push_back(read_object<SceneR::Graphics::ModelMesh>(mesh, context));
            }
            // Images
            for (const auto& image : json["images"].object_items())
            {
                auto uri  = Encoding::convert(image.second["uri"].string_value());
                context.images[image.first] = read_external_reference(uri);
            }
            // Textures
            for (const auto& texture : json["textures"].object_items())
            {
                context.textures.push_back(read_object<SceneR::Graphics::Texture2D>(texture, context));
            }
            // Shaders
            for (const auto& shader : json["shaders"].object_items())
            {
                context.shaders.push_back(read_object<SceneR::Graphics::Shader>(shader, context));
            }
            // Programs
            for (const auto& program : json["programs"].object_items())
            {
                context.programs.push_back(read_object<SceneR::Graphics::Program>(program, context));
            }
            // Samplers
            for (const auto& sampler : json["samplers"].object_items())
            {
                context.samplers.push_back(read_object<SceneR::Graphics::SamplerState>(sampler, context));
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

//        template<typename T>
//        std::shared_ptr<T> ContentReader::read_object(const std::pair<std::string, json11::Json>& source
//                                                    , ContentReaderContext&                       context)
//        {
//            ContentTypeReader<T> reader;
//            return reader.read(source, context);
//        }

        std::vector<std::uint8_t> ContentReader::read_external_reference(const std::u16string& assetName) const
        {
            auto assetRoot = Path::combine(Path::get_directory_name(_asset_name), assetName);
            auto assetPath = Path::combine(_content_manager->root_directory(), assetRoot);

            assert(File::exists(assetPath));

            return File::read_all_bytes(assetPath);
        }
    }
}
