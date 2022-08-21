// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/text/utf8_encoder.hpp"

#include <algorithm>
#include <locale>
#include <string>
#include <stdexcept>

namespace scener::text
{
    std::size_t utf8_encoder::get_byte_count(const std::vector<char16_t>& chars
                                           , std::size_t                  index
                                           , std::size_t                  count
                                           , bool                         flush) const
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

            if ((((buffer >> 7) & 0xff) & 0x7F) == 0x7F)
            {
                if ((((buffer >> 11) & 0xff) & 0x7FF) == 0x7FF)
                {
                    if ((((buffer >> 21) & 0xff) & 0x10FFFF) == 0x10FFFF)
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

    std::size_t utf8_encoder::get_bytes(const std::vector<char16_t>& chars
                                      , std::size_t                  char_index
                                      , std::size_t                  char_count
                                      , std::vector<std::uint8_t>&   bytes
                                      , std::size_t                  byte_index
                                      , bool                         flush) const
    {
        if (char_index > chars.size() || char_count > chars.size() || (char_index + char_count) > chars.size())
        {
            throw std::invalid_argument("charIndex and charCount do not denote a valid range in chars.");
        }
        if (byte_index > bytes.size())
        {
            throw std::invalid_argument("byteIndex do not denote a valid offset in bytes.");
        }

        const char16_t* from      = chars.data() + char_index;
        const char16_t* from_end  = from + char_count;
        const char16_t* from_next = nullptr;
        auto            size      = char_count * _facet->max_length();
        auto            to        = std::vector<char>(size, 0);
        char*           to_start  = to.data();
        char*           to_end    = to_start + size;
        char*           to_next   = nullptr;
        auto            state     = std::mbstate_t();
        auto            r         = _facet->out(state, from, from_end, from_next, to_start, to_end, to_next);

        if (r == std::codecvt_base::error)
        {
            throw std::runtime_error("encoder error");
        }
        else if (r == std::codecvt_base::partial)
        {
        }
        else if (r == std::codecvt_base::ok)
        {
            auto count = static_cast<std::size_t>(to_next - to_start);

            if ((byte_index + count) > bytes.size())
            {
                throw std::invalid_argument("bytes does not have enough capacity from byteIndex to the end of the array to accommodate the resulting bytes.");
            }

            std::copy_n(to.begin(), count, bytes.begin() + byte_index);
        }

        return static_cast<std::size_t>(to_next - to_start);
    }
}
