// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for full license information.

#ifndef UTF8DECODER_HPP
#define UTF8DECODER_HPP

#include <codecvt>

#include <System/Text/Decoder.hpp>

namespace System
{
    namespace Text
    {
        class UTF8Decoder : public Decoder
        {
        public:
            UTF8Decoder();

            virtual ~UTF8Decoder();

        public:
            virtual System::Size GetCharCount(const std::vector<System::UByte>& bytes
                                            , const System::Size&               index
                                            , const System::Size&               count) const override;

            virtual System::Size GetChars(const std::vector<System::UByte>& bytes
                                        , const System::Size&               byteIndex
                                        , const System::Size&               byteCount
                                        , std::vector<System::Char>&        chars
                                        , const System::Size&               charIndex) const override;

            virtual void Reset();

        private:
            std::codecvt_utf8<char16_t> converter;
        };
    }
}

#endif // UTF8DECODER_HPP
