// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <System/Text/Decoder.hpp>

namespace System
{
    namespace Text
    {
        Decoder::Decoder()
        {
        }

        Decoder::~Decoder()
        {
        }

        std::size_t Decoder::GetCharCount(const std::uint8_t* bytes, const std::size_t& count, const bool& flush) const
        {
            auto vbytes = std::vector<std::uint8_t>(bytes, bytes + count);

            return this->GetCharCount(vbytes, 0, count, flush);
        }

        std::size_t Decoder::GetCharCount(const std::vector<std::uint8_t>& bytes
                                        , const std::size_t&               index
                                        , const std::size_t&               count
                                        , const bool&                      flush) const
        {
            return this->GetCharCount(bytes, index, count);
        }

        std::size_t Decoder::GetChars(const std::uint8_t* bytes
                                    , const std::size_t&  byteCount
                                    , char16_t*           chars
                                    , const std::size_t&  charCount
                                    , const bool&         flush) const
        {
            auto vbytes = std::vector<std::uint8_t>(bytes, bytes + byteCount);
            auto vchars = std::vector<char16_t>();

            vchars.reserve(this->GetCharCount(vbytes, 0, byteCount, flush));

            auto totalChars = this->GetChars(vbytes, 0, byteCount, vchars, 0, flush);
            auto result     = ((totalChars > charCount) ? charCount : totalChars);

            std::copy_n(vchars.begin(), result, chars);

            return result;
        }

        std::size_t Decoder::GetChars(const std::vector<std::uint8_t>& bytes
                                    , const std::size_t&               byteIndex
                                    , const std::size_t&               byteCount
                                    , std::vector<char16_t>&           chars
                                    , const std::size_t&               charIndex
                                    , const bool&                      flush) const
        {
            return this->GetChars(bytes, byteIndex, byteCount, chars, charIndex);
        }
    }
}
