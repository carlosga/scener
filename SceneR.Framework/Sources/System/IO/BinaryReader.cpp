// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <System/IO/BinaryReader.hpp>

#include <System/IO/Stream.hpp>

using namespace System;
using namespace System::IO;
using namespace System::Text;

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

Int32 BinaryReader::PeekChar()
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

UInt32 BinaryReader::Read7BitEncodedInt()
{
    UInt32 result   = 0;
    UInt32 bitsRead = 0;
    UInt32 value    = 0;

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

UByte BinaryReader::ReadByte()
{
    UByte buffer;

    this->stream.Read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

std::vector<UByte> BinaryReader::ReadBytes(const Size& count)
{
    auto buffer = std::vector<UByte>(count);
    auto readed = this->stream.Read(reinterpret_cast<char*>(&buffer[0]), 0, count);

    if (readed < count)
    {
        buffer.resize(readed);
    }

    return buffer;
}

Int16 BinaryReader::ReadInt16()
{
    Int16 buffer;

    this->stream.Read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

UInt16 BinaryReader::ReadUInt16()
{
    UInt16 buffer;

    this->stream.Read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

Int32 BinaryReader::ReadInt32()
{
    Int32 buffer;

    this->stream.Read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

UInt32 BinaryReader::ReadUInt32()
{
    UInt32 buffer;

    this->stream.Read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

Int64 BinaryReader::ReadInt64()
{
    Int64 buffer;

    this->stream.Read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

UInt64 BinaryReader::ReadUInt64()
{
    UInt64 buffer;

    this->stream.Read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

Single BinaryReader::ReadSingle()
{
    Single buffer;

    this->stream.Read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

Double BinaryReader::ReadDouble()
{
    Double buffer;

    this->stream.Read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}
