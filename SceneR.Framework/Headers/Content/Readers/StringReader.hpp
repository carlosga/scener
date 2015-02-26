// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef STRINGREADER_HPP
#define STRINGREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * String reader
         */
        class StringReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a new instance of the StringReader class
             */
            StringReader();

            /**
             * Destructor
             */
            ~StringReader() override;

        public:
            /**
             * Reads the string contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif /* STRINGREADER_HPP */
