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
            const auto name = source.first;
            const auto type = static_cast<ShaderType>(source.second["type"].int_value());

            std::shared_ptr<Shader> shader = nullptr;

            if (GLAD_GL_ARB_shading_language_include)
            {
                auto extras = source.second["extras"];

                if (!extras.is_null())
                {
                    const auto ssource   = input->read_external_reference(source.second["uri"].string_value());
                    const auto& includes = extras["includes"];

                    shader = std::make_shared<Shader>(name, type, ssource);

                    if (!includes.is_null())
                    {
                        for (const auto& include : includes.object_items())
                        {
                            shader->add_include(input->read_object<ShaderInclude>(include));
                        }
                    }
                }
            }

            if (shader == nullptr)
            {
                const auto ssource = load_shader_with_includes(input, source.second["uri"].string_value());

                shader = std::make_shared<Shader>(name, type, ssource);
            }

            shader->compile();

            return shader;
        }

        std::string ContentTypeReader<Shader>::load_shader_with_includes(gsl::not_null<ContentReader*> input
                                                                       , const std::string&            uri) const
        {
            const auto buffer      = input->read_external_reference(uri);
            const auto rx          = std::regex("[ ]*#[ ]*include[ ]+[\"](.*)[\"].*");
            const auto fonly       = std::regex_constants::format_first_only;
            auto       source      = std::string(buffer.begin(), buffer.end());
            auto       source_copy = source;

            std::smatch m;

            while (std::regex_search(source, m, rx))
            {
                const auto include_buffer = input->read_external_reference(m[1].str());
                const auto include_source = std::string(include_buffer.begin(), include_buffer.end());

                source_copy = std::regex_replace(source_copy, rx, include_source, fonly);
                source      = m.suffix().str();
            }

            return source_copy;
        }
    }
}

