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
#include <Graphics/VertexBuffer.hpp>
#include <Graphics/VertexBufferTarget.hpp>
#include <Graphics/VertexBufferUsage.hpp>
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
      vbo(0),
      vao(0)
{
    // Create the vertex array ...
    this->CreateVertexArray();
    // ... create the Vertex Buffer ...
    this->CreateVertexBuffer();
}

VertexBuffer::~VertexBuffer()
{
    this->Release();
}

const UInt32& VertexBuffer::GetVertexCount() const
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
    VertexDeclaration vDecl      = VertexPositionColor::GetVertexDeclaration();
    Size              index      = 0;
    Size              bufferSize = (data.size() * vDecl.GetComponentCount());

    // Create the data buffer
    Single buffer[bufferSize];

    // Fill the data buffer with vertex data
    // Raw processing there should be a better way to serialize vertex data
    for (const auto& vertex : data)
    {
        const Vector3& position = vertex.GetPosition();
        const Color&   color    = vertex.GetColor();

        // process position components
        for (int i = 0; i < 3; i++)
        {
            buffer[index++] = position[i];
        }

        // process color components
        for (int i = 0; i < 4; i++)
        {
            buffer[index++] = color[i];
        }
    }

    this->BindVertexBuffer();

    glBufferData(static_cast<GLenum>(VertexBufferTarget::ArrayBuffer),
                 bufferSize * sizeof(Single),
                 &buffer,
                 static_cast<GLenum>(VertexBufferUsage::StaticDraw));

    this->UnbindVertexBuffer();
    this->DeclareVertexFormat(VertexPositionColor::GetVertexDeclaration());
 }

template <>
void VertexBuffer::SetData(const std::vector<VertexPositionColorTexture>& data)
{
    VertexDeclaration vDecl      = VertexPositionColorTexture::GetVertexDeclaration();
    Size              index      = 0;
    Size              bufferSize = (data.size() * vDecl.GetComponentCount());

    // Create the data buffer
    Single buffer[bufferSize];

    // Fill the data buffer with vertex data
    // Raw processing there should be a better way to serialize vertex data
    for (const auto& vertex : data)
    {
        const Vector3& position = vertex.GetPosition();
        const Color&   color    = vertex.GetColor();
        const Vector2& tcoord   = vertex.GetTextureCoordinate();

        // process position components
        for (int i = 0; i < 3; i++)
        {
            buffer[index++] = position[i];
        }

        // process color components
        for (int i = 0; i < 4; i++)
        {
            buffer[index++] = color[i];
        }

        // process texture components
        for (int i = 0; i < 2; i++)
        {
            buffer[index++] = tcoord[i];
        }
    }

    this->BindVertexBuffer();

    glBufferData(static_cast<GLenum>(VertexBufferTarget::ArrayBuffer),
                 bufferSize * sizeof(Single),
                 &buffer,
                 static_cast<GLenum>(VertexBufferUsage::StaticDraw));

    this->UnbindVertexBuffer();
    this->DeclareVertexFormat(vDecl);
}

template <>
void VertexBuffer::SetData(const std::vector<VertexPositionNormalTexture>& data)
{
    VertexDeclaration vDecl      = VertexPositionNormalTexture::GetVertexDeclaration();
    Size              index      = 0;
    Size              bufferSize = (data.size() * vDecl.GetComponentCount());

    // Create the data buffer
    Single buffer[bufferSize];

    // Fill the data buffer with vertex data
    // Raw processing there should be a better way to serialize vertex data
    for (const auto& vertex : data)
    {
        const Vector3& position = vertex.GetPosition();
        const Vector3& normal   = vertex.GetNormal();
        const Vector2& tcoord   = vertex.GetTextureCoordinate();

        // process position components
        for (int i = 0; i < 3; i++)
        {
            buffer[index++] = position[i];
        }

        // process normal components
        for (int i = 0; i < 3; i++)
        {
            buffer[index++] = normal[i];
        }

        // process texture components
        for (int i = 0; i < 2; i++)
        {
            buffer[index++] = tcoord[i];
        }
    }

    this->BindVertexBuffer();

    glBufferData(static_cast<GLenum>(VertexBufferTarget::ArrayBuffer),
                 bufferSize * sizeof(Single),
                 &buffer,
                 static_cast<GLenum>(VertexBufferUsage::StaticDraw));

    this->UnbindVertexBuffer();
    this->DeclareVertexFormat(vDecl);
}

void VertexBuffer::CreateVertexBuffer()
{
    glGenBuffers(1, &this->vbo);
}

void VertexBuffer::BindVertexBuffer() const
{
    glBindBuffer(static_cast<GLenum>(VertexBufferTarget::ArrayBuffer), this->vbo);
}

void VertexBuffer::UnbindVertexBuffer() const
{
    if (this->vbo != 0)
    {
        glBindBuffer(static_cast<GLenum>(VertexBufferTarget::ArrayBuffer), 0);
    }
}

void VertexBuffer::DeleteVertexBuffer()
{
    if (this->vbo != 0)
    {
        this->UnbindVertexBuffer();
        glDeleteBuffers(1, &this->vbo);
        this->vbo = 0;
    }
}

void VertexBuffer::CreateVertexArray()
{
    glGenVertexArrays(1, &this->vao);
}

void VertexBuffer::BindVertexArray() const
{
    glBindVertexArray(this->vao);
}

void VertexBuffer::UnbindVertexArray() const
{
    if (this->vao != 0)
    {
        glBindVertexArray(0);
    }
}

void VertexBuffer::DeleteVertexArray()
{
    if (this->vao != 0)
    {
        this->UnbindVertexArray();
        glDeleteVertexArrays(1, &this->vao);
        this->vao = 0;
    }
}

void VertexBuffer::DeclareVertexFormat(const VertexDeclaration& vDecl) const
{
    // Bind the vertex buffer and array ...
    this->BindVertexBuffer();
    this->BindVertexArray();

    glBindVertexBuffer(0, this->vbo, 0, vDecl.GetVertexStride());

    // ... declare vertex elements
    for (const VertexElement& ve : vDecl.GetVertexElements())
    {
        glVertexAttribFormat(ve.GetUsageIndex(),
                             ve.GetComponentCount(),
                             GL_FLOAT,
                             false,
                             ve.GetOffset());

        glVertexAttribBinding(ve.GetUsageIndex(), 0);
        glEnableVertexAttribArray(ve.GetUsageIndex());
    }

    // ... and unbind the vertex array and buffer
    this->UnbindVertexArray();
    this->UnbindVertexBuffer();
}

void VertexBuffer::Release()
{
    this->DeleteVertexBuffer();
    this->DeleteVertexArray();
}
