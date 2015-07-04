// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <System/Text/UTF8Encoder.hpp>

#include <codecvt>

using namespace System;
using namespace System::Text;

UTF8Encoder::UTF8Encoder()
{
}

UTF8Encoder::~UTF8Encoder()
{
}

size_t UTF8Encoder::GetByteCount(const std::vector<char16_t>& chars
                               , const size_t&                index
                               , const size_t&                count
                               , const bool&                  flush) const
{
    size_t byteCount = 0;

    /**
     * Unicode code points
     * 00-7F           ( 7 bits)
     * 0080-07FF       (11 bits)
     * 0800-FFFF       (16 bits)
     * 010000-10FFFF   (21 bits)
     */
    for (size_t i = index; i < (index + count); i++)
    {
        char16_t buffer = chars[i];
        size_t   offset = 1;

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

size_t UTF8Encoder::GetBytes(const std::vector<char16_t>& chars
                           , const size_t&                charIndex
                           , const size_t&                charCount
                           , std::vector<uint8_t>&        bytes
                           , const size_t&                byteIndex
                           , const bool&                  flush) const
{
    auto            from     = const_cast<char16_t*>(&chars[0] + charIndex);
    auto            fromEnd  = from + charCount;
    const char16_t* fromNext = nullptr;
    auto            size     = charCount * this->converter.max_length();
    auto            to       = std::vector<char>(size);
    auto            toStart  = &to[0];
    auto            toEnd    = toStart + size;
    char*           toNext   = nullptr;
    auto            iterator = bytes.begin() + byteIndex;
    auto            state    = std::mbstate_t();
    auto            r        = this->converter.out(state, from, fromEnd, fromNext, toStart, toEnd, toNext);

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
            bytes.emplace(iterator++, static_cast<uint8_t>(*position));
        }
    }

    return static_cast<size_t>(toNext - toStart);
}
