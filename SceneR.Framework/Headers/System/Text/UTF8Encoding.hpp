// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef UTF8ENCODING_HPP
#define UTF8ENCODING_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

#include <System/Text/UTF8Decoder.hpp>
#include <System/Text/UTF8Encoder.hpp>
#include <System/Text/Encoding.hpp>

namespace System
{
    namespace Text
    {
        /**
         * Represents a UTF-8 encoding of Unicode characters.
         */
        class UTF8Encoding final : public virtual Encoding
        {
        public:
            /**
             * Initializes a new instance of the UTF8Encoding class.
             */
            UTF8Encoding();

            /**
             * Releases all resources being used by this Encoding.
             */
            ~UTF8Encoding() override;

        public:
            std::u16string encoding_name() const override;

            bool is_single_byte() const override;

            using Encoding::get_byte_count;
            using Encoding::get_bytes;
            using Encoding::get_char_count;
            using Encoding::get_chars;
            using Encoding::get_string;

            std::size_t get_byte_count(const std::vector<char16_t>& chars
                                     , const std::size_t&           index
                                     , const std::size_t&           count) const override;

            std::size_t get_bytes(const std::vector<char16_t>& chars
                                , const std::size_t&           charIndex
                                , const std::size_t&           charCount
                                , std::vector<std::uint8_t>&   bytes
                                , const std::size_t&           byteIndex) const override;

            std::size_t get_char_count(const std::vector<std::uint8_t>& bytes
                                    , const std::size_t&               index
                                    , const std::size_t&               count) const override;

            std::size_t get_chars(const std::vector<std::uint8_t>& bytes
                                , const std::size_t&               byteIndex
                                , const std::size_t&               byteCount
                                , std::vector<char16_t>&           chars
                                , const std::size_t&               charIndex) const override;

            std::size_t get_max_byte_count(const std::size_t& charCount) override;

            std::size_t get_max_char_count(const std::size_t& byteCount) override;

            std::vector<std::uint8_t> get_preamble() const override;

            const Decoder& get_decoder() const override;

            const Encoder& get_encoder() const override;

        private:
            UTF8Encoder _encoder;
            UTF8Decoder _decoder;
        };
    }
}

#endif // UTF8ENCODING_HPP
