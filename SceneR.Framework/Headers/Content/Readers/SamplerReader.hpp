// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_SAMPLERREADER_HPP
#define CONTENT_READERS_SAMPLERREADER_HPP

#include <Content/ContentTypeReader.hpp>
#include <Graphics/SamplerState.hpp>

namespace SceneR
{
    namespace Content
    {
        template <>
        class ContentTypeReader<SceneR::Graphics::SamplerState>
        {
        public:
            ContentTypeReader() = default;

            ~ContentTypeReader() = default;

        public:
            std::shared_ptr<SceneR::Graphics::SamplerState> read(Guide::not_null<ContentReader*>             input
                                                               , const std::pair<std::string, json11::Json>& value) const;
        };
    }
}

#endif //CONTENT_READERS_SAMPLERREADER_HPP
