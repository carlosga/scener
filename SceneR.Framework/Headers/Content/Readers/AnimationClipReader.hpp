// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef ANIMATIONCLIPREADER_HPP
#define ANIMATIONCLIPREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Animation clip reader
         */
        class AnimationClipReader : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the AnimationClipReader class.
             */
            AnimationClipReader() = default;

        public:
            /**
             * Reads the index buffer contents from the given ContentReader.
             */
            virtual std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif  /* ANIMATIONCLIPREADER_HPP */
