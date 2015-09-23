// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_ACCESSORREADER_HPP
#define CONTENT_READERS_ACCESSORREADER_HPP

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
            ContentTypeReader() = default;

            /**
             * Destructor
             */
            ~ContentTypeReader() = default;

        public:
            /**
             * Reads the accessors contents.
             */
            std::shared_ptr<SceneR::Graphics::Accessor> read(Guide::not_null<ContentReader*>             input
                                                           , const std::pair<std::string, json11::Json>& source);
        };
    }
}

#endif // CONTENT_READERS_ACCESSORREADER_HPP

