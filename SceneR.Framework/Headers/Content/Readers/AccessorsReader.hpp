// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_ACCESSORSREADER_HPP
#define CONTENT_READERS_ACCESSORSREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        /**
         * Accessors reader
         */
        class AccessorsReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the BufferReader class.
             */
            AccessorsReader();

            /**
             * Destructor
             */
            ~AccessorsReader();

        public:
            /**
             * Reads the accessors contents.
             */
            void read(const json11::Json& value, ContentReaderContext& context) override;
        };
    }
}

#endif // CONTENT_READERS_ACCESSORSREADER_HPP

