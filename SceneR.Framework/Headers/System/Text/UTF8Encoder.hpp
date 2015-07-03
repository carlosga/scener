// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef UTF8ENCODER_HPP
#define UTF8ENCODER_HPP

#include <codecvt>

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
            System::Size GetByteCount(const std::vector<char16_t>& chars
                                    , const System::Size&          index
                                    , const System::Size&          count
                                    , const bool&                  flush) const override;

            System::Size GetBytes(const std::vector<char16_t>& chars
                                , const System::Size&          charIndex
                                , const System::Size&          charCount
                                , std::vector<System::UByte>&  bytes
                                , const System::Size&          byteIndex
                                , const bool&                  flush) const override;

        private:
            std::codecvt_utf8<char16_t> converter;
        };
    }
}

#endif // UTF8ENCODER_HPP
