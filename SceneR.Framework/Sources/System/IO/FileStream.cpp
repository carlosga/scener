// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <System/IO/FileStream.hpp>

#include <System/Text/Encoding.hpp>

using namespace System;
using namespace System::IO;
using namespace System::Text;

FileStream::FileStream(const String& path)
    : FileStream { path, std::ios::in | std::ios::binary }
{
}

FileStream::FileStream(const String& path, const std::ios::openmode& mode)
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

Size FileStream::Position()
{
    return this->stream.tellg();
}

Size FileStream::Length()
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

UByte FileStream::ReadByte()
{
    UByte buffer;

    this->Read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

Size FileStream::Read(char* buffer, const Size& offset, const Size& count)
{
    this->stream.read(buffer + offset, count);

    return this->stream.gcount();
}

Size FileStream::Seek(const Size& offset, const std::ios::seekdir& origin)
{
    this->stream.seekg(offset, origin);

    return this->Position();
}
