// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/ProgramReader.hpp>

#include <json11.hpp>
#include <Content/ContentReader.hpp>
#include <Graphics/Shader.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Graphics::Program;
        using SceneR::Graphics::Shader;

        std::shared_ptr<Program> ContentTypeReader<Program>::read(Guide::not_null<ContentReader*>     input
                                                                , const std::pair<std::string, Json>& source) const
        {
            auto program        = std::make_shared<Program>();
            auto vertexShader   = source.second["vertexShader"].string_value();
            auto fragmentShader = source.second["fragmentShader"].string_value();

            program->name = source.first;
            program->create();
            program->add_shader(input->read_object<Shader>("shaders", vertexShader));
            program->add_shader(input->read_object<Shader>("shaders", fragmentShader));
            program->link();

            return program;
        }
    }
}

