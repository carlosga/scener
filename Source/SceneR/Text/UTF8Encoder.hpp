// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_TEXT_UTF8ENCODER_HPP
#define SCENER_TEXT_UTF8ENCODER_HPP

#include <codecvt>
#include <cstddef>
#include <cstdint>

#include "SceneR/Text/Encoder.hpp"

namespace scener { namespace text {

/// Converts a set of UTF-8 encoded characters into a sequence of bytes.
class UTF8Encoder final : public Encoder
{
public:
    /// Initializes a new instance of the UTF8Encoder class.
    UTF8Encoder() = default;

    /// Releases all resources being used by this UTF8Encoder.
    ~UTF8Encoder() override = default;

public:
    std::size_t get_byte_count(const std::vector<char16_t>& chars
                             , std::size_t                  index
                             , std::size_t                  count
                             , bool                         flush) const override;

    std::size_t get_bytes(const std::vector<char16_t>& chars
                        , std::size_t                  charIndex
                        , std::size_t                  charCount
                        , std::vector<std::uint8_t>&   bytes
                        , std::size_t                  byteIndex
                        , bool                         flush) const override;

private:
    std::codecvt_utf8_utf16<char16_t> _converter;
};

}}

#endif // SCENER_TEXT_UTF8ENCODER_HPP
