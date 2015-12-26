// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_BUFFERREADER_HPP
#define SCENER_CONTENT_READERS_BUFFERREADER_HPP

#include <Content/ContentTypeReader.hpp>
#include <Content/Readers/Buffer.hpp>

namespace SceneR
{
    namespace Content
    {
        /**
         * Buffers reader
         */
        template <>
        class ContentTypeReader<Buffer>
        {
        public:
            /**
             * Initializes a news instance of the BuffersReader class.
             */
            ContentTypeReader() = default;

            /**
             * Destructor
             */
            ~ContentTypeReader() = default;

        public:
            /**
             * Reads the buffers contents.
             */
            std::shared_ptr<Buffer> read(gsl::not_null<ContentReader*>               input
                                       , const std::pair<std::string, json11::Json>& source) const;
        };
    }
}

#endif // SCENER_CONTENT_READERS_BUFFERREADER_HPP
