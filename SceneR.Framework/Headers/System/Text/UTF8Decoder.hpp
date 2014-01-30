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

#ifndef UTF8DECODER_HPP
#define UTF8DECODER_HPP

#include <System/Core.hpp>
#include <System/Text/Decoder.hpp>
#include <codecvt>
#include <vector>

namespace System
{
    namespace Text
    {
        class UTF8Decoder : public Decoder
        {
            typedef std::codecvt_utf8<char16_t> Converter;

        public:
            UTF8Decoder();

            virtual ~UTF8Decoder();

        public:
            virtual System::UInt32 GetCharCount(const std::vector<System::UByte>& bytes
                                              , const System::UInt32&             index
                                              , const System::UInt32&             count) const override;

            virtual System::UInt32 GetChars(const std::vector<System::UByte>& bytes
                                    , const System::UInt32&                   byteIndex
                                    , const System::UInt32&                   byteCount
                                    , std::vector<System::Char>&              chars
                                    , const System::UInt32&                   charIndex) const override;

            virtual void Reset();

        private:
            UTF8Decoder::Converter converter;
        };
    }
}

#endif // UTF8DECODER_HPP
