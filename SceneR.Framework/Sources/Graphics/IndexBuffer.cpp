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

#include <GL/glew.h>
#include <Graphics/IndexBuffer.hpp>
#include <Graphics/VertexBufferTarget.hpp>
#include <Graphics/VertexBufferUsage.hpp>
#include <stdexcept>

using namespace System;
using namespace SceneR::Graphics;

IndexBuffer::IndexBuffer(GraphicsDevice&         graphicsDevice,
                         const IndexElementSize& indexElementSize,
                         const UInt32&           indexCount)
    : GraphicsResource(graphicsDevice),
      ibo(0),
      indexCount(indexCount),
      indexElementSize(indexElementSize)
{
    this->CreateIndexBuffer();
}

IndexBuffer::~IndexBuffer()
{
    this->Release();
}

const UInt32& IndexBuffer::GetIndexCount() const
{
    return this->indexCount;
}

const IndexElementSize& IndexBuffer::GetIndexElementSize() const
{
    return this->indexElementSize;
}

const std::vector<UInt32>& IndexBuffer::GetData() const
{
    throw std::runtime_error("Not implemented");
}

void IndexBuffer::SetData(const std::vector<UInt32>& data)
{
    this->BufferData(data);
}

void IndexBuffer::Release()
{
    this->DeleteIndexBuffer();
}

void IndexBuffer::CreateIndexBuffer()
{
    glGenBuffers(1, &this->ibo);
}

void IndexBuffer::BindIndexBuffer() const
{
    glBindBuffer(static_cast<GLenum>(VertexBufferTarget::ElementArraybuffer),
                 this->ibo);
}

void IndexBuffer::BufferData(const std::vector<UInt32>& data) const
{
    this->BindIndexBuffer();

    glBufferData(static_cast<GLenum>(VertexBufferTarget::ElementArraybuffer),
                 data.size() * this->GetElementSizeInBytes(),
                 data.data(),
                 static_cast<GLenum>(VertexBufferUsage::StaticDraw));

    this->UnbindIndexBuffer();
}

void IndexBuffer::UnbindIndexBuffer() const
{
    glBindBuffer(static_cast<GLenum>(VertexBufferTarget::ElementArraybuffer), 0);
}

void IndexBuffer::DeleteIndexBuffer()
{
    if (this->ibo != 0)
    {
        glDeleteBuffers(1, &this->ibo);
    }

    this->ibo = 0;
}

const UInt32 IndexBuffer::GetElementSizeInBytes() const
{
    return ((this->indexElementSize == IndexElementSize::SixteenBits) ? sizeof(UInt16) : sizeof(UInt32));
}
