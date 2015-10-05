// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_BUFFERVIEWREADER_HPP
#define CONTENT_READERS_BUFFERVIEWREADER_HPP

#include <Content/ContentTypeReader.hpp>
#include <Graphics/BufferView.hpp>

namespace SceneR
{
    namespace Content
    {
        /**
         * Buffer views reader
         */
        template <>
        class ContentTypeReader<SceneR::Graphics::BufferView>
        {
        public:
            /**
             * Initializes a news instance of the ContentTypeReader class.
             */
            ContentTypeReader() = default;

            /**
             * Destructor
             */
            ~ContentTypeReader() = default;

        public:
            /**
             * Reads the buffer views contents.
             */
            std::shared_ptr<SceneR::Graphics::BufferView> read(gsl::not_null<ContentReader*>               input
                                                             , const std::pair<std::string, json11::Json>& value) const;
        };
    }
}

#endif // CONTENT_READERS_BUFFERVIEWREADER_HPP
