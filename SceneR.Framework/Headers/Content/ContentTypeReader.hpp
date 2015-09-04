// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENTTYPEREADER_HPP
#define CONTENTTYPEREADER_HPP

#include <memory>

namespace json11
{
    class Json;
}

namespace SceneR
{
    namespace Graphics
    {
        class Model;
    }
}

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
            virtual ~ContentTypeReader();

        public:
            /**
             * Reads a object from the current stream.
             */
            virtual void Read(const json11::Json& value, SceneR::Graphics::Model* root) = 0;
        };
    }
}

#endif  /* CONTENTTYPEREADER_HPP */
