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

#include <System/IO/MemoryStream.hpp>

using namespace System;
using namespace System::IO;

MemoryStream::MemoryStream(const std::vector<UByte>& buffer)
    : stream(std::ios::in | std::ios::out | std::ios::binary)
    , mode(std::ios::in | std::ios::out | std::ios::binary)
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

UByte MemoryStream::ReadByte()
{
    UByte buffer;

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
