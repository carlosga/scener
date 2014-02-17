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

#include <Graphics/BufferTarget.hpp>
#include <Graphics/BufferUsage.hpp>
#include <Graphics/VertexBuffer.hpp>
#include <Graphics/VertexDeclaration.hpp>
#include <Graphics/VertexElement.hpp>
#include <Graphics/VertexElementFormat.hpp>
#include <Graphics/VertexElementUsage.hpp>

using namespace System;
using namespace SceneR::Graphics;

VertexBuffer::VertexBuffer(GraphicsDevice&                                             graphicsDevice
                         , const System::Size&                                         vertexCount
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

const Size& VertexBuffer::VertexCount() const
{
    return this->vertexCount;
}

std::vector<UByte> VertexBuffer::GetData() const
{
    return this->GetData(0, this->vertexCount);
}

std::vector<UByte> VertexBuffer::GetData(const Size& startIndex, const Size& elementCount) const
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
    glBindVertexBuffer(0, this->vbo.Id(), 0, this->vertexDeclaration->VertexStride());
}

void VertexBuffer::Deactivate()
{
    glBindVertexBuffer(0, 0, 0, this->vertexDeclaration->VertexStride());
    this->vao.Deactivate();
}
