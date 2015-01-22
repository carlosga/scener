// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for full license information.

#ifndef TIMESPANREADER_HPP
#define TIMESPANREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * TimeSpan reader
         */
        class TimeSpanReader : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the TimeSpanReader class.
             */
            TimeSpanReader() = default;

            /**
             * Releases all resources being used by this TimeSpanReader.
             */
            virtual ~TimeSpanReader() = default;

        public:
            /**
             * Reads the index buffer contents from the given ContentReader.
             */
            virtual std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif  /* TIMESPANREADER_HPP */
