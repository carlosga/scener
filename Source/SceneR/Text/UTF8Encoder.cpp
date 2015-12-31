// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Text/UTF8Encoder.hpp"

#include <string>
#include <locale>
#include <stdexcept>
// #include <iomanip>

namespace SceneR { namespace Text {

std::size_t UTF8Encoder::get_byte_count(const std::vector<char16_t>& chars
                                      , const std::size_t&           index
                                      , const std::size_t&           count
                                      , const bool&                  flush) const
{
    if (index > chars.size() || count > chars.size() || (index + count) > chars.size())
    {
        throw std::invalid_argument("index and count do not denote a valid range in chars.");
    }

    std::size_t byteCount = 0;

    /**
     * Unicode code points
     * 00-7F           ( 7 bits)
     * 0080-07FF       (11 bits)
     * 0800-FFFF       (16 bits)
     * 010000-10FFFF   (21 bits)
     */
    for (std::size_t i = index; i < (index + count); i++)
    {
        std::uint32_t buffer = static_cast<std::uint32_t>(chars[i]);
        std::size_t   offset = 1;

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

std::size_t UTF8Encoder::get_bytes(const std::vector<char16_t>& chars
                                 , const std::size_t&           charIndex
                                 , const std::size_t&           charCount
                                 , std::vector<std::uint8_t>&   bytes
                                 , const std::size_t&           byteIndex
                                 , const bool&                  flush) const
{
    if (charIndex > chars.size() || charCount > chars.size() || (charIndex + charCount) > chars.size())
    {
        throw std::invalid_argument("charIndex and charCount do not denote a valid range in chars.");
    }
    if (byteIndex > bytes.size())
    {
        throw std::invalid_argument("byteIndex do not denote a valid offset in bytes.");
    }

    const char16_t* from     = chars.data() + charIndex;
    const char16_t* fromEnd  = from + charCount;
    const char16_t* fromNext = nullptr;
    auto            size     = charCount * _converter.max_length();
    auto            to       = std::vector<char>(size, 0);
    char*           toStart  = to.data();
    char*           toEnd    = toStart + size;
    char*           toNext   = nullptr;
    auto            state    = std::mbstate_t();
    auto            r        = _converter.out(state, from, fromEnd, fromNext, toStart, toEnd, toNext);

    if (r == std::codecvt_base::error)
    {
        throw std::runtime_error("encoder error");
    }
    else if (r == std::codecvt_base::partial)
    {
    }
    else if (r == std::codecvt_base::ok)
    {
        auto count = static_cast<std::size_t>(toNext - toStart);

        if ((byteIndex + count) > bytes.size())
        {
            throw std::invalid_argument("bytes does not have enough capacity from byteIndex to the end of the array to accommodate the resulting bytes.");
        }

        std::copy_n(to.begin(), count, bytes.begin() + byteIndex);
    }

    return static_cast<std::size_t>(toNext - toStart);
}

}}
