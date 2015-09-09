// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_BUFFERSREADER_HPP
#define CONTENT_READERS_BUFFERSREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        /**
         * Buffers reader
         */
        class BuffersReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the BuffersReader class.
             */
            BuffersReader();

            /**
             * Destructor
             */
            ~BuffersReader();

        public:
            /**
             * Reads the buffers contents.
             */
            void read(const json11::Json& value, ContentReaderContext& context) override;
        };
    }
}

#endif // CONTENT_READERS_BUFFERSREADER_HPP