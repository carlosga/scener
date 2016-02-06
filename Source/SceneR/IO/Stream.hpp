// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_IO_STREAM_HPP
#define SCENER_IO_STREAM_HPP

#include <cstddef>
#include <cstdint>
#include <ios>

namespace SceneR { namespace IO {

/// Contract for stream implementations.
class Stream
{
public:
    /// Virtual destructor.
    virtual ~Stream() = default;

public:
    /// Gets a value indicating whether the current stream supports reading.
    /// \returns true if the stream supports reading; false otherwise.
    virtual bool can_read() const noexcept = 0;

    /// Gets a value indicating whether the current stream supports seeking.
    /// \returns true if the stream supports seeking; false otherwise.
    virtual bool can_seek() const noexcept = 0;

    /// Gets a value indicating whether the current stream supports writing.
    /// \returns true if the stream supports writing; false otherwise.
    virtual bool can_write() const noexcept = 0;

    /// Gets the current position of this stream.
    /// \returns the current position of this stream.
    virtual std::size_t position() noexcept = 0;

    /// Returns the length in bytes of the stream.
    /// \returns the length in bytes of the stream.
    virtual std::size_t length() noexcept = 0;

    /// Closes the current stream
    virtual void close() noexcept = 0;

    /// Reads a byte from the file and advances the read position one byte.
    /// \returns the byte, cast to an std::uint32_t, or -1 if the end of the stream has been reached.
    virtual std::int32_t read_byte() noexcept = 0;

    /// Reads a sequence of bytes from the current stream.
    /// \param buffer when this method returns, contains the specified byte array with the values
    ///               between offset and (offset + count - 1) replaced by the bytes read from the current source.
    /// \param offset the byte offset in buffer at which the read bytes will be placed.
    /// \param count the maximum number of bytes to read.
    /// \returns The total number of bytes read into the buffer. This might be less than the number of bytes requested
    ///          if that number of bytes are not currently available, or zero if the end of the stream is reached.
    virtual std::size_t read(char* buffer, std::size_t offset, std::size_t count) noexcept = 0;

    /// Sets the position within the current stream.
    /// \param offset the point relative to origin from which to begin seeking.
    /// \param origin specifies the beginning, the end, or the current position as a reference point for offset.
    /// \returns the new position in the stream.
    virtual std::size_t seek(std::size_t offset, std::ios::seekdir origin) noexcept = 0;
};

}}

#endif // SCENER_IO_STREAM_HPP
