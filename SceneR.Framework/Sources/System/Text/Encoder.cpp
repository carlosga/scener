// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <System/Text/Encoder.hpp>

#include <algorithm>
#include <stdexcept>

namespace System
{
    namespace Text
    {
        Encoder::Encoder()
        {
        }

        Encoder::~Encoder()
        {
        }

        std::size_t Encoder::GetByteCount(const char16_t* chars, const std::size_t& count, const bool& flush) const
        {
            auto vchars = std::vector<char16_t>(chars, chars + count);

            return this->GetByteCount(vchars, 0, count, flush);
        }

        std::size_t Encoder::GetBytes(const char16_t*    chars
                                    , const std::size_t& charCount
                                    , std::uint8_t*      bytes
                                    , const std::size_t& byteCount
                                    , const bool&        flush) const
        {
            if (chars == nullptr)
            {
                throw std::runtime_error("chars is null");
            }
            if (bytes == nullptr)
            {
                throw std::runtime_error("bytes is null");
            }

            auto vchars = std::vector<char16_t>(chars, chars + charCount);
            auto bcount = this->GetByteCount(vchars, 0, charCount, flush);

            if (bcount > byteCount)
            {
                throw std::runtime_error("byteCount is less than the resulting number of bytes.");
            }

            auto vbytes     = std::vector<std::uint8_t>(bcount, 0);
            auto totalBytes = this->GetBytes(vchars, 0, charCount, vbytes, 0, flush);
            auto result     = ((totalBytes > byteCount) ? byteCount : totalBytes);

            std::copy_n(vbytes.begin(), result, bytes);

            return result;
        }

        void Encoder::Reset()
        {
        }
    }
}
