// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_IO_BINARYREADER_HPP
#define SCENER_IO_BINARYREADER_HPP

#include <cstdint>
#include <vector>

#include "SceneR/Text/Encoding.hpp"

namespace SceneR
{
    namespace IO
    {
        class Stream;

        /**
         * Reads primitive data types as binary values in a specific encoding.
         */
        class BinaryReader final
        {
        public:
            /**
             * Initializes a new instance of the BinaryReader class with the given stream.
             */
            BinaryReader(Stream& stream, const SceneR::Text::Encoding& encoding = SceneR::Text::Encoding::utf8);

            /**
             * Releases all resources being used by this BinaryReader.
             */
            ~BinaryReader();

        public:
            /**
             * Gets the underliying Stream.
             */
            Stream& base_stream();

            /**
             * Closes the current reader and the underlying stream.
             */
            void close();

            /**
             * Reads data from the current stream.
             */
            template <typename T>
            T read();

            /**
             * Returns the next available character, or -1 if no more characters are available.
             */
            std::int32_t peek_char();

            /**
             * Reads a 7-bit encoded unsigned int
             */
            std::uint32_t read_7_bit_encoded_int();

            /**
             * Reads the specified number of bytes from the underliying stream
             */
            std::vector<std::uint8_t> read_bytes(const std::size_t& count);

        public:
            BinaryReader() = delete;
            BinaryReader(const BinaryReader& reader) = delete;
            BinaryReader& operator=(const BinaryReader& reader) = delete;

        private:
            Stream&                       _stream;
            const SceneR::Text::Encoding& _encoding;
        };
    }
}

#endif // SCENER_IO_BINARYREADER_HPP
