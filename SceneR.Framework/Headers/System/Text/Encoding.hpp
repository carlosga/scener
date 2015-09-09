// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SYSTEM_TEXT_ENCODING_HPP
#define SYSTEM_TEXT_ENCODING_HPP

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace System
{
    namespace Text
    {
        class Decoder;
        class Encoder;
    }
}

namespace System
{
    namespace Text
    {
        /**
         * Represents a character encoding.
         */
        class Encoding
        {
        public:
            /**
             * Gets an encoding for the UTF-8 format.
             */
            static const Encoding& utf8;

        public:
            /**
             * Converts an entire byte array from one encoding to another.
             */
            static std::vector<std::uint8_t> convert(const Encoding&                  srcEncoding
                                                   , const Encoding&                  dstEncoding
                                                   , const std::vector<std::uint8_t>& bytes);

            /*
             * Converts a range of bytes in a byte array from one encoding to another.
             */
            static std::vector<std::uint8_t> convert(const Encoding&                  srcEncoding
                                                   , const Encoding&                  dstEncoding
                                                   , const std::vector<std::uint8_t>& bytes
                                                   , const std::size_t&               index
                                                   , const std::size_t&               count);

            /**
             * Converts a UTF-16 encoded string to a regular UTF-8 encoded string.
             */
            static std::string convert(const std::u16string& source);

            /**
             * Converts a UTF-8 encoded string to a regular UTF-16 encoded string.
             */
            static std::u16string convert(const std::string& source);

        protected:

            /**
             * Initializes a new instance of the System.Text.Encoding class.
             */
            Encoding();

            /**
             * Releases all resources being used by this Encoding.
             */
            virtual ~Encoding();

        public:
            /**
             * When overridden in a derived class, gets the human-readable description of
             * the current encoding.
             */
            virtual std::u16string encoding_name() const = 0;

            /**
             * When overridden in a derived class, gets a value indicating whether the current
             * encoding is read-only.
             */
            bool is_read_only() const;

            /**
             * When overridden in a derived class, gets a value indicating whether the current
             * encoding uses single-std::uint8_t code points.
             */
            virtual bool is_single_byte() const = 0;

            /**
             * Calculates the number of bytes produced by encoding all
             * the characters in the specified character array.
             */
            std::size_t get_byte_count(const std::vector<char16_t>& chars) const;

            /**
             * Calculates the number of bytes produced by encoding the characters in the specified string.
             */
            std::size_t get_byte_count(const std::u16string& s) const;

            /**
             * Calculates the number of bytes produced by encoding a set of characters
             * starting at the specified character pointer.
             */
            std::size_t get_byte_count(const char16_t* chars, const std::size_t& count) const;

            /**
             * When overridden in a derived class, calculates the number of bytes produced
             * by encoding a set of characters from the specified character array.
             */
            virtual std::size_t get_byte_count(const std::vector<char16_t>& chars
                                             , const std::size_t&           index
                                             , const std::size_t&           count) const = 0;

            /**
             * Encodes all the characters in the specified character array into a sequence of bytes.
             */
            std::vector<std::uint8_t> get_bytes(const std::vector<char16_t>& chars) const;

            /**
             * Encodes all the characters in the specified string into a sequence of bytes.
             */
            std::vector<std::uint8_t> get_bytes(const std::u16string& s) const;

            /**
             * Encodes a set of characters from the specified character array into a sequence of bytes.
             */
            std::vector<std::uint8_t> get_bytes(const std::vector<char16_t>& chars
                                              , const std::size_t&           index
                                              , const std::size_t&           count) const;

            /**
             * Encodes a set of characters starting at the specified
             * character pointer into a sequence of bytes that are stored
             * starting at the specified byte pointer.
             */
            std::size_t get_bytes(const char16_t*    chars
                                , const std::size_t& charCount
                                , std::uint8_t*      bytes
                                , const std::size_t& byteCount) const;

            /**
             * When overridden in a derived class, encodes a set of characters from the
             * specified character array into the specified byte array.
             */
            virtual std::size_t get_bytes(const std::vector<char16_t>& chars
                                        , const std::size_t&           charIndex
                                        , const std::size_t&           charCount
                                        , std::vector<std::uint8_t>&   bytes
                                        , const std::size_t&           byteIndex) const = 0;

            /**
             * Encodes a set of characters from the specified string into the specified byte array.
             */
            std::size_t get_bytes(const std::u16string&      s
                                , const std::size_t&         charIndex
                                , const std::size_t&         charCount
                                , std::vector<std::uint8_t>& bytes
                                , const std::size_t&         byteIndex) const;

            /**
             * Calculates the number of characters produced by decoding
             * all the bytesin the specified byte array.
             */
            std::size_t get_char_count(const std::vector<std::uint8_t>& bytes) const;

            /**
             * Calculates the number of characters produced by decoding a sequence
             * of bytes starting at the specified byte pointer.
             */
            std::size_t get_char_count(const std::uint8_t* bytes, const std::size_t& count) const;

            /**
             * When overridden in a derived class, calculates the number of characters produced
             * by decoding a sequence of bytes from the specified byte array.
             */
            virtual std::size_t get_char_count(const std::vector<std::uint8_t>& bytes
                                             , const std::size_t&               index
                                             , const std::size_t&               count) const = 0;

            /**
             * Decodes all the bytes in the specified byte array into a set of characters.
             */
            std::vector<char16_t> get_chars(const std::vector<std::uint8_t>& bytes) const;

            /**
             * Decodes a sequence of bytes from the specified byte array into a set of characters.
             */
            std::vector<char16_t> get_chars(const std::vector<std::uint8_t>& bytes
                                          , const std::size_t&               index
                                          , const std::size_t&               count) const;

            /**
             * Decodes a sequence of bytes starting at the specified byte pointer
             * into a set of characters that are stored starting at the specified
             * character pointer.
             */
            std::size_t get_chars(const std::uint8_t* bytes
                                , const std::size_t&  byteCount
                                , char16_t*           chars
                                , const std::size_t&  charCount) const;

            /**
             * When overridden in a derived class, decodes a sequence of bytes from the
             * specified std::uint8_t array into the specified character array.
             */
            virtual std::size_t get_chars(const std::vector<std::uint8_t>& bytes
                                        , const std::size_t&               byteIndex
                                        , const std::size_t&               byteCount
                                        , std::vector<char16_t>&           chars
                                        , const std::size_t&               charIndex) const = 0;

            /**
             * When overridden in a derived class, obtains a decoder that converts an encoded
             * sequence of bytes into a sequence of characters.
             */
            virtual const Decoder& get_decoder() const = 0;

            /**
             * When overridden in a derived class, obtains an encoder that converts a sequence
             * of Unicode characters into an encoded sequence of bytes.
             */
            virtual const Encoder& get_encoder() const = 0;

            /**
             * When overridden in a derived class, calculates the maximum number of bytes
             * produced by encoding the specified number of characters.
             */
            virtual std::size_t get_max_byte_count(const std::size_t& charCount) = 0;

            /**
             * When overridden in a derived class, calculates theB maximum number of characters
             * produced by decoding the specified number of bytes.
             */
            virtual std::size_t get_max_char_count(const std::size_t& byteCount) = 0;

            /**
             * When overridden in a derived class, returns a sequence of bytes that specifies
             * the encoding used.
             */
            virtual std::vector<std::uint8_t> get_preamble() const = 0;

            /**
             * Decodes all the bytes in the specified byte array into a string.
             */
            std::u16string get_string(const std::vector<std::uint8_t>& bytes) const;

            /**
             * Decodes a sequence of bytes from the specified byte array into a string.
             */
            std::u16string get_string(const std::vector<std::uint8_t>& bytes
                                    , const std::size_t&               index
                                    , const std::size_t&               count) const;
        };
    }
}

#endif  // SYSTEM_TEXT_ENCODING_HPP
