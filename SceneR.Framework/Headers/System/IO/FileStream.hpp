// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SYSTEM_IO_FILESTREAM_HPP
#define SYSTEM_IO_FILESTREAM_HPP

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <string>

#include <System/IO/Stream.hpp>

namespace System
{
    namespace IO
    {
        /**
         * A Stream around a file, supporting read operations.
         */
        class FileStream  final : public Stream
        {
        public:
            /**
             * Initializes a new instance of the FileStream class with the specified and opening mode.
             */
            FileStream(const std::u16string& path, const std::ios::openmode& mode = std::ios::in | std::ios::binary);

            /**
             * Releases all resources being used by this FileStream.
             */
            ~FileStream() override;

        public:
            /**
             * Gets a value indicating whether the current stream supports reading.
             */
            bool can_read() override;

            /**
             * Gets a value indicating whether the current stream supports seeking.
             */
            bool can_seek() override;

            /**
             * Gets a value indicating whether the current stream supports writing.
             */
            bool can_write() override;

            /**
             * Returns the current position of the reader.
             */
            std::size_t position() override;

            /**
             * Returns the length in bytes of the stream.
             */
            std::size_t length() override;

            /**
             * Closes the current stream
             */
            void close() override;

            /**
             * Reads a byte from the stream or returns -1 if at the end of the stream.
             */
            std::uint32_t read_byte() override;

            /**
             * Reads a sequence of bytes from the current stream.
             */
            std::size_t read(char* buffer, const std::size_t& offset, const std::size_t& count) override;

            /**
             * Sets the position within the current stream.
             */
            std::size_t seek(const std::size_t& offset, const std::ios::seekdir& origin) override;

        private:
            FileStream() = delete;
            FileStream(const FileStream& stream) = delete;
            FileStream& operator=(const FileStream& stream) = delete;

        private:
            std::fstream       _stream;
            std::ios::openmode _mode;
        };
    }
}

#endif  // SYSTEM_IO_FILESTREAM_HPP
