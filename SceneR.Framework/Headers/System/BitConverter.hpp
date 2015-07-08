// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef BITCONVERTER_HPP
#define BITCONVERTER_HPP

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace System
{
    /**
     * Converts base data types to an array of bytes, and an array of bytes to base data types.
     */
    class BitConverter
    {
    public:
        // Summary:
        //     Converts the specified double-precision floating point number to a 64-bit
        //     signed integer.
        //
        // Parameters:
        //   value:
        //     The number to convert.
        //
        // Returns:
        //     A 64-bit signed integer whose value is equivalent to value.
        static std::int64_t DoubleToInt64Bits(const double& value)
        {
            return static_cast<std::int64_t>(value);
        }

        //
        // Summary:
        //     Converts the specified 64-bit signed integer to a double-precision floating
        //     point number.
        //
        // Parameters:
        //   value:
        //     The number to convert.
        //
        // Returns:
        //     A double-precision floating point number whose value is equivalent to value.
        static double Int64BitsToDouble(const std::int64_t& value)
        {
            return static_cast<double>(value);
        }

        //
        // Summary:
        //     Returns the specified Boolean value as an array of bytes.
        //
        // Parameters:
        //   value:
        //     A Boolean value.
        //
        // Returns:
        //     An array of bytes with length 1.
        static std::vector<std::uint8_t> GetBytes(const bool& value)
        {
            return GetBytes<bool>(value);
        }

        //
        // Summary:
        //     Returns the specified Unicode char16_tacter value as an array of bytes.
        //
        // Parameters:
        //   value:
        //     A char16_tacter to convert.
        //
        // Returns:
        //     An array of bytes with length 2.
        static std::vector<std::uint8_t> GetBytes(const char16_t& value)
        {
            return GetBytes<std::int16_t>(static_cast<std::int16_t>(value));
        }

        //
        // Summary:
        //     Returns the specified double-precision floating point value as an array of
        //     bytes.
        //
        // Parameters:
        //   value:
        //     The number to convert.
        //
        // Returns:
        //     An array of bytes with length 8.
        static std::vector<std::uint8_t> GetBytes(const double& value)
        {
            return GetBytes<std::int64_t>(static_cast<std::int64_t>(value));
        }

        //
        // Summary:
        //     Returns the specified single-precision floating point value as an array of
        //     bytes.
        //
        // Parameters:
        //   value:
        //     The number to convert.
        //
        // Returns:
        //     An array of bytes with length 4.
        static std::vector<std::uint8_t> GetBytes(const float& value)
        {
            return GetBytes<std::int32_t>(static_cast<std::int32_t>(value));
        }

        //
        // Summary:
        //     Returns the specified 32-bit signed integer value as an array of bytes.
        //
        // Parameters:
        //   value:
        //     The number to convert.
        //
        // Returns:
        //     An array of bytes with length 4.
        static std::vector<std::uint8_t> GetBytes(const std::int32_t& value)
        {
            return GetBytes<std::int32_t>(value);
        }

        //
        // Summary:
        //     Returns the specified 64-bit signed integer value as an array of bytes.
        //
        // Parameters:
        //   value:
        //     The number to convert.
        //
        // Returns:
        //     An array of bytes with length 8.
        static std::vector<std::uint8_t> GetBytes(const std::int64_t& value)
        {
            return GetBytes<std::int64_t>(value);
        }

        //
        // Summary:
        //     Returns the specified 16-bit signed integer value as an array of bytes.
        //
        // Parameters:
        //   value:
        //     The number to convert.
        //
        // Returns:
        //     An array of bytes with length 2.
        static std::vector<std::uint8_t> GetBytes(const std::int16_t& value)
        {
            return GetBytes<std::int16_t>(value);
        }

        //
        // Summary:
        //     Returns the specified 32-bit unsigned integer value as an array of bytes.
        //
        // Parameters:
        //   value:
        //     The number to convert.
        //
        // Returns:
        //     An array of bytes with length 4.
        static std::vector<std::uint8_t> GetBytes(const std::int32_t& value)
        {
            return GetBytes<std::int32_t>(value);
        }

        //
        // Summary:
        //     Returns the specified 64-bit unsigned integer value as an array of bytes.
        //
        // Parameters:
        //   value:
        //     The number to convert.
        //
        // Returns:
        //     An array of bytes with length 8.
        static std::vector<std::uint8_t> GetBytes(const std::int64_t& value)
        {
            return GetBytes<std::int64_t>(value);
        }

        //
        // Summary:
        //     Returns the specified 16-bit unsigned integer value as an array of bytes.
        //
        // Parameters:
        //   value:
        //     The number to convert.
        //
        // Returns:
        //     An array of bytes with length 2.
        static std::vector<std::uint8_t> GetBytes(const std::int16_t& value)
        {
            return GetBytes<std::int16_t>(value);
        }

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
        static bool ToBoolean(const std::vector<std::uint8_t>& value, const std::size_t& startIndex)
        {
            assert(startIndex <= (value.size() - 1));

            return (value[startIndex] == 1);
        }

        //
        // Summary:
        //     Returns a Unicode char16_tacter converted from two bytes at a specified position
        //     in a std::uint8_t array.
        //
        // Parameters:
        //   value:
        //     An array.
        //
        //   startIndex:
        //     The starting position within value.
        //
        // Returns:
        //     A char16_tacter formed by two bytes beginning at startIndex.
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
        static char16_t ToChar(const std::vector<std::uint8_t>& value, const std::size_t& startIndex)
        {
            throw std::runtime_error("Not implemented");
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
        static double ToDouble(const std::vector<std::uint8_t>& value, const std::size_t& startIndex)
        {
            return ToValue<double>(value, startIndex);
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
        static std::int16_t ToInt16(const std::vector<std::uint8_t>& value, const std::size_t& startIndex)
        {
            return ToValue<std::int16_t>(value, startIndex);
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
        static std::int32_t ToInt32(const std::vector<std::uint8_t>& value, const std::size_t& startIndex)
        {
            return ToValue<std::int32_t>(value, startIndex);
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
        static std::int64_t ToInt64(const std::vector<std::uint8_t>& value, const std::size_t& startIndex)
        {
            return ToValue<std::int64_t>(value, startIndex);
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
        static float ToSingle(const std::vector<std::uint8_t>& value, const std::size_t& startIndex)
        {
            return ToValue<float>(value, startIndex);
        }

        //
        // Summary:
        //     Converts the numeric value of each element of a specified array of bytes
        //     to its equivalent hexadecimal string representation.
        //
        // Parameters:
        //   value:
        //     An array of bytes.
        //
        // Returns:
        //     A System.String of hexadecimal pairs separated by hyphens, where each pair
        //     represents the corresponding element in value; for example, "7F-2C-4A".
        //
        // Exceptions:
        //   System.ArgumentNullException:
        //     value is null.
        static std::u16string ToString(const std::vector<std::uint8_t>& value)
        {
            throw std::runtime_error("Not implemented");
        }

        //
        // Summary:
        //     Converts the numeric value of each element of a specified subarray of bytes
        //     to its equivalent hexadecimal string representation.
        //
        // Parameters:
        //   value:
        //     An array of bytes.
        //
        //   startIndex:
        //     The starting position within value.
        //
        // Returns:
        //     A System.String of hexadecimal pairs separated by hyphens, where each pair
        //     represents the corresponding element in a subarray of value; for example,
        //     "7F-2C-4A".
        //
        // Exceptions:
        //   System.ArgumentNullException:
        //     value is null.
        //
        //   System.ArgumentOutOfRangeException:
        //     startIndex is less than zero or greater than the length of value minus 1.
        static std::u16string ToString(const std::vector<std::uint8_t>& value, const std::size_t& startIndex)
        {
            throw std::runtime_error("Not implemented");
        }

        //
        // Summary:
        //     Converts the numeric value of each element of a specified subarray of bytes
        //     to its equivalent hexadecimal string representation.
        //
        // Parameters:
        //   value:
        //     An array of bytes.
        //
        //   startIndex:
        //     The starting position within value.
        //
        //   length:
        //     The number of array elements in value to convert.
        //
        // Returns:
        //     A System.String of hexadecimal pairs separated by hyphens, where each pair
        //     represents the corresponding element in a subarray of value; for example,
        //     "7F-2C-4A".
        //
        // Exceptions:
        //   System.ArgumentNullException:
        //     value is null.
        //
        //   System.ArgumentOutOfRangeException:
        //     startIndex or length is less than zero.  -or- startIndex is greater than
        //     zero and is greater than or equal to the length of value.
        //
        //   System.ArgumentException:
        //     The combination of startIndex and length does not specify a position within
        //     value; that is, the startIndex parameter is greater than the length of value
        //     minus the length parameter.
        static std::u16string ToString(const std::vector<std::uint8_t>& value, const std::size_t& startIndex, std::size_t length)
        {
            throw std::runtime_error("Not implemented");
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
        static std::int16_t ToUInt16(const std::vector<std::uint8_t>& value, const std::size_t& startIndex)
        {
            return ToValue<std::int16_t>(value, startIndex);
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
        static std::int32_t ToUInt32(const std::vector<std::uint8_t>& value, const std::size_t& startIndex)
        {
            return ToValue<std::int32_t>(value, startIndex);
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
        static std::int64_t ToUInt64(const std::vector<std::uint8_t>& value, const std::size_t& startIndex)
        {
            return ToValue<std::int64_t>(value, startIndex);
        }

    private:
        template <typename T>
        static T ToValue(const std::vector<std::uint8_t>& value, const std::size_t& startIndex)
        {
            assert(startIndex <= (value.size() - 1));

            T   result = 0;
            int shift  = 0;
            int i      = startIndex;
            int c      = sizeof(T);

            while (--c >= 0 && i <= value.size())
            {
                result += (value[i++] & 0xff) << shift;
                shift  += 8;
            }

            return result;
        }

        template <typename T>
        static std::vector<std::uint8_t> GetBytes(const T& value)
        {
            std::vector<std::uint8_t> result(0);
            std::int32_t shift = 0;

            for (std::size_t i = 0; i < sizeof(T); i++)
            {
                result.push_back((std::uint8_t)((value >> shift) & 0xff));
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
