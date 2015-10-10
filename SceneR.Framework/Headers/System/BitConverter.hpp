// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef BITCONVERTER_HPP
#define BITCONVERTER_HPP

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

#include <gsl.h>

namespace System
{
    /**
     * Converts base data types to an array of bytes, and an array of bytes to base data types.
     */
    class BitConverter
    {
    public:
        //
        // Summary:
        //     Returns a Boolean value converted from one std::uint8_t at a specified position in
        //     a std::uint8_t array.
        //
        // Parameters:
        //   value:
        //     An array of bytes.
        //
        //   startIndex:
        //     The starting position within value.
        //
        // Returns:
        //     true if the byte at startIndex in value is nonzero; otherwise, false.
        //
        // Exceptions:
        //   System.ArgumentNullException:
        //     value is null.
        //
        //   System.ArgumentOutOfRangeException:
        //     startIndex is less than zero or greater than the length of value minus 1.
        static bool to_boolean(const gsl::array_view<std::uint8_t>& value, const std::size_t& startIndex = 0)
        {
            return (value[startIndex] == 1);
        }

        //
        // Summary:
        //     Returns a double-precision floating point number converted from eight bytes
        //     at a specified position in a byte array.
        //
        // Parameters:
        //   value:
        //     An array of bytes.
        //
        //   startIndex:
        //     The starting position within value.
        //
        // Returns:
        //     A double precision floating point number formed by eight bytes beginning
        //     at startIndex.
        //
        // Exceptions:
        //   System.ArgumentException:
        //     startIndex is greater than or equal to the length of value minus 7, and is
        //     less than or equal to the length of value minus 1.
        //
        //   System.ArgumentNullException:
        //     value is null.
        //
        //   System.ArgumentOutOfRangeException:
        //     startIndex is less than zero or greater than the length of value minus 1.
        static double to_double(const gsl::array_view<std::uint8_t>& value, const std::size_t& startIndex = 0)
        {
            Expects(startIndex <= (value.size() - 1));

            return to_value<double>(value, startIndex);
        }

        //
        // Summary:
        //     Returns a 16-bit signed integer converted from two bytes at a specified position
        //     in a std::uint8_t array.
        //
        // Parameters:
        //   value:
        //     An array of bytes.
        //
        //   startIndex:
        //     The starting position within value.
        //
        // Returns:
        //     A 16-bit signed integer formed by two bytes beginning at startIndex.
        //
        // Exceptions:
        //   System.ArgumentException:
        //     startIndex equals the length of value minus 1.
        //
        //   System.ArgumentNullException:
        //     value is null.
        //
        //   System.ArgumentOutOfRangeException:
        //     startIndex is less than zero or greater than the length of value minus 1.
        static std::int16_t to_int16(const gsl::array_view<std::uint8_t>& value, const std::size_t& startIndex = 0)
        {
            return to_value<std::int16_t>(value, startIndex);
        }

        //
        // Summary:
        //     Returns a 32-bit signed integer converted from four bytes at a specified
        //     position in a byte array.
        //
        // Parameters:
        //   value:
        //     An array of bytes.
        //
        //   startIndex:
        //     The starting position within value.
        //
        // Returns:
        //     A 32-bit signed integer formed by four bytes beginning at startIndex.
        //
        // Exceptions:
        //   System.ArgumentException:
        //     startIndex is greater than or equal to the length of value minus 3, and is
        //     less than or equal to the length of value minus 1.
        //
        //   System.ArgumentNullException:
        //     value is null.
        //
        //   System.ArgumentOutOfRangeException:
        //     startIndex is less than zero or greater than the length of value minus 1.
        static std::int32_t to_int32(const gsl::array_view<std::uint8_t>& value, const std::size_t& startIndex = 0)
        {
            return to_value<std::int32_t>(value, startIndex);
        }

        //
        // Summary:
        //     Returns a 64-bit signed integer converted from eight bytes at a specified
        //     position in a byte array.
        //
        // Parameters:
        //   value:
        //     An array of bytes.
        //
        //   startIndex:
        //     The starting position within value.
        //
        // Returns:
        //     A 64-bit signed integer formed by eight bytes beginning at startIndex.
        //
        // Exceptions:
        //   System.ArgumentException:
        //     startIndex is greater than or equal to the length of value minus 7, and is
        //     less than or equal to the length of value minus 1.
        //
        //   System.ArgumentNullException:
        //     value is null.
        //
        //   System.ArgumentOutOfRangeException:
        //     startIndex is less than zero or greater than the length of value minus 1.
        static std::int64_t to_int64(const gsl::array_view<std::uint8_t>& value, const std::size_t& startIndex = 0)
        {
            return to_value<std::int64_t>(value, startIndex);
        }

        //
        // Summary:
        //     Returns a single-precision floating point number converted from four bytes
        //     at a specified position in a byte array.
        //
        // Parameters:
        //   value:
        //     An array of bytes.
        //
        //   startIndex:
        //     The starting position within value.
        //
        // Returns:
        //     A single-precision floating point number formed by four bytes beginning at
        //     startIndex.
        //
        // Exceptions:
        //   System.ArgumentException:
        //     startIndex is greater than or equal to the length of value minus 3, and is
        //     less than or equal to the length of value minus 1.
        //
        //   System.ArgumentNullException:
        //     value is null.
        //
        //   System.ArgumentOutOfRangeException:
        //     startIndex is less than zero or greater than the length of value minus 1.
        static float to_single(const gsl::array_view<std::uint8_t>& value, const std::size_t& startIndex = 0)
        {
            return to_value<float>(value, startIndex);
        }

        //
        // Summary:
        //     Returns a 16-bit unsigned integer converted from two bytes at a specified
        //     position in a byte array.
        //
        // Parameters:
        //   value:
        //     The array of bytes.
        //
        //   startIndex:
        //     The starting position within value.
        //
        // Returns:
        //     A 16-bit unsigned integer formed by two bytes beginning at startIndex.
        //
        // Exceptions:
        //   System.ArgumentException:
        //     startIndex equals the length of value minus 1.
        //
        //   System.ArgumentNullException:
        //     value is null.
        //
        //   System.ArgumentOutOfRangeException:
        //     startIndex is less than zero or greater than the length of value minus 1.
        static std::int16_t to_uint16(const gsl::array_view<std::uint8_t>& value, const std::size_t& startIndex = 0)
        {
            return to_value<std::int16_t>(value, startIndex);
        }

        //
        // Summary:
        //     Returns a 32-bit unsigned integer converted from four bytes at a specified
        //     position in a byte array.
        //
        // Parameters:
        //   value:
        //     An array of bytes.
        //
        //   startIndex:
        //     The starting position within value.
        //
        // Returns:
        //     A 32-bit unsigned integer formed by four bytes beginning at startIndex.
        //
        // Exceptions:
        //   System.ArgumentException:
        //     startIndex is greater than or equal to the length of value minus 3, and is
        //     less than or equal to the length of value minus 1.
        //
        //   System.ArgumentNullException:
        //     value is null.
        //
        //   System.ArgumentOutOfRangeException:
        //     startIndex is less than zero or greater than the length of value minus 1.
        static std::int32_t to_uint32(const gsl::array_view<std::uint8_t>& value, const std::size_t& startIndex = 0)
        {
            return to_value<std::int32_t>(value, startIndex);
        }

        //
        // Summary:
        //     Returns a 64-bit unsigned integer converted from eight bytes at a specified
        //     position in a byte array.
        //
        // Parameters:
        //   value:
        //     An array of bytes.
        //
        //   startIndex:
        //     The starting position within value.
        //
        // Returns:
        //     A 64-bit unsigned integer formed by the eight bytes beginning at startIndex.
        //
        // Exceptions:
        //   System.ArgumentException:
        //     startIndex is greater than or equal to the length of value minus 7, and is
        //     less than or equal to the length of value minus 1.
        //
        //   System.ArgumentNullException:
        //     value is null.
        //
        //   System.ArgumentOutOfRangeException:
        //     startIndex is less than zero or greater than the length of value minus 1.
        static std::int64_t to_uint64(const gsl::array_view<std::uint8_t>& value, const std::size_t& startIndex = 0)
        {
            return to_value<std::int64_t>(value, startIndex);
        }

    private:
        template <typename T>
        static T to_value(const gsl::array_view<std::uint8_t>& value, const std::size_t& startIndex)
        {
            Expects(startIndex <= (value.size() - 1));

            T            result = 0;
            std::size_t  shift  = 0;
            std::size_t  i      = startIndex;
            std::int32_t c      = sizeof(T);

            while (--c >= 0 && i <= value.size())
            {
                result += (value[i++] & 0xff) << shift;
                shift  += 8;
            }

            return result;
        }

    private:
        BitConverter() = delete;
        BitConverter(const BitConverter& converter) = delete;
        BitConverter& operator=(const BitConverter& pointer) = delete;
    };
}

#endif // BITCONVERTER_HPP
