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

std::u16string UTF8Encoding::EncodingName() const
{
    return u"Unicode (UTF-8)";
}

bool UTF8Encoding::IsSingleByte() const
{
    return false;
}

size_t UTF8Encoding::GetByteCount(const std::vector<char16_t>& chars
                                , const size_t&                index
                                , const size_t&                count) const
{
    return this->encoder.GetByteCount(chars, index, count, false);
}

size_t UTF8Encoding::GetBytes(const std::vector<char16_t>& chars
                            , const size_t&                charIndex
                            , const size_t&                charCount
                            , std::vector<uint8_t>&        bytes
                            , const size_t&                byteIndex) const
{
    return this->encoder.GetBytes(chars, charIndex, charCount, bytes, byteIndex, false);
}

size_t UTF8Encoding::GetCharCount(const std::vector<uint8_t>& bytes
                                , const size_t&               index
                                , const size_t&               count) const
{
    return this->decoder.GetCharCount(bytes, index, count);
}

size_t UTF8Encoding::GetChars(const std::vector<uint8_t>& bytes
                            , const size_t&               byteIndex
                            , const size_t&               byteCount
                            , std::vector<char16_t>&      chars
                            , const size_t&               charIndex) const
{
    return this->decoder.GetChars(bytes, byteIndex, byteCount, chars, charIndex);
}

size_t UTF8Encoding::GetMaxByteCount(const size_t& charCount)
{
    return (charCount * 4);
}

size_t UTF8Encoding::GetMaxCharCount(const size_t& byteCount)
{
    return byteCount; // Every character could be 1 byte lenght
}

std::vector<uint8_t> UTF8Encoding::GetPreamble() const
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
