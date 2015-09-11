// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_SHADERREADER_HPP
#define CONTENT_READERS_SHADERREADER_HPP

#include <Content/ContentTypeReader.hpp>
#include <Graphics/Shader.hpp>

namespace SceneR
{
    namespace Content
    {
        template <>
        class ContentTypeReader<SceneR::Graphics::Shader>
        {
        public:
            ContentTypeReader();
            ~ContentTypeReader();

        public:
            std::shared_ptr<SceneR::Graphics::Shader> read(ContentReader*                              input
                                                         , const std::pair<std::string, json11::Json>& source);
        };
    }
}

#endif //CONTENT_READERS_SHADERREADER_HPP
