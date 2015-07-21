// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <System/Text/UTF8Decoder.hpp>

#include <memory>

namespace System
{
    namespace Text
    {
        UTF8Decoder::UTF8Decoder()
            : Decoder { }
        {
        }

        UTF8Decoder::~UTF8Decoder()
        {
        }

        std::size_t UTF8Decoder::GetCharCount(const std::vector<std::uint8_t>& bytes
                                            , const std::size_t&               index
                                            , const std::size_t&               count) const
        {
            std::size_t result = 0;

            for (std::size_t i = index; i < (index + count);)
            {
                auto        buffer    = bytes[i];
                std::size_t byteCount = 1;

                // http://xbox.create.msdn.com/en-US/sample/xnb_format
                // Decode UTF-8.
                if (buffer & 0x80)
                {
                    while (buffer & (0x80 >> byteCount))
                    {
                        byteCount++;
                    }
                }

                i += byteCount;
                result++;
            }

            return result;
        }

        std::size_t UTF8Decoder::GetChars(const std::vector<std::uint8_t>& bytes
                                        , const std::size_t&               byteIndex
                                        , const std::size_t&               byteCount
                                        , std::vector<char16_t>&           chars
                                        , const std::size_t&               charIndex) const
        {
            auto        from     = (char*)&bytes[0] + byteIndex;
            auto        fromEnd  = from + byteCount;
            const char* fromNext = nullptr;
            auto        to       = std::vector<char16_t>(byteCount);
            auto        toStart  = &to[0];
            auto        toEnd    = toStart + byteCount;
            char16_t*   toNext   = nullptr;
            auto        iterator = chars.begin() + charIndex;
            auto        state    = std::mbstate_t();
            auto        status   = this->converter.in(state, from, fromEnd, fromNext, toStart, toEnd, toNext);

            if (status == std::codecvt_base::error)
            {
                throw std::runtime_error("decoder error");
            }
            else if (status == std::codecvt_base::partial)
            {
            }
            else if (status == std::codecvt_base::ok)
            {
                for (auto position = toStart; position < toNext; position++)
                {
                    chars.emplace(iterator++, *position);
                }
            }

            return static_cast<std::size_t>(toNext - toStart);
        }

        void UTF8Decoder::Reset()
        {
        }
    }
}
