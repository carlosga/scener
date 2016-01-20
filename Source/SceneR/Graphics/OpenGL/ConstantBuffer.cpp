// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/OpenGL/ConstantBuffer.hpp"

#include "SceneR/Graphics/OpenGL/Buffer.hpp"
#include "SceneR/Graphics/OpenGL/BufferTarget.hpp"
#include "SceneR/Graphics/OpenGL/BufferUsage.hpp"

namespace SceneR { namespace Graphics { namespace OpenGL {

ConstantBuffer::ConstantBuffer(const std::string& name) noexcept
    : _name          { name }
    , _index         { 0 }
    , _binding_point { 0 }
    , _size          { 0 }
    , _buffer_object { std::make_unique<Buffer>(BufferTarget::uniform_buffer, BufferUsage::dynamic_draw) }
{
}

std::int32_t ConstantBuffer::binding_point() const noexcept
{
    return _binding_point;
}

std::size_t ConstantBuffer::index() const noexcept
{
    return _index;
}

std::size_t ConstantBuffer::size() const noexcept
{
    return _size;
}

void ConstantBuffer::bind() const noexcept
{
    glBindBufferBase(static_cast<GLenum>(_buffer_object->target()), _binding_point, _buffer_object->id());
}

void ConstantBuffer::create(std::uint32_t programId) noexcept
{
    std::int32_t binding   = 0;
    std::int32_t blockSize = 0;

    // Get the uniform block index
    _index = glGetUniformBlockIndex(programId, _name.c_str());

    // Get the binding point
    glGetActiveUniformBlockiv(programId, _index, GL_UNIFORM_BLOCK_BINDING, &binding);

    // Get uniform block data size
    glGetActiveUniformBlockiv(programId, _index, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);

    // update class members
    _binding_point = binding;
    _size          = blockSize;

    // Create the buffer object
    _buffer_object->create();

    // initialize the buffer object
    std::vector<std::uint8_t> data(_size, 0);

    _buffer_object->set_data(_size, data.data());
}

void ConstantBuffer::unbind() const noexcept
{
    glBindBufferBase(static_cast<GLenum>(_buffer_object->target()), 0, 0);
}

std::vector<std::uint8_t> ConstantBuffer::get_data() const noexcept
{
    return get_data(0, _size);
}

std::vector<std::uint8_t> ConstantBuffer::get_data(std::size_t offset, std::size_t count) const noexcept
{
    return _buffer_object->get_data(offset, count);
}

void ConstantBuffer::set_data(gsl::not_null<const void*> data) const noexcept
{
    set_data(0, _size, data);
}

void ConstantBuffer::set_data(std::size_t offset, std::size_t count, gsl::not_null<const void*> data) const noexcept
{
    _buffer_object->set_data(offset, count, data);
}

}}}
