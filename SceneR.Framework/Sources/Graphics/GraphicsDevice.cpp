// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/GraphicsDevice.hpp>

#include <Graphics/VertexBuffer.hpp>
#include <Graphics/IndexBuffer.hpp>
#include <Graphics/Effect.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

GraphicsDevice::GraphicsDevice(const GraphicsAdapter&                   adapter
                             , const SceneR::Graphics::GraphicsProfile& graphicsProfile)
    : blendState             { *this }
    , depthStencilState      { *this }
    , effect                 { nullptr }
    , graphicsAdapter        { adapter }
    , graphicsProfile        { graphicsProfile }
    , indexBuffer            { nullptr }
    , presentationParameters { }
    , rasterizerState        { *this }
    , samplerStates          ( )
    , vertexBuffer           { nullptr }
    , viewport               { }
{
    this->samplerStates.push_back(SamplerState(*this));
}

GraphicsDevice::~GraphicsDevice()
{
}

void GraphicsDevice::Dispose()
{
    this->blendState.Dispose();
    this->depthStencilState.Dispose();
    this->rasterizerState.Dispose();

    if (this->samplerStates.size() > 0)
    {
        for (auto& sampler : this->samplerStates)
        {
            sampler.Dispose();
        }

        this->samplerStates.clear();
    }

    if (this->effect)
    {
        this->effect->Dispose();
        this->effect = nullptr;
    }
    if (this->indexBuffer)
    {
        this->indexBuffer->Dispose();
        this->indexBuffer = nullptr;
    }
    if (this->vertexBuffer)
    {
        this->vertexBuffer->Dispose();
        this->vertexBuffer = nullptr;
    }
}

void GraphicsDevice::Clear(const Color& color) const
{
    UInt32 bufferBits = GL_COLOR_BUFFER_BIT;

    glClearColor(color.R(), color.G(), color.B(), color.A());

    if (this->depthStencilState.DepthBufferEnable())
    {
        bufferBits |= GL_DEPTH_BUFFER_BIT;
        glClearDepth(1.0f);
    }
    if (this->depthStencilState.StencilEnable())
    {
        bufferBits |= GL_STENCIL_BUFFER_BIT;
        glClearStencil(1);
    }

    glClear(bufferBits);
}

void GraphicsDevice::DrawIndexedPrimitives(const PrimitiveType& primitiveType
                                         , const Size&          baseVertex
                                         , const Size&          minVertexIndex
                                         , const Size&          numVertices
                                         , const Size&          startIndex
                                         , const Size&          primitiveCount) const
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

    auto offset = startIndex * ((this->indexBuffer->IndexElementSize() == IndexElementSize::SixteenBits) ? 2 : 4);

    this->effect->Begin();

    this->vertexBuffer->Activate();
    this->indexBuffer->Activate();

    glDrawElementsBaseVertex(static_cast<GLenum>(primitiveType)
                           , numVertices
                           , static_cast<GLenum>(this->indexBuffer->IndexElementSize())
                           , reinterpret_cast<void*>(offset)
                           , baseVertex);

    this->indexBuffer->Deactivate();
    this->vertexBuffer->Deactivate();

    this->effect->End();
}

void GraphicsDevice::DrawPrimitives(const PrimitiveType& primitiveType
                                  , const Size&          startVertex
                                  , const Size&          primitiveCount) const
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

const std::shared_ptr<SceneR::Graphics::Effect>& GraphicsDevice::Effect()
{
    return this->effect;
}

void GraphicsDevice::Effect(const std::shared_ptr<SceneR::Graphics::Effect>& effect)
{
    this->effect = effect;
}

const GraphicsAdapter& GraphicsDevice::Adapter() const
{
    return this->graphicsAdapter;
}

const SceneR::Graphics::GraphicsProfile& GraphicsDevice::GraphicsProfile() const
{
    return this->graphicsProfile;
}

SceneR::Graphics::BlendState& GraphicsDevice::BlendState()
{
    return this->blendState;
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

SceneR::Graphics::RasterizerState& GraphicsDevice::RasterizerState()
{
    return this->rasterizerState;
}

std::vector<SceneR::Graphics::SamplerState>& GraphicsDevice::SamplerStates()
{
    return samplerStates;
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
    this->viewport.Update();
}
