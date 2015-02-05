// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef BOUNDINGSPHEREREADER_HPP
#define BOUNDINGSPHEREREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * BoundingSphere reader
         */
        class BoundingSphereReader: public ContentTypeReader
        {
        public:
            /**
             * Initializes a new instance of the BoundingSphereReader class.
             */
            BoundingSphereReader() = default;

            /**
             * Releases all resources being used by this BoundingSphereReader.
             */
            virtual ~BoundingSphereReader() = default;

        public:
            /**
             * Reads the string contents from the given ContentReader.
             */
            virtual std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif /* BOUNDINGSPHEREREADER_HPP */
