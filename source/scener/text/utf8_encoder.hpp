// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_TEXT_UTF8_ENCODER_HPP
#define SCENER_TEXT_UTF8_ENCODER_HPP

#include <codecvt>
#include <cstddef>
#include <cstdint>
#include <locale>
#include <memory>

#include "scener/text/encoder.hpp"

namespace scener::text
{
    /// Converts a set of UTF-8 encoded characters into a sequence of bytes.
    class utf8_encoder final : public encoder
    {
    public:
        /// Initializes a new instance of the UTF8Encoder class.
        utf8_encoder()
            : _facet { std::make_shared<std::codecvt_utf8<char16_t, 0x10ffff, std::consume_header>>() }
        {

        }

        /// Releases all resources being used by this UTF8Encoder.
        ~utf8_encoder() override = default;

    public:
        std::size_t get_byte_count(const std::vector<char16_t>& chars
                                 , std::size_t                  index
                                 , std::size_t                  count
                                 , bool                         flush) const override;
 
        std::size_t get_bytes(const std::vector<char16_t>& chars
                            , std::size_t                  char_index
                            , std::size_t                  char_count
                            , std::vector<std::uint8_t>&   bytes
                            , std::size_t                  byte_index
                            , bool                         flush) const override;

    private:
        std::shared_ptr<std::codecvt_utf8<char16_t, 0x10ffff, std::consume_header>> _facet;
    };
}

#endif // SCENER_TEXT_UTF8_ENCODER_HPP
