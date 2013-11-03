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

#include <System/IO/FileStream.hpp>
#include <fstream>

using namespace System;
using namespace System::IO;

FileStream::FileStream(const String& path)
    : FileStream(path, std::ios::in | std::ios::binary)
{
}

FileStream::FileStream(const String& path, const std::ios::openmode& mode)
    : stream(path, mode),
      mode(mode)
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

bool System::IO::FileStream::CanWrite()
{
    return ((this->mode & std::ios::out) == std::ios::out);
}

Size FileStream::Position()
{
    return this->stream.tellg();
}

Size FileStream::Length()
{
    Size position = this->Position();
    this->Seek(0, std::ios::end);
    Size result = this->Position();
    this->Seek(position, std::ios::end);

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

void FileStream::Read(char* buffer, const Size& offset, const Size& count)
{
    this->stream.read(buffer + offset, count);
}

Size FileStream::Seek(const Size& offset, const std::ios::seekdir& origin)
{
    this->stream.seekg(offset, origin);

    return this->Position();
}
