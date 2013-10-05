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

#include "Content/ContentReader.hpp"

using namespace SceneR::Core;
using namespace SceneR::Content;
using namespace SceneR::Graphics;

ContentReader::ContentReader(GraphicsDevice&           graphicsDevice,
                             ContentTypeReaderManager& typeReaderManager,
                             const std::string&        file)
    : graphicsDevice(graphicsDevice), typeReaderManager(typeReaderManager)
{
    this->stream.open(file.c_str(), std::ios::in | std::ios::binary);

    if (!this->stream.is_open())
    {
        throw std::runtime_error(std::string("Failed to open file: ") + file);
    }

    this->stream.seekg(0, std::ios_base::beg);
    this->ReadHeader();
}

ContentReader::~ContentReader()
{
    this->Close();
}

void ContentReader::Close()
{
    if (this->stream.is_open())
    {
        this->stream.close();
    }
}

GraphicsDevice& ContentReader::GetGraphicsDevice()
{
    return this->graphicsDevice;
}

wchar_t ContentReader::ReadChar()
{
    wchar_t buffer = this->ReadByte();

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

std::wstring ContentReader::ReadString()
{
    std::wstring buffer;
    UInt32       length = this->ReadUInt32();

    for (int i = 0; i < length; i++)
    {
        buffer.push_back(this->ReadChar());
    }

    return buffer;
}

UInt32 ContentReader::Read7BitEncodedInt()
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

UInt32 ContentReader::ReadByte()
{
    char buffer;

    int pos = this->stream.tellg();

    this->stream.read(&buffer, sizeof buffer);

    pos = this->stream.tellg();

    return static_cast<UInt32>(buffer);
}

Int16 ContentReader::ReadInt16()
{
    Int16 buffer;

    this->stream.read((char*) &buffer, sizeof buffer);

    return buffer;
}

UInt16 SceneR::Content::ContentReader::ReadUInt16()
{
    UInt16 buffer;

    this->stream.read((char*) &buffer, sizeof buffer);

    return buffer;
}

Int32 ContentReader::ReadInt32()
{
    Int32 buffer;

    this->stream.read((char*) &buffer, sizeof buffer);

    return buffer;
}

UInt32 SceneR::Content::ContentReader::ReadUInt32()
{
    UInt32 buffer;

    this->stream.read((char*) &buffer, sizeof buffer);

    return buffer;
}

Single ContentReader::ReadSingle()
{
    Single buffer;

    this->stream.read((char*) &buffer, sizeof buffer);

    return buffer;
}

Double ContentReader::ReadDouble()
{
    Double buffer;

    this->stream.read((char*) &buffer, sizeof buffer);

    return buffer;
}

Color ContentReader::ReadColor()
{
    Single r = this->ReadSingle();
    Single g = this->ReadSingle();
    Single b = this->ReadSingle();
    Single a = this->ReadSingle();

    return Color(r, g, b, a);
}

Matrix ContentReader::ReadMatrix()
{
    Single m11 = this->ReadSingle();
    Single m12 = this->ReadSingle();
    Single m13 = this->ReadSingle();
    Single m14 = this->ReadSingle();

    Single m21 = this->ReadSingle();
    Single m22 = this->ReadSingle();
    Single m23 = this->ReadSingle();
    Single m24 = this->ReadSingle();

    Single m31 = this->ReadSingle();
    Single m32 = this->ReadSingle();
    Single m33 = this->ReadSingle();
    Single m34 = this->ReadSingle();

    Single m41 = this->ReadSingle();
    Single m42 = this->ReadSingle();
    Single m43 = this->ReadSingle();
    Single m44 = this->ReadSingle();

    return Matrix(m11, m12, m13, m14,
                  m21, m22, m23, m24,
                  m31, m32, m33, m34,
                  m41, m42, m43, m44);
}

Vector2 ContentReader::ReadVector2()
{
    Single x = this->ReadSingle();
    Single y = this->ReadSingle();

    return Vector2(x, y);
}

Vector3 ContentReader::ReadVector3()
{
    Single x = this->ReadSingle();
    Single y = this->ReadSingle();
    Single z = this->ReadSingle();

    return Vector3(x, y, z);
}

Vector4 ContentReader::ReadVector4()
{
    Single x = this->ReadSingle();
    Single y = this->ReadSingle();
    Single z = this->ReadSingle();
    Single w = this->ReadSingle();

    return Vector4(x, y, z, w);
}

Quaternion ContentReader::ReadQuaternion()
{
    Single x = this->ReadSingle();
    Single y = this->ReadSingle();
    Single z = this->ReadSingle();
    Single w = this->ReadSingle();

    return Quaternion(x, y, z, w);
}

std::vector<Int16> ContentReader::ReadBytes(Int32 count)
{
    std::vector<Int16> result;

    result.reserve(count);

    for (int i = 0; i < count; i++)
    {
        result.push_back(this->ReadByte());
    }

    return result;
}

void ContentReader::ReadHeader()
{
    // Magic number.
    this->ReadByte();
    this->ReadByte();
    this->ReadByte();
    this->ReadByte();

    // Format version.
    this->ReadInt32();
}

const int ContentReader::Position()
{
    return this->stream.tellg();
}
