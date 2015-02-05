// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENTTYPEREADER_HPP
#define CONTENTTYPEREADER_HPP

#include <memory>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Interface for content type reader implementations.
         */
        class ContentTypeReader
        {
        public:
            /**
             * Releases all resources being used by this ContentTypeReader.
             */
            virtual ~ContentTypeReader() = default;

        public:
            /**
             * Reads a object from the current stream.
             */
            virtual std::shared_ptr<void> Read(ContentReader& input) = 0;
        };
    }
}

#endif  /* CONTENTTYPEREADER_HPP */
