// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <IO/MemoryStream.hpp>

#include <algorithm>

namespace SceneR
{
    namespace IO
    {
        MemoryStream::MemoryStream(const gsl::span<std::uint8_t>& buffer)
            : _buffer   { buffer }
            , _position { _buffer.begin() }
        {
        }

        bool MemoryStream::can_read()
        {
            return true;
        }

        bool MemoryStream::can_seek()
        {
            return true;
        }

        bool MemoryStream::can_write()
        {
            return false;
        }

        std::size_t MemoryStream::position()
        {
            return std::distance(_position, _buffer.begin());
        }

        std::size_t MemoryStream::length()
        {
            return _buffer.size();
        }

        void MemoryStream::close()
        {
        }

        std::uint32_t MemoryStream::read_byte()
        {
            std::uint8_t buffer;

            read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

            return buffer;
        }

        std::size_t MemoryStream::read(char* buffer, const std::size_t& offset, const std::size_t& count)
        {
            Ensures(_position + count <= _buffer.end());

            std::copy_n(_position, count, buffer + offset);

            _position += count;

            return count;
        }

        std::size_t MemoryStream::seek(const std::size_t& offset, const std::ios::seekdir& origin)
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
    }
}
