// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/opengl/Shader.hpp"

#include <gsl_assert.h>

namespace scener { namespace graphics { namespace opengl {

Shader::Shader(const std::string& name, ShaderType type, const std::vector<std::uint8_t>& source) noexcept
    : Shader { name, type, std::string(source.begin(), source.end()) }
{
}

Shader::Shader(const std::string& name, ShaderType type, const std::string& source) noexcept
    : _id     { 0 }
    , _type   { type }
    , _name   { name }
    , _source { source }
{
}

Shader::~Shader() noexcept
{
    if (_id != 0)
    {
        glDeleteShader(_id);
        _id = 0;
    }
}

std::uint32_t Shader::id() const noexcept
{
    return _id;
}

const std::string& Shader::name() const noexcept
{
    return _name;
}

ShaderType Shader::type() const noexcept
{
    return _type;
}

void Shader::compile() noexcept
{
    if (is_compiled())
    {
        return;
    }

    // create the shader object
    _id = glCreateShader(static_cast<GLenum>(_type));

    Ensures(_id > 0);

    // Shader source
    const char* cstring = _source.c_str();
    glShaderSource(_id, 1, reinterpret_cast<const GLchar**>(&cstring), NULL);

    // Compile the shader source
    glCompileShader(_id);

    // Verify compilation state
    verify_compilation_state();
}

bool Shader::is_compiled() const noexcept
{
    bool result = false;

    if (_id != 0)
    {
        GLint status;
        glGetShaderiv(_id, GL_COMPILE_STATUS, &status);

        result = (status == GL_TRUE);
    }

    return result;
}

void Shader::verify_compilation_state()
{
    if (is_compiled())
    {
        return;
    }

    std::string msg("Compile failure in shader:\n");

    GLint infoLogLength;
    glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength)
    {
        auto compileErrorMessage = std::string("", static_cast<std::size_t>(infoLogLength));

        glGetShaderInfoLog(_id, infoLogLength, NULL, &compileErrorMessage[0]);

        msg += compileErrorMessage;
    }

    throw std::runtime_error(msg);
}

 }}}
