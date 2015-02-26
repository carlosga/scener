// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MATRIXREADER_HPP
#define MATRIXREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Matrix reader
         */
        class MatrixReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the MatrixReader class.
             */
            MatrixReader();

            /**
             * Destructor
             */
            ~MatrixReader() override;

        public:
            /**
             * Reads the matrix contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif  /* MATRIXREADER_HPP */
