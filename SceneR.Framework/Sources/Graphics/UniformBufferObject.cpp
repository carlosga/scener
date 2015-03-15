// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/UniformBufferObject.hpp>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>

#include <System/Graphics/Platform.hpp>
#include <System/IO/BinaryReader.hpp>
#include <System/IO/MemoryStream.hpp>
#include <System/Text/Encoding.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/ShaderProgram.hpp>
#include <Graphics/Uniform.hpp>

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

UniformBufferObject::UniformBufferObject(const UInt32& programId, const String& name)
    : programId    { programId }
    , name         { name }
    , blockIndex   { 0 }
    , bindingPoint { 0 }
    , blockSize    { 0 }
    , uniforms     ()
    , bufferObject { BufferTarget::UniformBuffer, BufferUsage::DynamicDraw }
{
}

UniformBufferObject::~UniformBufferObject()
{
}

void UniformBufferObject::Dispose()
{
    this->bufferObject.Dispose();
}

void UniformBufferObject::Activate()
{
    glBindBufferBase(static_cast<GLenum>(this->bufferObject.Target()), this->bindingPoint, this->bufferObject.Id());
}

void UniformBufferObject::Deactivate()
{
    glBindBufferBase(static_cast<GLenum>(this->bufferObject.Target()), 0, 0);
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

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Int32) * value.size(), value.data());
}

void UniformBufferObject::SetValue(const System::String& uniformName, const UInt32& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(UInt32), &value);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const std::vector<UInt32>& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(UInt32) * value.size(), value.data());
}

void UniformBufferObject::SetValue(const System::String& uniformName, const Matrix& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Matrix), &value[0]);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const std::vector<Matrix>& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Matrix) * value.size(), value.data());
}

void UniformBufferObject::SetValueTranspose(const System::String& uniformName, const Matrix& value) const
{
    const auto& uniform   = this->uniforms.find(uniformName)->second;
    const auto  transpose = Matrix::Transpose(value);

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Matrix), &transpose[0]);
}

void UniformBufferObject::SetValueTranspose(const System::String& uniformName, const std::vector<Matrix>& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Matrix) * value.size(), value.data());
}

void UniformBufferObject::SetValue(const System::String& uniformName, const Quaternion& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Quaternion), &value[0]);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const std::vector<Quaternion>& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Quaternion) * value.size(), value.data());
}

void UniformBufferObject::SetValue(const System::String& uniformName, const Single& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Single), &value);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const std::vector<Single>& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Single) * value.size(), value.data());
}

void UniformBufferObject::SetValue(const System::String& uniformName, const SceneR::Framework::Vector2& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Vector2), &value[0]);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const std::vector<SceneR::Framework::Vector2>& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Vector2) * value.size(), value.data());
}

void UniformBufferObject::SetValue(const System::String& uniformName, const Vector3& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Vector3), &value[0]);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const std::vector<Vector3>& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Vector3) * value.size(), value.data());
}

void UniformBufferObject::SetValue(const System::String& uniformName, const Vector4& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Vector4), &value[0]);
}

void UniformBufferObject::SetValue(const System::String& uniformName, const std::vector<Vector4>& value) const
{
    const auto& uniform = this->uniforms.find(uniformName)->second;

    this->bufferObject.BufferData(uniform.Offset(), sizeof(Vector4) * value.size(), value.data());
}

void UniformBufferObject::Describe()
{
    std::string tmp = Encoding::Convert(this->name);

    // Get the uniform block index
    this->blockIndex = glGetUniformBlockIndex(this->programId, tmp.c_str());

    // Get the binding point
    glGetActiveUniformBlockiv(this->programId, this->blockIndex, GL_UNIFORM_BLOCK_BINDING, &this->bindingPoint);

    // Get uniform block data size
    glGetActiveUniformBlockiv(this->programId, this->blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &this->blockSize);

    // Describe uniforms
    this->DescribeUniforms();

    // Initialize the buffer object
    std::vector<UByte> data(this->blockSize, 0);
    this->bufferObject.BufferData(this->blockSize, data.data());
}

void UniformBufferObject::DescribeUniforms()
{
    // Check the number of active uniforms
    GLint activeUniforms = 0;

    glGetActiveUniformBlockiv(this->programId, this->blockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &activeUniforms);

    std::vector<GLint> indices(activeUniforms, 0);
    std::vector<GLint> nameLengths(activeUniforms, 0);
    std::vector<GLint> offsets(activeUniforms, 0);
    std::vector<GLint> types(activeUniforms, 0);

    glGetActiveUniformBlockiv(this->programId, this->blockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, indices.data());

    GLuint* address = reinterpret_cast<GLuint*>(indices.data());

    glGetActiveUniformsiv(this->programId, activeUniforms, address, GL_UNIFORM_NAME_LENGTH, nameLengths.data());
    glGetActiveUniformsiv(this->programId, activeUniforms, address, GL_UNIFORM_OFFSET     , offsets.data());
    glGetActiveUniformsiv(this->programId, activeUniforms, address, GL_UNIFORM_TYPE       , types.data());

    for (Int32 i = 0; i < activeUniforms; i++)
    {
        GLsizei length = 0;
        GLint   size   = 0;
        GLenum  type   = GL_ZERO;
        auto    name   = std::vector<char>(nameLengths[i], 0);

        glGetActiveUniform(this->programId, indices[i], nameLengths[i], &length, &size, &type, name.data());

        String  uniformName(name.begin(), name.begin() + length);
        Uniform uniform { uniformName
                        , static_cast<UInt32>(indices[i])
                        , static_cast<UInt32>(offsets[i])
                        , static_cast<UInt32>(types[i]) };

        this->uniforms.emplace(uniformName, uniform);
    }
}

void UniformBufferObject::Dump() const
{
    std::vector<UByte> data(this->blockSize, 0);

    this->bufferObject.GetData(0, this->blockSize, data.data());

    MemoryStream stream(data);
    BinaryReader reader(stream);

    std::vector<Uniform> sorted(0);

    for (auto& kvp : this->uniforms)
    {
        sorted.push_back(kvp.second);
    }

    // Sort uniforms by offset
    std::sort(sorted.begin(), sorted.end(), [] (const Uniform& a, const Uniform& b) { return a.Offset() < b.Offset(); });

    for (auto& uniform : sorted)
    {
        UInt32 stride = 1;
        auto   uname  = Encoding::Convert(uniform.Name());

        stream.Seek(uniform.Offset(), std::ios_base::beg);

        if (uniform.ParameterClass() != EffectParameterClass::Scalar)
        {
            stride = uniform.RowCount() * uniform.ColumnCount();
        }

        std::cout << "Stream Position " << std::to_string(stream.Position());
        std::cout << " Offset " << std::to_string(uniform.Offset());
        std::cout << " Uniform " << uname << std::endl;

        for (UInt32 i = 0; i < stride; i++)
        {
            std::cout << std::to_string(reader.ReadSingle()) << "  ";
        }

        std::cout << "" << std::endl;
    }
}

