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

#include <System/Text/Encoder.hpp>

using namespace System;
using namespace System::Text;

Encoder::Encoder()
{
}

Encoder::~Encoder()
{
}

Size Encoder::GetByteCount(const Char* chars, const Size& count, const Boolean& flush) const
{
    std::vector<Char> vchars(chars, chars + count);

    return this->GetByteCount(vchars, 0, count, flush);
}

Size Encoder::GetBytes(const Char*    chars
                     , const Size&    charCount
                     , UByte*         bytes
                     , const Size&    byteCount
                     , const Boolean& flush) const
{
    std::vector<Char>  vchars(chars, chars + charCount);
    std::vector<UByte> vbytes;

    vbytes.reserve(this->GetByteCount(vchars, 0, charCount, flush));

    Size totalBytes = this->GetBytes(vchars, 0, charCount, vbytes, 0, flush);
    Size result     = ((totalBytes > byteCount) ? byteCount : totalBytes);

    std::copy_n(vbytes.begin(), result, bytes);

    return result;
}

void Encoder::Reset()
{
}
