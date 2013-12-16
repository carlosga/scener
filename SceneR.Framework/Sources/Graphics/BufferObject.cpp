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

#include <Graphics/BufferObject.hpp>
#include <Graphics/BufferTarget.hpp>
#include <Graphics/BufferUsage.hpp>

using namespace System;
using namespace SceneR::Graphics;

BufferObject::BufferObject(const BufferTarget& target, const BufferUsage& usage)
    : id(0),
      target(target),
      usage(usage)
{
    this->Create();
}

BufferObject::~BufferObject()
{
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

void BufferObject::Delete()
{
    if (this->id != 0)
    {
        this->Deactivate();
        glDeleteBuffers(1, &this->id);
        this->id = 0;
    }
}

void SceneR::Graphics::BufferObject::BufferData(const System::Size& size, const GLvoid* data)
{
    this->Activate();

    glBufferData(static_cast<GLenum>(this->target), size, data, static_cast<GLenum>(this->usage));

    this->Deactivate();
}