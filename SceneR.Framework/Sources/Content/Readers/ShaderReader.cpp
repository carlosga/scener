// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/ShaderReader.hpp>

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
            auto name   = source.first;
            auto type   = static_cast<ShaderType>(source.second["type"].int_value());
            auto code   = input->read_external_reference(source.second["uri"].string_value());
            auto shader = std::make_shared<Shader>(name, type, code);
            auto extras = source.second["extras"];

            if (!extras.is_null())
            {
                const auto& includes = extras["includes"];

                if (!includes.is_null())
                {
                    for (const auto& include : includes.object_items())
                    {
                        shader->add_include(input->read_object<ShaderInclude>(include));
                    }
                }
            }

            shader->compile();

            return shader;
        }
    }
}

