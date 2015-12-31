// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/IO/BinaryReader.hpp"

#include <string>

#include "SceneR/IO/Stream.hpp"
#include "SceneR/Text/Encoding.hpp"

namespace SceneR { namespace IO {

using SceneR::Text::Encoding;

BinaryReader::BinaryReader(Stream& stream, const Encoding& encoding)
    : _stream   { stream }
    , _encoding { encoding }
{
}

BinaryReader::~BinaryReader()
{
    close();
}

Stream& BinaryReader::base_stream()
{
    return _stream;
}

void BinaryReader::close()
{
    _stream.close();
}

template<>
char16_t BinaryReader::read()
{
    std::uint32_t buffer = _stream.read_byte();

    // http://xbox.create.msdn.com/en-US/sample/xnb_format
    // Decode UTF-8.
    if (buffer & 0x80)
    {
        std::uint32_t byteCount = 1;

        while (buffer & (0x80 >> byteCount))
        {
            byteCount++;
        }

        buffer &= (1 << (8 - byteCount)) - 1;

        while (--byteCount)
        {
            buffer <<= 6;
            buffer  |= _stream.read_byte() & 0x3F;
        }
    }

    return static_cast<char16_t>(buffer);
}

template<>
std::string BinaryReader::read()
{
    auto buffer = read_bytes(read_7_bit_encoded_int());

    return std::string(buffer.begin(), buffer.end());
}

template<>
bool BinaryReader::read()
{
    return static_cast<bool>(_stream.read_byte());
}

template <>
std::int8_t BinaryReader::read()
{
    std::int8_t buffer;

    _stream.read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

template <>
std::uint8_t BinaryReader::read()
{
    std::uint8_t buffer;

    _stream.read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

template <>
std::int16_t BinaryReader::read()
{
    std::int16_t buffer;

    _stream.read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

template <>
std::uint16_t BinaryReader::read()
{
    std::uint16_t buffer;

    _stream.read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

template <>
std::int32_t BinaryReader::read()
{
    std::int32_t buffer;

    _stream.read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

template <>
std::uint32_t BinaryReader::read()
{
    std::uint32_t buffer;

    _stream.read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

template <>
std::int64_t BinaryReader::read()
{
    std::int64_t buffer;

    _stream.read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

template <>
std::uint64_t BinaryReader::read()
{
    std::uint64_t buffer;

    _stream.read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

template <>
float BinaryReader::read()
{
    float buffer;

    _stream.read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

template <>
double BinaryReader::read()
{
    double buffer;

    _stream.read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

std::int32_t BinaryReader::peek_char()
{
    std::int32_t nextChar = -1;

    if (_stream.can_seek())
    {
        auto position = _stream.position();

        if (position != _stream.length())
        {
            nextChar = _stream.read_byte();

            _stream.seek(position, std::ios::beg);
        }
    }

    return nextChar;
}

std::uint32_t BinaryReader::read_7_bit_encoded_int()
{
    std::uint32_t result   = 0;
    std::uint32_t bitsRead = 0;
    std::uint32_t value    = 0;

    do
    {
        value     = read<std::uint8_t>();
        result   |= (value & 0x7f) << bitsRead;
        bitsRead += 7;
    } while (value & 0x80);

    return result;
}

std::vector<std::uint8_t> BinaryReader::read_bytes(const std::size_t& count)
{
    auto buffer = std::vector<std::uint8_t>(count, 0);
    auto readed = _stream.read(reinterpret_cast<char*>(&buffer[0]), 0, count);

    if (readed < count)
    {
        buffer.resize(readed);
    }

    return buffer;
}

}}
