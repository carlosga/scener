//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#ifndef FILESTREAM_HPP
#define FILESTREAM_HPP

#include <System/Core.hpp>
#include <System/IO/Stream.hpp>
#include <fstream>

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
			 * Initializes a new FileStream with the specified file.
			 */
            FileStream(const String& path);
			
			/**
			 * Initializes a new FileStream with the specified and opening mode.
			 */		
            FileStream(const String& path, const std::ios::openmode& mode);

            /**
			 * Releases all resources being used by this FileStream.
			 */
            ~FileStream();

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
            FileStream(const FileStream& stream);
			FileStream& operator=(const FileStream& stream) = delete;

        private:		
            std::fstream       stream;
            std::ios::openmode mode;
        };
    }
}

#endif  /* FILESTREAM_HPP */
