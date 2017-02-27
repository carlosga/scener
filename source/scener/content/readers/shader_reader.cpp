// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/shader_reader.hpp"

#include <regex>

#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/constants.hpp"
#include "scener/graphics/opengl/shader.hpp"

namespace scener::content::readers
{
    using nlohmann::json;
    using scener::graphics::opengl::shader;
    using scener::graphics::opengl::shader_type;
    using namespace scener::content::gltf;

    auto content_type_reader<shader>::read(content_reader* input, const std::string& key, const json& source) const noexcept
    {
        auto type     = static_cast<shader_type>(source[k_type].get<std::int32_t>());
        auto ssource  = load_shader(input, source[k_uri].get<std::string>());
        auto instance = std::make_shared<shader>(key, type, ssource);

        instance->compile();

        return instance;
    }

    std::string content_type_reader<shader>::load_shader(content_reader* input, const std::string& uri) const noexcept
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
}

