// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef ANIMATIONCLIPMAPREADER_HPP
#define ANIMATIONCLIPMAPREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Animation clip reader
         */
        class AnimationClipMapReader : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the AnimationClipMapReader class.
             */
            AnimationClipMapReader() = default;

            /**
             * Releases all resources being used by this AnimationClipMapReader.
             */
            virtual ~AnimationClipMapReader() = default;

        public:
            /**
             * Reads the index buffer contents from the given ContentReader.
             */
            virtual std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif  /* ANIMATIONCLIPMAPREADER_HPP */
