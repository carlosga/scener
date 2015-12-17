// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/ShaderReader.hpp>

#include <regex>

#include <json11.hpp>
#include <Content/ContentReader.hpp>
#include <Graphics/ShaderInclude.hpp>
#include <Graphics/ShaderType.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Graphics::Shader;
        using SceneR::Graphics::ShaderInclude;
        using SceneR::Graphics::ShaderType;

        std::shared_ptr<Shader> ContentTypeReader<Shader>::read(gsl::not_null<ContentReader*>       input
                                                              , const std::pair<std::string, Json>& source) const
        {
            auto name    = source.first;
            auto type    = static_cast<ShaderType>(source.second["type"].int_value());
            auto ssource = load_shader_with_includes(input, source.second["uri"].string_value());
            auto shader  = std::make_shared<Shader>(name, type, ssource);

            shader->compile();

            return shader;
        }

        std::string ContentTypeReader<Shader>::load_shader_with_includes(gsl::not_null<ContentReader*> input
                                                                       , const std::string&            uri) const
        {
            auto buffer = input->read_external_reference(uri);
            auto source = std::string(buffer.begin(), buffer.end());
            auto rx     = std::regex("[ ]*#[ ]*include[ ]+[\"](.*)[\"].*");

            std::smatch m;
            auto source_copy = source;
            auto fonly       = std::regex_constants::format_first_only;

            while (std::regex_search(source, m, rx))
            {
                auto include_buffer = input->read_external_reference(m[1].str());
                auto include_source = std::string(include_buffer.begin(), include_buffer.end());

                source_copy = std::regex_replace(source_copy, rx, include_source, fonly);
                source      = m.suffix().str();
            }

            return source_copy;
        }
    }
}

