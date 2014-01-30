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

#ifndef BINARYREADER_HPP
#define BINARYREADER_HPP

#include <System/Core.hpp>
#include <System/Text/Encoding.hpp>
#include <memory>
#include <vector>

namespace System
{
    namespace IO
    {
        class Stream;
    }
}

namespace System
{
	namespace IO
	{
	    /**
	     * Reads primitive data types as binary values in a specific encoding.
	     */
	    class BinaryReader
	    {
	    public:
            /**
             * Initializes a new instance of the BinaryReader class with the given stream.
             */
            BinaryReader(Stream& stream);

            /**
             * Initializes a new instance of the BinaryReader class with the given stream.
             */
            BinaryReader(Stream& stream, const System::Text::Encoding& encoding);

	        /**
	         * Releases all resources being used by this BinaryReader.
	         */
	        virtual ~BinaryReader();

	    public:
	        /**
	         * Gets the underliying Stream.
	         */
	        Stream& BaseStream();

            /**
             * Closes the current reader and the underlying stream.
             */
            void Close();

            /**
             * Returns the next available character, or -1 if no more characters are available.
             */
            int PeekChar();

            /**
             * Reads the next character from the current stream.
             */
            Char ReadChar();

            /**
             * Reads a string from the current stream. The string is prefixed with the length.
             */
            String ReadString();

            /**
             * Reads a 7-bit encoded int
             */
            Int32 Read7BitEncodedInt();

            /**
             * Reads a Boolean value from the current stream.
             */
            Boolean ReadBoolean();

            /**
             * Reads the next byte from the current stream.
             */
            UByte ReadByte();

            /**
             * Reads the specified number of bytes from the underliying stream
             */
            std::vector<UByte> ReadBytes(const Size& count);

            /**
             * Reads a 2-byte signed integer from the current stream.
             */
            Int16 ReadInt16();

            /**
             * Reads a 2-byte unsigned integer from the current stream.
             */
            UInt16 ReadUInt16();

            /**
             * Reads a 4-byte signed integer from the current stream.
             */
            Int32 ReadInt32();

            /**
             * Reads a 4-byte unsigned integer from the current stream.
             */
            UInt32 ReadUInt32();

            /**
             * Reads a 8-byte signed integer from the current stream.
             */
            Int64 ReadInt64();

            /**
             * Reads a 8-byte unsigned integer from the current stream.
             */
            UInt64 ReadUInt64();

            /**
             * Reads a float value from the currently open stream.
             */
            Single ReadSingle();

            /**
             * Reads a double value from the currently open stream.
             */
            Double ReadDouble();

        private:
			BinaryReader(const BinaryReader& reader) = delete;
			BinaryReader& operator=(const BinaryReader& reader) = delete;
			
	    private:
            Stream&                       stream;
            const System::Text::Encoding& encoding;
	    };
	}
}

#endif  /* BINARYREADER_HPP */
