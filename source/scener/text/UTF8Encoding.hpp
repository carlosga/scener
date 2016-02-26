// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_TEXT_UTF8ENCODING_HPP
#define SCENER_TEXT_UTF8ENCODING_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

#include "scener/text/Encoding.hpp"
#include "scener/text/UTF8Decoder.hpp"
#include "scener/text/UTF8Encoder.hpp"

namespace scener { namespace text {

/// Represents a UTF-8 encoding of Unicode characters.
class UTF8Encoding final : public virtual Encoding
{
public:
    /// Initializes a new instance of the UTF8Encoding class.
    UTF8Encoding() = default;

    /// Releases all resources being used by this Encoding.
    ~UTF8Encoding() override = default;

public:
    std::u16string encoding_name() const override;

    bool is_single_byte() const override;

    using Encoding::get_byte_count;
    using Encoding::get_bytes;
    using Encoding::get_char_count;
    using Encoding::get_chars;
    using Encoding::get_string;

    std::size_t get_byte_count(const std::vector<char16_t>& chars, std::size_t index, std::size_t count) const override;

    std::size_t get_bytes(const std::vector<char16_t>& chars
                        , std::size_t                  charIndex
                        , std::size_t                  charCount
                        , std::vector<std::uint8_t>&   bytes
                        , std::size_t                  byteIndex) const override;

    std::size_t get_char_count(const std::vector<std::uint8_t>& bytes, std::size_t index, std::size_t count) const override;

    std::size_t get_chars(const std::vector<std::uint8_t>& bytes
                        , std::size_t                      byteIndex
                        , std::size_t                      byteCount
                        , std::vector<char16_t>&           chars
                        , std::size_t                      charIndex) const override;

    std::size_t get_max_byte_count(std::size_t charCount) override;

    std::size_t get_max_char_count(std::size_t byteCount) override;

    std::vector<std::uint8_t> get_preamble() const override;

    const Decoder& get_decoder() const override;

    const Encoder& get_encoder() const override;

private:
    UTF8Encoder _encoder;
    UTF8Decoder _decoder;
};

}}

#endif // SCENER_SYSTEM_TEXT_UTF8ENCODING_HPP
