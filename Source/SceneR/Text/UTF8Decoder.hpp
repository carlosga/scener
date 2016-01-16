// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_TEXT_UTF8DECODER_HPP
#define SCENER_TEXT_UTF8DECODER_HPP

#include <codecvt>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "SceneR/Text/Decoder.hpp"

namespace SceneR { namespace Text {

/**
 * Converts a sequence of encoded bytes into a set of UTF-8 encoded characters.
 */
class UTF8Decoder final : public Decoder
{
public:
    /**
     * Initializes a new instance of the UTF8Decoder class.
     */
    UTF8Decoder() = default;

    /**
     * Releases all resources being used by this UTF8Decoder.
     */
    ~UTF8Decoder() override = default;

public:
    std::size_t get_char_count(const std::vector<std::uint8_t>& bytes, std::size_t index, std::size_t count) const override;

    std::size_t get_chars(const std::vector<std::uint8_t>& bytes
                        , std::size_t                      byteIndex
                        , std::size_t                      byteCount
                        , std::vector<char16_t>&           chars
                        , std::size_t                      charIndex) const override;

    void reset() override;

private:
    std::codecvt_utf8_utf16<char16_t> _converter;
};

}}

#endif // SCENER_TEXT_UTF8DECODER_HPP
