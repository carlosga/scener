// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for full license information.

#ifndef KEYFRAMEREADER_HPP
#define KEYFRAMEREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Keyframe reader
         */
        class KeyframeReader : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the KeyframeReader class.
             */
            KeyframeReader() = default;

            /**
             * Releases all resources being used by this KeyframeReader.
             */
            virtual ~KeyframeReader() = default;

        public:
            /**
             * Reads the index buffer contents from the given ContentReader.
             */
            virtual std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif  /* KEYFRAMEREADER_HPP */
