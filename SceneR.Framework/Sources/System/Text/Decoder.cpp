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

#include <System/Text/Decoder.hpp>

using namespace System;
using namespace System::Text;

Decoder::Decoder()
{
}

Decoder::~Decoder()
{
}

UInt32 Decoder::GetCharCount(const UByte* bytes, const UInt32& count, const Boolean& flush) const
{
    std::vector<UByte> vbytes(bytes, bytes + count);

    return this->GetCharCount(vbytes, 0, count, flush);
}

UInt32 Decoder::GetCharCount(const std::vector<UByte>& bytes
                           , const UInt32&             index
                           , const UInt32&             count
                           , const Boolean&            flush) const
{
    return this->GetCharCount(bytes, index, count);
}

UInt32 Decoder::GetChars(const UByte*   bytes
                       , const UInt32&  byteCount
                       , Char*          chars
                       , const UInt32&  charCount
                       , const Boolean& flush) const
{
    std::vector<UByte> vbytes(bytes, bytes + byteCount);
    std::vector<Char>  vchars;
    UInt32             count;

    count = this->GetCharCount(vbytes, 0, byteCount, flush);

    vchars.reserve(count);

    UInt32 totalChars = this->GetChars(vbytes, 0, byteCount, vchars, 0, flush);
    UInt32 result     = ((totalChars > charCount) ? charCount : totalChars);

    std::copy_n(vchars.begin(), result, chars);

    return result;
}

UInt32 Decoder::GetChars(const std::vector<UByte>& bytes
                       , const UInt32&             byteIndex
                       , const UInt32&             byteCount
                       , std::vector<Char>&        chars
                       , const UInt32&             charIndex
                       , const Boolean&            flush) const
{
    return this->GetChars(bytes, byteIndex, byteCount, chars, charIndex);
}
