// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/VertexBuffer.hpp>

#include <Graphics/VertexDeclaration.hpp>

using namespace System;
using namespace SceneR::Graphics;

VertexBuffer::VertexBuffer(GraphicsDevice&                                             graphicsDevice
                         , const System::UInt32&                                       vertexCount
                         , const std::shared_ptr<SceneR::Graphics::VertexDeclaration>& vertexDeclaration)
    : GraphicsResource  { graphicsDevice }
    , vertexDeclaration { vertexDeclaration }
    , vertexCount       { vertexCount }
    , vao               { }
    , vbo               { BufferTarget::ArrayBuffer, BufferUsage::StaticDraw }
{
    this->Activate();
    this->vertexDeclaration->Activate();
    this->Deactivate();
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::Dispose()
{
    this->vao.Dispose();
    this->vbo.Dispose();
}

const UInt32& VertexBuffer::VertexCount() const
{
    return this->vertexCount;
}

std::vector<UByte> VertexBuffer::GetData() const
{
    return this->GetData(0, this->vertexCount);
}

std::vector<UByte> VertexBuffer::GetData(const UInt32& startIndex, const UInt32& elementCount) const
{
    auto offset = (startIndex * this->vertexDeclaration->VertexStride());
    auto size   = (elementCount * this->vertexDeclaration->VertexStride());
    auto data   = std::vector<UByte>(size);

    this->vbo.GetData(offset, size, data.data());

    return data;
}

void VertexBuffer::SetData(const void* data)
{
    this->vbo.BufferData(this->vertexCount * this->vertexDeclaration->VertexStride(), data);
}

std::shared_ptr<SceneR::Graphics::VertexDeclaration> VertexBuffer::VertexDeclaration() const
{
    return this->vertexDeclaration;
}

void VertexBuffer::Activate()
{
    this->vao.Activate();
    glBindVertexBuffer(0, this->vbo.Id(), 0, static_cast<GLsizei>(this->vertexDeclaration->VertexStride()));
}

void VertexBuffer::Deactivate()
{
    glBindVertexBuffer(0, 0, 0, static_cast<GLsizei>(this->vertexDeclaration->VertexStride()));
    this->vao.Deactivate();
}
