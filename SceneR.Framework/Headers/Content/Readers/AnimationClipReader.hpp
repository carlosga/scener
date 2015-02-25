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
            AnimationClipReader();

            /**
             * Destructor
             */
            ~AnimationClipReader();

        public:
            /**
             * Reads the animation clip contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif  /* ANIMATIONCLIPREADER_HPP */
