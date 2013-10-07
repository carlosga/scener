//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#include <stdexcept>
#include <vector>
#include "Shaders/Shader.hpp"

using namespace SceneR::Shaders;

Shader::Shader(const std::wstring& shaderCode, const ShaderType& shaderType)
    : object(0), shaderCode(shaderCode), shaderType(shaderType)
{
}

Shader::~Shader()
{
    this->Release();
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
    std::string temp(this->shaderCode.begin(), this->shaderCode.end());
    const char* code = temp.c_str();
    glShaderSource(this->object, 1, (const GLchar**)&code, NULL);

    // Compile the shader source
    glCompileShader(this->object);

    // Verify compilation state
    this->VerifyCompilationState();
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
            std::string compileErrorMessage("", infoLogLength);

            glGetShaderInfoLog(this->object, infoLogLength, NULL, &compileErrorMessage[0]);

            msg += compileErrorMessage;
        }

        this->Release();

        throw std::runtime_error(msg);
    }
}

const bool Shader::IsCompiled() const
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

void Shader::Release()
{
    if (this->object != 0)
    {
        glDeleteShader(this->object);
        this->object = 0;
    }
}
