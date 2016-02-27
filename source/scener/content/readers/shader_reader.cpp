// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/ShaderReader.hpp"

#include <regex>

#include <json11.hpp>

#include "scener/content/content_reader.hpp"
#include "scener/graphics/opengl/Shader.hpp"

namespace scener { namespace content { namespace readers {

namespace opengl = scener::graphics::opengl;

auto content_type_reader<opengl::shader>::read(content_reader* input, const std::string& key, const json11::Json& source) const noexcept
{
    auto type    = static_cast<opengl::shader_type>(source["type"].int_value());
    auto ssource = load_shader(input, source["uri"].string_value());
    auto shader  = std::make_shared<opengl::shader>(key, type, ssource);

    shader->compile();

    return shader;
}

std::string content_type_reader<opengl::shader>::load_shader(content_reader* input, const std::string& uri) const noexcept
{
    auto buffer = input->read_external_reference(uri);
    auto rx     = std::regex("[ ]*#[ ]*include[ ]+[\"](.*)[\"].*");
    auto fonly  = std::regex_constants::format_first_only;
    auto source = std::string(buffer.begin(), buffer.end());
    auto copy   = source;

    std::smatch m;

    while (std::regex_search(source, m, rx))
    {
        const auto include_buffer = input->read_external_reference(m[1].str());
        const auto include_source = std::string(include_buffer.begin(), include_buffer.end());

        copy   = std::regex_replace(copy, rx, include_source, fonly);
        source = m.suffix().str();
    }

    return copy;
}

}}}

