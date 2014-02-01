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

Size Decoder::GetCharCount(const UByte* bytes, const Size& count, const Boolean& flush) const
{
    std::vector<UByte> vbytes(bytes, bytes + count);

    return this->GetCharCount(vbytes, 0, count, flush);
}

Size Decoder::GetCharCount(const std::vector<UByte>& bytes
                         , const Size&               index
                         , const Size&               count
                         , const Boolean&            flush) const
{
    return this->GetCharCount(bytes, index, count);
}

Size Decoder::GetChars(const UByte*   bytes
                     , const Size&    byteCount
                     , Char*          chars
                     , const Size&    charCount
                     , const Boolean& flush) const
{
    std::vector<UByte> vbytes(bytes, bytes + byteCount);
    std::vector<Char>  vchars;

    vchars.reserve(this->GetCharCount(vbytes, 0, byteCount, flush));

    Size totalChars = this->GetChars(vbytes, 0, byteCount, vchars, 0, flush);
    Size result     = ((totalChars > charCount) ? charCount : totalChars);

    std::copy_n(vchars.begin(), result, chars);

    return result;
}

Size Decoder::GetChars(const std::vector<UByte>& bytes
                     , const Size&               byteIndex
                     , const Size&               byteCount
                     , std::vector<Char>&        chars
                     , const Size&               charIndex
                     , const Boolean&            flush) const
{
    return this->GetChars(bytes, byteIndex, byteCount, chars, charIndex);
}
