// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_ACCESSORREADER_HPP
#define SCENER_CONTENT_READERS_ACCESSORREADER_HPP

#include <Content/ContentTypeReader.hpp>
#include <Content/Readers/Accessor.hpp>

namespace SceneR
{
    namespace Content
    {
        /**
         * Accessors reader
         */
        template <>
        class ContentTypeReader<Accessor>
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
            std::shared_ptr<Accessor> read(gsl::not_null<ContentReader*>               input
                                         , const std::pair<std::string, json11::Json>& source) const;
        };
    }
}

#endif // SCENER_CONTENT_READERS_ACCESSORREADER_HPP

