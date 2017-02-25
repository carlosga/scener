// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/text/decoder.hpp"

#include <algorithm>

namespace scener::text
{
    decoder::decoder()
    {
    }

    decoder::~decoder()
    {
    }

    std::size_t decoder::get_char_count(const std::uint8_t* bytes, std::size_t count, bool flush) const
    {
        auto vbytes = std::vector<std::uint8_t>(bytes, bytes + count);

        return get_char_count(vbytes, 0, count, flush);
    }

    std::size_t decoder::get_char_count(const std::vector<std::uint8_t>& bytes
                                      , std::size_t                      index
                                      , std::size_t                      count
                                      , bool                             flush) const
     {
        return this->get_char_count(bytes, index, count);
    }

    std::size_t decoder::get_chars(const std::uint8_t* bytes
                                 , std::size_t         byte_count
                                 , char16_t*           chars
                                 , std::size_t         char_count
                                 , bool                flush) const
    {
        auto vbytes = std::vector<std::uint8_t>(bytes, bytes + byte_count);
        auto vchars = std::vector<char16_t>();

        vchars.reserve(get_char_count(vbytes, 0, byte_count, flush));

        auto count  = get_chars(vbytes, 0, byte_count, vchars, 0, flush);
        auto result = ((count > char_count) ? char_count : count);

        std::copy_n(vchars.begin(), result, chars);

        return result;
    }

    std::size_t decoder::get_chars(const std::vector<std::uint8_t>& bytes
                                 , std::size_t                      byte_index
                                 , std::size_t                      byte_count
                                 , std::vector<char16_t>&           chars
                                 , std::size_t                      char_index
                                 , bool                             flush) const
    {
        return get_chars(bytes, byte_index, byte_count, chars, char_index);
    }
}
