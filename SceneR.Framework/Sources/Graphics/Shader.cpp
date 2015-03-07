// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Shader.hpp>

#include <iostream>

#include <System/Text/Encoding.hpp>

using namespace System;
using namespace System::Text;
using namespace SceneR::Graphics;

const std::string Shader::ShaderIncludeRoot = "/SceneR/" ;

Shader::Shader(const ShaderType& shaderType, const String& shaderCode)
    : Shader { shaderType, shaderCode, std::map<System::String, System::String>() }
{
}

Shader::Shader(const ShaderType& shaderType, const String& shaderCode, const std::map<String, String>& shaderIncludes)
    : object         { 0 }
    , shaderType     { shaderType }
    , shaderCode     { shaderCode }
    , shaderIncludes { shaderIncludes }
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
    std::map<std::string, std::string> shaders = this->Convert();
    std::vector<const char*> paths(0);
    std::vector<int> pathLengths(0);

    // Process includes
    for (const auto& kvp : shaders)
    {
        paths.push_back(kvp.first.c_str());
        pathLengths.push_back(kvp.first.size());

        if (!glIsNamedStringARB(kvp.first.size(), kvp.first.c_str()))
        {
            glNamedStringARB(GL_SHADER_INCLUDE_ARB
                           , kvp.first.size()
                           , kvp.first.c_str()
                           , kvp.second.size()
                           , kvp.second.c_str());
        }
    }

    //create the shader object
    this->object = glCreateShader(static_cast<GLenum>(this->shaderType));

    if (this->object == 0)
    {
        throw std::runtime_error("glCreateShader failed");
    }

    // root shader
    std::string rootShader = Encoding::Convert(this->shaderCode);
    const char* cstring = rootShader.c_str();

    glShaderSource(this->object, 1, (const GLchar**)&cstring, NULL);

    // Compile the shader source
    glCompileShaderIncludeARB(this->object, paths.size(), (const GLchar**)&paths[0], &pathLengths[0]);

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

std::map<std::string, std::string> Shader::Convert()
{
    std::map<std::string, std::string> shaders;

    for (const auto& kvp : this->shaderIncludes)
    {
        shaders.emplace(ShaderIncludeRoot + Encoding::Convert(kvp.first), Encoding::Convert(kvp.second));
    }

    return shaders;
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
            auto compileErrorMessage = std::string("", static_cast<Size>(infoLogLength));

            glGetShaderInfoLog(this->object, infoLogLength, NULL, &compileErrorMessage[0]);

            msg += compileErrorMessage;
        }

        this->Dispose();

        throw std::runtime_error(msg);
    }
}
