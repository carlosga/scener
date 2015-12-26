// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SYSTEM_TEXT_UTF8ENCODER_HPP
#define SYSTEM_TEXT_UTF8ENCODER_HPP

#include <codecvt>
#include <cstddef>
#include <cstdint>

#include <System/Text/Encoder.hpp>

namespace System
{
    namespace Text
    {
        /**
         * Converts a set of UTF-8 encoded characters into a sequence of bytes.
         */
        class UTF8Encoder final : public Encoder
        {
        public:
            /**
             * Initializes a new instance of the UTF8Encoder class.
             */
             UTF8Encoder();

            /**
             * Releases all resources being used by this UTF8Encoder.
             */
            ~UTF8Encoder() override;

        public:
            std::size_t get_byte_count(const std::vector<char16_t>& chars
                                     , const std::size_t&           index
                                     , const std::size_t&           count
                                     , const bool&                  flush) const override;

            std::size_t get_bytes(const std::vector<char16_t>& chars
                                , const std::size_t&           charIndex
                                , const std::size_t&           charCount
                                , std::vector<std::uint8_t>&   bytes
                                , const std::size_t&           byteIndex
                                , const bool&                  flush) const override;

        private:
            std::codecvt_utf8_utf16<char16_t> _converter;
        };
    }
}

#endif  // SYSTEM_TEXT_UTF8ENCODER_HPP
