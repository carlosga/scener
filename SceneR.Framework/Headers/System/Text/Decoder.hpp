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

#ifndef DECODER_HPP
#define DECODER_HPP

#include <System/Core.hpp>
#include <vector>

namespace System
{
    namespace Text
    {
        /**
         * Converts a sequence of encoded bytes into a set of characters.
         */
        class Decoder
        {
        protected:
            /**
             * Initializes a new instance of the Decoder class.
             */
            Decoder();

            /**
             * Releases all resources being used by this Decoder.
             */
            virtual ~Decoder();

        public:
            /**
             * Calculates the number of characters produced by decoding a sequence of bytes
             * starting at the specified byte pointer. A parameter indicates whether to clear
             * the internal state of the decoder after the calculation.
             */
            virtual System::Size GetCharCount(const System::UByte*   bytes
                                            , const System::Size&    count
                                            , const System::Boolean& flush) const;

            /**
             * When overridden in a derived class, calculates the number of characters produced
             * by decoding a sequence of bytes from the specified byte array.
             */
            virtual System::Size GetCharCount(const std::vector<System::UByte>& bytes
                                            , const System::Size&               index
                                            , const System::Size&               count) const = 0;

            /**
             * Calculates the number of characters produced by decoding a sequence of bytes
             * from the specified byte array. A parameter indicates whether to clear the
             * internal state of the decoder after the calculation.
             */
            virtual System::Size GetCharCount(const std::vector<System::UByte>& bytes
                                            , const System::Size&               index
                                            , const System::Size&               count
                                            , const System::Boolean&            flush) const;

            /**
             * Decodes a sequence of bytes starting at the specified byte pointer and
             * any bytes in the internal buffer into a set of characters that are
             * stored starting at the specified character pointer.
             * A parameter indicates whether to clear the internal state of the decoder
             * after the conversion.
             */
            virtual System::Size GetChars(const System::UByte*   bytes
                                        , const System::Size&    byteCount
                                        , System::Char*          chars
                                        , const System::Size&    charCount
                                        , const System::Boolean& flush) const;

            /**
             * When overridden in a derived class, decodes a sequence of bytes from the
             * specified byte array and any bytes in the internal buffer into the specified
             * character array.
             */
            virtual System::Size GetChars(const std::vector<System::UByte>& bytes
                                        , const System::Size&               byteIndex
                                        , const System::Size&               byteCount
                                        , std::vector<System::Char>&        chars
                                        , const System::Size&               charIndex) const = 0;

            /**
             * Decodes a sequence of bytes from the specified byte array and any bytes
             * in the internal buffer into the specified character array.
             * A parameter indicates whether to clear the internal state of the decoder after the conversion.
             */
            virtual System::Size GetChars(const std::vector<System::UByte>& bytes
                                        , const System::Size&               byteIndex
                                        , const System::Size&               byteCount
                                        , std::vector<System::Char>&        chars
                                        , const System::Size&               charIndex
                                        , const System::Boolean&            flush) const;

            /**
             * Sets the encoder back to its initial state.
             */
            virtual void Reset() = 0;
        };
    }
}

#endif // DECODER_HPP
