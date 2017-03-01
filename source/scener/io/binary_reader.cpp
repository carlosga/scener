// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/io/binary_reader.hpp"

#include <string>

#include "scener/io/stream.hpp"

namespace scener::io
{
    binary_reader::binary_reader(io::stream& stream) noexcept
        : _stream { stream }
    {
    }

    stream& binary_reader::base_stream() noexcept
    {
        return _stream;
    }

    void binary_reader::close() noexcept
    {
        _stream.close();
    }

    template<>
    char16_t binary_reader::read() noexcept
    {
        std::uint32_t buffer = _stream.read_byte();

        // http://xbox.create.msdn.com/en-US/sample/xnb_format
        // Decode UTF-8.
        if ((buffer & 0x80) != 0)
        {
            std::uint32_t byte_count = 1;

            while ((buffer & (0x80 >> byte_count)) != 0)
            {
                byte_count++;
            }

            buffer &= (1 << (8 - byte_count)) - 1;

            while (--byte_count != 0)
            {
                buffer <<= 6;
                buffer  |= _stream.read_byte() & 0x3F;
            }
        }

        return static_cast<char16_t>(buffer);
    }

    template<>
    std::string binary_reader::read() noexcept
    {
        auto buffer = read_bytes(read_7_bit_encoded_int());

        return std::string(buffer.begin(), buffer.end());
    }


    template<>
    bool binary_reader::read() noexcept
    {
        return static_cast<bool>(_stream.read_byte());
    }

    template <>
    std::int8_t binary_reader::read() noexcept
    {
        std::int8_t buffer;

        _stream.read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

        return buffer;
    }

    template <>
    std::uint8_t binary_reader::read() noexcept
    {
        std::uint8_t buffer;

        _stream.read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

        return buffer;
    }

    template <>
    std::int16_t binary_reader::read() noexcept
    {
        std::int16_t buffer;

        _stream.read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

        return buffer;
    }

    template <>
    std::uint16_t binary_reader::read() noexcept
    {
        std::uint16_t buffer;

        _stream.read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

        return buffer;
    }

    template <>
    std::int32_t binary_reader::read() noexcept
    {
        std::int32_t buffer;

        _stream.read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

        return buffer;
    }

    template <>
    std::uint32_t binary_reader::read() noexcept
    {
        std::uint32_t buffer;

        _stream.read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

        return buffer;
    }

    template <>
    std::int64_t binary_reader::read() noexcept
    {
        std::int64_t buffer;

        _stream.read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

        return buffer;
    }

    template <>
    std::uint64_t binary_reader::read() noexcept
    {
        std::uint64_t buffer;

        _stream.read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

        return buffer;
    }

    template <>
    float binary_reader::read() noexcept
    {
        float buffer;

        _stream.read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

        return buffer;
    }

    template <>
    double binary_reader::read() noexcept
    {
        double buffer;

        _stream.read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

        return buffer;
    }

    std::int32_t binary_reader::peek_char() noexcept
    {
        std::int32_t next_char = -1;

        if (_stream.can_seek())
        {
            auto position = _stream.position();

            if (position != _stream.length())
            {
                next_char = _stream.read_byte();

                _stream.seek(position, std::ios::beg);
            }
        }

        return next_char;
    }

    std::uint32_t binary_reader::read_7_bit_encoded_int() noexcept
    {
        std::uint32_t result    = 0;
        std::uint32_t bits_read = 0;
        std::uint32_t value     = 0;

        do
        {
            value     = read<std::uint8_t>();
            result   |= (value & 0x7f) << bits_read;
            bits_read += 7;
        } while (value & 0x80);

        return result;
    }

    std::vector<std::uint8_t> binary_reader::read_bytes(std::size_t count) noexcept
    {
        auto buffer = std::vector<std::uint8_t>(count, 0);
        auto readed = _stream.read(reinterpret_cast<char*>(&buffer[0]), 0, count);

        if (readed < count)
        {
            buffer.resize(readed);
        }

        return buffer;
    }
}
