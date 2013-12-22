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
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/VertexBuffer.hpp>
#include <Graphics/VertexDeclaration.hpp>
#include <stdexcept>

using namespace System;
using namespace SceneR::Graphics;

VertexBuffer::VertexBuffer(GraphicsDevice&                                      graphicsDevice
                         , System::UInt32                                       vertexCount
                         , std::shared_ptr<SceneR::Graphics::VertexDeclaration> vertexDeclaration)
    : GraphicsResource(graphicsDevice),
      vertexDeclaration(vertexDeclaration),
      vertexCount(vertexCount),
      vbo(BufferTarget::ArrayBuffer, BufferUsage::StaticDraw),
      vao()
{
    this->vao.DeclareVertexFormat(*this->vertexDeclaration);
}

VertexBuffer::~VertexBuffer()
{
    this->vbo.Delete();
    this->vao.Delete();
}

const UInt32& VertexBuffer::VertexCount() const
{
    return this->vertexCount;
}

const std::vector<Single>& VertexBuffer::GetData() const
{
    throw std::runtime_error("Not implemented");
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
