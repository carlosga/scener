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

#include <Framework/Matrix.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <GL/glew.h>
#include <Shaders/ShaderProgram.hpp>
#include <System/Text/Unicode.hpp>
#include <cassert>
#include <stdexcept>

using namespace SceneR::Framework;
using namespace SceneR::Shaders;

ShaderProgram::ShaderProgram(const std::wstring& name, std::vector<std::shared_ptr<Shader>>& shaders)
    : name(name), object(0), shaders(shaders)
{
}

ShaderProgram::~ShaderProgram()
{
    this->Release();
}

void ShaderProgram::Activate() const
{
    glUseProgram(this->object);
}

void ShaderProgram::Build()
{
    // Compile the shaders if needed ...
    for (auto &s : this->shaders)
    {
        if (!s->IsCompiled())
        {
            s->Compile();
        }
    }

    // ... Create the program object
    this->object = glCreateProgram();

    if (this->object == 0)
    {
        throw std::runtime_error("glCreateProgram failed");
    }

    // ... attach the shaders to the new shader program
    for (auto &s : this->shaders)
    {
        // Attach the shader
        glAttachShader(this->object, s->object);
    }

    // ... link the shader program
    glLinkProgram(this->object);

    // ... verify program linking
    this->VerifyLinkingState();
}

void ShaderProgram::Deactivate() const
{
    glUseProgram(0);
}

const std::wstring& ShaderProgram::Name() const
{
    return this->name;
}

const Int32 ShaderProgram::GetParameterLocation(const std::wstring& parameterName) const
{
    String temp = System::Text::Unicode::Narrow(parameterName);

    return glGetUniformLocation(this->object, temp.c_str());
}

void ShaderProgram::SetValue(const std::wstring& parameterName, const Matrix& matrix) const
{
    Int32 location = this->GetParameterLocation(parameterName);

    this->SetValue(location, matrix);
}

void ShaderProgram::SetValue(const Int32& location, const Matrix& matrix) const
{
    assert(location != -1);

    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0]);
}

void ShaderProgram::SetValue(const std::wstring& parameterName, const Vector3& vector3) const
{
    Int32 location = this->GetParameterLocation(parameterName);

    this->SetValue(location, vector3);
}

void ShaderProgram::SetValue(const Int32& location, const Vector3& vector3) const
{
    assert(location != -1);

    glUniform3fv(location, 1, &vector3[0]);
}

void ShaderProgram::SetValue(const std::wstring& parameterName, const Vector4& vector4) const
{
    Int32 location = this->GetParameterLocation(parameterName);

    this->SetValue(location, vector4);
}

void ShaderProgram::SetValue(const Int32& location, const Vector4& vector4) const
{
    assert(location != -1);

    glUniform4fv(location, 1, &vector4[0]);
}

void ShaderProgram::SetValue(const std::wstring& parameterName, const Single& value) const
{
    Int32 location = this->GetParameterLocation(parameterName);

    this->SetValue(location, value);
}

void ShaderProgram::SetValue(const Int32& location, const Single& value) const
{
    assert(location != -1);

    glUniform1f(location, value);
}

void ShaderProgram::Release()
{
    if (this->object != 0)
    {
        glDeleteProgram(this->object);
        this->object = 0;
    }
}

void ShaderProgram::VerifyLinkingState()
{
    // ... verify program linking
    GLint status;
    glGetProgramiv(this->object, GL_LINK_STATUS, &status);

    if (status == GL_FALSE)
    {
        String msg("Program linking failure: ");

        GLint infoLogLength;
        glGetProgramiv(this->object, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength)
        {
            String linkErrorMessage("", infoLogLength);

            glGetProgramInfoLog(this->object, infoLogLength, NULL, &linkErrorMessage[0]);

            msg += linkErrorMessage;
        }

        this->Release();

        throw std::runtime_error(msg);
    }
}
