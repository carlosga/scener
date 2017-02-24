// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/opengl/shader.hpp"

#include <gsl/gsl_assert>

namespace scener { namespace graphics { namespace opengl {

shader::shader(const std::string& name, shader_type type, const std::vector<std::uint8_t>& source) noexcept
    : shader { name, type, std::string(source.begin(), source.end()) }
{
}

shader::shader(const std::string& name, shader_type type, const std::string& source) noexcept
    : _id     { 0 }
    , _type   { type }
    , _name   { name }
    , _source { source }
{
}

shader::~shader() noexcept
{
    if (_id != 0)
    {
        glDeleteShader(_id);
        _id = 0;
    }
}

std::uint32_t shader::id() const noexcept
{
    return _id;
}

const std::string& shader::name() const noexcept
{
    return _name;
}

shader_type shader::type() const noexcept
{
    return _type;
}

void shader::compile() noexcept
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

bool shader::is_compiled() const noexcept
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

void shader::verify_compilation_state()
{
    if (is_compiled())
    {
        return;
    }

    std::string msg("Compile failure in shader:\n");

    GLint length;
    glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &length);

    if (length)
    {
        auto compileErrorMessage = std::string("", static_cast<std::size_t>(length));

        glGetShaderInfoLog(_id, length, NULL, &compileErrorMessage[0]);

        msg += compileErrorMessage;
    }

    throw std::runtime_error(msg);
}

 }}}
