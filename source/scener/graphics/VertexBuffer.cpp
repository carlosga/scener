// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/VertexBuffer.hpp"

#include "scener/graphics/GraphicsDevice.hpp"
#include "scener/graphics/opengl/BufferTarget.hpp"
#include "scener/graphics/opengl/BufferUsage.hpp"

namespace scener { namespace graphics {

using scener::graphics::opengl::buffer;
using scener::graphics::opengl::buffer_target;
using scener::graphics::opengl::buffer_usage;
using scener::graphics::opengl::vertex_array_object;

vertex_buffer::vertex_buffer(gsl::not_null<graphics_device*>     device
                           , std::size_t                         vertex_count
                           , const graphics::vertex_declaration& vertex_declaration) noexcept
    : graphics_resource   { device }
    , _binding_index      { 0 }
    , _vertex_count       { vertex_count }
    , _vertex_declaration { vertex_declaration }
    , _vao                { }
    , _vbo                { buffer_target::array_buffer, buffer_usage::static_draw }
{
    _vao.bind_to_buffer(_vbo, _binding_index, 0, _vertex_declaration.vertex_stride());
    _vao.declare(_vertex_declaration, _binding_index);
}

std::size_t vertex_buffer::vertex_count() const noexcept
{
    return _vertex_count;
}

std::vector<std::uint8_t> vertex_buffer::get_data() const noexcept
{
    return get_data(0, _vertex_count);
}

std::vector<std::uint8_t> vertex_buffer::get_data(std::size_t startIndex, std::size_t elementCount) const noexcept
{
    auto offset = (startIndex   * _vertex_declaration.vertex_stride());
    auto size   = (elementCount * _vertex_declaration.vertex_stride());

    return _vbo.get_data(offset, size);
}

void vertex_buffer::set_data(const gsl::span<const std::uint8_t>& data) const noexcept
{
    _vbo.set_data(_vertex_count * _vertex_declaration.vertex_stride(), data.data());
}

const vertex_declaration& vertex_buffer::vertex_declaration() const noexcept
{
    return _vertex_declaration;
}

void vertex_buffer::bind() noexcept
{
    _vao.bind();
}

void vertex_buffer::unbind() noexcept
{
    _vao.unbind();
}

}}
