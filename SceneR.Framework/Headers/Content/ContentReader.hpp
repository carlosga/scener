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
#include <Content/ContentReaderContext.hpp>

namespace json11
{
    class Json;
}

namespace SceneR
{
    namespace Graphics
    {
        class GraphicsDevice;
        class Model;
    }
}

namespace SceneR
{
    namespace Content
    {
        class ContentTypeReader;

       /**
         * Reads application content_manager from disk
         */
        class ContentReader final
        {
        private:
            static ContentTypeReaderManager TypeReaderManager;

        public:
            /**
             * Initializes a new instance of the ContentReader.
             * @param assetName the name of the asset to be readed.
             * @param contentManager the content_manager that owns this ContentReader.
             * @param stream the base stream.
             */
            ContentReader(const std::u16string&             assetName
                        , SceneR::Graphics::GraphicsDevice& graphicsDevice
                        , System::IO::Stream&               stream);

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
            void read_object(const std::string& key, const json11::Json& value, ContentReaderContext& context);

        private:
            std::u16string                    _asset_name;
            System::IO::BinaryReader          _asset_reader;
            SceneR::Graphics::GraphicsDevice& _graphics_device;
        };
    }
}

#endif  /* CONTENTREADER_HPP */
