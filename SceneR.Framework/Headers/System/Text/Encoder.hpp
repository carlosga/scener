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

#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <vector>

#include <System/Core.hpp>

namespace System
{
    namespace Text
    {
        /**
         * Converts a set of characters into a sequence of bytes.
         */
        class Encoder
        {
        protected:
            /**
             * Initializes a new instance of the Encoder class.
             */
            Encoder();

            virtual ~Encoder();

        public:
            /**
             * Calculates the number of bytes produced by encoding a set of characters
             * starting at the specified character pointer.
             * A parameter indicates whether to clear the internal state of the encoder
             * after the calculation.
             */
            virtual System::Size GetByteCount(const System::Char*    chars
                                            , const System::Size&    count
                                            , const System::Boolean& flush) const;

            /**
             * When overridden in a derived class, calculates the number of bytes produced
             * by encoding a set of characters from the specified character array. A parameter
             * indicates whether to clear the internal state of the encoder after the calculation.
             */
            virtual System::Size GetByteCount(const std::vector<System::Char>& chars
                                            , const System::Size&              index
                                            , const System::Size&              count
                                            , const System::Boolean&           flush) const = 0;

            /**
             * When overridden in a derived class, encodes a set of characters starting
             * at the specified character pointer and any characters in the internal buffer
             * into a sequence of bytes that are stored starting at the specified byte pointer.
             * A parameter indicates whether to clear the internal state of the encoder
             * after the conversion.
             */
            virtual System::Size GetBytes(const System::Char*    chars
                                        , const System::Size&    charCount
                                        , System::UByte*         bytes
                                        , const System::Size&    byteCount
                                        , const System::Boolean& flush) const;

            /**
             * When overridden in a derived class, encodes a set of characters from the
             * specified character array and any characters in the internal buffer into
             * the specified byte array. A parameter indicates whether to clear the internal
             * state of the encoder after the conversion.
             */
            virtual System::Size GetBytes(const std::vector<System::Char>& chars
                                        , const System::Size&              charIndex
                                        , const System::Size&              charCount
                                        , std::vector<System::UByte>&      bytes
                                        , const System::Size&              byteIndex
                                        , const System::Boolean&           flush) const = 0;

            /**
             * When overridden in a derived class, sets the encoder back to its initial
             * state.
             */
            virtual void Reset();
        };
    }
}

#endif // ENCODER_HPP
