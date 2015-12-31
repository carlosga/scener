// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/VertexBuffer.hpp"

#include "SceneR/Graphics/GraphicsDevice.hpp"
#include "SceneR/Graphics/VertexDeclaration.hpp"
#include "SceneR/Graphics/OpenGL/Buffer.hpp"
#include "SceneR/Graphics/OpenGL/BufferTarget.hpp"
#include "SceneR/Graphics/OpenGL/BufferUsage.hpp"
#include "SceneR/Graphics/OpenGL/VertexArrayObject.hpp"

namespace SceneR { namespace Graphics {

using SceneR::Graphics::OpenGL::Buffer;
using SceneR::Graphics::OpenGL::BufferTarget;
using SceneR::Graphics::OpenGL::BufferUsage;
using SceneR::Graphics::OpenGL::VertexArrayObject;

VertexBuffer::VertexBuffer(gsl::not_null<GraphicsDevice*>     graphicsDevice
                         , const std::size_t&                 vertexCount
                         , std::unique_ptr<VertexDeclaration> vertexDeclaration) noexcept
    : GraphicsResource    { graphicsDevice }
    , _binding_index      { 0 }
    , _vertex_count       { vertexCount }
    , _vertex_declaration { std::move(vertexDeclaration) }
    , _vao                { nullptr }
    , _vbo                { nullptr }
{
    create();
}

void VertexBuffer::dispose()
{
    if (_vao != nullptr)
    {
        _vao->dispose();
        _vao = nullptr;
    }
    if (_vbo != nullptr)
    {
        _vbo->dispose();
        _vbo = nullptr;
    }
}

std::size_t VertexBuffer::vertex_count() const noexcept
{
    return _vertex_count;
}

std::vector<std::uint8_t> VertexBuffer::get_data() const noexcept
{
    return get_data(0, _vertex_count);
}

std::vector<std::uint8_t> VertexBuffer::get_data(const std::size_t& startIndex
                                               , const std::size_t& elementCount) const noexcept
{
    Expects(_vbo != nullptr)

    auto offset = (startIndex   * _vertex_declaration->vertex_stride());
    auto size   = (elementCount * _vertex_declaration->vertex_stride());

    return _vbo->get_data(offset, size);
}

void VertexBuffer::set_data(const gsl::span<std::uint8_t>& data) const noexcept
{
    Expects(_vbo != nullptr)

    _vbo->set_data(_vertex_count * _vertex_declaration->vertex_stride(), data.data());
}

VertexDeclaration* VertexBuffer::vertex_declaration() const noexcept
{
    return _vertex_declaration.get();
}

void VertexBuffer::bind() noexcept
{
    Expects(_vao != nullptr)

    _vao->bind();
}

void VertexBuffer::unbind() noexcept
{
    Expects(_vao != nullptr)

    _vao->unbind();
}

void VertexBuffer::create() noexcept
{
    _vao = std::make_unique<VertexArrayObject>();
    _vbo = std::make_unique<Buffer>(BufferTarget::array_buffer, BufferUsage::static_draw);

    _vao->create();
    _vbo->create();

    _vertex_declaration->declare(_vao->id(), _binding_index);

    glVertexArrayVertexBuffer(_vao->id(), _binding_index, _vbo->id(), 0, _vertex_declaration->vertex_stride());
}

}}
