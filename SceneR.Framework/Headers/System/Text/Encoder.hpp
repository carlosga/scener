// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

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

            /**
             * Releases all resources being used by this Encoder.
             */
            virtual ~Encoder();

        public:
            /**
             * Calculates the number of bytes produced by encoding a set of characters
             * starting at the specified character pointer.
             * A parameter indicates whether to clear the internal state of the encoder
             * after the calculation.
             */
            virtual std::size_t GetByteCount(const char16_t*    chars
                                           , const std::size_t& count
                                           , const bool&        flush) const;

            /**
             * When overridden in a derived class, calculates the number of bytes produced
             * by encoding a set of characters from the specified character array. A parameter
             * indicates whether to clear the internal state of the encoder after the calculation.
             */
            virtual std::size_t GetByteCount(const std::vector<char16_t>& chars
                                           , const std::size_t&           index
                                           , const std::size_t&           count
                                           , const bool&                  flush) const = 0;

            /**
             * When overridden in a derived class, encodes a set of characters starting
             * at the specified character pointer and any characters in the internal buffer
             * into a sequence of bytes that are stored starting at the specified byte pointer.
             * A parameter indicates whether to clear the internal state of the encoder
             * after the conversion.
             */
            virtual std::size_t GetBytes(const char16_t*    chars
                                       , const std::size_t& charCount
                                       , std::uint8_t*      bytes
                                       , const std::size_t& byteCount
                                       , const bool&        flush) const;

            /**
             * When overridden in a derived class, encodes a set of characters from the
             * specified character array and any characters in the internal buffer into
             * the specified byte array. A parameter indicates whether to clear the internal
             * state of the encoder after the conversion.
             */
            virtual std::size_t GetBytes(const std::vector<char16_t>& chars
                                       , const std::size_t&           charIndex
                                       , const std::size_t&           charCount
                                       , std::vector<std::uint8_t>&   bytes
                                       , const std::size_t&           byteIndex
                                       , const bool&                  flush) const = 0;

            /**
             * When overridden in a derived class, sets the encoder back to its initial
             * state.
             */
            virtual void Reset();
        };
    }
}

#endif // ENCODER_HPP
