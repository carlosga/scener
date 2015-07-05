// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TEXTURE2DREADER_HPP
#define TEXTURE2DREADER_HPP

#include <cstdint>

#include <Graphics/SurfaceFormat.hpp>
#include <Content/ContentTypeReader.hpp>

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        /**
         * Texture 2D reader.
         */
        class Texture2DReader final : public ContentTypeReader
        {
        public:
            /**
             * Initializes a new instance of the Texture2DReader class.
             */
            Texture2DReader();

            /**
             * Destructor
             */
            ~Texture2DReader() override;

        public:
            /**
             * Reads the 2D texture contents from the given ContentReader.
             */
            std::shared_ptr<void> Read(ContentReader& input) override;

        private:
            SceneR::Graphics::SurfaceFormat DecodeFormat(const std::uint32_t& format) const;
        };
    }
}

#endif  /* TEXTURE2DREADER_HPP */
