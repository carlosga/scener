// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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
    auto vbytes = std::vector<UByte>(bytes, bytes + count);

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
    auto vbytes = std::vector<UByte>(bytes, bytes + byteCount);
    auto vchars = std::vector<Char>();

    vchars.reserve(this->GetCharCount(vbytes, 0, byteCount, flush));

    auto totalChars = this->GetChars(vbytes, 0, byteCount, vchars, 0, flush);
    auto result     = ((totalChars > charCount) ? charCount : totalChars);

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
