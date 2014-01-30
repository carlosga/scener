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

#ifndef ENCODING_HPP
#define ENCODING_HPP

#include <System/Core.hpp>
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
             * @returns a System::Text::Encoding for the UTF-8 format.
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
                                                    , const System::UInt32&             index
                                                    , const System::UInt32&             count);

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
            virtual System::UInt32 GetByteCount(const std::vector<Char>& chars) const;

            /**
             * Calculates the number of bytes produced by encoding the characters in the specified string.
             */
            virtual System::UInt32 GetByteCount(const System::String& s) const;

            /**
             * Calculates the number of bytes produced by encoding a set of characters
             * starting at the specified character pointer.
             */
            virtual System::UInt32 GetByteCount(const Char* chars, const System::UInt32& count) const;

            /**
             * When overridden in a derived class, calculates the number of bytes produced
             * by encoding a set of characters from the specified character array.
             */
            virtual System::UInt32 GetByteCount(const std::vector<Char>& chars
                                              , const System::UInt32&    index
                                              , const System::UInt32&    count) const = 0;

            /**
             * Encodes all the characters in the specified character array into a sequence of bytes.
             */
            virtual std::vector<System::UByte> GetBytes(const std::vector<Char>& chars) const;

            /**
             * Encodes all the characters in the specified string into a sequence of bytes.
             */
            virtual std::vector<System::UByte> GetBytes(const System::String& s) const;

            /**
             * Encodes a set of characters from the specified character array into a sequence of bytes.
             */
            virtual std::vector<System::UByte> GetBytes(const std::vector<Char>& chars
                                                      , const System::UInt32&    index
                                                      , const System::UInt32&    count) const;

            /**
             * Encodes a set of characters starting at the specified
             * character pointer into a sequence of bytes that are stored
             * starting at the specified byte pointer.
             */
            virtual System::UInt32 GetBytes(const Char*           chars
                                          , const System::UInt32& charCount
                                          , System::UByte*        bytes
                                          , const System::UInt32& byteCount) const;

            /**
             * When overridden in a derived class, encodes a set of characters from the
             * specified character array into the specified byte array.
             */
            virtual System::UInt32 GetBytes(const std::vector<Char>&     chars
                                          , const System::UInt32&        charIndex
                                          , const System::UInt32&        charCount
                                          , std::vector<System::UByte>&  bytes
                                          , const System::UInt32&        byteIndex) const = 0;

            /**
             * Encodes a set of characters from the specified string into the specified byte array.
             */
            virtual System::UInt32 GetBytes(const System::String&       s
                                          , const System::UInt32&       charIndex
                                          , const System::UInt32&       charCount
                                          , std::vector<System::UByte>& bytes
                                          , const System::UInt32&       byteIndex) const;


            /**
             * Calculates the number of characters produced by decoding
             * all the bytesin the specified byte array.
             */
            virtual System::UInt32 GetCharCount(const std::vector<System::UByte>& bytes) const;

            /**
             * Calculates the number of characters produced by decoding a sequence
             * of bytes starting at the specified byte pointer.
             */
            virtual System::UInt32 GetCharCount(const System::UByte* bytes, const System::UInt32& count) const;

            /**
             * When overridden in a derived class, calculates the number of characters produced
             * by decoding a sequence of bytes from the specified byte array.
             */
            virtual System::UInt32 GetCharCount(const std::vector<System::UByte>& bytes
                                              , const System::UInt32&             index
                                              , const System::UInt32&             count) const = 0;

            /**
             * Decodes all the bytes in the specified byte array into a set of characters.
             */
            virtual std::vector<Char> GetChars(const std::vector<System::UByte>& bytes) const;

            /**
             * Decodes a sequence of bytes from the specified byte array into a set of characters.
             */
            virtual std::vector<Char> GetChars(const std::vector<System::UByte>& bytes
                                                 , const System::UInt32&         index
                                                 , const System::UInt32&         count) const;

            /**
             * Decodes a sequence of bytes starting at the specified byte pointer
             * into a set of characters that are stored starting at the specified
             * character pointer.
             */
            virtual System::UInt32 GetChars(const System::UByte*  bytes
                                          , const System::UInt32& byteCount
                                          , Char*                 chars
                                          , const System::UInt32& charCount) const;

            /**
             * When overridden in a derived class, decodes a sequence of bytes from the
             * specified System::UByte array into the specified character array.
             */
            virtual System::UInt32 GetChars(const std::vector<System::UByte>& bytes
                                          , const System::UInt32&             byteIndex
                                          , const System::UInt32&             byteCount
                                          , std::vector<Char>&                chars
                                          , const System::UInt32&             charIndex) const = 0;

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
            virtual System::UInt32 GetMaxByteCount(const System::UInt32& charCount) = 0;

            /**
             * When overridden in a derived class, calculates the maximum number of characters
             * produced by decoding the specified number of bytes.
             */
            virtual System::UInt32 GetMaxCharCount(const System::UInt32& byteCount) = 0;

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
                                           , const System::UInt32&             index
                                           , const System::UInt32&             count) const;
        };
    }
}

#endif // ENCODING_HPP
