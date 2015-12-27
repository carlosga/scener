// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/IO/FileStream.hpp"

#include "SceneR/Text/Encoding.hpp"

namespace SceneR
{
    namespace IO
    {
        using SceneR::Text::Encoding;

        FileStream::FileStream(const std::string& path, const std::ios::openmode& mode)
            : _stream { path, mode }
            , _mode   { mode }
        {
        }

        FileStream::~FileStream()
        {
            close();
        }

        bool FileStream::can_read()
        {
            return ((_mode & std::ios::in) == std::ios::in);
        }

        bool FileStream::can_seek()
        {
            return true;
        }

        bool FileStream::can_write()
        {
            return ((_mode & std::ios::out) == std::ios::out);
        }

        std::size_t FileStream::position()
        {
            return _stream.tellg();
        }

        std::size_t FileStream::length()
        {
            auto original = position();
            seek(0, std::ios::end);
            auto result = position();
            seek(original, std::ios::beg);

            return result;
        }

        void FileStream::close()
        {
            if (_stream.is_open())
            {
                _stream.close();
            }
        }

        std::uint32_t FileStream::read_byte()
        {
            std::uint8_t buffer;

            read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

            return buffer;
        }

        std::size_t FileStream::read(char* buffer, const std::size_t& offset, const std::size_t& count)
        {
            _stream.read(buffer + offset, count);

            return _stream.gcount();
        }

        std::size_t FileStream::seek(const std::size_t& offset, const std::ios::seekdir& origin)
        {
            _stream.seekg(offset, origin);

            return position();
        }
    }
}
