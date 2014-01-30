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

            virtual uint32_t GetByteCount(const std::vector<char16_t>& chars
                                        , const uint32_t&              index
                                        , const uint32_t&              count) const override;

            virtual uint32_t GetBytes(const std::vector<char16_t>& chars
                                    , const uint32_t&              charIndex
                                    , const uint32_t&              charCount
                                    , std::vector<uint8_t>&        bytes
                                    , const uint32_t&              byteIndex) const override;

            virtual uint32_t GetCharCount(const std::vector<uint8_t>& bytes
                                        , const uint32_t&             index
                                        , const uint32_t&             count) const override;

            virtual uint32_t GetChars(const std::vector<uint8_t>& bytes
                                    , const uint32_t&             byteIndex
                                    , const uint32_t&             byteCount
                                    , std::vector<char16_t>&      chars
                                    , const uint32_t&             charIndex) const override;

            virtual uint32_t GetMaxByteCount(const uint32_t& charCount) override;

            virtual uint32_t GetMaxCharCount(const uint32_t& byteCount) override;

            virtual std::vector<uint8_t> GetPreamble() const;

            virtual const Decoder& GetDecoder() const override;

            virtual const Encoder& GetEncoder() const override;

        private:
            UTF8Encoder encoder;
            UTF8Decoder decoder;
        };
    }
}

#endif // UTF8ENCODING_HPP
