// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/OpenGL/Buffer.hpp"

#include "SceneR/Graphics/OpenGL/BufferTarget.hpp"
#include "SceneR/Graphics/OpenGL/BufferUsage.hpp"

namespace SceneR { namespace Graphics { namespace OpenGL {

Buffer::Buffer(BufferTarget target, BufferUsage usage) noexcept
    : _id     { 0 }
    , _target { target }
    , _usage  { usage }
{
    create();
}

Buffer::~Buffer() noexcept
{
    if (_id != 0)
    {
        glDeleteBuffers(1, &_id);
        _id = 0;
    }
}

std::uint32_t Buffer::id() const noexcept
{
    return _id;
}

BufferTarget Buffer::target() const noexcept
{
    return _target;
}

BufferUsage Buffer::usage() const noexcept
{
    return _usage;
}

void Buffer::bind() const noexcept
{
    glBindBuffer(static_cast<GLenum>(_target), _id);
}

void Buffer::unbind() const noexcept
{
    glBindBuffer(static_cast<GLenum>(_target), 0);
}

std::vector<std::uint8_t> Buffer::get_data(std::size_t offset, std::size_t count) const noexcept
{
    auto data = std::vector<std::uint8_t>(count, 0);

    glGetNamedBufferSubData(_id, static_cast<GLintptr>(offset), static_cast<GLintptr>(count), data.data());

    return data;
}

void Buffer::set_data(std::size_t count, gsl::not_null<const void*> data) const noexcept
{
    glNamedBufferData(_id, static_cast<GLintptr>(count), data, static_cast<GLenum>(_usage));
}

void Buffer::set_data(std::size_t offset, std::size_t count, gsl::not_null<const void*> data) const noexcept
{
    glNamedBufferSubData(_id, static_cast<GLintptr>(offset), static_cast<GLintptr>(count), data);
}

void Buffer::invalidate() const noexcept
{
    glInvalidateBufferData(_id);
}

void Buffer::invalidate(std::size_t offset, const std::size_t count) const noexcept
{
    glInvalidateBufferSubData(_id, static_cast<GLintptr>(offset), static_cast<GLintptr>(count));
}

void Buffer::create() noexcept
{
    glCreateBuffers(1, &_id);

    Ensures(_id > 0);
}

}}}
