// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TEXTUREREADER_HPP
#define TEXTUREREADER_HPP

#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Texture reader
         */
        class TextureReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a new instance of the TextureReader class.
             */
            TextureReader();

            /**
             * Destructor
             */
            ~TextureReader() override;

        public:
            /**
             * Reads the texture contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input) override;
        };
    }
}

#endif /* TEXTUREREADER_HPP */
