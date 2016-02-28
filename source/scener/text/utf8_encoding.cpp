// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/text/utf8_encoding.hpp"

namespace scener { namespace text {

std::u16string utf8_encoding::encoding_name() const
{
    return u"Unicode (UTF-8)";
}

bool utf8_encoding::is_single_byte() const
{
    return false;
}

std::size_t utf8_encoding::get_byte_count(const std::vector<char16_t>& chars, std::size_t index, std::size_t count) const
{
    return _encoder.get_byte_count(chars, index, count, false);
}

std::size_t utf8_encoding::get_bytes(const std::vector<char16_t>& chars
                                   , std::size_t                  char_index
                                   , std::size_t                  char_count
                                   , std::vector<std::uint8_t>&   bytes
                                   , std::size_t                  byte_index) const
{
    return _encoder.get_bytes(chars, char_index, char_count, bytes, byte_index, false);
}

std::size_t utf8_encoding::get_char_count(const std::vector<std::uint8_t>& bytes
                                       , std::size_t                      index
                                       , std::size_t                      count) const
{
    return _decoder.get_char_count(bytes, index, count);
}

std::size_t utf8_encoding::get_chars(const std::vector<std::uint8_t>& bytes
                                   , std::size_t                      byte_index
                                   , std::size_t                      byte_count
                                   , std::vector<char16_t>&           chars
                                   , std::size_t                      char_index) const
{
    return _decoder.get_chars(bytes, byte_index, byte_count, chars, char_index);
}

std::size_t utf8_encoding::get_max_byte_count(std::size_t charCount)
{
    return (charCount * 4);
}

std::size_t utf8_encoding::get_max_char_count(std::size_t byteCount)
{
    return byteCount; // Every character could be 1 byte lenght
}

std::vector<std::uint8_t> utf8_encoding::get_preamble() const
{
    return { 0xef, 0xbb, 0xbf };
}

const decoder& utf8_encoding::get_decoder() const
{
    return _decoder;
}

const encoder& utf8_encoding::get_encoder() const
{
    return _encoder;
}

}}
