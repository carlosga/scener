// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <System/Text/Encoding.hpp>

#include <locale>

#include <System/Text/UTF8Encoding.hpp>

using namespace System;
using namespace System::Text;

const Encoding& Encoding::UTF8 = UTF8Encoding { };

Encoding::Encoding()
{
}

Encoding::~Encoding()
{
}

std::vector<uint8_t> Encoding::Convert(const Encoding&            srcEncoding
                                     , const Encoding&            dstEncoding
                                     , const std::vector<uint8_t> &bytes)
{
    return Encoding::Convert(srcEncoding, dstEncoding, bytes, 0, bytes.size());
}

std::vector<uint8_t> Encoding::Convert(const Encoding&             srcEncoding
                                     , const Encoding&             dstEncoding
                                     , const std::vector<uint8_t>& bytes
                                     , const size_t&               index
                                     , const size_t&               count)
{
    auto srcChars = srcEncoding.GetChars(bytes, index, count);

    return dstEncoding.GetBytes(srcChars, 0, srcChars.size());
}

std::string Encoding::Convert(const std::u16string& source)
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter; // UTF-8 <-> UTF-16 converter

    return converter.to_bytes(source);
}

std::u16string Encoding::Convert(const std::string& source)
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter; // UTF-8 <-> UTF-16 converter

    return converter.from_bytes(source);
}

bool Encoding::IsReadOnly() const
{
    return true;
}

size_t Encoding::GetByteCount(const std::vector<char16_t>& chars) const
{
    return this->GetByteCount(chars, 0, chars.size());
}

size_t Encoding::GetByteCount(const std::u16string& s) const
{
    auto temp = std::vector<char16_t>(s.begin(), s.end());

    return this->GetByteCount(temp, 0, temp.size());
}

size_t Encoding::GetByteCount(const char16_t* chars, const size_t& count) const
{
    auto temp = std::vector<char16_t>(chars, chars + count);

    return this->GetByteCount(temp, 0, count);
}

std::vector<uint8_t> Encoding::GetBytes(const std::vector<char16_t>& chars) const
{
    return this->GetBytes(chars, 0, chars.size());
}

std::vector<uint8_t> Encoding::GetBytes(const std::u16string& s) const
{
    auto temp = std::vector<char16_t>(s.begin(), s.end());

    return this->GetBytes(temp, 0, temp.size());
}

std::vector<uint8_t> Encoding::GetBytes(const std::vector<char16_t>& chars
                                      , const size_t&                index
                                      , const size_t&                count) const
{
    auto result = std::vector<uint8_t>();

    result.reserve(this->GetByteCount(chars, index, count));

    this->GetBytes(chars, index, count, result, 0);

    return result;
}

size_t Encoding::GetBytes(const char16_t* chars
                        , const size_t&   charCount
                        , uint8_t*        bytes
                        , const size_t&   byteCount) const
{
    return this->GetEncoder().GetBytes(chars, charCount, bytes, byteCount, false);
}

size_t Encoding::GetBytes(const std::u16string& s
                        , const size_t&         charIndex
                        , const size_t&         charCount
                        , std::vector<uint8_t>& bytes
                        , const size_t&         byteIndex) const
{
    auto temp = std::vector<char16_t>(s.begin(), s.end());

    return this->GetBytes(temp, charIndex, charCount, bytes, byteIndex);
}

size_t Encoding::GetCharCount(const std::vector<uint8_t>& bytes) const
{
    return this->GetCharCount(bytes, 0, bytes.size());
}

size_t Encoding::GetCharCount(const uint8_t* bytes, const size_t& count) const
{
    auto temp = std::vector<uint8_t>(bytes, bytes + count);

    return this->GetCharCount(temp, 0, count);
}

std::vector<char16_t> Encoding::GetChars(const std::vector<uint8_t>& bytes) const
{
    return this->GetChars(bytes, 0, bytes.size());
}

std::vector<char16_t> Encoding::GetChars(const std::vector<uint8_t>& bytes
                                       , const size_t&               index
                                       , const size_t&               count) const
{
    auto result = std::vector<char16_t>();

    result.reserve(this->GetCharCount(bytes, index, count));

    this->GetChars(bytes, index, count, result, 0);

    return result;
}

size_t Encoding::GetChars(const uint8_t* bytes
                        , const size_t&  byteCount
                        , char16_t*      chars
                        , const size_t&  charCount) const
{
    return this->GetDecoder().GetChars(bytes, byteCount, chars, charCount, false);
}

std::u16string Encoding::GetString(const std::vector<uint8_t>& bytes) const
{
    return this->GetString(bytes, 0, bytes.size());
}

std::u16string Encoding::GetString(const std::vector<uint8_t>& bytes
                                 , const size_t&               index
                                 , const size_t&               count) const
{
    auto chars = this->GetChars(bytes, index, count);

    return std::u16string(chars.begin(), chars.end());
}
