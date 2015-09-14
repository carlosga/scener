// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_IMAGEREADER_HPP
#define CONTENT_READERS_IMAGEREADER_HPP

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
            ContentTypeReader();

            /**
             * Destructor
             */
            ~ContentTypeReader();

        public:
            /**
             * Reads the meshes contents.
             */
            std::shared_ptr<SceneR::Texture::Surface> read(ContentReader*                              input
                                                         , const std::pair<std::string, json11::Json>& source);
        };
    }
}

#endif  // CONTENT_READERS_IMAGEREADER_HPP
