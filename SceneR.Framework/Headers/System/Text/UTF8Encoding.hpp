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
        class UTF8Encoding final : public Encoding
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
            std::u16string EncodingName() const override;

            bool IsSingleByte() const override;

            std::size_t GetByteCount(const std::vector<char16_t>& chars
                                   , const std::size_t&           index
                                   , const std::size_t&           count) const override;

            std::size_t GetBytes(const std::vector<char16_t>& chars
                               , const std::size_t&           charIndex
                               , const std::size_t&           charCount
                               , std::vector<std::uint8_t>&   bytes
                               , const std::size_t&           byteIndex) const override;

            std::size_t GetCharCount(const std::vector<std::uint8_t>& bytes
                                   , const std::size_t&               index
                                   , const std::size_t&               count) const override;

            std::size_t GetChars(const std::vector<std::uint8_t>& bytes
                               , const std::size_t&               byteIndex
                               , const std::size_t&               byteCount
                               , std::vector<char16_t>&           chars
                               , const std::size_t&               charIndex) const override;

            std::size_t GetMaxByteCount(const std::size_t& charCount) override;

            std::size_t GetMaxCharCount(const std::size_t& byteCount) override;

            std::vector<std::uint8_t> GetPreamble() const override;

            const Decoder& GetDecoder() const override;

            const Encoder& GetEncoder() const override;

        private:
            UTF8Encoder encoder;
            UTF8Decoder decoder;
        };
    }
}

#endif // UTF8ENCODING_HPP
