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
            virtual uint32_t GetCharCount(const std::vector<uint8_t>& bytes
                                        , const uint32_t&             index
                                        , const uint32_t&             count) const override;

            virtual uint32_t GetChars(const std::vector<uint8_t>& bytes
                                    , const uint32_t&             byteIndex
                                    , const uint32_t&             byteCount
                                    , std::vector<char16_t>&      chars
                                    , const uint32_t&             charIndex) const override;

            virtual void Reset();

        private:
            UTF8Decoder::Converter converter;
        };
    }
}

#endif // UTF8DECODER_HPP
