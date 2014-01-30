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

#ifndef UTF8ENCODER_HPP
#define UTF8ENCODER_HPP

#include <System/Text/Encoder.hpp>

namespace System
{
    namespace Text
    {
        class UTF8Encoder : public Encoder
        {
            typedef std::codecvt_utf8<char16_t> Converter;

        public:
            UTF8Encoder();

            virtual ~UTF8Encoder();

        public:
            virtual uint32_t GetByteCount(const std::vector<System::Char>& chars
                                        , const System::UInt32&            index
                                        , const System::UInt32&            count
                                        , const bool&                      flush) const override;

            virtual uint32_t GetBytes(const std::vector<System::Char>& chars
                                    , const System::UInt32&            charIndex
                                    , const System::UInt32&            charCount
                                    , std::vector<System::UByte>&      bytes
                                    , const System::UInt32&            byteIndex
                                    , const bool&                      flush) const override;

        private:
            UTF8Encoder::Converter converter;
        };
    }
}

#endif // UTF8ENCODER_HPP
