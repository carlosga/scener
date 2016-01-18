// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_IO_FILESTREAM_HPP
#define SCENER_IO_FILESTREAM_HPP

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <string>

#include "SceneR/IO/Stream.hpp"

namespace SceneR { namespace IO {

/**
 * A Stream around a file, supporting read operations.
 */
class FileStream  final : public Stream
{
public:
    /**
     * Initializes a new instance of the FileStream class with the specified and opening mode.
     */
    FileStream(const std::string& path, const std::ios::openmode& mode = std::ios::in | std::ios::binary) noexcept;

    /**
     * Releases all resources being used by this FileStream.
     */
    ~FileStream() override = default;

public:
    /**
     * Gets a value indicating whether the current stream supports reading.
     */
    bool can_read() const noexcept override;

    /**
     * Gets a value indicating whether the current stream supports seeking.
     */
    bool can_seek() const noexcept override;

    /**
     * Gets a value indicating whether the current stream supports writing.
     */
    bool can_write() const noexcept override;

    /**
     * Returns the current position of the reader.
     */
    std::size_t position() noexcept override;

    /**
     * Returns the length in bytes of the stream.
     */
    std::size_t length() noexcept override;

    /**
     * Closes the current stream
     */
    void close() noexcept override;

    /**
     * Reads a byte from the stream or returns -1 if at the end of the stream.
     */
    std::uint32_t read_byte() noexcept override;

    /**
     * Reads a sequence of bytes from the current stream.
     */
    std::size_t read(char* buffer, std::size_t offset, std::size_t count) noexcept override;

    /**
     * Sets the position within the current stream.
     */
    std::size_t seek(std::size_t offset, const std::ios::seekdir& origin) noexcept override;

private:
    FileStream() = delete;
    FileStream(const FileStream& stream) = delete;
    FileStream& operator=(const FileStream& stream) = delete;

private:
    std::fstream       _stream;
    std::ios::openmode _mode;
};

}}

#endif // SCENER_IO_FILESTREAM_HPP
