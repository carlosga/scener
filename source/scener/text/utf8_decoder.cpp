// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/text/utf8_decoder.hpp"

#include <algorithm>
#include <stdexcept>

namespace scener { namespace text {

std::size_t urf8_decoder::get_char_count(const std::vector<std::uint8_t>& bytes
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
        std::size_t   byte_count = 1;

        // http://xbox.create.msdn.com/en-US/sample/xnb_format
        // Decode UTF-8.
        if (buffer & 0x80)
        {
            while (buffer & (0x80 >> byte_count))
            {
                byte_count++;
            }
        }

        i += byte_count;
        result++;
    }

    return result;
}

std::size_t urf8_decoder::get_chars(const std::vector<std::uint8_t>& bytes
                                  , std::size_t                      byte_index
                                  , std::size_t                      byte_count
                                  , std::vector<char16_t>&           chars
                                  , std::size_t                      char_index) const
{
    if (byte_index > bytes.size() || byte_count > bytes.size() || (byte_index + byte_count) > bytes.size())
    {
        throw std::invalid_argument("byteIndex and byteCount do not denote a valid range in bytes.");
    }
    if (char_index > chars.size())
    {
        throw std::invalid_argument("charIndex do not denote a valid offset in chars.");
    }

    auto        from      = reinterpret_cast<const char*>(bytes.data()) + byte_index;
    auto        from_end  = from + byte_count;
    const char* from_next = nullptr;
    auto        to        = std::vector<char16_t>(byte_count);
    char16_t*   to_start  = to.data();
    char16_t*   to_end    = to_start + byte_count;
    char16_t*   to_next   = nullptr;
    auto        state     = std::mbstate_t();
    auto        status    = _facet->in(state, from, from_end, from_next, to_start, to_end, to_next);

    if (status == std::codecvt_base::error)
    {
        throw std::runtime_error("decoder error");
    }
    else if (status == std::codecvt_base::partial)
    {
    }
    else if (status == std::codecvt_base::ok)
    {
        auto count = static_cast<std::size_t>(to_next - to_start);

        if ((char_index + count) > chars.size())
        {
            throw std::invalid_argument("chars does not have enough capacity from charIndex to the end of the array to accommodate the resulting chars.");
        }

        std::copy_n(to.begin(), count, chars.begin() + char_index);
    }

    return static_cast<std::size_t>(to_next - to_start);
}

void urf8_decoder::reset()
{
}

}}
