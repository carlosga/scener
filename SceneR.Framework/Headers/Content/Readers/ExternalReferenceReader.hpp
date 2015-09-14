// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_EXTERNALREFERENCE_HPP
#define CONTENT_READERS_EXTERNALREFERENCE_HPP

#include <cstdint>
#include <vector>

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        /**
         * Image reader
         */
        template<>
        class ContentTypeReader<std::vector<std::uint8_t>>
        {
        public:
            /**
             * Initializes a news instance of the ContentTypeReader class.
             */
            ContentTypeReader();

            /**
             * Destructor
             */
            ~ContentTypeReader();

        public:
            /**
             * Reads the meshes contents.
             */
            std::shared_ptr<std::vector<std::uint8_t>> read(ContentReader*                              input
                                                          , const std::pair<std::string, json11::Json>& source);
        };
    }
}

#endif  // CONTENT_READERS_EXTERNALREFERENCE_HPP
