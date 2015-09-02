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
#include <GLTF/Model.hpp>

namespace json11
{
    class Json;
}

namespace SceneR
{
    namespace Content
    {
        class ContentTypeReader;

       /**
         * Reads application content from disk
         */
        class ContentReader final
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
            ContentReader(const std::u16string& assetName
                        , System::IO::Stream&   stream);

            /**
             * Releases all resources used by the current instance of the ContentReader class.
             */
            ~ContentReader();

        public:
            /**
             * Gets the name of the asset currently being read by this ContentReader.
             */
            const std::u16string& AssetName() const;

         public:
            std::shared_ptr<SceneR::GLTF::Model> LoadModel();

            /**
             * Reads a single object from the current stream.
             */
            void ReadObject(const std::string& key, const json11::Json& value, SceneR::GLTF::Model* root);

        private:
            bool ReadHeader();

        private:
            std::u16string           assetName;
            std::size_t              sharedResourceCount;
            System::IO::BinaryReader assetReader;

            friend class ContentManager;
        };
    }
}

#endif  /* CONTENTREADER_HPP */
