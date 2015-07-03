// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/UniformBufferObject.hpp>

#include <System/Graphics/Platform.hpp>
#include <System/Text/Encoding.hpp>

using namespace System;
using namespace System::Text;
using namespace SceneR::Graphics;

UniformBufferObject::UniformBufferObject(const std::u16string& name, const UInt32& programId)
    : name         { name }
    , programId    { programId }
    , index        { 0 }
    , bindingPoint { 0 }
    , size         { 0 }
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

System::UInt32 UniformBufferObject::Index() const
{
    return this->index;
}

System::Int32 UniformBufferObject::BindingPoint() const
{
    return this->bindingPoint;
}

System::Int32 UniformBufferObject::Size() const
{
    return this->size;
}

void UniformBufferObject::Activate()
{
    glBindBufferBase(static_cast<GLenum>(this->bufferObject.Target()), this->bindingPoint, this->bufferObject.Id());
}

void UniformBufferObject::Deactivate()
{
    glBindBufferBase(static_cast<GLenum>(this->bufferObject.Target()), 0, 0);
}

std::vector<uint8_t> UniformBufferObject::GetData() const
{
    return this->GetData(0, this->size);
}

std::vector<uint8_t> UniformBufferObject::GetData(const UInt32& startIndex, const UInt32& elementCount) const
{
    auto data = std::vector<uint8_t>(elementCount, 0);

    this->bufferObject.GetData(startIndex, elementCount, data.data());

    return data;
}

void UniformBufferObject::SetData(const void* data)
{
    this->bufferObject.BufferData(0, this->size, data);
}

void UniformBufferObject::SetData(const UInt32& startIndex, const UInt32& elementCount, const void *data)
{
    if (data == nullptr)
    {
        return;
    }

    this->bufferObject.BufferData(startIndex, elementCount, data);
}

void UniformBufferObject::Describe()
{
    std::string tmp = Encoding::Convert(this->name);

    // Get the uniform block index
    this->index = glGetUniformBlockIndex(this->programId, tmp.c_str());

    // Get the binding point
    glGetActiveUniformBlockiv(this->programId, this->index, GL_UNIFORM_BLOCK_BINDING, &this->bindingPoint);

    // Get uniform block data size
    glGetActiveUniformBlockiv(this->programId, this->index, GL_UNIFORM_BLOCK_DATA_SIZE, &this->size);

    // Initialize the buffer object
    std::vector<uint8_t> data(this->size, 0);
    this->bufferObject.BufferData(this->size, data.data());
}
