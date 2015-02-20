// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/BufferObject.hpp>

using namespace System;
using namespace SceneR::Graphics;

BufferObject::BufferObject(const BufferTarget& target, const BufferUsage& usage)
    : id     { 0 }
    , target { target }
    , usage  { usage }
{
    this->Create();
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

void BufferObject::Create()
{
    glGenBuffers(1, &this->id);
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

void BufferObject::GetData(const Size& offset, const Size& size, void* data) const
{
    glGetNamedBufferSubDataEXT(this->id, offset, size, data);
}

void BufferObject::BufferData(const System::Size& size, const void* data) const
{
    glNamedBufferDataEXT(this->id, size, data, static_cast<GLenum>(this->usage));
}

void BufferObject::BufferData(const System::Size& offset, const System::Size& size, const void *data) const
{
    glNamedBufferSubDataEXT(this->id, offset, size, data);
}

void BufferObject::Invalidate() const
{
    glInvalidateBufferData(this->id);
}

void BufferObject::Invalidate(const System::Size& offset, const System::Size& length) const
{
    glInvalidateBufferSubData(this->id, offset, length);
}
