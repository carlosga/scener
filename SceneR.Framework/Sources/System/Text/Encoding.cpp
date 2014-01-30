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

#include <System/Text/Encoding.hpp>
#include <System/Text/UTF8Encoding.hpp>
#include <codecvt>
#include <locale>

using namespace System;
using namespace System::Text;

const Encoding& Encoding::UTF8 = UTF8Encoding{};

Encoding::Encoding()
{
}

Encoding::~Encoding()
{
}

std::vector<UByte> Encoding::Convert(const Encoding&           srcEncoding
                                   , const Encoding&           dstEncoding
                                   , const std::vector<UByte>& bytes)
{
    return Encoding::Convert(srcEncoding, dstEncoding, bytes, 0, bytes.size());
}

std::vector<UByte> Encoding::Convert(const Encoding&           srcEncoding
                                   , const Encoding&           dstEncoding
                                   , const std::vector<UByte>& bytes
                                   , const UInt32&             index
                                   , const UInt32&             count)
{
    auto srcChars = srcEncoding.GetChars(bytes, index, count);

    return dstEncoding.GetBytes(srcChars, 0, srcChars.size());
}

std::string Encoding::Convert(const String& source)
{
    typedef std::codecvt_utf8_utf16<char16_t> convert_type; // UTF-8 <-> UTF-16 converter
    std::wstring_convert<convert_type, char16_t> converter;

    return converter.to_bytes(source);
};

System::String Encoding::Convert(const std::string& source)
{
    typedef std::codecvt_utf8_utf16<char16_t> convert_type; // UTF-8 <-> UTF-16 converter
    std::wstring_convert<convert_type, char16_t> converter;

    return converter.from_bytes(source);
};

bool Encoding::IsReadOnly() const
{
    return true;
}

UInt32 Encoding::GetByteCount(const std::vector<Char>& chars) const
{
    return this->GetByteCount(chars, 0, chars.size());
}

UInt32 Encoding::GetByteCount(const String& s) const
{
    std::vector<Char> temp(s.begin(), s.end());

    return this->GetByteCount(temp, 0, temp.size());
}

UInt32 Encoding::GetByteCount(const Char* chars, const UInt32& count) const
{
    std::vector<Char> temp(chars, chars + count);

    return this->GetByteCount(temp, 0, count);
}

std::vector<UByte> Encoding::GetBytes(const std::vector<Char>& chars) const
{
    return this->GetBytes(chars, 0, chars.size());
}

std::vector<UByte> Encoding::GetBytes(const String& s) const
{
    std::vector<Char> temp(s.begin(), s.end());

    return this->GetBytes(temp, 0, temp.size());
}

std::vector<UByte> Encoding::GetBytes(const std::vector<Char>& chars
                                    , const UInt32&            index
                                    , const UInt32&            count) const
{
    std::vector<UByte> result;

    result.reserve(this->GetByteCount(chars, index, count));

    this->GetBytes(chars, index, count, result, 0);

    return result;
}

UInt32 Encoding::GetBytes(const Char*   chars
                        , const UInt32& charCount
                        , UByte*        bytes
                        , const UInt32& byteCount) const
{
    return this->GetEncoder().GetBytes(chars, charCount, bytes, byteCount, false);
}

UInt32 Encoding::GetBytes(const String&       s
                        , const UInt32&       charIndex
                        , const UInt32&       charCount
                        , std::vector<UByte>& bytes
                        , const UInt32&       byteIndex) const
{
    return this->GetBytes(s, charIndex, charCount, bytes, byteIndex);
}

UInt32 Encoding::GetCharCount(const std::vector<UByte>& bytes) const
{
    return this->GetCharCount(bytes, 0, bytes.size());
}

UInt32 Encoding::GetCharCount(const UByte* bytes, const UInt32& count) const
{
    std::vector<UByte> temp(bytes, bytes + count);

    return this->GetCharCount(temp, 0, count);
}

std::vector<Char> Encoding::GetChars(const std::vector<UByte>& bytes) const
{
    return this->GetChars(bytes, 0, bytes.size());
}

std::vector<Char> Encoding::GetChars(const std::vector<UByte>& bytes
                                   , const UInt32&             index
                                   , const UInt32&             count) const
{
    std::vector<Char> result;

    result.reserve(this->GetCharCount(bytes, index, count));

    this->GetChars(bytes, index, count, result, 0);

    return result;
}

UInt32 Encoding::GetChars(const UByte*  bytes
                        , const UInt32& byteCount
                        , Char*         chars
                        , const UInt32& charCount) const
{
    return this->GetDecoder().GetChars(bytes, byteCount, chars, charCount, false);
}

String Encoding::GetString(const std::vector<UByte>& bytes) const
{
    return this->GetString(bytes, 0, bytes.size());
}

String Encoding::GetString(const std::vector<UByte>& bytes
                         , const UInt32&             index
                         , const UInt32&             count) const
{
    std::vector<Char> chars = this->GetChars(bytes, index, count);
    String result(chars.begin(), chars.end());

    return result;
}
