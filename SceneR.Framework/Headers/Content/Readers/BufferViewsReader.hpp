// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef BUFFERVIEWSSREADER_HPP
#define BUFFERVIEWSSREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        /**
         * Buffer views reader
         */
        class BufferViewsReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the BufferViewsReader class.
             */
            BufferViewsReader();

            /**
             * Destructor
             */
            ~BufferViewsReader();

        public:
            /**
             * Reads the buffers contents from the given ContentReader.
             */
            void Read(const json11::Json& value, SceneR::GLTF::Model* root) override;
        };
    }
}

#endif // BUFFERVIEWSSREADER_HPP
