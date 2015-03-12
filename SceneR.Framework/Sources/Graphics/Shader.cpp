// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Shader.hpp>

#include <iostream>

#include <System/Text/Encoding.hpp>
#include <Graphics/ShaderManager.hpp>

using namespace System;
using namespace System::Text;
using namespace SceneR::Graphics;

Shader::Shader(const String& name, const ShaderType& type, const std::string& source)
    : Shader { name, type, source, std::vector<std::string>() }
{
}

Shader::Shader(const String&                   name
             , const ShaderType&               type
             , const std::string&              source
             , const std::vector<std::string>& includes)
    : name     { name }
    , id       { 0 }
    , type     { type }
    , source   { source }
    , includes { includes }
{

}

Shader::~Shader()
{
}

void Shader::Dispose()
{
    if (this->id != 0)
    {
        glDeleteShader(this->id);
        this->id = 0;
    }
}

const String&Shader::Name() const
{
    return this->name;
}

const ShaderType&Shader::Type() const
{
    return this->type;
}

void Shader::Compile()
{
    if (this->IsCompiled())
    {
        return;
    }

    ShaderManager manager;

    std::vector<const char*> cpaths(0);

    // process includes
    for (const auto& path : this->includes)
    {
        cpaths.push_back(manager.GetPathReference(path));
    }

    // create the shader object
    this->id = glCreateShader(static_cast<GLenum>(this->type));

    if (this->id == 0)
    {
        throw std::runtime_error("glCreateShader failed");
    }

    // root shader
    const char* cstring = this->source.c_str();

    glShaderSource(this->id, 1, (const GLchar**)&cstring, NULL);

    // Compile the shader source
    glCompileShaderIncludeARB(this->id, cpaths.size(), (const GLchar**)&cpaths[0], NULL);

    // Verify compilation state
    this->VerifyCompilationState();
}

Boolean Shader::IsCompiled() const
{
    bool result = false;

    if (this->id != 0)
    {
        GLint status;
        glGetShaderiv(this->id, GL_COMPILE_STATUS, &status);

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
        glGetShaderiv(this->id, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength)
        {
            auto compileErrorMessage = std::string("", static_cast<Size>(infoLogLength));

            glGetShaderInfoLog(this->id, infoLogLength, NULL, &compileErrorMessage[0]);

            msg += compileErrorMessage;
        }

        this->Dispose();

        throw std::runtime_error(msg);
    }
}
