// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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
            KeyframeReader();

            /**
             * Destructor
             */
            ~KeyframeReader();

        public:
            /**
             * Reads the key frame contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif  /* KEYFRAMEREADER_HPP */
