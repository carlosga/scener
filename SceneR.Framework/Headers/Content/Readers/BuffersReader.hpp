// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef BUFFERSREADER_HPP
#define BUFFERSREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        /**
         * Buffers reader
         */
        class BuffersReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the BuffersReader class.
             */
            BuffersReader();

            /**
             * Destructor
             */
            ~BuffersReader();

        public:
            /**
             * Reads the buffers contents from the given ContentReader.
             */
            void Read(const json11::Json& value, SceneR::GLTF::Model* root) override;
        };
    }
}

#endif // BUFFERSREADER_HPP
