// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_IO_STREAM_HPP
#define SCENER_IO_STREAM_HPP

#include <cstddef>
#include <cstdint>
#include <ios>

namespace SceneR { namespace IO {

/**
 * Contract for stream implementations.
 */
class Stream
{
public:
    /**
     * Releases all resources being used by this Stream.
     */
    virtual ~Stream() = default;

public:
    /**
     * Gets a value indicating whether the current stream supports reading.
     */
    virtual bool can_read() const noexcept = 0;

    /**
     * Gets a value indicating whether the current stream supports seeking.
     */
    virtual bool can_seek() const noexcept = 0;

    /**
     * Gets a value indicating whether the current stream supports writing.
     */
    virtual bool can_write() const noexcept = 0;

    /**
     * Returns the current position of the reader.
     */
    virtual std::size_t position() noexcept = 0;

    /**
     * Returns the length in bytes of the stream.
     */
    virtual std::size_t length() noexcept = 0;

    /**
     * Closes the current stream
     */
    virtual void close() noexcept = 0;

    /**
     * Reads a byte from the stream.
     */
    virtual std::uint32_t read_byte() noexcept = 0;

    /**
     * Reads a sequence of bytes from the current stream.
     */
    virtual std::size_t read(char* buffer, std::size_t offset, std::size_t count) noexcept = 0;

    /**
     * Sets the position within the current stream.
     */
    virtual std::size_t seek(std::size_t offset, std::ios::seekdir origin) noexcept = 0;
};

}}

#endif // SCENER_IO_STREAM_HPP
