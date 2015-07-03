// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <System/Text/UTF8Encoding.hpp>

using namespace System;
using namespace System::Text;

UTF8Encoding::UTF8Encoding()
    : Encoding { }
{
}

UTF8Encoding::~UTF8Encoding()
{
}

const String UTF8Encoding::EncodingName() const
{
    return u"Unicode (UTF-8)";
}

bool UTF8Encoding::IsSingleByte() const
{
    return false;
}

Size UTF8Encoding::GetByteCount(const std::vector<char16_t>& chars
                              , const Size&                  index
                              , const Size&                  count) const
{
    return this->encoder.GetByteCount(chars, index, count, false);
}

Size UTF8Encoding::GetBytes(const std::vector<char16_t>& chars
                          , const Size&                  charIndex
                          , const Size&                  charCount
                          , std::vector<UByte>&          bytes
                          , const Size&                  byteIndex) const
{
    return this->encoder.GetBytes(chars, charIndex, charCount, bytes, byteIndex, false);
}

Size UTF8Encoding::GetCharCount(const std::vector<UByte>& bytes
                              , const Size&               index
                              , const Size&               count) const
{
    return this->decoder.GetCharCount(bytes, index, count);
}

Size UTF8Encoding::GetChars(const std::vector<UByte>& bytes
                          , const Size&               byteIndex
                          , const Size&               byteCount
                          , std::vector<char16_t>&    chars
                          , const Size&               charIndex) const
{
    return this->decoder.GetChars(bytes, byteIndex, byteCount, chars, charIndex);
}

Size UTF8Encoding::GetMaxByteCount(const Size& charCount)
{
    return (charCount * 4);
}

Size UTF8Encoding::GetMaxCharCount(const Size& byteCount)
{
    return byteCount; // Every character could be 1 byte lenght
}

std::vector<UByte> UTF8Encoding::GetPreamble() const
{
    return { 0xef, 0xbb, 0xbf };
}

const Decoder& System::Text::UTF8Encoding::GetDecoder() const
{
    return this->decoder;
}

const Encoder& System::Text::UTF8Encoding::GetEncoder() const
{
    return this->encoder;
}
