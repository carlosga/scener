// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SKINNEDEFFECTREADER_HPP
#define SKINNEDEFFECTREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Skinned Effect reader
         */
        class SkinnedEffectReader : public ContentTypeReader
        {
        public:
            /**
             * Initializes a news instance of the SkinnedEffectReader class.
             */
            SkinnedEffectReader();

            /**
             * Destructor
             */
            ~SkinnedEffectReader();

        public:
            /**
             * Reads the skinned effect contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif  /* SKINNEDEFFECTREADER_HPP */
