// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SKINNINGDATAREADER_HPP
#define SKINNINGDATAREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Skinning Data reader
         */
        class SkinningDataReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the SkinningDataReader class.
             */
            SkinningDataReader();

            /**
             * Destructor
             */
            ~SkinningDataReader() override;

        public:
            /**
             * Reads the skinning data contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif  /* SKINNINGDATAREADER_HPP */
