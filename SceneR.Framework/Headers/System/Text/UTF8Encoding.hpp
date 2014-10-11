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

#include <System/Text/UTF8Decoder.hpp>
#include <System/Text/UTF8Encoder.hpp>
#include <System/Text/Encoding.hpp>

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
            virtual const System::String EncodingName() const override;

            virtual bool IsSingleByte() const override;

            virtual System::Size GetByteCount(const std::vector<System::Char>& chars
                                            , const System::Size&              index
                                            , const System::Size&              count) const override;

            virtual System::Size GetBytes(const std::vector<System::Char>& chars
                                        , const System::Size&              charIndex
                                        , const System::Size&              charCount
                                        , std::vector<System::UByte>&      bytes
                                        , const System::Size&              byteIndex) const override;

            virtual System::Size GetCharCount(const std::vector<System::UByte>& bytes
                                            , const System::Size&               index
                                            , const System::Size&               count) const override;

            virtual System::Size GetChars(const std::vector<System::UByte>& bytes
                                        , const System::Size&               byteIndex
                                        , const System::Size&               byteCount
                                        , std::vector<System::Char>&        chars
                                        , const System::Size&               charIndex) const override;

            virtual System::Size GetMaxByteCount(const System::Size& charCount) override;

            virtual System::Size GetMaxCharCount(const System::Size& byteCount) override;

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
