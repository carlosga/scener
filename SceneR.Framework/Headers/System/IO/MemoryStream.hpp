// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MEMORYSTREAM_HPP
#define MEMORYSTREAM_HPP

#include <cstddef>
#include <cstdint>
#include <sstream>
#include <vector>

#include <System/IO/Stream.hpp>

namespace System
{
    namespace IO
    {
        /**
         * A Stream around a in memory buffer, supporting read operations.
         */
        class MemoryStream : public Stream
        {
        public:
            /**
             * Initializes a new instance of the MemoryStream class.
             */
            MemoryStream(const std::vector<std::uint8_t>& buffer);

            /**
             * Releases all resources being used by this MemoryStream.
             */
            ~MemoryStream() override;

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
            MemoryStream() = delete;
            MemoryStream(const MemoryStream& stream) = delete;
            MemoryStream& operator=(const MemoryStream& stream) = delete;

        private:
            std::stringstream  _stream;
            std::ios::openmode _mode;
        };
    }
}

#endif  /* MEMORYSTREAM_HPP */
