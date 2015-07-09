// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef FILESTREAM_HPP
#define FILESTREAM_HPP

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
        class FileStream : public Stream
        {
        public:
            /**
             * Initializes a new instance of the FileStream class with the specified file.
             */
            FileStream(const std::u16string& path);

            /**
             * Initializes a new instance of the FileStream class with the specified and opening mode.
             */
            FileStream(const std::u16string& path, const std::ios::openmode& mode);

            /**
             * Releases all resources being used by this FileStream.
             */
            ~FileStream() override;

        public:
            /**
             * Gets a value indicating whether the current stream supports reading.
             */
            bool CanRead() override;

            /**
             * Gets a value indicating whether the current stream supports seeking.
             */
            bool CanSeek() override;

            /**
             * Gets a value indicating whether the current stream supports writing.
             */
            bool CanWrite() override;

            /**
             * Returns the current position of the reader.
             */
            std::size_t Position() override;

            /**
             * Returns the length in bytes of the stream.
             */
            std::size_t Length() override;

            /**
             * Closes the current stream
             */
            void Close() override;

            /**
             * Reads a byte from the stream or returns -1 if at the end of the stream.
             */
            std::uint8_t ReadByte() override;

            /**
             * Reads a sequence of bytes from the current stream.
             */
            std::size_t Read(char* buffer, const std::size_t& offset, const std::size_t& count) override;

            /**
             * Sets the position within the current stream.
             */
            std::size_t Seek(const std::size_t& offset, const std::ios::seekdir& origin) override;

        private:
            FileStream() = delete;
            FileStream(const FileStream& stream) = delete;
            FileStream& operator=(const FileStream& stream) = delete;

        private:
            std::fstream       stream;
            std::ios::openmode mode;
        };
    }
}

#endif  /* FILESTREAM_HPP */
