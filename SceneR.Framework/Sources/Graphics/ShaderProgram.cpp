// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/ShaderProgram.hpp>

#include <cassert>

#include <Graphics/Shader.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <System/Text/Encoding.hpp>

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
}

void ShaderProgram::Dispose()
{
    if (this->id != 0)
    {
        // Dipose all the shader instances
        if (this->shaders.size() > 0)
        {
            for (auto& shader : this->shaders)
            {
                shader->Dispose();
            }
        }

        glDeleteProgram(this->id);

        this->shaders.clear();
        this->id = 0;
    }
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

void ShaderProgram::SetValue(const System::Int32& location, const SceneR::Framework::Vector2& value) const
{
    glProgramUniform2fv(this->id, location, 1, &value[0]);
}

void ShaderProgram::SetValue(const System::Int32& location, const std::vector<SceneR::Framework::Vector2>& value) const
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

        this->Dispose();

        throw std::runtime_error(msg);
    }
}
