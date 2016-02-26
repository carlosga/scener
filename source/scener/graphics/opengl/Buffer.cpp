// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/opengl/Buffer.hpp"

#include "scener/graphics/opengl/BufferTarget.hpp"
#include "scener/graphics/opengl/BufferUsage.hpp"

namespace scener { namespace graphics { namespace opengl {

buffer::buffer(buffer_target target, buffer_usage usage) noexcept
    : _id     { 0 }
    , _target { target }
    , _usage  { usage }
{
    create();
}

buffer::~buffer() noexcept
{
    if (_id != 0)
    {
        glDeleteBuffers(1, &_id);
        _id = 0;
    }
}

std::uint32_t buffer::id() const noexcept
{
    return _id;
}

buffer_target buffer::target() const noexcept
{
    return _target;
}

buffer_usage buffer::usage() const noexcept
{
    return _usage;
}

void buffer::bind() const noexcept
{
    glBindBuffer(static_cast<GLenum>(_target), _id);
}

void buffer::unbind() const noexcept
{
    glBindBuffer(static_cast<GLenum>(_target), 0);
}

std::vector<std::uint8_t> buffer::get_data(std::size_t offset, std::size_t count) const noexcept
{
    auto data = std::vector<std::uint8_t>(count, 0);

    glGetNamedBufferSubData(_id, static_cast<GLintptr>(offset), static_cast<GLintptr>(count), data.data());

    return data;
}

void buffer::set_data(std::size_t count, gsl::not_null<const void*> data) const noexcept
{
    glNamedBufferData(_id, static_cast<GLintptr>(count), data, static_cast<GLenum>(_usage));
}

void buffer::set_data(std::size_t offset, std::size_t count, gsl::not_null<const void*> data) const noexcept
{
    glNamedBufferSubData(_id, static_cast<GLintptr>(offset), static_cast<GLintptr>(count), data);
}

void buffer::invalidate() const noexcept
{
    glInvalidateBufferData(_id);
}

void buffer::invalidate(std::size_t offset, const std::size_t count) const noexcept
{
    glInvalidateBufferSubData(_id, static_cast<GLintptr>(offset), static_cast<GLintptr>(count));
}

void buffer::create() noexcept
{
    glCreateBuffers(1, &_id);

    Ensures(_id > 0);
}

}}}
