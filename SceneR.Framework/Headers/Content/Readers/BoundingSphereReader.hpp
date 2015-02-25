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
            BoundingSphereReader();

            /**
             * Destructor
             */
            ~BoundingSphereReader();

        public:
            /**
             * Reads the bounding sphere contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif /* BOUNDINGSPHEREREADER_HPP */
