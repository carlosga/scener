// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/opengl/Program.hpp"

#include <gsl_assert.h>

#include "scener/graphics/opengl/Buffer.hpp"
#include "scener/graphics/opengl/ConstantBuffer.hpp"
#include "scener/graphics/opengl/Shader.hpp"

namespace scener { namespace graphics { namespace opengl {

using scener::graphics::opengl::constant_buffer;

program::program()
{
    create();
}

program::~program() noexcept
{
    if (_id != 0)
    {
        // Delete the shader program
        glDeleteProgram(_id);

        // Reset the shader program name
        _id = 0;
    }
}

std::uint32_t program::id() const noexcept
{
    return _id;
}

opengl::constant_buffer* program::constant_buffer() const noexcept
{
    return _constant_buffer.get();
}

void program::bind() const noexcept
{
    glUseProgram(_id);

    if (_constant_buffer != nullptr)
    {
        _constant_buffer->bind();
    }
}

void program::add_shader(const std::shared_ptr<shader>& shader) noexcept
{
    // compile the shader if necessary
    if (!shader->is_compiled())
    {
        shader->compile();
    }

    // attach the shader to the program
    glAttachShader(_id, shader->id());
}

void program::unbind() const noexcept
{
    if (_constant_buffer != nullptr)
    {
        _constant_buffer->unbind();
    }

    glUseProgram(0);
}

void program::link() noexcept
{
    // ... link the shader program
    glLinkProgram(_id);

    // ... verify program linking state
    verify_linking_state();

    // ... fill uniform buffer info
    _constant_buffer = std::make_unique<opengl::constant_buffer>("ConstantBuffer", _id);
}

std::map<std::string, std::size_t> program::get_uniform_offsets() const noexcept
{
    std::map<std::string, std::size_t> uniformOffsets;

    // Check the number of active uniforms
    std::int32_t activeUniforms = 0;

    glGetActiveUniformBlockiv(_id, _constant_buffer->index(), GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &activeUniforms);

    std::vector<std::int32_t> indices(activeUniforms, 0);
    std::vector<std::int32_t> nameLengths(activeUniforms, 0);
    std::vector<std::int32_t> offsets(activeUniforms, 0);
    std::vector<std::int32_t> types(activeUniforms, 0);

    glGetActiveUniformBlockiv(_id, _constant_buffer->index(), GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, indices.data());

    GLuint* address = reinterpret_cast<GLuint*>(indices.data());

    glGetActiveUniformsiv(_id, activeUniforms, address, GL_UNIFORM_NAME_LENGTH, nameLengths.data());
    glGetActiveUniformsiv(_id, activeUniforms, address, GL_UNIFORM_OFFSET     , offsets.data());
    glGetActiveUniformsiv(_id, activeUniforms, address, GL_UNIFORM_TYPE       , types.data());

    for (std::int32_t i = 0; i < activeUniforms; ++i)
    {
        GLsizei length = 0;
        GLint   size   = 0;
        GLenum  type   = GL_ZERO;
        auto    uname   = std::vector<char>(nameLengths[i], 0);

        glGetActiveUniform(_id, indices[i], nameLengths[i], &length, &size, &type, uname.data());

        std::string uniformName = { uname.begin(), uname.begin() + length };

        auto pos = uniformName.find("[0]");
        if (pos != std::string::npos)
        {
            uniformName.replace(pos, pos + 3, "");
        }

        uniformOffsets[uniformName] = offsets[i];
    }

    return uniformOffsets;
}

void program::activate_subroutine(shader_type stage, std::uint32_t index) const noexcept
{
    glUniformSubroutinesuiv(static_cast<GLenum>(stage), 1, &index);
}

void program::create() noexcept
{
    // ... Create the program object
    _id = glCreateProgram();

    Ensures(_id > 0);
}

void program::verify_linking_state()
{
    // ... verify program linking
    GLint status;
    glGetProgramiv(_id, GL_LINK_STATUS, &status);

    if (status == GL_FALSE)
    {
        auto msg = std::string("Program linking failure: ");

        GLint length;
        glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &length);

        if (length)
        {
            std::string linkErrorMessage("", static_cast<std::size_t>(length));

            glGetProgramInfoLog(_id, length, NULL, &linkErrorMessage[0]);

            msg += linkErrorMessage;
        }

        throw std::runtime_error(msg);
    }
}

}}}
