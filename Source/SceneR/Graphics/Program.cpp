// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "Program.hpp"

#include <gsl_assert.h>

#include "Shader.hpp"

namespace SceneR
{
    namespace Graphics
    {
        void Program::dispose()
        {
            if (_id != 0)
            {
                // Delete the uniform buffer object
                _uniform_buffer->dispose();
                _uniform_buffer.reset();

                // Delete the shader program
                glDeleteProgram(_id);

                // Reset the shader program name
                _id = 0;
            }
        }

        std::uint32_t Program::id() const noexcept
        {
            return _id;
        }

        UniformBufferObject* Program::uniform_buffer() const noexcept
        {
            return _uniform_buffer.get();
        }

        void Program::create()
        {
            // ... Create the program object
            _id = glCreateProgram();

            Ensures(_id > 0);
        }

        void Program::bind() const
        {
            glUseProgram(_id);
            _uniform_buffer->bind();
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

        void Program::unbind() const
        {
            _uniform_buffer->unbind();
            glUseProgram(0);
        }

        void Program::link()
        {
            // ... link the shader program
            glLinkProgram(_id);

            // ... verify program linking state
            verify_linking_state();

            // ... fill uniform buffer info
            _uniform_buffer = std::make_unique<UniformBufferObject>("ConstantBuffer", _id);
            _uniform_buffer->create();
        }

        std::map<std::string, std::size_t> Program::get_uniform_offsets() const
        {
            std::map<std::string, std::size_t> uniformOffsets;

            // Check the number of active uniforms
            std::int32_t activeUniforms = 0;

            glGetActiveUniformBlockiv(_id, _uniform_buffer->index(), GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &activeUniforms);

            std::vector<std::int32_t> indices(activeUniforms, 0);
            std::vector<std::int32_t> nameLengths(activeUniforms, 0);
            std::vector<std::int32_t> offsets(activeUniforms, 0);
            std::vector<std::int32_t> types(activeUniforms, 0);

            glGetActiveUniformBlockiv(_id, _uniform_buffer->index(), GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, indices.data());

            GLuint* address = reinterpret_cast<GLuint*>(indices.data());

            glGetActiveUniformsiv(_id, activeUniforms, address, GL_UNIFORM_NAME_LENGTH, nameLengths.data());
            glGetActiveUniformsiv(_id, activeUniforms, address, GL_UNIFORM_OFFSET     , offsets.data());
            glGetActiveUniformsiv(_id, activeUniforms, address, GL_UNIFORM_TYPE       , types.data());

            for (std::int32_t i = 0; i < activeUniforms; i++)
            {
                GLsizei length = 0;
                GLint   size   = 0;
                GLenum  type   = GL_ZERO;
                auto    name   = std::vector<char>(nameLengths[i], 0);

                glGetActiveUniform(_id, indices[i], nameLengths[i], &length, &size, &type, name.data());

                std::string uniformName = { name.begin(), name.begin() + length };

                auto pos = uniformName.find("[0]");
                if (pos != std::string::npos)
                {
                    uniformName.replace(pos, pos + 3, "");
                }

                uniformOffsets[uniformName] = offsets[i];
            }

            return uniformOffsets;
        }

        void Program::activate_subroutine(const ShaderType& type, const std::uint32_t& subroutineIndex) const
        {
            glUniformSubroutinesuiv(static_cast<GLenum>(type), 1, &subroutineIndex);
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
