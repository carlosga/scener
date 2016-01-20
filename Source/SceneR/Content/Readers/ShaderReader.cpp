// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/Readers/ShaderReader.hpp"

#include <regex>

#include <json11.hpp>

#include "SceneR/Content/ContentReader.hpp"
#include "SceneR/Graphics/Shader.hpp"
#include "SceneR/Graphics/ShaderInclude.hpp"

namespace SceneR { namespace Content { namespace Readers {

using json11::Json;
using SceneR::Graphics::Shader;
using SceneR::Graphics::ShaderInclude;
using SceneR::Graphics::ShaderType;

auto ContentTypeReader<Shader>::read(ContentReader* input, const std::string& key, const Json& source) const noexcept
{
    const auto type = static_cast<ShaderType>(source["type"].int_value());

    std::shared_ptr<Shader> shader = nullptr;

    if (GLAD_GL_ARB_shading_language_include)
    {
        auto extras = source["extras"];

        if (!extras.is_null())
        {
            const auto ssource   = input->read_external_reference(source["uri"].string_value());
            const auto& includes = extras["includes"];

            shader = std::make_shared<Shader>(key, type, ssource);

            if (!includes.is_null())
            {
                for (const auto& include : includes.object_items())
                {
                    shader->add_include(input->read_object<ShaderInclude>(include.first, include.second));
                }
            }
        }
    }

    if (shader == nullptr)
    {
        const auto ssource = load_shader_with_includes(input, source["uri"].string_value());

        shader = std::make_shared<Shader>(key, type, ssource);
    }

    shader->compile();

    return shader;
}

std::string ContentTypeReader<Shader>::load_shader_with_includes(ContentReader* input, const std::string& uri) const noexcept
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

}}}

