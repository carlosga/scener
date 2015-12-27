// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_SHADERREADER_HPP
#define SCENER_CONTENT_READERS_SHADERREADER_HPP

#include "../ContentTypeReader.hpp"
#include "../../Graphics/Shader.hpp"

namespace SceneR
{
    namespace Content
    {
        template <>
        class ContentTypeReader<SceneR::Graphics::Shader>
        {
        public:
            ContentTypeReader() = default;

            ~ContentTypeReader() = default;

        public:
            std::shared_ptr<SceneR::Graphics::Shader> read(gsl::not_null<ContentReader*>               input
                                                         , const std::pair<std::string, json11::Json>& source) const;

        private:
            std::string load_shader_with_includes(gsl::not_null<ContentReader*> input
                                                , const std::string&            uri) const;
        };
    }
}

#endif // SCENER_CONTENT_READERS_SHADERREADER_HPP
