// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef UTF8ENCODING_HPP
#define UTF8ENCODING_HPP

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
            const System::String EncodingName() const override;

            bool IsSingleByte() const override;

            System::Size GetByteCount(const std::vector<System::Char>& chars
                                    , const System::Size&              index
                                    , const System::Size&              count) const override;

            System::Size GetBytes(const std::vector<System::Char>& chars
                                , const System::Size&              charIndex
                                , const System::Size&              charCount
                                , std::vector<System::UByte>&      bytes
                                , const System::Size&              byteIndex) const override;

            System::Size GetCharCount(const std::vector<System::UByte>& bytes
                                    , const System::Size&               index
                                    , const System::Size&               count) const override;

            System::Size GetChars(const std::vector<System::UByte>& bytes
                                , const System::Size&               byteIndex
                                , const System::Size&               byteCount
                                , std::vector<System::Char>&        chars
                                , const System::Size&               charIndex) const override;

            System::Size GetMaxByteCount(const System::Size& charCount) override;

            System::Size GetMaxCharCount(const System::Size& byteCount) override;

            std::vector<System::UByte> GetPreamble() const;

            const Decoder& GetDecoder() const override;

            const Encoder& GetEncoder() const override;

        private:
            UTF8Encoder encoder;
            UTF8Decoder decoder;
        };
    }
}

#endif // UTF8ENCODING_HPP
