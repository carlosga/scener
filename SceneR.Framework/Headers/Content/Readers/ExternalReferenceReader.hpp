// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef EXTERNALREFERENCEREADER_HPP
#define EXTERNALREFERENCEREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * External reference reader
         */
        class ExternalReferenceReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a new instance of the ExternalReferenceReader class.
             */
            ExternalReferenceReader();

            /**
             * Destructor
             */
            ~ExternalReferenceReader() override;

        public:
            /**
             * Reads the external reference contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif /* EXTERNALREFERENCEREADER_HPP */
