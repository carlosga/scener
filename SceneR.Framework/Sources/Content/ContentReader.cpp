// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/ContentReader.hpp>

#include <iostream>

#include <System/IO/BinaryReader.hpp>
#include <Content/ContentLoadException.hpp>
#include <Content/ContentTypeReader.hpp>
#include <Content/json11.hpp>
#include <Graphics/BufferObject.hpp>
#include <GLTF/Model.hpp>

namespace SceneR
{
    namespace Content
    {
        using System::IO::Stream;
        using json11::Json;

        ContentTypeReaderManager ContentReader::TypeReaderManager;

        ContentReader::ContentReader(const std::u16string& assetName
                                   , Stream&               stream)
            : assetName           { assetName }
            , sharedResourceCount { 0 }
            , assetReader         { stream }
        {
        }

        ContentReader::~ContentReader()
        {
            this->assetReader.Close();
            this->sharedResourceCount = 0;
        }

        const std::u16string& ContentReader::AssetName() const
        {
            return this->assetName;
        }

        std::shared_ptr<SceneR::GLTF::Model> ContentReader::ReadAsset()
        {
            using SceneR::GLTF::Model;
            using SceneR::GLTF::Accessor;
            using SceneR::GLTF::Buffer;
            using SceneR::GLTF::BufferView;

            std::string err;

            auto jsonOffset = this->assetReader.ReadUInt32();
            auto jsonLength = this->assetReader.ReadUInt32();
            auto dataOffset = this->assetReader.BaseStream().Position();
            auto dataLength = jsonOffset - dataOffset;

            this->assetReader.BaseStream().Seek(jsonOffset, std::ios::beg);

            auto buffer = this->assetReader.ReadBytes(jsonLength);
            auto json   = json11::Json::parse(reinterpret_cast<char*>(buffer.data()), err);

            buffer.clear();

            if (!err.empty())
            {
                throw ContentLoadException(err);
            }

            auto gltf = std::make_shared<Model>();

            ReadObject("buffers"     , json, gltf.get());
            ReadObject("bufferViews" , json, gltf.get());
            ReadObject("accessors"   , json, gltf.get());
            ReadObject("techniques"  , json, gltf.get());
            ReadObject("materials"   , json, gltf.get());
            ReadObject("meshes"      , json, gltf.get());

            // ReadObject("lights", json, gltf.get());
            // ReadObject("cameras", json, gltf.get());
            // ReadObject("nodes", json, gltf.get());
            // ReadObject("images", json, gltf.get());
            // ReadObject("textures", json, gltf.get());
            // ReadObject("shaders", json, gltf.get());
            // ReadObject("programs", json, gltf.get());
            // ReadObject("samplers", json, gltf.get());
            // ReadObject("animations", json, gltf.get());
            // ReadObject("skins", json, gltf.get());

            // TODO: Process external data references
            // Binary GLTF has a single buffer with everything on it

//            this->assetReader.BaseStream().Seek(dataOffset, std::ios::beg);

//            const auto data = this->assetReader.ReadBytes(dataLength);

//            for (const auto bufferView : gltf->bufferViews)
//            {
//                bufferView.SetData(data, bufferView->byteOffset, bufferView->byteLength);
//            }

            return gltf;
        }

        bool ContentReader::ReadHeader()
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
            auto magic = this->assetReader.ReadBytes(4);
            auto mstr  = std::string(magic.begin(), magic.end());

            if (mstr != "glTF")
            {
                return false;
            }

            this->assetReader.ReadUInt32();   // version
            this->assetReader.ReadUInt32();   // file length

            return true;
        }

        void ContentReader::ReadObject(const std::string& key, const json11::Json& value, SceneR::GLTF::Model* root)
        {
            auto typeReader = TypeReaderManager.GetByReaderName(key);

            if (typeReader == nullptr)
            {
                throw ContentLoadException("Unknown type reader");
            }

            typeReader->Read(value, root);
        }
    }
}
