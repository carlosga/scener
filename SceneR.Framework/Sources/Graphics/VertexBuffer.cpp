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

#include <System/Graphics/BufferTarget.hpp>
#include <System/Graphics/BufferUsage.hpp>
#include <Graphics/VertexBuffer.hpp>
#include <Graphics/VertexElement.hpp>
#include <Graphics/VertexElementFormat.hpp>
#include <Graphics/VertexElementUsage.hpp>

using namespace System;
using namespace System::Graphics;
using namespace SceneR::Graphics;

VertexBuffer::VertexBuffer(GraphicsDevice&                                      graphicsDevice
                         , System::UInt32                                       vertexCount
                         , std::shared_ptr<SceneR::Graphics::VertexDeclaration> vertexDeclaration)
    : GraphicsResource(graphicsDevice),
      vertexDeclaration(vertexDeclaration),
      vertexCount(vertexCount),
      vao(),
      vbo(BufferTarget::ArrayBuffer, BufferUsage::StaticDraw)
{
    this->vao.DeclareVertexFormat(this->vbo, *this->vertexDeclaration);
}

VertexBuffer::~VertexBuffer()
{
}

const UInt32& VertexBuffer::VertexCount() const
{
    return this->vertexCount;
}

std::vector<UByte> VertexBuffer::GetData() const
{
    UInt32 size = (this->vertexCount * this->vertexDeclaration->VertexStride());
    std::vector<UByte> data(size);

    this->vbo.GetData(0, size, data.data());

    return data;
}

std::vector<UByte> VertexBuffer::GetData(const System::Int32& startIndex, const System::Int32& elementCount)
{
    UInt32 offset = (startIndex * this->vertexDeclaration->VertexStride());
    UInt32 size   = (elementCount * this->vertexDeclaration->VertexStride());
    std::vector<UByte> data(size);

    this->vbo.GetData(offset, size, data.data());

    return data;
}

void VertexBuffer::SetData(const void* data)
{
    this->vbo.BufferData(this->vertexCount * this->vertexDeclaration->VertexStride(), data);
}

std::shared_ptr<SceneR::Graphics::VertexDeclaration> VertexBuffer::VertexDeclaration()
{
    return this->vertexDeclaration;
}

void VertexBuffer::Activate()
{
    this->vao.Activate();
}

void VertexBuffer::Deactivate()
{
    this->vao.Deactivate();
}
