// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_TEXT_DECODER_HPP
#define SCENER_TEXT_DECODER_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

namespace scener { namespace text {

/// Converts a sequence of encoded bytes into a set of characters.
class Decoder
{
protected:
    /// Initializes a new instance of the Decoder class.
    Decoder();

    /// Virtual destructor.
    virtual ~Decoder();

public:
    /// Calculates the number of characters produced by decoding a sequence of bytes
    /// starting at the specified byte pointer. A parameter indicates whether to clear
    /// the internal state of the decoder after the calculation.
    virtual std::size_t get_char_count(const std::uint8_t* bytes, std::size_t count, bool flush) const;

    /// When overridden in a derived class, calculates the number of characters produced
    /// by decoding a sequence of bytes from the specified byte array.
    virtual std::size_t get_char_count(const std::vector<std::uint8_t>& bytes
                                     , std::size_t                      index
                                     , std::size_t                      count) const = 0;

    /// Calculates the number of characters produced by decoding a sequence of bytes
    /// from the specified byte array. A parameter indicates whether to clear the
    /// internal state of the decoder after the calculation.
    virtual std::size_t get_char_count(const std::vector<std::uint8_t>& bytes
                                     , std::size_t                      index
                                     , std::size_t                      count
                                     , bool                             flush) const;

    /// Decodes a sequence of bytes starting at the specified byte pointer and
    /// any bytes in the internal buffer into a set of characters that are
    /// stored starting at the specified character pointer.
    /// A parameter indicates whether to clear the internal state of the decoder
    /// after the conversion.
    virtual std::size_t get_chars(const std::uint8_t* bytes
                                , std::size_t         byteCount
                                , char16_t*           chars
                                , std::size_t         charCount
                                , bool                flush) const;

    /// When overridden in a derived class, decodes a sequence of bytes from the
    /// specified byte array and any bytes in the internal buffer into the specified
    /// character array.
    virtual std::size_t get_chars(const std::vector<std::uint8_t>& bytes
                                , std::size_t                      byteIndex
                                , std::size_t                      byteCount
                                , std::vector<char16_t>&           chars
                                , std::size_t                      charIndex) const = 0;

    /// Decodes a sequence of bytes from the specified byte array and any bytes
    /// in the internal buffer into the specified character array.
    /// A parameter indicates whether to clear the internal state of the decoder after the conversion.
    virtual std::size_t get_chars(const std::vector<std::uint8_t>& bytes
                                , std::size_t                      byteIndex
                                , std::size_t                      byteCount
                                , std::vector<char16_t>&           chars
                                , std::size_t                      charIndex
                                , bool                             flush) const;

    /// Sets the encoder back to its initial state.
    virtual void reset() = 0;
};

}}

#endif // SCENER_TEXT_DECODER_HPP
