// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_READERS_SHADERSREADER_HPP
#define CONTENT_READERS_SHADERSREADER_HPP

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
            std::shared_ptr<SceneR::Graphics::Shader> read(const std::pair<std::string, json11::Json>& source
                                                         , ContentReaderContext&                       context);
        };
    }
}

#endif //CONTENT_READERS_SHADERSREADER_HPP
