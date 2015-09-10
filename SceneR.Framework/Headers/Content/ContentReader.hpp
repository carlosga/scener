// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_CONTENTREADER_HPP
#define CONTENT_CONTENTREADER_HPP

#include <cstdint>
#include <memory>
#include <vector>
#include <string>

#include <System/IO/BinaryReader.hpp>
#include <System/IO/Stream.hpp>
#include <Content/ContentReaderContext.hpp>

namespace json11
{
    class Json;
}

namespace SceneR
{
    namespace Content
    {
        class ContentManager;

       /**
         * Reads application content_manager from disk
         */
        class ContentReader final
        {
        public:
            /**
             * Initializes a new instance of the ContentReader.
             * @param assetName the name of the asset to be readed.
             * @param contentManager the content_manager that owns this ContentReader.
             * @param stream the base stream.
             */
            ContentReader(const std::u16string&            assetName
                        , SceneR::Content::ContentManager* contentManager
                        , System::IO::Stream&              stream);

            /**
             * Releases all resources used by the current instance of the ContentReader class.
             */
            ~ContentReader();

        public:
            /**
             * Gets the name of the asset currently being read by this ContentReader.
             */
            const std::u16string& asset_name() const;

         public:
            std::shared_ptr<SceneR::Graphics::Model> read_asset();

            /**
             * Reads the header from the current stream.
             */
            bool read_header();

            /**
             * Reads a single object from the current stream.
             */
            template <typename T>
            std::shared_ptr<T> read_object(const std::pair<std::string, json11::Json>& source, ContentReaderContext& context);

            /**
             * Reads a link to an external file.
             * @returns The contents stored in the external file.
             */
            std::vector<std::uint8_t> read_external_reference(const std::u16string& assetName) const;

        private:
            std::u16string                   _asset_name;
            System::IO::BinaryReader         _asset_reader;
            SceneR::Content::ContentManager* _content_manager;
        };
    }
}

#endif  // CONTENT_CONTENTREADER_HPP
