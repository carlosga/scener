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
#include <codecvt>

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
