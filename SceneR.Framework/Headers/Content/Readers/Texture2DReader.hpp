// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TEXTURE2DREADER_HPP
#define TEXTURE2DREADER_HPP

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
        class Texture2DReader : public ContentTypeReader
        {
        public:
            /**
             * Initializes a new instance of the Texture2DReader class.
             */
            Texture2DReader() = default;

        public:
            /**
             * Reads the 2D texture contents from the given ContentReader.
             */
            virtual std::shared_ptr<void> Read(ContentReader& input) override;

        private:
            virtual SceneR::Graphics::SurfaceFormat DecodeFormat(const System::UInt32& format) const;
        };
    }
}

#endif  /* TEXTURE2DREADER_HPP */
