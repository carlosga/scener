// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_SHADERREADER_HPP
#define SCENER_CONTENT_READERS_SHADERREADER_HPP

#include "SceneR/Content/Readers/ContentTypeReader.hpp"

namespace SceneR { namespace Graphics { namespace OpenGL { class Shader; } } }

namespace SceneR { namespace Content { namespace Readers {

template <>
class ContentTypeReader<Graphics::OpenGL::Shader>
{
public:
    ContentTypeReader() = default;

public:
    auto read(ContentReader* input, const std::string& key, const json11::Json& source) const noexcept;

private:
    std::string load_shader_with_includes(ContentReader* input, const std::string& uri) const noexcept;
};

}}}

#endif // SCENER_CONTENT_READERS_SHADERREADER_HPP
