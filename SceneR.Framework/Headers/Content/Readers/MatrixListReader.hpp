// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MATRIXLISTREADER_HPP
#define MATRIXLISTREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Matrix list reader
         */
        class MatrixListReader : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the MatrixListReader class.
             */
            MatrixListReader() = default;

            /**
             * Releases all resources being used by this MatrixListReader.
             */
            virtual ~MatrixListReader() = default;

        public:
            /**
             * Reads the index buffer contents from the given ContentReader.
             */
            virtual std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif  /* MATRIXLISTREADER_HPP */
