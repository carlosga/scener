// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <System/IO/BinaryReader.hpp>

#include <string>

#include <System/IO/Stream.hpp>
#include <System/Text/Encoding.hpp>

namespace System
{
    namespace IO
    {
        using System::Text::Encoding;

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
            char16_t buffer = static_cast<std::uint32_t>(_stream.read_byte());

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
                    buffer  |= static_cast<std::uint32_t>(_stream.read_byte()) & 0x3F;
                }
            }

            return buffer;
        }

        template<>
        std::u16string BinaryReader::read()
        {
            return _encoding.GetString(read_bytes(read_7_bit_encoded_int()));
        }

        template<>
        bool BinaryReader::read()
        {
            return static_cast<bool>(_stream.read_byte());
        }

        template <>
        std::uint8_t BinaryReader::read()
        {
            return _stream.read_byte();
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
            return -1;
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
    }
}