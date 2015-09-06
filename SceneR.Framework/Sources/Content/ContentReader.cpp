// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/ContentReader.hpp>

#include <iostream>

#include <Graphics/GraphicsDevice.hpp>
#include <Content/ContentLoadException.hpp>
#include <Content/json11.hpp>
#include <Graphics/BufferView.hpp>
#include <Graphics/Model.hpp>

namespace SceneR
{
    namespace Content
    {
        using System::IO::Stream;
        using SceneR::Graphics::BufferTarget;
        using SceneR::Graphics::GraphicsDevice;
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
            auto dataLength = jsonOffset - dataOffset;

            _asset_reader.base_stream().seek(jsonOffset, std::ios::beg);

            auto buffer = _asset_reader.read_bytes(jsonLength);
            auto json   = json11::Json::parse(reinterpret_cast<char*>(buffer.data()), err);

            if (!err.empty())
            {
                throw ContentLoadException(err);
            }

            auto gltf = std::make_shared<Model>();

            const auto nodes = std::vector<std::string>
            {
                "buffers"
              , "bufferViews"
              , "accessors"
              , "techniques"
              , "materials"
              , "meshes"
//              , "lights"
//              , "cameras"
//              , "nodes"
//              , "images"
//              , "textures"
//              , "shaders"
//              , "programs"
//              , "samplers"
//              , "animations"
//              , "skins"
            };

            for (const auto& node : nodes)
            {
                read_object(node, json, gltf.get());
            }

            // Binary GLTF has a single buffer, so all buffer views data comes from the same buffer
            for (const auto& bufferView : gltf->_buffer_views)
            {
                _asset_reader.base_stream().seek(dataOffset + bufferView->_byte_offset, std::ios::beg);

                const auto data = _asset_reader.read_bytes(bufferView->_byte_length);

                bufferView->create();
                bufferView->set_data(bufferView->_byte_length, data.data());
            }

            return gltf;
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

        void ContentReader::read_object(const std::string& key, const json11::Json& value, SceneR::Graphics::Model* root)
        {
            auto typeReader = TypeReaderManager.get_by_reader_name(key);

            if (typeReader == nullptr)
            {
                throw ContentLoadException("Unknown type reader");
            }

            typeReader->read(value, _graphics_device, root);
        }
    }
}
