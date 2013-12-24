//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#include <System/IO/BinaryReader.hpp>
#include <System/IO/Stream.hpp>

using namespace System;
using namespace System::IO;

BinaryReader::BinaryReader(Stream& stream)
    : stream(stream)
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

int BinaryReader::PeekChar()
{
    return -1;
}

Char BinaryReader::ReadChar()
{
    Char buffer = this->ReadByte();

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

String BinaryReader::ReadString()
{
    auto buffer = this->ReadBytes(this->Read7BitEncodedInt());

    return String(buffer.begin(), buffer.end());
}

Int32 BinaryReader::Read7BitEncodedInt()
{
    Int32 result   = 0;
    Int32 bitsRead = 0;
    Int32 value    = 0;

    do
    {
        value = this->ReadByte();

        result |= (value & 0x7f) << bitsRead;

        bitsRead += 7;
    } while (value & 0x80);

    return result;
}

Boolean BinaryReader::ReadBoolean()
{
    return static_cast<Boolean>(this->ReadByte());
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
