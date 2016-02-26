// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/text/Decoder.hpp"

namespace scener { namespace text {

Decoder::Decoder()
{
}

Decoder::~Decoder()
{
}

std::size_t Decoder::get_char_count(const std::uint8_t* bytes, std::size_t count, bool flush) const
{
    auto vbytes = std::vector<std::uint8_t>(bytes, bytes + count);

    return this->get_char_count(vbytes, 0, count, flush);
}

std::size_t Decoder::get_char_count(const std::vector<std::uint8_t>& bytes
                                  , std::size_t                      index
                                  , std::size_t                      count
                                  , bool                             flush) const
{
    return this->get_char_count(bytes, index, count);
}

std::size_t Decoder::get_chars(const std::uint8_t* bytes
                             , std::size_t         byteCount
                             , char16_t*           chars
                             , std::size_t         charCount
                             , bool                flush) const
{
    auto vbytes = std::vector<std::uint8_t>(bytes, bytes + byteCount);
    auto vchars = std::vector<char16_t>();

    vchars.reserve(this->get_char_count(vbytes, 0, byteCount, flush));

    auto totalChars = this->get_chars(vbytes, 0, byteCount, vchars, 0, flush);
    auto result     = ((totalChars > charCount) ? charCount : totalChars);

    std::copy_n(vchars.begin(), result, chars);

    return result;
}

std::size_t Decoder::get_chars(const std::vector<std::uint8_t>& bytes
                             , std::size_t                      byteIndex
                             , std::size_t                      byteCount
                             , std::vector<char16_t>&           chars
                             , std::size_t                      charIndex
                             , bool                             flush) const
{
    return this->get_chars(bytes, byteIndex, byteCount, chars, charIndex);
}

}}
