// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef KEYFRAMELISTREADER_HPP
#define KEYFRAMELISTREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Keyframe list reader
         */
        class KeyframeListReader : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the KeyframeListReader class.
             */
            KeyframeListReader() = default;

            /**
             * Releases all resources being used by this KeyframeListReader.
             */
            virtual ~KeyframeListReader() = default;

        public:
            /**
             * Reads the index buffer contents from the given ContentReader.
             */
            virtual std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif  /* KEYFRAMELISTREADER_HPP */
