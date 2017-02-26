// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_SHADER_READER_HPP
#define SCENER_CONTENT_READERS_SHADER_READER_HPP

#include "scener/content/readers/content_type_reader.hpp"

namespace scener::graphics::opengl { class shader; }

namespace scener::content::readers
{
    template <>
    class content_type_reader<graphics::opengl::shader>
    {
    public:
        content_type_reader() = default;

    public:
        auto read(content_reader* input, const std::string& key, const nlohmann::json& source) const noexcept;

    private:
        std::string load_shader(content_reader* input, const std::string& uri) const noexcept;
    };
}

#endif // SCENER_CONTENT_READERS_SHADER_READER_HPP
