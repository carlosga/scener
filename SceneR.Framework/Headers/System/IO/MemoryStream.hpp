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

#ifndef MEMORYSTREAM_HPP
#define MEMORYSTREAM_HPP

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
            MemoryStream(const std::vector<UByte>& buffer);

            /**
			 * Releases all resources being used by this MemoryStream.
			 */
            virtual ~MemoryStream();

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
            MemoryStream() = delete;
            MemoryStream(const MemoryStream& stream) = delete;
            MemoryStream& operator=(const MemoryStream& stream) = delete;

        private:
            std::stringstream  stream;
            std::ios::openmode mode;
        };
    }
}

#endif  /* MEMORYSTREAM_HPP */
