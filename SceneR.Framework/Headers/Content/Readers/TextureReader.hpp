// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_TEXTUREREADER_HPP
#define CONTENT_READERS_TEXTUREREADER_HPP

#include <Content/ContentTypeReader.hpp>
#include <Graphics/Texture2D.hpp>

namespace SceneR
{
    namespace Content
    {
        template <>
        class ContentTypeReader<SceneR::Graphics::Texture2D>
        {
        public:
            ContentTypeReader() = default;

            ~ContentTypeReader() = default;

        public:
            std::shared_ptr<SceneR::Graphics::Texture2D> read(gsl::not_null<ContentReader*>               input
                                                            , const std::pair<std::string, json11::Json>& source) const;
        };
    }
}

#endif //CONTENT_READERS_TEXTUREREADER_HPP
