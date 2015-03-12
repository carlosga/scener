// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/ShaderProgram.hpp>

#include <cassert>

#include <System/Pointer.hpp>
#include <System/Text/Encoding.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/UniformBufferObject.hpp>

using namespace System;
using namespace System::Text;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

ShaderProgram::ShaderProgram(const System::String& name)
    : name    { name }
    , id      { 0 }
    , shaders {}
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

const String&ShaderProgram::Name() const
{
    return this->name;
}

void ShaderProgram::AddShader(const String& name, const ShaderType& type, const std::string& source)
{
    this->AddShader(name, type, source, std::vector<std::string>());
}

void ShaderProgram::AddShader(const String&                   name
                            , const ShaderType&               type
                            , const std::string&              source
                            , const std::vector<std::string>& includes)
{
    this->shaders.push_back(std::make_shared<Shader>(name, type, source, includes));
}

void ShaderProgram::Build()
{
    // Compile the shaders if needed ...
    for (auto &s : this->shaders)
    {
        s->Compile();
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
        glAttachShader(this->id, s->id);
    }

    // ... link the shader program
    glLinkProgram(this->id);

    // ... verify program linking
    this->VerifyLinkingState();

    // ... fill uniform buffer info
    this->uniformBuffer = std::make_shared<UniformBufferObject>(this->id, String(name.begin(), name.end()));
    this->uniformBuffer->Describe();
}

void ShaderProgram::Activate() const
{
    glUseProgram(this->id);
}

void ShaderProgram::ActivateSubroutine(const UInt32& subroutineIndex) const
{
    for (const auto& shader : this->shaders)
    {
        this->ActivateSubroutine(shader->Type(), subroutineIndex);
    }
}

void ShaderProgram::ActivateSubroutine(const ShaderType& type, const UInt32& subroutineIndex) const
{
    glUniformSubroutinesuiv(static_cast<GLenum>(type), 1, &subroutineIndex);
}

void ShaderProgram::Deactivate() const
{
    glUseProgram(0);
}

void ShaderProgram::SetValue(const System::String& uniformName, const Boolean& value) const
{
    this->uniformBuffer->SetValue(uniformName, value);
}

void ShaderProgram::SetValue(const System::String& uniformName, const std::vector<Boolean>& value) const
{
    this->uniformBuffer->SetValue(uniformName, value);
}

void ShaderProgram::SetValue(const System::String& uniformName, const Int32& value) const
{
    this->uniformBuffer->SetValue(uniformName, value);
}

void ShaderProgram::SetValue(const System::String& uniformName, const std::vector<Int32>& value) const
{
    this->uniformBuffer->SetValue(uniformName, value);
}

void ShaderProgram::SetValue(const System::String& uniformName, const UInt32& value) const
{
    this->uniformBuffer->SetValue(uniformName, value);
}

void ShaderProgram::SetValue(const System::String& uniformName, const std::vector<UInt32>& value) const
{
    this->uniformBuffer->SetValue(uniformName, value);
}

void ShaderProgram::SetValue(const System::String& uniformName, const Matrix& value) const
{
    this->uniformBuffer->SetValue(uniformName, value);
}

void ShaderProgram::SetValue(const System::String& uniformName, const std::vector<Matrix>& value) const
{
    this->uniformBuffer->SetValue(uniformName, value);
}

void ShaderProgram::SetValueTranspose(const System::String& uniformName, const Matrix& value) const
{
    this->uniformBuffer->SetValueTranspose(uniformName, value);
}

void ShaderProgram::SetValueTranspose(const System::String& uniformName, const std::vector<Matrix>& value) const
{
    this->uniformBuffer->SetValueTranspose(uniformName, value);
}

void ShaderProgram::SetValue(const System::String& uniformName, const Quaternion& value) const
{
    this->uniformBuffer->SetValue(uniformName, value);
}

void ShaderProgram::SetValue(const System::String& uniformName, const std::vector<Quaternion>& value) const
{
    this->uniformBuffer->SetValue(uniformName, value);
}

void ShaderProgram::SetValue(const System::String& uniformName, const Single& value) const
{
    this->uniformBuffer->SetValue(uniformName, value);
}

void ShaderProgram::SetValue(const System::String& uniformName, const std::vector<Single>& value) const
{
    this->uniformBuffer->SetValue(uniformName, value);
}

void ShaderProgram::SetValue(const System::String& uniformName, const SceneR::Framework::Vector2& value) const
{
    this->uniformBuffer->SetValue(uniformName, value);
}

void ShaderProgram::SetValue(const System::String& uniformName, const std::vector<SceneR::Framework::Vector2>& value) const
{
    this->uniformBuffer->SetValue(uniformName, value);
}

void ShaderProgram::SetValue(const System::String& uniformName, const Vector3& value) const
{
    this->uniformBuffer->SetValue(uniformName, value);
}

void ShaderProgram::SetValue(const System::String& uniformName, const std::vector<Vector3>& value) const
{
    this->uniformBuffer->SetValue(uniformName, value);
}

void ShaderProgram::SetValue(const System::String& uniformName, const Vector4& value) const
{
    this->uniformBuffer->SetValue(uniformName, value);
}

void ShaderProgram::SetValue(const System::String& uniformName, const std::vector<Vector4>& value) const
{
    this->uniformBuffer->SetValue(uniformName, value);
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
            std::string linkErrorMessage("", static_cast<Size>(infoLogLength));

            glGetProgramInfoLog(this->id, infoLogLength, NULL, &linkErrorMessage[0]);

            msg += linkErrorMessage;
        }

        this->Dispose();

        throw std::runtime_error(msg);
    }
}

/*
void ShaderProgram::DescribeUniformBlocks()
{
    GLint numBlocks;

    glGetProgramiv(this->id, GL_ACTIVE_UNIFORM_BLOCKS, &numBlocks);

    assert(numBlocks == 1);

    GLsizei length = 0;
    glGetActiveUniformBlockiv(this->id, 0, GL_UNIFORM_BLOCK_NAME_LENGTH, &length);

    std::vector<GLchar> name(length);

    glGetActiveUniformBlockName(this->id, 0, length, NULL, &name[0]);

    name.resize(length);

    this->uniformBuffer = std::make_shared<UniformBufferObject>(this->id, String(name.begin(), name.end()));

    this->uniformBuffer->Describe();
}

void ShaderProgram::DescribeUniforms()
{
    const GLchar** cnames;

    GLint   uniformCount        = 0;
    GLsizei bufSize             = 0;
    auto    names               = std::vector<std::string>();
    auto    indices             = std::vector<GLuint>();
    auto    offsets             = std::vector<GLint>();
    auto    types               = std::vector<GLint>();
    auto    array_sizes         = std::vector<GLint>();
    auto    array_strides       = std::vector<GLint>();
    auto    matrix_strides      = std::vector<GLint>();
    auto    matrix_is_row_major = std::vector<GLint>();

    glGetProgramiv(this->id, GL_ACTIVE_UNIFORMS, &uniformCount);

    if (uniformCount > 0)
    {
        cnames = new const GLchar*[uniformCount];
        names.reserve(uniformCount);
        indices.reserve(uniformCount);
        offsets.reserve(uniformCount);
        types.reserve(uniformCount);
        array_sizes.reserve(uniformCount);
        array_strides.reserve(uniformCount);
        matrix_strides.reserve(uniformCount);
        matrix_is_row_major.reserve(uniformCount);

        glGetProgramiv(this->id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &bufSize);

        for (Int32 index = 0; index < uniformCount; index++)
        {
            GLsizei length = 0;
            GLint   size   = 0;
            GLenum  type   = GL_ZERO;
            auto    name   = std::vector<char>();

            name.reserve(bufSize);

            glGetActiveUniform(this->id, index, bufSize, &length, &size, &type, &name[0]);

            std::string uname(name.begin(), name.begin() + length);

            names.push_back(uname);

            cnames[index] = uname.c_str();
        }

        glGetUniformIndices(this->id, uniformCount, cnames, &indices[0]);

        glGetActiveUniformsiv(this->id, uniformCount, &indices[0], GL_UNIFORM_OFFSET       , &offsets[0]);
        glGetActiveUniformsiv(this->id, uniformCount, &indices[0], GL_UNIFORM_TYPE         , &types[0]);
        glGetActiveUniformsiv(this->id, uniformCount, &indices[0], GL_UNIFORM_SIZE         , &array_sizes[0]);
        glGetActiveUniformsiv(this->id, uniformCount, &indices[0], GL_UNIFORM_ARRAY_STRIDE , &array_strides[0]);
        glGetActiveUniformsiv(this->id, uniformCount, &indices[0], GL_UNIFORM_MATRIX_STRIDE, &matrix_strides[0]);
        glGetActiveUniformsiv(this->id, uniformCount, &indices[0], GL_UNIFORM_IS_ROW_MAJOR , &matrix_is_row_major[0]);
    }
}
*/
