//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#ifndef UTF8ENCODING_HPP
#define UTF8ENCODING_HPP

#include <System/Text/Encoding.hpp>
#include <System/Text/UTF8Decoder.hpp>
#include <System/Text/UTF8Encoder.hpp>

namespace System
{
    namespace Text
    {
        class UTF8Encoding : public Encoding
        {
        public:
            UTF8Encoding();

            virtual ~UTF8Encoding();

        public:
            virtual const std::u16string EncodingName() const override;

            virtual bool IsSingleByte() const override;

            virtual System::UInt32 GetByteCount(const std::vector<System::Char>& chars
                                              , const System::UInt32&            index
                                              , const System::UInt32&            count) const override;

            virtual System::UInt32 GetBytes(const std::vector<System::Char>& chars
                                          , const System::UInt32&            charIndex
                                          , const System::UInt32&            charCount
                                          , std::vector<System::UByte>&      bytes
                                          , const System::UInt32&            byteIndex) const override;

            virtual System::UInt32 GetCharCount(const std::vector<System::UByte>& bytes
                                        , const System::UInt32&                   index
                                        , const System::UInt32&                   count) const override;

            virtual System::UInt32 GetChars(const std::vector<System::UByte>& bytes
                                    , const System::UInt32&                   byteIndex
                                    , const System::UInt32&                   byteCount
                                    , std::vector<System::Char>&              chars
                                    , const System::UInt32&                   charIndex) const override;

            virtual System::UInt32 GetMaxByteCount(const System::UInt32& charCount) override;

            virtual System::UInt32 GetMaxCharCount(const System::UInt32& byteCount) override;

            virtual std::vector<System::UByte> GetPreamble() const;

            virtual const Decoder& GetDecoder() const override;

            virtual const Encoder& GetEncoder() const override;

        private:
            UTF8Encoder encoder;
            UTF8Decoder decoder;
        };
    }
}

#endif // UTF8ENCODING_HPP
