// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/io/file_stream.hpp"

//#include <locale>
//#include <codecvt>

namespace scener { namespace io {

file_stream::file_stream(const std::string& path, const std::ios::openmode& mode) noexcept
    : _stream { path, mode }
    , _mode   { mode }
{
//    if (_stream.is_open() && _stream.good())
//    {
//        _stream.imbue(std::locale(_stream.getloc(), new std::codecvt_utf8<char16_t, 0x10ffff, std::consume_header>));
//    }
}

bool file_stream::can_read() const noexcept
{
    return ((_mode & std::ios::in) == std::ios::in && _stream.is_open() && _stream.good());
}

bool file_stream::can_seek() const noexcept
{
    return true;
}

bool file_stream::can_write() const noexcept
{
    return ((_mode & std::ios::out) == std::ios::out && _stream.is_open() && _stream.good());
}

std::size_t file_stream::position() noexcept
{
    return _stream.tellg();
}

std::size_t file_stream::length() noexcept
{
    auto original = position();
    seek(0, std::ios::end);
    auto result = position();
    seek(original, std::ios::beg);

    return result;
}

void file_stream::close() noexcept
{
    if (_stream.is_open())
    {
        _stream.close();
    }
}

std::int32_t file_stream::read_byte() noexcept
{
    if (!_stream.good())
    {
        return -1;
    }

    std::uint8_t buffer;

    read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

std::size_t file_stream::read(char* buffer, std::size_t offset, std::size_t count) noexcept
{
    if (!_stream.good())
    {
        return 0;
    }

    _stream.read(buffer + offset, count);

    return _stream.gcount();
}

std::size_t file_stream::seek(std::size_t offset, std::ios::seekdir origin) noexcept
{
    _stream.seekg(offset, origin);

    return position();
}

}}
