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
#include <Graphics/IndexElementSize.hpp>
#include <Graphics/VertexBuffer.hpp>
#include <stdexcept>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

GraphicsDevice::GraphicsDevice(const GraphicsAdapter& adapter, const GraphicsProfile& graphicsProfile)
    : depthStencilState(*this),
      effect(nullptr),
      graphicsAdapter(adapter),
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

    if (this->depthStencilState.DepthBufferEnable())
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

    Size offset = startIndex * ((this->indexBuffer->IndexElementSize() == IndexElementSize::SixteenBits) ? 2 : 4);

    this->effect->Begin();

    this->vertexBuffer->Activate();
    this->indexBuffer->Activate();

    glDrawElements(static_cast<GLenum>(primitiveType),
                   numVertices,
                   static_cast<GLenum>(this->indexBuffer->IndexElementSize()),
                   reinterpret_cast<void*>(offset));

    this->indexBuffer->Deactivate();
    this->vertexBuffer->Deactivate();

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

    this->vertexBuffer->Activate();

    glDrawArrays(static_cast<GLenum>(primitiveType), startVertex, primitiveCount);

    this->vertexBuffer->Deactivate();

    this->effect->End();
}

void GraphicsDevice::Present()
{
    glfwSwapBuffers(glfwGetCurrentContext());
}

std::shared_ptr<SceneR::Graphics::Effect> GraphicsDevice::Effect()
{
    return this->effect;
}

void GraphicsDevice::Effect(std::shared_ptr<SceneR::Graphics::Effect> effect)
{
    this->effect = effect;
}

const GraphicsAdapter& GraphicsDevice::Adapter() const
{
    return this->graphicsAdapter;
}

const GraphicsProfile& GraphicsDevice::GetGraphicsProfile() const
{
    return this->graphicsProfile;
}

SceneR::Graphics::DepthStencilState& GraphicsDevice::DepthStencilState()
{
    return this->depthStencilState;
}

SceneR::Graphics::PresentationParameters& GraphicsDevice::PresentationParameters()
{
    return this->presentationParameters;
}

std::shared_ptr<SceneR::Graphics::IndexBuffer> GraphicsDevice::IndexBuffer()
{
    return this->indexBuffer;
}

void GraphicsDevice::IndexBuffer(const std::shared_ptr<SceneR::Graphics::IndexBuffer>& indexBuffer)
{
    this->indexBuffer = indexBuffer;
}

RasterizerState& GraphicsDevice::RasterizerState()
{
    return this->rasterizerState;
}

std::shared_ptr<SceneR::Graphics::VertexBuffer> GraphicsDevice::VertexBuffer()
{
    return this->vertexBuffer;
}

void GraphicsDevice::VertexBuffer(const std::shared_ptr<SceneR::Graphics::VertexBuffer>& vertexBuffer)
{
    this->vertexBuffer = vertexBuffer;
}

SceneR::Graphics::Viewport& GraphicsDevice::Viewport()
{
   return this->viewport;
}

void GraphicsDevice::Viewport(SceneR::Graphics::Viewport& viewport)
{
    this->viewport = viewport;
    this->viewport.Refresh();
}
