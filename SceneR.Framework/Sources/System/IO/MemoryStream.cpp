// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <System/IO/MemoryStream.hpp>

using namespace System;
using namespace System::IO;

MemoryStream::MemoryStream(const std::vector<uint8_t>& buffer)
    : stream { std::ios::in | std::ios::out | std::ios::binary }
    , mode   { std::ios::in | std::ios::out | std::ios::binary }
{
    // TODO: There should be a better way of doing this
    for (Size i = 0; i < buffer.size(); i++)
    {
        this->stream << buffer[i];
    }

    this->Seek(0, std::ios_base::beg);
}

MemoryStream::~MemoryStream()
{
    this->Close();
}

bool MemoryStream::CanRead()
{
    return ((this->mode & std::ios::in) == std::ios::in);
}

bool MemoryStream::CanSeek()
{
    return true;
}

bool MemoryStream::CanWrite()
{
    return ((this->mode & std::ios::out) == std::ios::out);
}

Size MemoryStream::Position()
{
    return this->stream.tellg();
}

Size MemoryStream::Length()
{
    auto position = this->Position();
    this->Seek(0, std::ios::end);
    auto result = this->Position();
    this->Seek(position, std::ios::beg);

    return result;
}

void MemoryStream::Close()
{
}

uint8_t MemoryStream::ReadByte()
{
    uint8_t buffer;

    this->Read(reinterpret_cast<char*>(&buffer), 0, sizeof buffer);

    return buffer;
}

Size MemoryStream::Read(char* buffer, const Size& offset, const Size& count)
{
    this->stream.read(buffer + offset, count);

    return this->stream.gcount();
}

Size MemoryStream::Seek(const Size& offset, const std::ios::seekdir& origin)
{
    this->stream.seekg(offset, origin);

    return this->Position();
}
