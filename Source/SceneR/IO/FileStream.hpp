// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_IO_FILESTREAM_HPP
#define SCENER_IO_FILESTREAM_HPP

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <string>

#include "SceneR/IO/Stream.hpp"

namespace scener { namespace io {

/// A Stream around a file, supporting read operations.
class FileStream  final : public Stream
{
public:
    /// Initializes a new instance of the FileStream class with the specified and opening mode.
    /// \param path a relative or absolute path for the file that the current FileStream object will encapsulate.
    /// \param mode a constant that determines how to open or create the file.
    FileStream(const std::string& path, const std::ios::openmode& mode = std::ios::in | std::ios::binary) noexcept;

    /// Releases all resources being used by this FileStream.
    ~FileStream() override = default;

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

    /// Closes the current stream.
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
    FileStream() = delete;
    FileStream(const FileStream& stream) = delete;
    FileStream& operator=(const FileStream& stream) = delete;

private:
    std::fstream       _stream;
    std::ios::openmode _mode;
};

}}

#endif // SCENER_IO_FILESTREAM_HPP
