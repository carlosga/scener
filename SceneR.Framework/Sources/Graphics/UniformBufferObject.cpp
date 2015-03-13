// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/UniformBufferObject.hpp>

#include <cassert>

#include <System/Graphics/Platform.hpp>
#include <System/Text/Encoding.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/ShaderProgram.hpp>
#include <Graphics/Uniform.hpp>

using namespace System;
using namespace System::Text;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

UniformBufferObject::UniformBufferObject(const UInt32& programId, const String& name)
    : programId    { programId }
    , name         { name }
    , binding      { 0 }
    , uniforms     ()
    , bufferObject { BufferTarget::UniformBuffer, BufferUsage::DynamicDraw }
{
}

UniformBufferObject::~UniformBufferObject()
{
}

void UniformBufferObject::Activate()
{
    this->bufferObject.Activate();
}

void UniformBufferObject::Deactivate()
{
    this->bufferObject.Deactivate();
}

void UniformBufferObject::SetValue(const System::String& uniformName, const Boolean& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), 1, &value);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const std::vector<Boolean>& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), value.size(), &value);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const Int32& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Int32), &value);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const std::vector<Int32>& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Int32) * value.size(), &value[0]);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const UInt32& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(UInt32), &value);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const std::vector<UInt32>& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(UInt32) * value.size(), &value[0]);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const Matrix& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Matrix), &value[0]);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const std::vector<Matrix>& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Matrix) * value.size(), &value[0][0]);
}

void UniformBufferObject::SetValueTranspose(const System::String& uniformName, const Matrix& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Matrix), &value[0]);
}

void UniformBufferObject::SetValueTranspose(const System::String& uniformName, const std::vector<Matrix>& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Matrix) * value.size(), &value[0][0]);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const Quaternion& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Quaternion), &value[0]);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const std::vector<Quaternion>& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Quaternion) * value.size(), &value[0][0]);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const Single& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Single), &value);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const std::vector<Single>& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Quaternion), &value[0]);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const SceneR::Framework::Vector2& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Vector2), &value[0]);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const std::vector<SceneR::Framework::Vector2>& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Vector2) * value.size(), &value[0][0]);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const Vector3& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Vector3), &value[0]);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const std::vector<Vector3>& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Vector3) * value.size(), &value[0][0]);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const Vector4& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Vector4), &value[0]);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const std::vector<Vector4>& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Vector4) * value.size(), &value[0][0]);
}

void UniformBufferObject::Describe()
{
    // Get uniform block name
    GLsizei nameLength = 0;
    glGetActiveUniformBlockiv(this->programId, 0, GL_UNIFORM_BLOCK_NAME_LENGTH, &nameLength);

    std::vector<GLchar> blockName(nameLength);

    glGetActiveUniformBlockName(this->programId, 0, nameLength, NULL, &blockName[0]);

    std::string tmp = std::string(blockName.begin(), blockName.begin() + nameLength);

    this->binding = glGetUniformBlockIndex(this->programId, tmp.c_str());

    // Get buffer block size
    GLint blockSize = 0;

    glGetActiveUniformBlockiv(this->programId, this->binding, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);

    // Create the buffer object
    this->bufferObject.Create(blockSize);

    // Check the number of active uniforms
    GLint activeUniforms = 0;

    glGetActiveUniformBlockiv(this->programId, this->binding, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &activeUniforms);

    // Describe uniforms
    this->DescribeUniforms(activeUniforms);
}

void UniformBufferObject::DescribeUniforms(const UInt32& count)
{
    std::vector<GLint> indices(count);
    std::vector<GLint> nameLengths(count);
    std::vector<GLint> offsets(count);
    std::vector<GLint> types(count);
    std::vector<GLint> array_sizes(count);
    std::vector<GLint> array_strides(count);
    std::vector<GLint> matrix_strides(count);
    std::vector<GLint> matrix_is_row_major(count);

    glGetActiveUniformBlockiv(this->programId, this->binding, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, &indices[0]);

    glGetActiveUniformsiv(this->programId, count, (GLuint*)&indices[0], GL_UNIFORM_NAME_LENGTH  , &nameLengths[0]);
    glGetActiveUniformsiv(this->programId, count, (GLuint*)&indices[0], GL_UNIFORM_OFFSET       , &offsets[0]);
    glGetActiveUniformsiv(this->programId, count, (GLuint*)&indices[0], GL_UNIFORM_TYPE         , &types[0]);
    glGetActiveUniformsiv(this->programId, count, (GLuint*)&indices[0], GL_UNIFORM_SIZE         , &array_sizes[0]);
    glGetActiveUniformsiv(this->programId, count, (GLuint*)&indices[0], GL_UNIFORM_ARRAY_STRIDE , &array_strides[0]);
    glGetActiveUniformsiv(this->programId, count, (GLuint*)&indices[0], GL_UNIFORM_MATRIX_STRIDE, &matrix_strides[0]);
    glGetActiveUniformsiv(this->programId, count, (GLuint*)&indices[0], GL_UNIFORM_IS_ROW_MAJOR , &matrix_is_row_major[0]);

    for (UInt32 i = 0; i < count; i++)
    {
        GLsizei length = 0;
        GLint   size   = 0;
        GLenum  type   = GL_ZERO;
        auto    name   = std::vector<char>();

        name.reserve(nameLengths[i]);

        glGetActiveUniform(this->programId, indices[i], nameLengths[i], &length, &size, &type, &name[0]);

        String  uniformName(name.begin(), name.begin() + length);
        Uniform uniform { uniformName
                        , indices[i]
                        , offsets[i]
                        , types[i]
                        , array_sizes[i]
                        , array_strides[i]
                        , matrix_strides[i]
                        , matrix_is_row_major[i] };

        this->uniforms.emplace(uniformName, uniform);
    }
}
