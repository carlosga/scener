// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for full license information.

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
        class SkinningDataReader : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the SkinningDataReader class.
             */
            SkinningDataReader() = default;

            /**
             * Releases all resources being used by this SkinningDataReader.
             */
            virtual ~SkinningDataReader() = default;

        public:
            /**
             * Reads the index buffer contents from the given ContentReader.
             */
            virtual std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif  /* SKINNINGDATAREADER_HPP */
