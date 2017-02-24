// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_IO_MEMORYSTREAM_HPP
#define SCENER_IO_MEMORYSTREAM_HPP

#include <cstddef>
#include <cstdint>

#include <gsl/span>

#include "scener/io/stream.hpp"

namespace scener { namespace io {

/// A Stream around a in memory buffer, supporting read operations.
class memory_stream final : public stream
{
public:
    /// Initializes a new instance of the memory_stream class.
    /// \param buffer a buffer view from which to create the current stream.
    memory_stream(const gsl::span<std::uint8_t>& buffer) noexcept;

    /// Releases all resources being used by this memory_stream.
    ~memory_stream() override = default;

public:
    /// Gets a value indicating whether the current stream supports reading.
    /// \returns true if the stream supports reading; false otherwise.
    bool can_read() const noexcept override;

    /// Gets a value indicating whether the current stream supports seeking.
    /// \returns true if the stream supports seeking; false otherwise.
    bool can_seek() const noexcept override;

    /// Gets a value indicating whether the current stream supports writing.
    /// \returns true if the stream supports writing; false otherwise.
    bool can_write() const noexcept override;

    /// Gets the current position of this stream.
    /// \returns the current position of this stream.
    std::size_t position() noexcept override;

    /// Returns the length in bytes of the stream.
    /// \returns the length in bytes of the stream.
    std::size_t length() noexcept override;

    /// Closes the current stream
    void close() noexcept override;

    /// Reads a byte from the file and advances the read position one byte.
    /// \returns the byte, cast to an std::uint32_t, or -1 if the end of the stream has been reached.
    std::int32_t read_byte() noexcept override;

    /// Reads a sequence of bytes from the current stream.
    /// \param buffer when this method returns, contains the specified byte array with the values
    ///               between offset and (offset + count - 1) replaced by the bytes read from the current source.
    /// \param offset the byte offset in buffer at which the read bytes will be placed.
    /// \param count the maximum number of bytes to read.
    /// \returns The total number of bytes read into the buffer. This might be less than the number of bytes requested
    ///          if that number of bytes are not currently available, or zero if the end of the stream is reached.
    std::size_t read(char* buffer, std::size_t offset, std::size_t count) noexcept override;

    /// Sets the position within the current stream.
    /// \param offset the point relative to origin from which to begin seeking.
    /// \param origin specifies the beginning, the end, or the current position as a reference point for offset.
    /// \returns the new position in the stream.
    std::size_t seek(std::size_t offset, std::ios::seekdir origin) noexcept override;

private:
    memory_stream() = delete;
    memory_stream(const memory_stream& stream) = delete;
    memory_stream& operator=(const memory_stream& stream) = delete;

private:
    gsl::span<std::uint8_t>           _buffer;
    gsl::span<std::uint8_t>::iterator _position;
};

}}

#endif // SCENER_IO_MEMORYSTREAM_HPP
