// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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
            BasicEffectReader();

            /**
             * Destructor
             */
            ~BasicEffectReader();

        public:
            /**
             * Reads the basic effect contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif /* BASICEFFECTREADER_HPP */
