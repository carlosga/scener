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

Size Encoder::GetByteCount(const Char* chars, const Size& count, const Boolean& flush) const
{
    auto vchars = std::vector<Char>(chars, chars + count);

    return this->GetByteCount(vchars, 0, count, flush);
}

Size Encoder::GetBytes(const Char*    chars
                     , const Size&    charCount
                     , UByte*         bytes
                     , const Size&    byteCount
                     , const Boolean& flush) const
{
    auto vchars = std::vector<Char>(chars, chars + charCount);
    auto vbytes = std::vector<UByte>();

    vbytes.reserve(this->GetByteCount(vchars, 0, charCount, flush));

    auto totalBytes = this->GetBytes(vchars, 0, charCount, vbytes, 0, flush);
    auto result     = ((totalBytes > byteCount) ? byteCount : totalBytes);

    std::copy_n(vbytes.begin(), result, bytes);

    return result;
}

void Encoder::Reset()
{
}
