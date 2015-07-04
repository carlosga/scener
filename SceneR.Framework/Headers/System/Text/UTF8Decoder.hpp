// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef UTF8DECODER_HPP
#define UTF8DECODER_HPP

#include <codecvt>

#include <System/Text/Decoder.hpp>

namespace System
{
    namespace Text
    {
        /**
         * Converts a sequence of encoded bytes into a set of UTF-8 encoded characters.
         */
        class UTF8Decoder final : public Decoder
        {
        public:
            /**
             * Initializes a new instance of the UTF8Decoder class.
             */
            UTF8Decoder();

            /**
             * Releases all resources being used by this UTF8Decoder.
             */
            ~UTF8Decoder() override;

        public:
            size_t GetCharCount(const std::vector<uint8_t>& bytes
                              , const size_t&               index
                              , const size_t&               count) const override;

            size_t GetChars(const std::vector<uint8_t>&  bytes
                                , const size_t&          byteIndex
                                , const size_t&          byteCount
                                , std::vector<char16_t>& chars
                                , const size_t&          charIndex) const override;

            void Reset() override;

        private:
            std::codecvt_utf8<char16_t> converter;
        };
    }
}

#endif // UTF8DECODER_HPP
