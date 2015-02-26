// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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
        class TimeSpanReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the TimeSpanReader class.
             */
            TimeSpanReader();

            /**
             * Destructor
             */
            ~TimeSpanReader() override;

        public:
            /**
             * Reads the timespan contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif  /* TIMESPANREADER_HPP */
