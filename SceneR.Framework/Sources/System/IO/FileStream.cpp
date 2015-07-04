// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <System/IO/FileStream.hpp>

#include <System/Text/Encoding.hpp>

using namespace System;
using namespace System::IO;
using namespace System::Text;

FileStream::FileStream(const std::u16string& path)
    : FileStream { path, std::ios::in | std::ios::binary }
{
}

FileStream::FileStream(const std::u16string& path, const std::ios::openmode& mode)
    : stream { Encoding::Convert(path), mode }
    , mode   { mode }
{
}

FileStream::~FileStream()
{
    this->Close();
}

bool FileStream::CanRead()
{
    return ((this->mode & std::ios::in) == std::ios::in);
}

bool FileStream::CanSeek()
{
    return true;
}

bool FileStream::CanWrite()
{
    return ((this->mode & std::ios::out) == std::ios::out);
}

size_t FileStream::Position()
{
    return this->stream.tellg();
}

size_t FileStream::Length()
{
    auto position = this->Position();
    this->Seek(0, std::ios::end);
    auto result = this->Position();
    this->Seek(position, std::ios::beg);

    return result;
}

void FileStream::Close()
{
    if (this->stream.is_open())
    {
        this->stream.close();
    }
}

uint8_t FileStream::ReadByte()
{
    uint8_t buffer;

    this->Read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

size_t FileStream::Read(char* buffer, const size_t& offset, const size_t& count)
{
    this->stream.read(buffer + offset, count);

    return this->stream.gcount();
}

size_t FileStream::Seek(const size_t& offset, const std::ios::seekdir& origin)
{
    this->stream.seekg(offset, origin);

    return this->Position();
}
