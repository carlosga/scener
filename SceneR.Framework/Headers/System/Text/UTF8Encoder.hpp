// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for full license information.

#ifndef UTF8ENCODER_HPP
#define UTF8ENCODER_HPP

#include <codecvt>

#include <System/Text/Encoder.hpp>

namespace System
{
    namespace Text
    {
        class UTF8Encoder : public Encoder
        {
        public:
            UTF8Encoder();

            virtual ~UTF8Encoder();

        public:
            virtual System::Size GetByteCount(const std::vector<System::Char>& chars
                                            , const System::Size&              index
                                            , const System::Size&              count
                                            , const System::Boolean&           flush) const override;

            virtual System::Size GetBytes(const std::vector<System::Char>& chars
                                        , const System::Size&              charIndex
                                        , const System::Size&              charCount
                                        , std::vector<System::UByte>&      bytes
                                        , const System::Size&              byteIndex
                                        , const System::Boolean&           flush) const override;

        private:
            std::codecvt_utf8<char16_t> converter;
        };
    }
}

#endif // UTF8ENCODER_HPP
