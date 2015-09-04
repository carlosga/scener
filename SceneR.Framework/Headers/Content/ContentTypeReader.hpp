// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENTTYPEREADER_HPP
#define CONTENTTYPEREADER_HPP

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
            virtual void read(const json11::Json&               value
                            , SceneR::Graphics::GraphicsDevice& graphicsDevice
                            , SceneR::Graphics::Model*          root) = 0;
        };
    }
}

#endif  /* CONTENTTYPEREADER_HPP */
