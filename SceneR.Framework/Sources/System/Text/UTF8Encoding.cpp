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

Size UTF8Encoding::GetByteCount(const std::vector<Char>& chars
                              , const Size&              index
                              , const Size&              count) const
{
    return this->encoder.GetByteCount(chars, index, count, false);
}

Size UTF8Encoding::GetBytes(const std::vector<Char>& chars
                          , const Size&              charIndex
                          , const Size&              charCount
                          , std::vector<UByte>&      bytes
                          , const Size&              byteIndex) const
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
                          , std::vector<Char>&        chars
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