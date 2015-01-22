// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for full license information.

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
            SkinnedEffectReader() = default;

            /**
             * Releases all resources being used by this SkinnedEffectReader.
             */
            virtual ~SkinnedEffectReader() = default;

        public:
            /**
             * Reads the index buffer contents from the given ContentReader.
             */
            virtual std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif  /* SKINNEDEFFECTREADER_HPP */
