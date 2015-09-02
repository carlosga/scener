// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENTREADER_HPP
#define CONTENTREADER_HPP

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include <System/IO/BinaryReader.hpp>
#include <System/IO/Stream.hpp>
#include <Content/ContentTypeReaderManager.hpp>
#include <Content/SharedResourceAction.hpp>

namespace json11
{
    class Json;
}

namespace SceneR
{
    namespace Content
    {
        class ContentManager;
        class ContentTypeReader;

       /**
         * Reads application content from disk
         */
        class ContentReader final : public System::IO::BinaryReader
        {
        private:
            static ContentTypeReaderManager TypeReaderManager;

        public:
            /**
             * Initializes a new instance of the ContentReader.
             * @param assetName the name of the asset to be readed.
             * @param contentManager the content that owns this ContentReader.
             * @param stream the base stream.
             */
            ContentReader(const std::u16string&            assetName
                        , SceneR::Content::ContentManager& contentManager
                        , System::IO::Stream&              stream);

            /**
             * Releases all resources used by the current instance of the ContentReader class.
             */
            ~ContentReader();

        public:
            /**
             * Gets the name of the asset currently being read by this ContentReader.
             */
            const std::u16string& AssetName() const;

            /**
             * Gets the content manager that owns this ContentReader.
             */
            SceneR::Content::ContentManager& ContentManager();

         public:
            template <typename T>
            std::shared_ptr<T> Load();

            /**
             * Reads a single object from the current stream.
             */
            template <typename T>
            std::shared_ptr<T> ReadObject(const std::string& key, const json11::Json& value);

            /**
             * Reads a shared resource ID, and records it for subsequent fix-up.
             */
            void ReadSharedResource(const std::function<void(const std::shared_ptr<void>&)>& fixup);

            /**
             * Reads a link to an external file.
             * @returns The asset stored in the external file.
             */
            template <class T>
            std::shared_ptr<T> ReadExternalReference();

            void ReadSharedResources();

        private:
            bool ReadHeader();

        private:
            std::u16string                    assetName;
            SceneR::Content::ContentManager&  contentManager;
            std::size_t                       sharedResourceCount;
            std::vector<SharedResourceAction> fixupActions;

            friend class ContentManager;
        };
    }
}

#include <System/IO/Path.hpp>
#include <Content/ContentManager.hpp>
#include <Content/ContentTypeReader.hpp>
#include <Content/json11.hpp>

template <typename T>
std::shared_ptr<T> SceneR::Content::ContentReader::Load()
{
    std::string err;

    auto jsonOffset = ReadUInt32();
    auto jsonLength = ReadUInt32();
    auto external   = ReadBytes(jsonOffset - BaseStream().Position());
    auto jsonBin    = ReadBytes(jsonLength);

    auto str  = std::string(jsonBin.begin(), jsonBin.end());
    auto json = json11::Json::parse(str.c_str(), err);

    if (!err.empty())
    {
        throw ContentLoadException(err);
    }

    return this->ReadObject<T>("gltf", json);
}

template <class T>
std::shared_ptr<T> SceneR::Content::ContentReader::ReadObject(const std::string& key, const json11::Json& value)
{
    auto typeReader = TypeReaderManager.GetByReaderName(key);

    if (typeReader == nullptr)
    {
        throw ContentLoadException("Unknown type reader");
    }

    return std::static_pointer_cast<T>(typeReader->Read(*this, value));
}

template <class T>
std::shared_ptr<T> SceneR::Content::ContentReader::ReadExternalReference()
{
    auto assetName = this->ReadString();

    if (assetName.size() > 0)
    {
        assetName = System::IO::Path::Combine(System::IO::Path::GetDirectoryName(this->assetName), assetName);

        return this->contentManager.Load<T>(assetName);
    }

    return nullptr;
}

#endif  /* CONTENTREADER_HPP */
