// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/io/memory_stream.hpp"

#include <algorithm>

namespace scener { namespace io {

memory_stream::memory_stream(const gsl::span<std::uint8_t>& buffer) noexcept
    : _buffer   { buffer }
    , _position { _buffer.begin() }
{
}

bool memory_stream::can_read() const noexcept
{
    return true;
}

bool memory_stream::can_seek() const noexcept
{
    return true;
}

bool memory_stream::can_write() const noexcept
{
    return false;
}

std::size_t memory_stream::position() noexcept
{
    return std::distance(_position, _buffer.begin());
}

std::size_t memory_stream::length() noexcept
{
    return _buffer.size();
}

void memory_stream::close() noexcept
{
}

std::int32_t memory_stream::read_byte() noexcept
{
    std::uint8_t buffer;

    read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

std::size_t memory_stream::read(char* buffer, std::size_t offset, std::size_t count) noexcept
{
    Ensures(_position + count <= _buffer.end());

    std::copy_n(_position, count, buffer + offset);

    _position += count;

    return count;
}

std::size_t memory_stream::seek(std::size_t offset, std::ios::seekdir origin) noexcept
{
    Expects(origin == std::ios_base::beg || origin == std::ios_base::cur);

    if (origin == std::ios_base::beg && offset < static_cast<std::size_t>(_buffer.size()))
    {
        _position = _buffer.begin() + offset;
    }
    else if (origin == std::ios_base::cur && ((_position + offset) <= _buffer.end()))
    {
        _position += offset;
    }

    return position();
}

}}
