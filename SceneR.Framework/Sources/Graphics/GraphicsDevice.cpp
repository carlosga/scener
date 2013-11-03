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

#include <Framework/Color.hpp>
#include <GL/glew.h>
#include <Graphics/Effect.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/IndexBuffer.hpp>
#include <Graphics/VertexBuffer.hpp>
#include <stdexcept>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;
using namespace SceneR::Shaders;

GraphicsDevice::GraphicsDevice(const GraphicsProfile&  graphicsProfile)
    : depthStencilState(*this),
      effect(nullptr),
      graphicsProfile(graphicsProfile),
      indexBuffer(nullptr),
      presentationParameters(),
      rasterizerState(*this),
      vertexBuffer(nullptr),
      viewport()
{
}

GraphicsDevice::~GraphicsDevice()
{
}

void GraphicsDevice::Clear(const Color& color) const
{
    glClearColor(color.R(), color.G(), color.B(), color.A());

    if (this->depthStencilState.GetDepthBufferEnable())
    {
        glClearDepth(1.0f);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsDevice::DrawIndexedPrimitives(const PrimitiveType& primitiveType,
                                           const UInt32&        baseVertex,
                                           const UInt32&        minVertexIndex,
                                           const UInt32&        numVertices,
                                           const UInt32&        startIndex,
                                           const UInt32&        primitiveCount) const
{
    if (this->indexBuffer == nullptr)
    {
        throw std::runtime_error("Set the IndexBuffer before calling DrawIndexedPrimitives");
    }
    if (this->vertexBuffer == nullptr)
    {
        throw std::runtime_error("Set the VertexBuffer before calling DrawIndexedPrimitives");
    }
    if (this->effect == nullptr)
    {
        throw std::runtime_error("Set the effect before calling DrawIndexedPrimitives");
    }

    this->effect->Begin();

    this->vertexBuffer->BindVertexArray();
    this->indexBuffer->BindIndexBuffer();

    glDrawElements(static_cast<GLenum>(primitiveType), numVertices, GL_UNSIGNED_INT, 0);

    this->indexBuffer->UnbindIndexBuffer();
    this->vertexBuffer->UnbindVertexArray();

    this->effect->End();
}

void GraphicsDevice::DrawInstancedPrimitives(const PrimitiveType& primitiveType,
                                             const UInt32&        baseVertex,
                                             const UInt32&        minVertexIndex,
                                             const UInt32&        numVertices,
                                             const UInt32&        startIndex,
                                             const UInt32&        primitiveCount,
                                             const UInt32&        instanceCount) const
{
    throw std::runtime_error("Not implemented");
}

void GraphicsDevice::DrawPrimitives(const PrimitiveType& primitiveType,
                                    const UInt32&        startVertex,
                                    const UInt32&        primitiveCount) const
{
    if (this->vertexBuffer == nullptr)
    {
        throw std::runtime_error("Set the VertexBuffer before calling DrawIndexedPrimitives");
    }
    if (this->effect == nullptr)
    {
        throw std::runtime_error("Set the effect before calling DrawIndexedPrimitives");
    }

    this->effect->Begin();

    this->vertexBuffer->BindVertexArray();

    glDrawArrays(static_cast<GLenum>(primitiveType), startVertex, primitiveCount);

    this->vertexBuffer->UnbindVertexArray();

    this->effect->End();
}

void GraphicsDevice::Present()
{
}

std::shared_ptr<Effect> GraphicsDevice::GetEffect()
{
    return this->effect;
}

void GraphicsDevice::SetEffect(std::shared_ptr<Effect> effect)
{
    this->effect = effect;
}

const GraphicsProfile& GraphicsDevice::GetGraphicsProfile() const
{
    return this->graphicsProfile;
}

DepthStencilState& GraphicsDevice::GetDepthStencilState()
{
    return this->depthStencilState;
}

PresentationParameters& GraphicsDevice::GetPresentationParameters()
{
    return this->presentationParameters;
}

std::shared_ptr<IndexBuffer> GraphicsDevice::GetIndexBuffer()
{
    return this->indexBuffer;
}

void GraphicsDevice::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
    this->indexBuffer = indexBuffer;
}

RasterizerState& GraphicsDevice::GetRasterizerState()
{
    return this->rasterizerState;
}

std::shared_ptr<VertexBuffer> GraphicsDevice::GetVertexBuffer()
{
    return this->vertexBuffer;
}

void GraphicsDevice::SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
    this->vertexBuffer = vertexBuffer;
}

Viewport& GraphicsDevice::GetViewport()
{
   return this->viewport;
}

void GraphicsDevice::SetViewport(Viewport& viewport)
{
    this->viewport = viewport;
    this->viewport.Refresh();
}
