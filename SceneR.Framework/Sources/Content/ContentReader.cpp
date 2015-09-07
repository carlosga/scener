// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/ContentReader.hpp>

#include <Graphics/GraphicsDevice.hpp>
#include <Content/ContentLoadException.hpp>
#include <Content/json11.hpp>
#include <Graphics/Buffer.hpp>
#include <Graphics/Model.hpp>

namespace SceneR
{
    namespace Content
    {
        using System::IO::Stream;
        using SceneR::Graphics::Buffer;
        using SceneR::Graphics::GraphicsDevice;
        using SceneR::Graphics::Model;
        using json11::Json;

        ContentTypeReaderManager ContentReader::TypeReaderManager;

        ContentReader::ContentReader(const std::u16string& assetName
                                   , GraphicsDevice&       graphicsDevice
                                   , Stream&               stream)
            : _asset_name      { assetName }
            , _asset_reader    { stream }
            , _graphics_device { graphicsDevice }
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
            using SceneR::Graphics::Model;

            std::string err;

            auto jsonOffset = _asset_reader.read<std::uint32_t>();
            auto jsonLength = _asset_reader.read<std::uint32_t>();
            auto dataOffset = _asset_reader.base_stream().position();
            auto context    = ContentReaderContext(_graphics_device);

            _asset_reader.base_stream().seek(jsonOffset, std::ios::beg);

            auto buffer = _asset_reader.read_bytes(jsonLength);
            auto json   = json11::Json::parse(reinterpret_cast<char*>(buffer.data()), err);

            if (!err.empty())
            {
                throw ContentLoadException(err);
            }

            context.model = std::make_shared<Model>();

            read_object("buffers", json, context);

            // Set buffers data
            for (auto buffer : context.buffers)
            {
                _asset_reader.base_stream().seek(dataOffset, std::ios::beg);

                const auto data = _asset_reader.read_bytes(buffer->byte_length());

                buffer->set_data(data);
            }

            read_object("bufferViews", json, context);
            read_object("accessors"  , json, context);
            read_object("techniques" , json, context);
            read_object("materials"  , json, context);
            read_object("meshes"     , json, context);
            read_object("lights"     , json, context);
            read_object("cameras"    , json, context);
            read_object("nodes"      , json, context);
            read_object("images"     , json, context);
            read_object("textures"   , json, context);
            read_object("shaders"    , json, context);
            read_object("programs"   , json, context);
            read_object("samplers"   , json, context);
            read_object("animations" , json, context);
            read_object("skins"      , json, context);

            return context.model;
        }

        bool ContentReader::read_header()
        {
            // Binary glTF layout
            //
            // -------------------------------
            // 20-byte header
            // -------------------------------
            // magic         unsigned char[4]
            // version       uint32
            // length        uint32
            // jsonOffset    uint32
            // jsonLength    uint32
            // -------------------------------
            // body
            //  JSON UTF-8
            // -------------------------------
            auto magic = _asset_reader.read_bytes(4);
            auto mstr  = std::string(magic.begin(), magic.end());

            if (mstr != "glTF")
            {
                return false;
            }

            _asset_reader.read<std::uint32_t>();   // version
            _asset_reader.read<std::uint32_t>();   // file length

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
    }
}
