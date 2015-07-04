// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef UTF8ENCODER_HPP
#define UTF8ENCODER_HPP

#include <codecvt>
#include <stddef.h>
#include <stdint.h>

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
            size_t GetByteCount(const std::vector<char16_t>& chars
                              , const size_t&                index
                              , const size_t&                count
                              , const bool&                  flush) const override;

            size_t GetBytes(const std::vector<char16_t>& chars
                                , const size_t&          charIndex
                                , const size_t&          charCount
                                , std::vector<uint8_t>&  bytes
                                , const size_t&          byteIndex
                                , const bool&            flush) const override;

        private:
            std::codecvt_utf8<char16_t> converter;
        };
    }
}

#endif // UTF8ENCODER_HPP
