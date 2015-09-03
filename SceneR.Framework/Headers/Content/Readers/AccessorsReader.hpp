// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef ACCESSORSREADER_HPP
#define ACCESSORSREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        /**
         * Accessors reader
         */
        class AccessorsReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the BufferReader class.
             */
            AccessorsReader();

            /**
             * Destructor
             */
            ~AccessorsReader();

        public:
            /**
             * Reads the buffers contents from the given ContentReader.
             */
            void Read(const json11::Json& value, SceneR::GLTF::Model* root) override;
        };
    }
}

#endif // ACCESSORSREADER_HPP

