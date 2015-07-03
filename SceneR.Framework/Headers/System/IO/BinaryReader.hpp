// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef BINARYREADER_HPP
#define BINARYREADER_HPP

#include <memory>
#include <vector>

#include <System/Text/Encoding.hpp>

namespace System
{
    namespace IO
    {
        class Stream;

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
            ~BinaryReader();

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
            Int32 PeekChar();

            /**
             * Reads the next character from the current stream.
             */
            char16_t ReadChar();

            /**
             * Reads a string from the current stream. The string is prefixed with the length.
             */
            String ReadString();

            /**
             * Reads a 7-bit encoded unsigned int
             */
            UInt32 Read7BitEncodedInt();

            /**
             * Reads a Boolean value from the current stream.
             */
            bool ReadBoolean();

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

        public:
            BinaryReader() = delete;
            BinaryReader(const BinaryReader& reader) = delete;
            BinaryReader& operator=(const BinaryReader& reader) = delete;

        private:
            Stream&                       stream;
            const System::Text::Encoding& encoding;
        };
    }
}

#endif  /* BINARYREADER_HPP */
