// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <System/IO/MemoryStream.hpp>

namespace System
{
    namespace IO
    {
        MemoryStream::MemoryStream(const std::vector<std::uint8_t>& buffer)
            : _stream { std::ios::in | std::ios::out | std::ios::binary }
            , _mode   { std::ios::in | std::ios::out | std::ios::binary }
        {
            seek(0, std::ios_base::beg);

            _stream.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());

            seek(0, std::ios_base::beg);
        }

        MemoryStream::~MemoryStream()
        {
            this->close();
        }

        bool MemoryStream::can_read()
        {
            return ((_mode & std::ios::in) == std::ios::in);
        }

        bool MemoryStream::can_seek()
        {
            return true;
        }

        bool MemoryStream::can_write()
        {
            return ((_mode & std::ios::out) == std::ios::out);
        }

        std::size_t MemoryStream::position()
        {
            return _stream.tellg();
        }

        std::size_t MemoryStream::length()
        {
            auto original = position();
            seek(0, std::ios::end);
            auto result = position();
            seek(original, std::ios::beg);

            return result;
        }

        void MemoryStream::close()
        {
        }

        std::uint8_t MemoryStream::read_byte()
        {
            std::uint8_t buffer;

            read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

            return buffer;
        }

        std::size_t MemoryStream::read(char* buffer, const std::size_t& offset, const std::size_t& count)
        {
            _stream.read(buffer + offset, count);

            return _stream.gcount();
        }

        std::size_t MemoryStream::seek(const std::size_t& offset, const std::ios::seekdir& origin)
        {
            _stream.seekg(offset, origin);

            return position();
        }
    }
}
