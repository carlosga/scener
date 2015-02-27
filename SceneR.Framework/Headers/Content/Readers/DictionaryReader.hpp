// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef DICTIONARYREADER_HPP
#define DICTIONARYREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Dictionary reader
         */
        class DictionaryReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a new instance of the DictionaryReader class.
             */
            DictionaryReader();

            /**
             * Destructor
             */
            ~DictionaryReader() override;

        public:
            /**
             * Reads the Dicctionary<string, object> contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif /* DICTIONARYREADER_HPP */
