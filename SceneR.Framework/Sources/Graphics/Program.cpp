// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Program.hpp>

#include <cassert>

#include <Graphics/Shader.hpp>

namespace SceneR
{
    namespace Graphics
    {
        Program::Program()
            : name ()
        {
        }

        Program::~Program()
        {
        }

        void Program::dispose()
        {
            if (_id != 0)
            {
                // Delete the shader program
                glDeleteProgram(_id);

                // Reset the shader program name
                _id = 0;
            }
        }

        std::uint32_t Program::id() const
        {
            return _id;
        }

        void Program::create()
        {
            // ... Create the program object
            _id = glCreateProgram();

            assert(_id != 0);
        }

        void Program::add_shader(std::shared_ptr<Shader> shader)
        {
            // compile the shader if necessary
            if (!shader->is_compiled())
            {
                shader->compile();
            }

            // attach the shader to the program
            glAttachShader(_id, shader->id());
        }

        void Program::link()
        {
            // ... link the shader program
            glLinkProgram(_id);

            // ... verify program linking state
            verify_linking_state();
        }

        void Program::verify_linking_state()
        {
            // ... verify program linking
            GLint status;
            glGetProgramiv(_id, GL_LINK_STATUS, &status);

            if (status == GL_FALSE)
            {
                auto msg = std::string("Program linking failure: ");

                GLint infoLogLength;
                glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &infoLogLength);

                if (infoLogLength)
                {
                    std::string linkErrorMessage("", static_cast<std::size_t>(infoLogLength));

                    glGetProgramInfoLog(_id, infoLogLength, NULL, &linkErrorMessage[0]);

                    msg += linkErrorMessage;
                }

                dispose();

                throw std::runtime_error(msg);
            }
        }
    }
}
