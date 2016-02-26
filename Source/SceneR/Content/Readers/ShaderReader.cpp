// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/Readers/ShaderReader.hpp"

#include <regex>

#include <json11.hpp>

#include "SceneR/Content/ContentReader.hpp"
#include "SceneR/Graphics/OpenGL/Shader.hpp"

namespace scener { namespace content { namespace readers {

using json11::Json;
using scener::graphics::opengl::Shader;
using scener::graphics::opengl::ShaderType;

auto ContentTypeReader<Shader>::read(ContentReader* input, const std::string& key, const Json& source) const noexcept
{
    auto type    = static_cast<ShaderType>(source["type"].int_value());
    auto ssource = load_shader_with_includes(input, source["uri"].string_value());
    auto shader  = std::make_shared<Shader>(key, type, ssource);

    shader->compile();

    return shader;
}

std::string ContentTypeReader<Shader>::load_shader_with_includes(ContentReader* input, const std::string& uri) const noexcept
{
    auto buffer      = input->read_external_reference(uri);
    auto rx          = std::regex("[ ]*#[ ]*include[ ]+[\"](.*)[\"].*");
    auto fonly       = std::regex_constants::format_first_only;
    auto source      = std::string(buffer.begin(), buffer.end());
    auto source_copy = source;

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

