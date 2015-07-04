// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/VertexBuffer.hpp>

#include <Graphics/VertexDeclaration.hpp>

using namespace System;
using namespace SceneR::Graphics;

VertexBuffer::VertexBuffer(GraphicsDevice&                                             graphicsDevice
                         , const uint32_t&                                             vertexCount
                         , const std::shared_ptr<SceneR::Graphics::VertexDeclaration>& vertexDeclaration)
    : GraphicsResource  { graphicsDevice }
    , bindingIndex      { 0 }
    , vertexDeclaration { vertexDeclaration }
    , vertexCount       { vertexCount }
    , vao               { }
    , vbo               { BufferTarget::ArrayBuffer, BufferUsage::StaticDraw }
{
    this->vao.Activate();
    this->vertexDeclaration->Declare(this->vao.Id(), this->bindingIndex);
    this->vao.Deactivate();
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::Dispose()
{
    this->vao.Dispose();
    this->vbo.Dispose();
}

uint32_t VertexBuffer::VertexCount() const
{
    return this->vertexCount;
}

std::vector<uint8_t> VertexBuffer::GetData() const
{
    return this->GetData(0, this->vertexCount);
}

std::vector<uint8_t> VertexBuffer::GetData(const uint32_t& startIndex, const uint32_t& elementCount) const
{
    auto offset = (startIndex * this->vertexDeclaration->VertexStride());
    auto size   = (elementCount * this->vertexDeclaration->VertexStride());
    auto data   = std::vector<uint8_t>(size, 0);

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
    auto stride = this->vertexDeclaration->VertexStride();

    // glVertexArrayVertexBuffer(this->vao.Id(), this->bindingIndex, this->vbo.Id(), 0, static_cast<GLsizei>(this->vertexDeclaration->VertexStride()));
    this->vao.Activate();
    glBindVertexBuffer(this->bindingIndex, this->vbo.Id(), 0, static_cast<GLsizei>(stride));
}

void VertexBuffer::Deactivate()
{
    // glVertexArrayVertexBuffer(0, this->bindingIndex, 0, 0, static_cast<GLsizei>(this->vertexDeclaration->VertexStride()));
    glBindVertexBuffer(this->bindingIndex, 0, 0, static_cast<GLsizei>(this->vertexDeclaration->VertexStride()));
    this->vao.Deactivate();
}
