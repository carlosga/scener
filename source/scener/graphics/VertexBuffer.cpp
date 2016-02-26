// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/VertexBuffer.hpp"

#include "scener/graphics/GraphicsDevice.hpp"
#include "scener/graphics/opengl/BufferTarget.hpp"
#include "scener/graphics/opengl/BufferUsage.hpp"

namespace scener { namespace graphics {

using scener::graphics::opengl::Buffer;
using scener::graphics::opengl::BufferTarget;
using scener::graphics::opengl::BufferUsage;
using scener::graphics::opengl::VertexArrayObject;

VertexBuffer::VertexBuffer(gsl::not_null<GraphicsDevice*> graphicsDevice
                         , std::size_t                    vertexCount
                         , const VertexDeclaration&       vertexDeclaration) noexcept
    : GraphicsResource    { graphicsDevice }
    , _binding_index      { 0 }
    , _vertex_count       { vertexCount }
    , _vertex_declaration { vertexDeclaration }
    , _vao                { }
    , _vbo                { BufferTarget::array_buffer, BufferUsage::static_draw }
{
    _vao.bind_to_buffer(_vbo, _binding_index, 0, _vertex_declaration.vertex_stride());
    _vao.declare(_vertex_declaration, _binding_index);
}

std::size_t VertexBuffer::vertex_count() const noexcept
{
    return _vertex_count;
}

std::vector<std::uint8_t> VertexBuffer::get_data() const noexcept
{
    return get_data(0, _vertex_count);
}

std::vector<std::uint8_t> VertexBuffer::get_data(std::size_t startIndex, std::size_t elementCount) const noexcept
{
    auto offset = (startIndex   * _vertex_declaration.vertex_stride());
    auto size   = (elementCount * _vertex_declaration.vertex_stride());

    return _vbo.get_data(offset, size);
}

void VertexBuffer::set_data(const gsl::span<const std::uint8_t>& data) const noexcept
{
    _vbo.set_data(_vertex_count * _vertex_declaration.vertex_stride(), data.data());
}

const VertexDeclaration& VertexBuffer::vertex_declaration() const noexcept
{
    return _vertex_declaration;
}

void VertexBuffer::bind() noexcept
{
    _vao.bind();
}

void VertexBuffer::unbind() noexcept
{
    _vao.unbind();
}

}}
