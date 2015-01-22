// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for full license information.

#ifndef INDEXBUFFERREADER_HPP
#define INDEXBUFFERREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Index buffer reader.
         */
        class IndexBufferReader : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the IndexBufferReader class.
             */
            IndexBufferReader() = default;

            /**
             * Releases all resources being used by this IndexBufferReader.
             */
            virtual ~IndexBufferReader() = default;

        public:
            /**
             * Reads the index buffer contents from the given ContentReader.
             */
            virtual std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif  /* INDEXBUFFERREADER_HPP */
