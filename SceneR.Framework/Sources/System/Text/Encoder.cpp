// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <System/Text/Encoder.hpp>

using namespace System;
using namespace System::Text;

Encoder::Encoder()
{
}

Encoder::~Encoder()
{
}

size_t Encoder::GetByteCount(const char16_t* chars, const size_t& count, const bool& flush) const
{
    auto vchars = std::vector<char16_t>(chars, chars + count);

    return this->GetByteCount(vchars, 0, count, flush);
}

size_t Encoder::GetBytes(const char16_t* chars
                       , const size_t&   charCount
                       , uint8_t*        bytes
                       , const size_t&   byteCount
                       , const bool&     flush) const
{
    auto vchars = std::vector<char16_t>(chars, chars + charCount);
    auto vbytes = std::vector<uint8_t>();

    vbytes.reserve(this->GetByteCount(vchars, 0, charCount, flush));

    auto totalBytes = this->GetBytes(vchars, 0, charCount, vbytes, 0, flush);
    auto result     = ((totalBytes > byteCount) ? byteCount : totalBytes);

    std::copy_n(vbytes.begin(), result, bytes);

    return result;
}

void Encoder::Reset()
{
}
