// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_PROGRAMSREADER_HPP
#define CONTENT_READERS_PROGRAMSREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ProgramsReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the ProgramsReader class.
             */
            ProgramsReader();

            /**
             * Destructor
             */
            ~ProgramsReader();

        public:
            /**
             * Reads the programs contents.
             */
            void read(const json11::Json& value, ContentReaderContext& context) override;
        };
    }
}
#endif //CONTENT_READERS_PROGRAMSREADER_HPP
