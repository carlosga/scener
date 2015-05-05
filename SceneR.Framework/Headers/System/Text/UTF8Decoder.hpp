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
            System::Size GetCharCount(const std::vector<System::UByte>& bytes
                                    , const System::Size&               index
                                    , const System::Size&               count) const override;

            System::Size GetChars(const std::vector<System::UByte>& bytes
                                , const System::Size&               byteIndex
                                , const System::Size&               byteCount
                                , std::vector<System::Char>&        chars
                                , const System::Size&               charIndex) const override;

            void Reset() override;

        private:
            std::codecvt_utf8<char16_t> converter;
        };
    }
}

#endif // UTF8DECODER_HPP
