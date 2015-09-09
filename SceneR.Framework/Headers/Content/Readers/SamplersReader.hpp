// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_SAMPLERSREADER_HPP
#define CONTENT_READERS_SAMPLERSREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class SamplersReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the SamplersReader class.
             */
            SamplersReader();

            /**
             * Destructor
             */
            ~SamplersReader();

        public:
            /**
             * Reads the samplers contents.
             */
            void read(const json11::Json& value, ContentReaderContext& context) override;
        };
    }
}

#endif //CONTENT_READERS_SAMPLERSREADER_HPP
