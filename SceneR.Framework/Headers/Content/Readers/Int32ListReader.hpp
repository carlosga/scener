// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef INT32LISTREADER_HPP
#define INT32LISTREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Int32 list reader
         */
        class Int32ListReader : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the Int32ListReader class.
             */
            Int32ListReader();

            /**
             * Destructor
             */
            ~Int32ListReader();

        public:
            /**
             * Reads the 32-bit integer list buffer contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif  /* INT32READER_HPP */
