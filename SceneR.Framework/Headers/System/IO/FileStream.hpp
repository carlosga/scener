// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for full license information.

#ifndef FILESTREAM_HPP
#define FILESTREAM_HPP

#include <fstream>

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
            FileStream(const String& path);
			
			/**
			 * Initializes a new instance of the FileStream class with the specified and opening mode.
			 */		
            FileStream(const String& path, const std::ios::openmode& mode);

            /**
			 * Releases all resources being used by this FileStream.
			 */
            virtual ~FileStream();

        public:
            /**
             * Gets a value indicating whether the current stream supports reading.
             */
            virtual bool CanRead() override;

            /**
             * Gets a value indicating whether the current stream supports seeking.
             */
            virtual bool CanSeek() override;

            /**
             * Gets a value indicating whether the current stream supports writing.
             */
            virtual bool CanWrite() override;

            /**
             * Returns the current position of the reader.
             */
            virtual Size Position() override;

            /**
             * Returns the length in bytes of the stream.
             */
            virtual Size Length() override;

            /**
             * Closes the current stream
             */
            virtual void Close() override;

            /**
             * Reads a byte from the stream or returns -1 if at the end of the stream.
             */
            virtual UByte ReadByte() override;

            /**
             * Reads a sequence of bytes from the current stream.
             */
            virtual Size Read(char* buffer, const Size& offset, const Size& count) override;

            /**
             * Sets the position within the current stream.
             */
            virtual Size Seek(const Size& offset, const std::ios::seekdir& origin) override;

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
