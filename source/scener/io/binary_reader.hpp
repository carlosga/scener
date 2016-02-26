// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_IO_BINARYREADER_HPP
#define SCENER_IO_BINARYREADER_HPP

#include <cstdint>
#include <vector>

namespace scener { namespace io {

class stream;

/// Reads primitive data types as binary values in a specific encoding.
class binary_reader final
{
public:
    /// Initializes a new instance of the binary_reader class with the given stream.
    /// \param stream the input stream.
    binary_reader(io::stream& stream) noexcept;

    /// Releases all resources being used by this binary_reader.
    ~binary_reader() = default;

public:
    /// Gets the underliying Stream.
    /// \returns the underliying Stream.
    stream& base_stream() noexcept;

    /// Closes the current reader and the underlying stream.
    void close() noexcept;

    /// Reads data from the current stream.
    template <typename T>
    T read() noexcept;

    /// Returns the next available character, or -1 if no more characters are available.
    /// \returns the next available character, or -1 if no more characters are available.
    std::int32_t peek_char() noexcept;

    /// Reads a 7-bit encoded unsigned int.
    /// \returns a 7-bit encoded unsigned int.
    std::uint32_t read_7_bit_encoded_int() noexcept;

    /// Reads the specified number of bytes from the underliying stream
    /// \param count the number of bytes to read.
    /// \returns the data read from the underlying stream.
    std::vector<std::uint8_t> read_bytes(std::size_t count) noexcept;

private:
    binary_reader() = delete;
    binary_reader(const binary_reader& reader) = delete;
    binary_reader& operator=(const binary_reader& reader) = delete;

private:
    stream& _stream;
};

}}

#endif // SCENER_IO_BINARYREADER_HPP
