// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef ENCODING_HPP
#define ENCODING_HPP

#include <vector>

#include <System/Core.hpp>

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
            static const Encoding& UTF8;

        public:
            /**
             * Converts an entire byte array from one encoding to another.
             */
            static std::vector<System::UByte> Convert(const Encoding&                   srcEncoding
                                                    , const Encoding&                   dstEncoding
                                                    , const std::vector<System::UByte>& bytes);

            /*
             * Converts a range of bytes in a byte array from one encoding to another.
             */
            static std::vector<System::UByte> Convert(const Encoding&                   srcEncoding
                                                    , const Encoding&                   dstEncoding
                                                    , const std::vector<System::UByte>& bytes
                                                    , const System::Size&               index
                                                    , const System::Size&               count);

            /**
             * Converts a UTF-16 encoded string to a regular UTF-8 encoded string.
             */
            static std::string Convert(const String& source);

            /**
             * Converts a UTF-8 encoded string to a regular UTF-16 encoded string.
             */
            static System::String Convert(const std::string& source);

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
            virtual const System::String EncodingName() const = 0;

            /**
             * When overridden in a derived class, gets a value indicating whether the current
             * encoding is read-only.
             */
            bool IsReadOnly() const;

            /**
             * When overridden in a derived class, gets a value indicating whether the current
             * encoding uses single-System::UByte code points.
             */
            virtual bool IsSingleByte() const = 0;

            /**
             * Calculates the number of bytes produced by encoding all
             * the characters in the specified character array.
             */
            virtual System::Size GetByteCount(const std::vector<char16_t>& chars) const;

            /**
             * Calculates the number of bytes produced by encoding the characters in the specified string.
             */
            virtual System::Size GetByteCount(const System::String& s) const;

            /**
             * Calculates the number of bytes produced by encoding a set of characters
             * starting at the specified character pointer.
             */
            virtual System::Size GetByteCount(const char16_t* chars, const System::Size& count) const;

            /**
             * When overridden in a derived class, calculates the number of bytes produced
             * by encoding a set of characters from the specified character array.
             */
            virtual System::Size GetByteCount(const std::vector<char16_t>& chars
                                            , const System::Size&          index
                                            , const System::Size&          count) const = 0;

            /**
             * Encodes all the characters in the specified character array into a sequence of bytes.
             */
            virtual std::vector<System::UByte> GetBytes(const std::vector<char16_t>& chars) const;

            /**
             * Encodes all the characters in the specified string into a sequence of bytes.
             */
            virtual std::vector<System::UByte> GetBytes(const System::String& s) const;

            /**
             * Encodes a set of characters from the specified character array into a sequence of bytes.
             */
            virtual std::vector<System::UByte> GetBytes(const std::vector<char16_t>& chars
                                                      , const System::Size&          index
                                                      , const System::Size&          count) const;

            /**
             * Encodes a set of characters starting at the specified
             * character pointer into a sequence of bytes that are stored
             * starting at the specified byte pointer.
             */
            virtual System::Size GetBytes(const char16_t*     chars
                                        , const System::Size& charCount
                                        , System::UByte*      bytes
                                        , const System::Size& byteCount) const;

            /**
             * When overridden in a derived class, encodes a set of characters from the
             * specified character array into the specified byte array.
             */
            virtual System::Size GetBytes(const std::vector<char16_t>& chars
                                        , const System::Size&          charIndex
                                        , const System::Size&          charCount
                                        , std::vector<System::UByte>&  bytes
                                        , const System::Size&          byteIndex) const = 0;

            /**
             * Encodes a set of characters from the specified string into the specified byte array.
             */
            virtual System::Size GetBytes(const System::String&       s
                                        , const System::Size&         charIndex
                                        , const System::Size&         charCount
                                        , std::vector<System::UByte>& bytes
                                        , const System::Size&         byteIndex) const;

            /**
             * Calculates the number of characters produced by decoding
             * all the bytesin the specified byte array.
             */
            virtual System::Size GetCharCount(const std::vector<System::UByte>& bytes) const;

            /**
             * Calculates the number of characters produced by decoding a sequence
             * of bytes starting at the specified byte pointer.
             */
            virtual System::Size GetCharCount(const System::UByte* bytes, const System::Size& count) const;

            /**
             * When overridden in a derived class, calculates the number of characters produced
             * by decoding a sequence of bytes from the specified byte array.
             */
            virtual System::Size GetCharCount(const std::vector<System::UByte>& bytes
                                            , const System::Size&               index
                                            , const System::Size&               count) const = 0;

            /**
             * Decodes all the bytes in the specified byte array into a set of characters.
             */
            virtual std::vector<char16_t> GetChars(const std::vector<System::UByte>& bytes) const;

            /**
             * Decodes a sequence of bytes from the specified byte array into a set of characters.
             */
            virtual std::vector<char16_t> GetChars(const std::vector<System::UByte>& bytes
                                                 , const System::Size&               index
                                                 , const System::Size&               count) const;

            /**
             * Decodes a sequence of bytes starting at the specified byte pointer
             * into a set of characters that are stored starting at the specified
             * character pointer.
             */
            virtual System::Size GetChars(const System::UByte* bytes
                                        , const System::Size&  byteCount
                                        , char16_t*            chars
                                        , const System::Size&  charCount) const;

            /**
             * When overridden in a derived class, decodes a sequence of bytes from the
             * specified System::UByte array into the specified character array.
             */
            virtual System::Size GetChars(const std::vector<System::UByte>& bytes
                                        , const System::Size&               byteIndex
                                        , const System::Size&               byteCount
                                        , std::vector<char16_t>&            chars
                                        , const System::Size&               charIndex) const = 0;

            /**
             * When overridden in a derived class, obtains a decoder that converts an encoded
             * sequence of bytes into a sequence of characters.
             */
            virtual const Decoder& GetDecoder() const = 0;

            /**
             * When overridden in a derived class, obtains an encoder that converts a sequence
             * of Unicode characters into an encoded sequence of bytes.
             */
            virtual const Encoder& GetEncoder() const = 0;

            /**
             * When overridden in a derived class, calculates the maximum number of bytes
             * produced by encoding the specified number of characters.
             */
            virtual System::Size GetMaxByteCount(const System::Size& charCount) = 0;

            /**
             * When overridden in a derived class, calculates the maximum number of characters
             * produced by decoding the specified number of bytes.
             */
            virtual System::Size GetMaxCharCount(const System::Size& byteCount) = 0;

            /**
             * When overridden in a derived class, returns a sequence of bytes that specifies
             * the encoding used.
             */
            virtual std::vector<System::UByte> GetPreamble() const = 0;

            /**
             * Decodes all the bytes in the specified byte array into a string.
             */
            virtual System::String GetString(const std::vector<System::UByte>& bytes) const;

            /**
             * Decodes a sequence of bytes from the specified byte array into a string.
             */
            virtual System::String GetString(const std::vector<System::UByte>& bytes
                                           , const System::Size&               index
                                           , const System::Size&               count) const;
        };
    }
}

#endif // ENCODING_HPP
