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

Size Decoder::GetCharCount(const uint8_t* bytes, const Size& count, const bool& flush) const
{
    auto vbytes = std::vector<uint8_t>(bytes, bytes + count);

    return this->GetCharCount(vbytes, 0, count, flush);
}

Size Decoder::GetCharCount(const std::vector<uint8_t>& bytes
                         , const Size&                 index
                         , const Size&                 count
                         , const bool&                 flush) const
{
    return this->GetCharCount(bytes, index, count);
}

Size Decoder::GetChars(const uint8_t* bytes
                     , const Size&    byteCount
                     , char16_t*      chars
                     , const Size&    charCount
                     , const bool&    flush) const
{
    auto vbytes = std::vector<uint8_t>(bytes, bytes + byteCount);
    auto vchars = std::vector<char16_t>();

    vchars.reserve(this->GetCharCount(vbytes, 0, byteCount, flush));

    auto totalChars = this->GetChars(vbytes, 0, byteCount, vchars, 0, flush);
    auto result     = ((totalChars > charCount) ? charCount : totalChars);

    std::copy_n(vchars.begin(), result, chars);

    return result;
}

Size Decoder::GetChars(const std::vector<uint8_t>& bytes
                     , const Size&                 byteIndex
                     , const Size&                 byteCount
                     , std::vector<char16_t>&      chars
                     , const Size&                 charIndex
                     , const bool&                 flush) const
{
    return this->GetChars(bytes, byteIndex, byteCount, chars, charIndex);
}
