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
#include <Framework/Quaternion.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/ShaderProgram.hpp>
#include <System/Graphics/Platform.hpp>
#include <System/Text/Encoding.hpp>
#include <cassert>

using namespace System;
using namespace System::Text;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

ShaderProgram::ShaderProgram(std::vector<std::shared_ptr<Shader>>& shaders)
    : id      { 0 }
    , shaders { shaders }
{
}

ShaderProgram::~ShaderProgram()
{
    this->Release();
}

void ShaderProgram::Activate() const
{
    glUseProgram(this->id);
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
    this->id = glCreateProgram();

    if (this->id == 0)
    {
        throw std::runtime_error("glCreateProgram failed");
    }

    // ... attach the shaders to the new shader program
    for (auto &s : this->shaders)
    {
        // Attach the shader
        glAttachShader(this->id, s->object);
    }

    // ... link the shader program
    glLinkProgram(this->id);

    // ... verify program linking
    this->VerifyLinkingState();
}

void ShaderProgram::Deactivate() const
{
    glUseProgram(0);
}

Int32 ShaderProgram::GetParameterLocation(const String& parameterName) const
{
    auto temp     = System::Text::Encoding::Convert(parameterName);
    auto location = glGetUniformLocation(this->id, temp.c_str());

    assert(location != -1);

    return location;
}

void ShaderProgram::SetValue(const System::Int32& location, const Boolean& value) const
{
    glProgramUniform1i(this->id, location, value);
}

void ShaderProgram::SetValue(const System::Int32& location, const std::vector<Boolean>& value) const
{
    for (const auto& bValue : value)
    {
        this->SetValue(location, bValue);
    }
}

void ShaderProgram::SetValue(const System::Int32& location, const Int32& value) const
{
    glProgramUniform1i(this->id, location, value);
}

void ShaderProgram::SetValue(const System::Int32& location, const std::vector<Int32>& value) const
{
    glProgramUniform1iv(this->id, location, value.size(), &value[0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const UInt32& value) const
{
    glProgramUniform1ui(this->id, location, value);
}

void ShaderProgram::SetValue(const System::Int32& location, const std::vector<UInt32>& value) const
{
    glProgramUniform1uiv(this->id, location, value.size(), &value[0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const Matrix& value) const
{
    glProgramUniformMatrix4fv(this->id, location, 1, false, &value[0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const std::vector<Matrix>& value) const
{
    glProgramUniformMatrix4fv(this->id, location, value.size(), false, &value[0][0]);
}

void ShaderProgram::SetValueTranspose(const System::Int32& location, const Matrix& value) const
{
    glProgramUniformMatrix4fv(this->id, location, 1, true, &value[0]);
}

void ShaderProgram::SetValueTranspose(const System::Int32& location, const std::vector<Matrix>& value) const
{
    glProgramUniformMatrix4fv(this->id, location, value.size(), true, &value[0][0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const Quaternion& value) const
{
    glProgramUniform4fv(this->id, location, 1, &value[0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const std::vector<Quaternion>& value) const
{
    glProgramUniform4fv(this->id, location, value.size(), &value[0][0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const Single& value) const
{
    glProgramUniform1f(this->id, location, value);
}

void ShaderProgram::SetValue(const System::Int32& location, const std::vector<Single>& value) const
{
    glProgramUniform1fv(this->id, location, value.size(), &value[0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const SceneR::Framework::Vector2& value)
{
    glProgramUniform2fv(this->id, location, 1, &value[0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const std::vector<SceneR::Framework::Vector2>& value)
{
    glProgramUniform2fv(this->id, location, value.size(), &value[0][0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const Vector3& value) const
{
    glProgramUniform3fv(this->id, location, 1, &value[0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const std::vector<Vector3>& value) const
{
    glProgramUniform3fv(this->id, location, value.size(), &value[0][0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const Vector4& value) const
{
    glProgramUniform4fv(this->id, location, 1, &value[0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const std::vector<Vector4>& value) const
{
    glProgramUniform4fv(this->id, location, value.size(), &value[0][0]);
}

void ShaderProgram::Release()
{
    if (this->id != 0)
    {
        glDeleteProgram(this->id);
        this->id = 0;
    }
}

void ShaderProgram::VerifyLinkingState()
{
    // ... verify program linking
    GLint status;
    glGetProgramiv(this->id, GL_LINK_STATUS, &status);

    if (status == GL_FALSE)
    {
        auto msg = std::string("Program linking failure: ");

        GLint infoLogLength;
        glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength)
        {
            std::string linkErrorMessage("", infoLogLength);

            glGetProgramInfoLog(this->id, infoLogLength, NULL, &linkErrorMessage[0]);

            msg += linkErrorMessage;
        }

        this->Release();

        throw std::runtime_error(msg);
    }
}
