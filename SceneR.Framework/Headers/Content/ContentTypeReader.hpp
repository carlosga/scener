// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_CONTENTTYPEREADER_HPP
#define CONTENT_CONTENTTYPEREADER_HPP

#include <memory>

#include <Content/ContentReaderContext.hpp>

namespace json11
{
    class Json;
}

namespace SceneR
{
    namespace Content
    {
        /**
         * Interface for content type reader implementations.
         */
        template <typename T>
        class ContentTypeReader
        {
        public:
            /**
             * Initializes a new instance of the ContentTypeReader class.
             */
            ContentTypeReader();

            /**
             * Releases all resources being used by this ContentTypeReader.
             */
            ~ContentTypeReader();

        public:
            /**
             * Reads a object from the current stream.
             */
            std::shared_ptr<T> read(const std::pair<std::string, json11::Json>& source, ContentReaderContext& context);
        };
    }
}

#endif  // CONTENT_CONTENTTYPEREADER_HPP
