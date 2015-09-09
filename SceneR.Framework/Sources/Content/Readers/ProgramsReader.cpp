// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/ProgramsReader.hpp>

#include <Content/json11.hpp>
#include <Graphics/Program.hpp>
#include <Graphics/Shader.hpp>
#include <System/Text/Encoding.hpp>

namespace SceneR
{
    namespace Content
    {
        using SceneR::Graphics::Program;
        using SceneR::Graphics::Shader;
        using System::Text::Encoding;

        ProgramsReader::ProgramsReader()
        {
        }

        ProgramsReader::~ProgramsReader()
        {
        }

        void ProgramsReader::read(const json11::Json& value, ContentReaderContext& context)
        {
            // TODO : Handle program attributes

            for (const auto& source : value["programs"].object_items())
            {
                auto program = std::make_shared<Program>();

                program->name = Encoding::convert(source.first);
                program->create();
                program->add_shader(context.find_object<Shader>(source.second["vertexShader"].string_value()));
                program->add_shader(context.find_object<Shader>(source.second["fragmentShader"].string_value()));
                program->link();

                context.programs.push_back(program);
            }
        }
    }
}

