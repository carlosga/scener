// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for full license information.

#ifndef BASICEFFECTREADER_HPP
#define BASICEFFECTREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * BasicEffect reader
         */
        class BasicEffectReader: public ContentTypeReader
        {
        public:
            /**
             * Initializes a new instance of the BasicEffectReader class.
             */
            BasicEffectReader() = default;

            /**
             * Releases all resources being used by this BasicEffectReader.
             */
            virtual ~BasicEffectReader() = default;

        public:
            /**
             * Reads the string contents from the given ContentReader.
             */
            virtual std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif /* BASICEFFECTREADER_HPP */
