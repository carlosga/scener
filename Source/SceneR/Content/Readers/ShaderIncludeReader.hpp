// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_SHADERINCLUDEREADER_HPP
#define SCENER_CONTENT_READERS_SHADERINCLUDEREADER_HPP

#include <Content/ContentTypeReader.hpp>
#include <Graphics/ShaderInclude.hpp>

namespace SceneR
{
    namespace Content
    {
        template <>
        class ContentTypeReader<SceneR::Graphics::ShaderInclude>
        {
        public:
            ContentTypeReader() = default;

            ~ContentTypeReader() = default;

        public:
            std::shared_ptr<SceneR::Graphics::ShaderInclude> read(gsl::not_null<ContentReader*>               input
                                                                , const std::pair<std::string, json11::Json>& source) const;
        };
    }
}

#endif // SCENER_CONTENT_READERS_SHADERINCLUDEREADER_HPP
