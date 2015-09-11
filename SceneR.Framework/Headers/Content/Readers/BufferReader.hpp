// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_BUFFERREADER_HPP
#define CONTENT_READERS_BUFFERREADER_HPP

#include <Content/ContentTypeReader.hpp>
#include <Graphics/Buffer.hpp>

namespace SceneR
{
    namespace Content
    {
        /**
         * Buffers reader
         */
        template <>
        class ContentTypeReader<SceneR::Graphics::Buffer>
        {
        public:
            /**
             * Initializes a news instance of the BuffersReader class.
             */
            ContentTypeReader();

            /**
             * Destructor
             */
            ~ContentTypeReader();

        public:
            /**
             * Reads the buffers contents.
             */
            std::shared_ptr<SceneR::Graphics::Buffer> read(ContentReader*                              input
                                                         , const std::pair<std::string, json11::Json>& source);
        };
    }
}

#endif // CONTENT_READERS_BUFFERREADER_HPP
