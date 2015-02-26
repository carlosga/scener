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
        class AnimationClipMapReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the AnimationClipMapReader class.
             */
            AnimationClipMapReader();

            /**
             * Releases all resources being used by this AnimationClipMapReader.
             */
            ~AnimationClipMapReader() override;

        public:
            /**
             * Reads the animation clip contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif  /* ANIMATIONCLIPMAPREADER_HPP */
