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

size_t Decoder::GetCharCount(const uint8_t* bytes, const size_t& count, const bool& flush) const
{
    auto vbytes = std::vector<uint8_t>(bytes, bytes + count);

    return this->GetCharCount(vbytes, 0, count, flush);
}

size_t Decoder::GetCharCount(const std::vector<uint8_t>& bytes
                         , const size_t&                 index
                         , const size_t&                 count
                         , const bool&                   flush) const
{
    return this->GetCharCount(bytes, index, count);
}

size_t Decoder::GetChars(const uint8_t* bytes
                       , const size_t&  byteCount
                       , char16_t*      chars
                       , const size_t&  charCount
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

size_t Decoder::GetChars(const std::vector<uint8_t>& bytes
                       , const size_t&               byteIndex
                       , const size_t&               byteCount
                       , std::vector<char16_t>&      chars
                       , const size_t&               charIndex
                       , const bool&                 flush) const
{
    return this->GetChars(bytes, byteIndex, byteCount, chars, charIndex);
}
