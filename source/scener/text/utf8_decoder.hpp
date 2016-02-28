// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_TEXT_UTF8DECODER_HPP
#define SCENER_TEXT_UTF8DECODER_HPP

#include <codecvt>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include "scener/text/decoder.hpp"

namespace scener { namespace text {

/// Converts a sequence of encoded bytes into a set of UTF-8 encoded characters.
class urf8_decoder final : public decoder
{
public:
    /// Initializes a new instance of the UTF8Decoder class.
    urf8_decoder()
        : _facet { std::make_shared<std::codecvt_utf8<char16_t, 0x10ffff, std::consume_header>>() }
    {
    }

    /// Releases all resources being used by this UTF8Decoder.
    ~urf8_decoder() override = default;

public:
    std::size_t get_char_count(const std::vector<std::uint8_t>& bytes, std::size_t index, std::size_t count) const override;

    std::size_t get_chars(const std::vector<std::uint8_t>& bytes
                        , std::size_t                      byte_index
                        , std::size_t                      byte_count
                        , std::vector<char16_t>&           chars
                        , std::size_t                      char_index) const override;

    void reset() override;

private:
    std::shared_ptr<std::codecvt_utf8<char16_t, 0x10ffff, std::consume_header>> _facet;
};

}}

#endif // SCENER_TEXT_UTF8DECODER_HPP
