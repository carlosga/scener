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
                                   , const Size&               index
                                   , const Size&               count)
{
    auto srcChars = srcEncoding.GetChars(bytes, index, count);

    return dstEncoding.GetBytes(srcChars, 0, srcChars.size());
}

std::string Encoding::Convert(const String& source)
{
    std::wstring_convert<std::codecvt_utf8_utf16<Char>, Char> converter; // UTF-8 <-> UTF-16 converter

    return converter.to_bytes(source);
};

System::String Encoding::Convert(const std::string& source)
{
    std::wstring_convert<std::codecvt_utf8_utf16<Char>, Char> converter; // UTF-8 <-> UTF-16 converter

    return converter.from_bytes(source);
};

bool Encoding::IsReadOnly() const
{
    return true;
}

Size Encoding::GetByteCount(const std::vector<Char>& chars) const
{
    return this->GetByteCount(chars, 0, chars.size());
}

Size Encoding::GetByteCount(const String& s) const
{
    auto temp = std::vector<Char>(s.begin(), s.end());

    return this->GetByteCount(temp, 0, temp.size());
}

Size Encoding::GetByteCount(const Char* chars, const Size& count) const
{
    auto temp = std::vector<Char>(chars, chars + count);

    return this->GetByteCount(temp, 0, count);
}

std::vector<UByte> Encoding::GetBytes(const std::vector<Char>& chars) const
{
    return this->GetBytes(chars, 0, chars.size());
}

std::vector<UByte> Encoding::GetBytes(const String& s) const
{
    auto temp = std::vector<Char>(s.begin(), s.end());

    return this->GetBytes(temp, 0, temp.size());
}

std::vector<UByte> Encoding::GetBytes(const std::vector<Char>& chars
                                    , const Size&              index
                                    , const Size&              count) const
{
    auto result = std::vector<UByte>();

    result.reserve(this->GetByteCount(chars, index, count));

    this->GetBytes(chars, index, count, result, 0);

    return result;
}

Size Encoding::GetBytes(const Char* chars
                      , const Size& charCount
                      , UByte*      bytes
                      , const Size& byteCount) const
{
    return this->GetEncoder().GetBytes(chars, charCount, bytes, byteCount, false);
}

Size Encoding::GetBytes(const String&       s
                      , const Size&         charIndex
                      , const Size&         charCount
                      , std::vector<UByte>& bytes
                      , const Size&         byteIndex) const
{
    return this->GetBytes(s, charIndex, charCount, bytes, byteIndex);
}

Size Encoding::GetCharCount(const std::vector<UByte>& bytes) const
{
    return this->GetCharCount(bytes, 0, bytes.size());
}

Size Encoding::GetCharCount(const UByte* bytes, const Size& count) const
{
    auto temp = std::vector<UByte>(bytes, bytes + count);

    return this->GetCharCount(temp, 0, count);
}

std::vector<Char> Encoding::GetChars(const std::vector<UByte>& bytes) const
{
    return this->GetChars(bytes, 0, bytes.size());
}

std::vector<Char> Encoding::GetChars(const std::vector<UByte>& bytes
                                   , const Size&               index
                                   , const Size&               count) const
{
    auto result = std::vector<Char>();

    result.reserve(this->GetCharCount(bytes, index, count));

    this->GetChars(bytes, index, count, result, 0);

    return result;
}

Size Encoding::GetChars(const UByte* bytes
                      , const Size&  byteCount
                      , Char*        chars
                      , const Size&  charCount) const
{
    return this->GetDecoder().GetChars(bytes, byteCount, chars, charCount, false);
}

String Encoding::GetString(const std::vector<UByte>& bytes) const
{
    return this->GetString(bytes, 0, bytes.size());
}

String Encoding::GetString(const std::vector<UByte>& bytes
                         , const Size&               index
                         , const Size&               count) const
{
    auto chars = this->GetChars(bytes, index, count);

    return String(chars.begin(), chars.end());
}
