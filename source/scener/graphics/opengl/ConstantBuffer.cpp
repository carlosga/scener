// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/opengl/ConstantBuffer.hpp"

#include "scener/graphics/opengl/BufferTarget.hpp"
#include "scener/graphics/opengl/BufferUsage.hpp"

namespace scener { namespace graphics { namespace opengl {

constant_buffer::constant_buffer(const std::string& name, std::uint32_t programId) noexcept
    : _buffer_object { buffer_target::uniform_buffer, buffer_usage::dynamic_draw }
    , _program_id    { programId }
    , _index         { 0 }
    , _binding_point { 0 }
    , _size          { 0 }
    , _name          { name }
{
    create();
}

std::int32_t constant_buffer::binding_point() const noexcept
{
    return _binding_point;
}

std::size_t constant_buffer::index() const noexcept
{
    return _index;
}

std::size_t constant_buffer::size() const noexcept
{
    return _size;
}

void constant_buffer::bind() const noexcept
{
    glBindBufferBase(static_cast<GLenum>(_buffer_object.target()), _binding_point, _buffer_object.id());
}

void constant_buffer::unbind() const noexcept
{
    glBindBufferBase(static_cast<GLenum>(_buffer_object.target()), 0, 0);
}

std::vector<std::uint8_t> constant_buffer::get_data() const noexcept
{
    return get_data(0, _size);
}

std::vector<std::uint8_t> constant_buffer::get_data(std::size_t offset, std::size_t count) const noexcept
{
    Ensures(count <= _size);

    return _buffer_object.get_data(offset, count);
}

void constant_buffer::set_data(gsl::not_null<const void*> data) const noexcept
{
    set_data(0, _size, data);
}

void constant_buffer::set_data(std::size_t offset, std::size_t count, gsl::not_null<const void*> data) const noexcept
{
    Ensures((offset + count) <= _size);

    _buffer_object.set_data(offset, count, data);
}

void constant_buffer::create() noexcept
{
    std::int32_t binding   = 0;
    std::int32_t blockSize = 0;

    // Get the uniform block index
    _index = glGetUniformBlockIndex(_program_id, _name.c_str());

    // Get the binding point
    glGetActiveUniformBlockiv(_program_id, _index, GL_UNIFORM_BLOCK_BINDING, &binding);

    // Get uniform block data size
    glGetActiveUniformBlockiv(_program_id, _index, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);

    // update class members
    _binding_point = binding;
    _size          = blockSize;

    // initialize the buffer object
    std::vector<std::uint8_t> data(_size, 0);

    _buffer_object.set_data(_size, data.data());
}

}}}
