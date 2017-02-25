// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/text/encoder.hpp"

#include <algorithm>
#include <stdexcept>

namespace scener::text
{
    encoder::encoder()
    {
    }

    encoder::~encoder()
    {
    }

    std::size_t encoder::get_byte_count(const char16_t* chars, std::size_t count, bool flush) const
    {
        auto vchars = std::vector<char16_t>(chars, chars + count);

        return get_byte_count(vchars, 0, count, flush);
    }

    std::size_t encoder::get_bytes(const char16_t* chars
                                 , std::size_t     char_count
                                 , std::uint8_t*   bytes
                                 , std::size_t     byte_count
                                 , bool            flush) const
    {
        if (chars == nullptr)
        {
            throw std::runtime_error("chars is null");
        }
        if (bytes == nullptr)
        {
            throw std::runtime_error("bytes is null");
        }

        auto vchars = std::vector<char16_t>(chars, chars + char_count);
        auto bcount = get_byte_count(vchars, 0, char_count, flush);

        if (bcount > byte_count)
        {
            throw std::runtime_error("byteCount is less than the resulting number of bytes.");
        }

        auto vbytes = std::vector<std::uint8_t>(bcount, 0);
        auto count  = get_bytes(vchars, 0, char_count, vbytes, 0, flush);
        auto result = ((count > byte_count) ? byte_count : count);

        std::copy_n(vbytes.begin(), result, bytes);

        return result;
    }

    void encoder::reset()
    {
    }
}
