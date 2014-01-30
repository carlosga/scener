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

#include <codecvt>
#include <System/Text/UTF8Encoder.hpp>

using namespace System;
using namespace System::Text;

UTF8Encoder::UTF8Encoder()
{
}

UTF8Encoder::~UTF8Encoder()
{
}

UInt32 UTF8Encoder::GetByteCount(const std::vector<Char>& chars
                               , const UInt32&            index
                               , const UInt32&            count
                               , const Boolean&           flush) const
{
    int32_t byteCount = 0;

    /**
     * Unicode code points
     * 00-7F           ( 7 bits)
     * 0080-07FF       (11 bits)
     * 0800-FFFF       (16 bits)
     * 010000-10FFFF   (21 bits)
     */
    for (UInt32 i = index; i < (index + count); i++)
    {
        Char   buffer = chars[i];
        UInt32 offset = 1;

        if (((buffer >> 7) & 0xff) & 0x7F)
        {
            if (((buffer >> 11) & 0xff) & 0x7FF)
            {
                if (((buffer >> 21) & 0xff) & 0x10FFFF)
                {
                    offset = 4;
                }
                else
                {
                    offset = 3;
                }
            }
            else
            {
                offset = 2;
            }
        }

        byteCount += offset;
    }

    return byteCount;
}

UInt32 UTF8Encoder::GetBytes(const std::vector<Char>& chars
                           , const UInt32&            charIndex
                           , const UInt32&            charCount
                           , std::vector<UByte>&      bytes
                           , const UInt32&            byteIndex
                           , const Boolean&           flush) const
{
    Char*          from     = const_cast<Char*>(&chars[0] + charIndex);
    Char*          fromEnd  = from + charCount;
    const Char*    fromNext = nullptr;
    auto           size     = charCount * this->converter.max_length();
    auto           to       = std::vector<char>(size);
    auto           toStart  = &to[0];
    auto           toEnd    = toStart + size;
    char*          toNext   = nullptr;
    auto           iterator = bytes.begin() + byteIndex;
    std::mbstate_t state    = std::mbstate_t();

    std::codecvt_base::result r = this->converter.out(state, from, fromEnd, fromNext, toStart, toEnd, toNext);

    if (r == std::codecvt_base::error)
    {
        throw std::runtime_error("encoder error");
    }
    else if (r == std::codecvt_base::partial)
    {
    }
    else if (r == std::codecvt_base::ok)
    {
        for (auto position = toStart; position < toNext; position++)
        {
            bytes.emplace(iterator++, static_cast<UByte>(*position));
        }
    }

    return static_cast<UInt32>(toNext - toStart);
}
