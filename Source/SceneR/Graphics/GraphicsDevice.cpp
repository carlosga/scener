// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "GraphicsDevice.hpp"

#include <cstdint>

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "EffectTechnique.hpp"
#include "EffectTechnique.hpp"
#include "VertexDeclaration.hpp"

namespace SceneR { namespace Graphics {

using SceneR::Math::Color;

std::size_t GraphicsDevice::get_element_count(const PrimitiveType& primitiveType
                                            , const std::size_t&   primitiveCount) noexcept
{
    switch (primitiveType)
    {
    case PrimitiveType::LineList:
        return primitiveCount * 2;

    case PrimitiveType::LineLoop:
        return primitiveCount;

    case PrimitiveType::LineStrip:
        return primitiveCount + 1;

    case PrimitiveType::PointList:
        return primitiveCount;

    case PrimitiveType::TriangleFan:
        return primitiveCount;

    case PrimitiveType::TriangleList:
        return primitiveCount * 3;

    case PrimitiveType::TriangleStrip:
        return primitiveCount + 2;
    }
}

GraphicsDevice::GraphicsDevice() noexcept
    : effect                   { nullptr }
    , index_buffer             { nullptr }
    , vertex_buffer            { nullptr }
    , _blend_state             { this }
    , _depth_stencil_state     { this }
    , _presentation_parameters { }
    , _rasterizer_state        { this }
    , _viewport                { }
{
}

void GraphicsDevice::dispose()
{
    _blend_state.dispose();
    _depth_stencil_state.dispose();
    _rasterizer_state.dispose();

    if (effect)
    {
        effect = nullptr;
    }
    if (index_buffer)
    {
        index_buffer = nullptr;
    }
    if (vertex_buffer)
    {
        vertex_buffer = nullptr;
    }
}

void GraphicsDevice::clear(const Color& color) const
{
    std::uint32_t bufferBits = GL_COLOR_BUFFER_BIT;

    glClearColor(color.r, color.g, color.b, color.a);

    if (_depth_stencil_state.depth_buffer_enable)
    {
        bufferBits |= GL_DEPTH_BUFFER_BIT;
        glClearDepth(1.0f);
    }
    if (_depth_stencil_state.stencil_enable)
    {
        bufferBits |= GL_STENCIL_BUFFER_BIT;
        glClearStencil(1);
    }

    glClear(bufferBits);
}

void GraphicsDevice::draw_indexed_primitives(const PrimitiveType& primitiveType
                                           , const std::size_t&   baseVertex
                                           , const std::size_t&   minVertexIndex
                                           , const std::size_t&   numVertices
                                           , const std::size_t&   startIndex
                                           , const std::size_t&   primitiveCount) const
{
    if (index_buffer == nullptr)
    {
        throw std::runtime_error("Set the IndexBuffer before calling DrawIndexedPrimitives");
    }
    if (vertex_buffer == nullptr)
    {
        throw std::runtime_error("Set the VertexBuffer before calling DrawIndexedPrimitives");
    }
    if (effect == nullptr)
    {
        throw std::runtime_error("Set the effect before calling DrawIndexedPrimitives");
    }

    auto offset = startIndex * index_buffer->element_size_in_bytes();

    effect->begin();
    vertex_buffer->bind();
    index_buffer->bind();

    glDrawElementsBaseVertex(static_cast<GLenum>(primitiveType)
                           , static_cast<GLsizei>(get_element_count(primitiveType, primitiveCount))
                           , static_cast<GLenum>(index_buffer->index_element_type())
                           , reinterpret_cast<void*>(offset)
                           , static_cast<GLint>(baseVertex));

    index_buffer->unbind();
    vertex_buffer->unbind();
    effect->end();
}

void GraphicsDevice::draw_primitives(const PrimitiveType& primitiveType
                                   , const std::size_t&   startVertex
                                   , const std::size_t&   primitiveCount) const
{
    if (vertex_buffer == nullptr)
    {
        throw std::runtime_error("Set the VertexBuffer before calling DrawIndexedPrimitives");
    }
    if (effect == nullptr)
    {
        throw std::runtime_error("Set the effect before calling DrawIndexedPrimitives");
    }

    effect->begin();
    vertex_buffer->bind();

    glDrawArrays(static_cast<GLenum>(primitiveType)
               , static_cast<GLint>(startVertex)
               , static_cast<GLsizei>(primitiveCount));

    vertex_buffer->unbind();
    effect->end();
}

void GraphicsDevice::present()
{
    // TODO
    // glfwSwapBuffers(glfwGetCurrentContext());
}

BlendState& GraphicsDevice::blend_state() noexcept
{
    return _blend_state;
}

DepthStencilState& GraphicsDevice::depth_stencil_state() noexcept
{
    return _depth_stencil_state;
}

PresentationParameters& GraphicsDevice::presentation_parameters() noexcept
{
    return _presentation_parameters;
}

RasterizerState& GraphicsDevice::rasterizer_state() noexcept
{
    return _rasterizer_state;
}

Viewport& GraphicsDevice::viewport() noexcept
{
   return _viewport;
}

void GraphicsDevice::viewport(const Viewport& viewport) noexcept
{
    _viewport = viewport;
    _viewport.update();
}

}}
