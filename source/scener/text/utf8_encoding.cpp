// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/text/UTF8Encoding.hpp"

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
                                  , std::size_t                  charIndex
                                  , std::size_t                  charCount
                                  , std::vector<std::uint8_t>&   bytes
                                  , std::size_t                  byteIndex) const
{
    return _encoder.get_bytes(chars, charIndex, charCount, bytes, byteIndex, false);
}

std::size_t utf8_encoding::get_char_count(const std::vector<std::uint8_t>& bytes
                                       , std::size_t                      index
                                       , std::size_t                      count) const
{
    return _decoder.get_char_count(bytes, index, count);
}

std::size_t utf8_encoding::get_chars(const std::vector<std::uint8_t>& bytes
                                  , std::size_t                      byteIndex
                                  , std::size_t                      byteCount
                                  , std::vector<char16_t>&           chars
                                  , std::size_t                      charIndex) const
{
    return _decoder.get_chars(bytes, byteIndex, byteCount, chars, charIndex);
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
