// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_CONTENTTYPEREADER_HPP
#define CONTENT_CONTENTTYPEREADER_HPP

#include <Content/ContentReaderContext.hpp>

namespace json11
{
    class Json;
}

namespace SceneR
{
    namespace Graphics
    {
        class GraphicsDevice;
        class Model;
    }
}

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Interface for content_manager type reader implementations.
         */
        class ContentTypeReader
        {
        public:
            /**
             * Releases all resources being used by this ContentTypeReader.
             */
            virtual ~ContentTypeReader();

        public:
            /**
             * Reads a object from the current stream.
             */
            virtual void read(const json11::Json& value, ContentReaderContext& context) = 0;
        };
    }
}

#endif  // CONTENT_CONTENTTYPEREADER_HPP
