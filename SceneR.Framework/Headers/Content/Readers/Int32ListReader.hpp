// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for full license information.

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
            Int32ListReader() = default;

            /**
             * Releases all resources being used by this Int32ListReader.
             */
            virtual ~Int32ListReader() = default;

        public:
            /**
             * Reads the index buffer contents from the given ContentReader.
             */
            virtual std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif  /* INT32READER_HPP */
