// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/Readers/ProgramReader.hpp"

#include <json11.hpp>

#include "SceneR/Content/ContentReader.hpp"
#include "SceneR/Graphics/Program.hpp"
#include "SceneR/Graphics/Shader.hpp"
#include "SceneR/Graphics/OpenGL/Buffer.hpp"
#include "SceneR/Graphics/OpenGL/ConstantBuffer.hpp"

namespace SceneR { namespace Content { namespace Readers {

using json11::Json;
using SceneR::Graphics::Program;
using SceneR::Graphics::Shader;

auto ContentTypeReader<Program>::read(ContentReader* input, const std::string& key, const Json& source) const noexcept
{
    auto program        = std::make_shared<Program>();
    auto vertexShader   = source["vertexShader"].string_value();
    auto fragmentShader = source["fragmentShader"].string_value();

    program->name = key;
    program->create();
    program->add_shader(input->read_object<Shader>(vertexShader));
    program->add_shader(input->read_object<Shader>(fragmentShader));
    program->link();

    return program;
}

}}}

