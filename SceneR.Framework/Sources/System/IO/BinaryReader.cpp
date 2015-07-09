// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <System/IO/BinaryReader.hpp>

#include <System/IO/Stream.hpp>
#include <System/Text/Encoding.hpp>

namespace System
{
    namespace IO
    {
        using System::Text::Encoding;

        BinaryReader::BinaryReader(Stream& stream)
            : BinaryReader ( stream, Encoding::UTF8 )
        {
        }

        BinaryReader::BinaryReader(Stream& stream, const Encoding& encoding)
            : stream   { stream }
            , encoding { encoding }
        {
        }

        BinaryReader::~BinaryReader()
        {
            this->Close();
        }

        Stream& BinaryReader::BaseStream()
        {
            return this->stream;
        }

        void BinaryReader::Close()
        {
            this->stream.Close();
        }

        std::int32_t BinaryReader::PeekChar()
        {
            return -1;
        }

        char16_t BinaryReader::ReadChar()
        {
            char16_t buffer = this->ReadByte();

            // http://xbox.create.msdn.com/en-US/sample/xnb_format
            // Decode UTF-8.
            if (buffer & 0x80)
            {
                int byteCount = 1;

                while (buffer & (0x80 >> byteCount))
                {
                    byteCount++;
                }

                buffer &= (1 << (8 - byteCount)) - 1;

                while (--byteCount)
                {
                    buffer <<= 6;
                    buffer |= this->ReadByte() & 0x3F;
                }
            }

            return buffer;
        }

        std::u16string BinaryReader::ReadString()
        {
            return this->encoding.GetString(this->ReadBytes(this->Read7BitEncodedInt()));
        }

        std::uint32_t BinaryReader::Read7BitEncodedInt()
        {
            std::uint32_t result   = 0;
            std::uint32_t bitsRead = 0;
            std::uint32_t value    = 0;

            do
            {
                value = this->ReadByte();

                result |= (value & 0x7f) << bitsRead;

                bitsRead += 7;
            } while (value & 0x80);

            return result;
        }

        bool BinaryReader::ReadBoolean()
        {
            return static_cast<bool>(this->ReadByte());
        }

        std::uint8_t BinaryReader::ReadByte()
        {
            std::uint8_t buffer;

            this->stream.Read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

            return buffer;
        }

        std::vector<std::uint8_t> BinaryReader::ReadBytes(const std::size_t& count)
        {
            auto buffer = std::vector<std::uint8_t>(count);
            auto readed = this->stream.Read(reinterpret_cast<char*>(&buffer[0]), 0, count);

            if (readed < count)
            {
                buffer.resize(readed);
            }

            return buffer;
        }

        std::int16_t BinaryReader::ReadInt16()
        {
            std::int16_t buffer;

            this->stream.Read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

            return buffer;
        }

        std::uint16_t BinaryReader::ReadUInt16()
        {
            std::uint16_t buffer;

            this->stream.Read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

            return buffer;
        }

        std::int32_t BinaryReader::ReadInt32()
        {
            std::int32_t buffer;

            this->stream.Read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

            return buffer;
        }

        std::uint32_t BinaryReader::ReadUInt32()
        {
            std::uint32_t buffer;

            this->stream.Read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

            return buffer;
        }

        std::int64_t BinaryReader::ReadInt64()
        {
            std::int64_t buffer;

            this->stream.Read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

            return buffer;
        }

        std::uint64_t BinaryReader::ReadUInt64()
        {
            std::uint64_t buffer;

            this->stream.Read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

            return buffer;
        }

        float BinaryReader::ReadSingle()
        {
            float buffer;

            this->stream.Read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

            return buffer;
        }

        double BinaryReader::ReadDouble()
        {
            double buffer;

            this->stream.Read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

            return buffer;
        }
    }
}
