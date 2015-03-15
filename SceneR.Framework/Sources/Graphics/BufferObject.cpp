// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/BufferObject.hpp>

#include <vector>

using namespace System;
using namespace SceneR::Graphics;

BufferObject::BufferObject(const BufferTarget& target, const BufferUsage& usage)
    : id     { 0 }
    , target { target }
    , usage  { usage }
{
    this->Create();
}

BufferObject::~BufferObject()
{
}

void BufferObject::Dispose()
{
    if (this->id != 0)
    {
        glDeleteBuffers(1, &this->id);
        this->id = 0;
    }
}

const UInt32& BufferObject::Id() const
{
    return this->id;
}

const BufferTarget& BufferObject::Target() const
{
    return this->target;
}

const BufferUsage& BufferObject::Usage() const
{
    return this->usage;
}

void BufferObject::Activate() const
{
    glBindBuffer(static_cast<GLenum>(this->target), this->id);
}

void BufferObject::Deactivate() const
{
    if (this->id != 0)
    {
        glBindBuffer(static_cast<GLenum>(this->target), 0);
    }
}

void BufferObject::GetData(const UInt32& offset, const UInt32& size, void* data) const
{
    glGetNamedBufferSubDataEXT(this->id, offset, size, data);
}

void BufferObject::BufferData(const System::UInt32& size, const void* data) const
{
    glNamedBufferDataEXT(this->id, size, data, static_cast<GLenum>(this->usage));
}

void BufferObject::BufferData(const System::UInt32& offset, const System::UInt32& size, const void *data) const
{
    glNamedBufferSubDataEXT(this->id, offset, size, data);
}

void BufferObject::Invalidate() const
{
    glInvalidateBufferData(this->id);
}

void BufferObject::Invalidate(const System::UInt32& offset, const System::UInt32& length) const
{
    glInvalidateBufferSubData(this->id, offset, length);
}

void BufferObject::Create()
{
    glGenBuffers(1, &this->id);
    this->Activate();
    this->Deactivate();
}
