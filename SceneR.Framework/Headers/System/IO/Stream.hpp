// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef STREAM_HPP
#define STREAM_HPP

#include <cstddef>
#include <cstdint>
#include <ios>

namespace System
{
    namespace IO
    {
        /**
         * Contract for stream implementations.
         */
        class Stream
        {
        public:
            /**
             * Releases all resources being used by this Stream.
             */
            virtual ~Stream();

        public:
            /**
             * Gets a value indicating whether the current stream supports reading.
             */
            virtual bool CanRead() = 0;

            /**
             * Gets a value indicating whether the current stream supports seeking.
             */
            virtual bool CanSeek() = 0;

            /**
             * Gets a value indicating whether the current stream supports writing.
             */
            virtual bool CanWrite() = 0;

            /**
             * Returns the current position of the reader.
             */
            virtual std::size_t Position() = 0;

            /**
             * Returns the length in bytes of the stream.
             */
            virtual std::size_t Length() = 0;

            /**
             * Closes the current stream
             */
            virtual void Close() = 0;

            /**
             * Reads a byte from the stream or returns -1 if at the end of the stream.
             */
            virtual std::uint8_t ReadByte() = 0;

            /**
             * Reads a sequence of bytes from the current stream.
             */
            virtual std::size_t Read(char* buffer, const std::size_t& offset, const std::size_t& count) = 0;

            /**
             * Sets the position within the current stream.
             */
            virtual std::size_t Seek(const std::size_t& offset, const std::ios::seekdir& origin) = 0;
        };
    }
}

#endif  /* STREAM_HPP */
