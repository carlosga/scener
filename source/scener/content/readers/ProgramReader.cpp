// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/ProgramReader.hpp"

#include <json11.hpp>

#include "scener/content/content_reader.hpp"
#include "scener/graphics/opengl/Buffer.hpp"
#include "scener/graphics/opengl/ConstantBuffer.hpp"
#include "scener/graphics/opengl/Program.hpp"
#include "scener/graphics/opengl/Shader.hpp"

namespace scener { namespace content { namespace readers {

using json11::Json;

auto content_type_reader<graphics::opengl::Program>::read(content_reader* input, const std::string& key, const Json& source) const noexcept
{
    auto program        = std::make_shared<graphics::opengl::Program>();
    auto vertexShader   = source["vertexShader"].string_value();
    auto fragmentShader = source["fragmentShader"].string_value();

    program->name = key;
    program->add_shader(input->read_object<graphics::opengl::Shader>(vertexShader));
    program->add_shader(input->read_object<graphics::opengl::Shader>(fragmentShader));
    program->link();

    return program;
}

}}}

