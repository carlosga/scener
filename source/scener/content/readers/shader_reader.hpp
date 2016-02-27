// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_SHADERREADER_HPP
#define SCENER_CONTENT_READERS_SHADERREADER_HPP

#include "scener/content/readers/content_type_reader.hpp"

namespace scener { namespace graphics { namespace opengl { class shader; } } }

namespace scener { namespace content { namespace readers {

template <>
class content_type_reader<graphics::opengl::shader>
{
public:
    content_type_reader() = default;

public:
    auto read(content_reader* input, const std::string& key, const json11::Json& source) const noexcept;

private:
    std::string load_shader(content_reader* input, const std::string& uri) const noexcept;
};

}}}

#endif // SCENER_CONTENT_READERS_SHADERREADER_HPP