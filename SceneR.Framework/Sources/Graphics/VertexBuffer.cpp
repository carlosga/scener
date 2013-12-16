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
#include <Graphics/BufferTarget.hpp>
#include <Graphics/BufferUsage.hpp>
#include <Graphics/VertexBuffer.hpp>
#include <Graphics/VertexDeclaration.hpp>
#include <Graphics/VertexElement.hpp>
#include <Graphics/VertexPositionColor.hpp>
#include <Graphics/VertexPositionColorTexture.hpp>
#include <Graphics/VertexPositionNormalTexture.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

VertexBuffer::VertexBuffer(GraphicsDevice& graphicsDevice)
    : GraphicsResource(graphicsDevice),
      vertexCount(0),
      vbo(BufferTarget::ArrayBuffer, BufferUsage::StaticDraw),
      vao()
{
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

template <>
void VertexBuffer::SetData(const std::vector<VertexPositionColor>& data)
{
    VertexDeclaration vDecl = VertexPositionNormalTexture::GetVertexDeclaration();

    this->BufferData(vDecl, data.size(), data.data());
}

template <>
void VertexBuffer::SetData(const std::vector<VertexPositionColorTexture>& data)
{
    VertexDeclaration vDecl = VertexPositionNormalTexture::GetVertexDeclaration();

    this->BufferData(vDecl, data.size(), data.data());
}

template <>
void VertexBuffer::SetData(const std::vector<VertexPositionNormalTexture>& data)
{
    VertexDeclaration vDecl = VertexPositionNormalTexture::GetVertexDeclaration();

    this->BufferData(vDecl, data.size(), data.data());
}

void VertexBuffer::Activate()
{
    this->vao.Activate();
}

void VertexBuffer::Deactivate()
{
    this->vao.Deactivate();
}

void VertexBuffer::BufferData(const VertexDeclaration& vDecl, const UInt32& count, const GLvoid* data)
{
    this->vao.DeclareVertexFormat(vDecl);
    this->vbo.BufferData(count * vDecl.ComponentCount() * sizeof(Single), data);
}
