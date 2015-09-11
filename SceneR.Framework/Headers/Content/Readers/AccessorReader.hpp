// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_ACCESSORSREADER_HPP
#define CONTENT_READERS_ACCESSORSREADER_HPP

#include <Content/ContentTypeReader.hpp>
#include <Graphics/Accessor.hpp>

namespace SceneR
{
    namespace Content
    {
        /**
         * Accessors reader
         */
        template <>
        class ContentTypeReader<SceneR::Graphics::Accessor>
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
             * Reads the accessors contents.
             */
            std::shared_ptr<SceneR::Graphics::Accessor> read(ContentReader*                              input
                                                           , const std::pair<std::string, json11::Json>& source);
        };
    }
}

#endif // CONTENT_READERS_ACCESSORSREADER_HPP

