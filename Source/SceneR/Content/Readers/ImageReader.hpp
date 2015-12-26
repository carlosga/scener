// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_IMAGEREADER_HPP
#define SCENER_CONTENT_READERS_IMAGEREADER_HPP

#include <Content/ContentTypeReader.hpp>
#include <Texture/Surface.hpp>

namespace SceneR
{
    namespace Content
    {
        /**
         * Image reader
         */
        template<>
        class ContentTypeReader<SceneR::Texture::Surface>
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
             * Reads the meshes contents.
             */
            std::shared_ptr<SceneR::Texture::Surface> read(gsl::not_null<ContentReader*>               input
                                                         , const std::pair<std::string, json11::Json>& source) const;
        };
    }
}

#endif  // SCENER_CONTENT_READERS_IMAGEREADER_HPP
