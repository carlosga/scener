// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef INT32READER_HPP
#define INT32READER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Int32 reader
         */
        class Int32Reader : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the Int32Reader class.
             */
            Int32Reader() = default;

        public:
            /**
             * Reads the index buffer contents from the given ContentReader.
             */
            virtual std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif  /* INT32READER_HPP */
