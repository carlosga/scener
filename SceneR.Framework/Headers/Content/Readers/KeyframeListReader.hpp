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
            KeyframeListReader();

            /**
             * Destructor
             */
            ~KeyframeListReader();

        public:
            /**
             * Reads the key frame list contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif  /* KEYFRAMELISTREADER_HPP */
