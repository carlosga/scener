// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for full license information.

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
        class StringReader: public ContentTypeReader
        {
        public:
            /**
             * Initializes a new instance of the StringReader class
             */
            StringReader() = default;

            /**
             * Releases all resources being used by this StringReader.
             */
            virtual ~StringReader() = default;

        public:
            /**
             * Reads the string contents from the given ContentReader.
             */
            virtual std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif /* STRINGREADER_HPP */
