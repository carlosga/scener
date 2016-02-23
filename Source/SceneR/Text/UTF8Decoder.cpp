// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Text/UTF8Decoder.hpp"

#include <stdexcept>

namespace SceneR { namespace Text {

std::size_t UTF8Decoder::get_char_count(const std::vector<std::uint8_t>& bytes
                                      , std::size_t                      index
                                      , std::size_t                      count) const
{
    if (index > bytes.size() || count > bytes.size() || (index + count) > bytes.size())
    {
        throw std::invalid_argument("index and count do not denote a valid range in bytes.");
    }

    std::size_t result = 0;

    for (std::size_t i = index; i < (index + count);)
    {
        std::uint32_t buffer    = bytes[i];
        std::size_t   byteCount = 1;

        // http://xbox.create.msdn.com/en-US/sample/xnb_format
        // Decode UTF-8.
        if (buffer & 0x80)
        {
            while (buffer & (0x80 >> byteCount))
            {
                byteCount++;
            }
        }

        i += byteCount;
        result++;
    }

    return result;
}

std::size_t UTF8Decoder::get_chars(const std::vector<std::uint8_t>& bytes
                                 , std::size_t                      byteIndex
                                 , std::size_t                      byteCount
                                 , std::vector<char16_t>&           chars
                                 , std::size_t                      charIndex) const
{
    if (byteIndex > bytes.size() || byteCount > bytes.size() || (byteIndex + byteCount) > bytes.size())
    {
        throw std::invalid_argument("byteIndex and byteCount do not denote a valid range in bytes.");
    }
    if (charIndex > chars.size())
    {
        throw std::invalid_argument("charIndex do not denote a valid offset in chars.");
    }

    auto        from     = reinterpret_cast<const char*>(bytes.data()) + byteIndex;
    auto        fromEnd  = from + byteCount;
    const char* fromNext = nullptr;
    auto        to       = std::vector<char16_t>(byteCount);
    char16_t*   toStart  = to.data();
    char16_t*   toEnd    = toStart + byteCount;
    char16_t*   toNext   = nullptr;
    auto        state    = std::mbstate_t();
    auto        status   = _converter.in(state, from, fromEnd, fromNext, toStart, toEnd, toNext);

    if (status == std::codecvt_base::error)
    {
        throw std::runtime_error("decoder error");
    }
    else if (status == std::codecvt_base::partial)
    {
    }
    else if (status == std::codecvt_base::ok)
    {
        auto count = static_cast<std::size_t>(toNext - toStart);

        if ((charIndex + count) > chars.size())
        {
            throw std::invalid_argument("chars does not have enough capacity from charIndex to the end of the array to accommodate the resulting chars.");
        }

        std::copy_n(to.begin(), count, chars.begin() + charIndex);
    }

    return static_cast<std::size_t>(toNext - toStart);
}

void UTF8Decoder::reset()
{
}

}}
