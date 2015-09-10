// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/ProgramReader.hpp>

#include <Content/json11.hpp>
#include <Graphics/Shader.hpp>
#include <System/Text/Encoding.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Graphics::Program;
        using SceneR::Graphics::Shader;
        using System::Text::Encoding;

        ContentTypeReader<Program>::ContentTypeReader()
        {
        }

        ContentTypeReader<Program>::~ContentTypeReader()
        {
        }

        std::shared_ptr<Program> ContentTypeReader<Program>::read(const std::pair<std::string, Json>& source
                                                                , ContentReaderContext&               context)
        {
            auto program = std::make_shared<Program>();

            program->name = Encoding::convert(source.first);
            program->create();
            program->add_shader(context.find_object<Shader>(source.second["vertexShader"].string_value()));
            program->add_shader(context.find_object<Shader>(source.second["fragmentShader"].string_value()));
            program->link();

            return program;
        }
    }
}

