// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_TEXT_UTF8_ENCODING_HPP
#define SCENER_TEXT_UTF8_ENCODING_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

#include "scener/text/encoding.hpp"
#include "scener/text/utf8_decoder.hpp"
#include "scener/text/utf8_encoder.hpp"

namespace scener::text
{
    /// Represents a UTF-8 encoding of Unicode characters.
    class utf8_encoding final : public virtual encoding
    {
    public:
        /// Initializes a new instance of the UTF8Encoding class.
        utf8_encoding() = default;

        /// Releases all resources being used by this Encoding.
        ~utf8_encoding() override = default;

    public:
        std::u16string encoding_name() const override;

        bool is_single_byte() const override;

        using encoding::get_byte_count;
        using encoding::get_bytes;
        using encoding::get_char_count;
        using encoding::get_chars;
        using encoding::get_string;

        std::size_t get_byte_count(const std::vector<char16_t>& chars, std::size_t index, std::size_t count) const override;

        std::size_t get_bytes(const std::vector<char16_t>& chars
                            , std::size_t                  char_index
                            , std::size_t                  char_count
                            , std::vector<std::uint8_t>&   bytes
                            , std::size_t                  byte_index) const override;

        std::size_t get_char_count(const std::vector<std::uint8_t>& bytes, std::size_t index, std::size_t count) const override;

        std::size_t get_chars(const std::vector<std::uint8_t>& bytes
                            , std::size_t                      byte_index
                            , std::size_t                      byte_count
                            , std::vector<char16_t>&           chars
                            , std::size_t                      char_index) const override;

        std::size_t get_max_byte_count(std::size_t char_count) override;

        std::size_t get_max_char_count(std::size_t byte_count) override;

        std::vector<std::uint8_t> get_preamble() const override;

        const decoder& get_decoder() const override;

        const encoder& get_encoder() const override;

    private:
        utf8_encoder _encoder;
        urf8_decoder _decoder;
    };
}

#endif // SCENER_TEXT_UTF8_ENCODING_HPP
