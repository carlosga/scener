// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Shader.hpp>

#include <System/Text/Encoding.hpp>

using namespace System;
using namespace System::Text;
using namespace SceneR::Graphics;

Shader::Shader(const String& shaderCode, const ShaderType& shaderType)
    : object     { 0 }
    , shaderCode { shaderCode }
    , shaderType { shaderType }
{
}

Shader::~Shader()
{
}

void Shader::Dispose()
{
    if (this->object != 0)
    {
        glDeleteShader(this->object);
        this->object = 0;
    }
}

void Shader::Compile()
{
    //create the shader object
    this->object = glCreateShader(static_cast<GLenum>(this->shaderType));

    if (this->object == 0)
    {
        throw std::runtime_error("glCreateShader failed");
    }

    // Set the source code
    auto  temp = Encoding::Convert(this->shaderCode);
    auto* code = temp.c_str();
    glShaderSource(this->object, 1, (const GLchar**)&code, NULL);

    // Compile the shader source
    glCompileShader(this->object);

    // Verify compilation state
    this->VerifyCompilationState();
}

Boolean Shader::IsCompiled() const
{
    bool result = false;

    if (this->object != 0)
    {
        GLint status;
        glGetShaderiv(this->object, GL_COMPILE_STATUS, &status);

        result = (status == GL_TRUE);
    }

    return result;
}

void Shader::VerifyCompilationState()
{
    if (!this->IsCompiled())
    {
        std::string msg("Compile failure in shader:\n");

        GLint infoLogLength;
        glGetShaderiv(this->object, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength)
        {
            auto compileErrorMessage = std::string("", infoLogLength);

            glGetShaderInfoLog(this->object, infoLogLength, NULL, &compileErrorMessage[0]);

            msg += compileErrorMessage;
        }

        this->Dispose();

        throw std::runtime_error(msg);
    }
}
