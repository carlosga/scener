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

#ifndef STREAM_HPP
#define STREAM_HPP

#include <System/Core.hpp>
#include <iostream>

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
            virtual ~Stream()
            {
            };

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
            virtual System::Size Position() = 0;

            /**
             * Returns the length in bytes of the stream.
             */
            virtual System::Size Length() = 0;

            /**
             * Closes the current stream
             */
            virtual void Close() = 0;

            /**
             * Reads a byte from the stream or returns -1 if at the end of the stream.
             */
            virtual System::UByte ReadByte() = 0;

            /**
             * Reads a sequence of bytes from the current stream.
             */
            virtual Size Read(char* buffer, const System::Size& offset, const System::Size& count) = 0;

            /**
             * Sets the position within the current stream.
             */
            virtual System::Size Seek(const Size& offset, const std::ios::seekdir& origin) = 0;
        };
    }
}

#endif  /* STREAM_HPP */
