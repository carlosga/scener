// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_BUFFERVIEWREADER_HPP
#define SCENER_CONTENT_READERS_BUFFERVIEWREADER_HPP

#include "SceneR/Content/ContentTypeReader.hpp"
#include "SceneR/Content/Readers/BufferView.hpp"

namespace SceneR
{
    namespace Content
    {
        /**
         * Buffer views reader
         */
        template <>
        class ContentTypeReader<BufferView>
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
            std::shared_ptr<BufferView> read(gsl::not_null<ContentReader*>               input
                                           , const std::pair<std::string, json11::Json>& value) const;
        };
    }
}

#endif // SCENER_CONTENT_READERS_BUFFERVIEWREADER_HPP
