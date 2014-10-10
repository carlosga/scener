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

#ifndef BITCONVERTER_HPP
#define BITCONVERTER_HPP

#include <System/Core.hpp>
#include <cassert>
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
        //     Converts the specified System::Double-precision floating point number to a 64-bit
        //     signed integer.
        //
        // Parameters:
        //   value:
        //     The number to convert.
        //
        // Returns:
        //     A 64-bit signed integer whose value is equivalent to value.
        static System::Int64 DoubleToInt64Bits(const System::Double& value)
        {
            return static_cast<System::Int64>(value);
        };

        //
        // Summary:
        //     Converts the specified 64-bit signed integer to a System::Double-precision floating
        //     point number.
        //
        // Parameters:
        //   value:
        //     The number to convert.
        //
        // Returns:
        //     A System::Double-precision floating point number whose value is equivalent to value.
        static System::Double Int64BitsToDouble(const System::Int64& value)
        {
            return static_cast<System::Double>(value);
        };

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
        static std::vector<System::UByte> GetBytes(const System::Boolean& value)
        {
            return GetBytes<bool>(value);
        };

        //
        // Summary:
        //     Returns the specified Unicode System::Character value as an array of bytes.
        //
        // Parameters:
        //   value:
        //     A System::Character to convert.
        //
        // Returns:
        //     An array of bytes with length 2.
        static std::vector<System::UByte> GetBytes(const System::Char& value)
        {
            return GetBytes<System::Int16>(static_cast<System::Int16>(value));
        };

        //
        // Summary:
        //     Returns the specified System::Double-precision floating point value as an array of
        //     bytes.
        //
        // Parameters:
        //   value:
        //     The number to convert.
        //
        // Returns:
        //     An array of bytes with length 8.
        static std::vector<System::UByte> GetBytes(const System::Double& value)
        {
            return GetBytes<System::Int64>(static_cast<System::Int64>(value));
        };

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
        static std::vector<System::UByte> GetBytes(const System::Single& value)
        {
            return GetBytes<System::Int32>(static_cast<System::Int32>(value));
        };

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
        static std::vector<System::UByte> GetBytes(const System::Int32& value)
        {
            return GetBytes<System::Int32>(value);
        };

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
        static std::vector<System::UByte> GetBytes(const System::Int64& value)
        {
            return GetBytes<System::Int64>(value);
        };

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
        static std::vector<System::UByte> GetBytes(const System::Int16& value)
        {
            return GetBytes<System::Int16>(value);
        };

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
        static std::vector<System::UByte> GetBytes(const System::UInt32& value)
        {
            return GetBytes<System::UInt32>(value);
        };

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
        static std::vector<System::UByte> GetBytes(const System::Int64& value)
        {
            return GetBytes<System::Int64>(value);
        };

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
        static std::vector<System::UByte> GetBytes(const uSystem::Int16& value)
        {
            return GetBytes<uSystem::Int16>(value);
        };

        //
        // Summary:
        //     Returns a Boolean value converted from one System::UByte at a specified position in
        //     a System::UByte array.
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
        static bool ToBoolean(const std::vector<System::UByte>& value, const System::UInt32& startIndex)
        {
            assert(startIndex <= (value.size() - 1));

            return (value[startIndex] == 1);
        };

        //
        // Summary:
        //     Returns a Unicode System::Character converted from two bytes at a specified position
        //     in a System::UByte array.
        //
        // Parameters:
        //   value:
        //     An array.
        //
        //   startIndex:
        //     The starting position within value.
        //
        // Returns:
        //     A System::Character formed by two bytes beginning at startIndex.
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
        static System::Char ToChar(const std::vector<System::UByte>& value, const System::UInt32& startIndex)
        {
            throw std::runtime_error("Not implemented");
        };

        //
        // Summary:
        //     Returns a System::Double-precision floating poSystem::Int32 number converted from eight bytes
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
        //     A System::Double precision floating poSystem::Int32 number formed by eight bytes beginning
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
        static System::Double ToDouble(const std::vector<System::UByte>& value, const System::UInt32& startIndex)
        {
            return ToValue<System::Double>(value, startIndex);
        };

        //
        // Summary:
        //     Returns a 16-bit signed integer converted from two bytes at a specified position
        //     in a System::UByte array.
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
        static System::Int16 ToInt16(const std::vector<System::UByte>& value, const System::UInt32& startIndex)
        {
            return ToValue<System::Int16>(value, startIndex);
        };

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
        static System::Int32 ToInt32(const std::vector<System::UByte>& value, const System::UInt32& startIndex)
        {
            return ToValue<System::Int32>(value, startIndex);
        };

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
        static System::Int64 ToInt64(const std::vector<System::UByte>& value, const System::UInt32& startIndex)
        {
            return ToValue<System::Int64>(value, startIndex);
        };

        //
        // Summary:
        //     Returns a single-precision floating poSystem::Int32 number converted from four bytes
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
        //     A single-precision floating poSystem::Int32 number formed by four bytes beginning at
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
        static float ToSingle(const std::vector<System::UByte>& value, const System::UInt32& startIndex)
        {
            return ToValue<float>(value, startIndex);
        };

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
        static std::u16string ToString(const std::vector<System::UByte>& value)
        {
            throw std::runtime_error("Not implemented");
        };

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
        static std::u16string ToString(const std::vector<System::UByte>& value, const System::UInt32& startIndex)
        {
            throw std::runtime_error("Not implemented");
        };

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
        static std::u16string ToString(const std::vector<System::UByte>& value, const System::UInt32& startIndex, System::Int32 length)
        {
            throw std::runtime_error("Not implemented");
        };

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
        static System::UInt16 ToUInt16(const std::vector<System::UByte>& value, const System::UInt32& startIndex)
        {
            return ToValue<System::UInt16>(value, startIndex);
        };

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
        static System::Int32 ToUInt32(const std::vector<System::UByte>& value, const System::UInt32& startIndex)
        {
            return ToValue<System::Int32>(value, startIndex);
        };

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
        static System::Int64 ToUInt64(const std::vector<System::UByte>& value, const System::UInt32& startIndex)
        {
            return ToValue<System::Int64>(value, startIndex);
        };

    private:
        template <typename T>
        static T ToValue(const std::vector<System::UByte>& value, const System::UInt32& startIndex)
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
        };

        template <typename T>
        static std::vector<System::UByte> GetBytes(const T& value)
        {
            std::vector<System::UByte> result(0);
            int shift = 0;

            for (int i = 0; i < sizeof(T); i++)
            {
                result.push_back((System::UByte)((value >> shift) & 0xff));
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
