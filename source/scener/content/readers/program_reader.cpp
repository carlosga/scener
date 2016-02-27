// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/program_reader.hpp"

#include <json11.hpp>

#include "scener/content/content_reader.hpp"
#include "scener/graphics/opengl/Buffer.hpp"
#include "scener/graphics/opengl/ConstantBuffer.hpp"
#include "scener/graphics/opengl/Program.hpp"
#include "scener/graphics/opengl/Shader.hpp"

namespace scener { namespace content { namespace readers {

namespace opengl = scener::graphics::opengl;

auto content_type_reader<opengl::program>::read(content_reader* input, const std::string& key, const json11::Json& source) const noexcept
{
    auto program = std::make_shared<opengl::program>();
    auto vshader = source["vertexShader"].string_value();
    auto fshader = source["fragmentShader"].string_value();

    program->name = key;
    program->add_shader(input->read_object<opengl::shader>(vshader));
    program->add_shader(input->read_object<opengl::shader>(fshader));
    program->link();

    return program;
}

}}}

