// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MATH_HPP
#define MATH_HPP

#include <System/Core.hpp>

namespace System
{
    /**
     * Provides constants and static methods for trigonometric, logarithmic, and other common mathematical functions.
     */
    class Math
    {
    public:
        /**
        * Represents the mathematical constant e.
        */
        static const Single& E;

        /**
        * Represents the value of PI
        */
        static const Single& Pi;

    public:
        /**
         * Returns the absolute value of a double-precision floating-point number.
         */
        static Double Abs(const Double& value);

        /**
         * Returns the absolute value of a single-precision floating-point number.
         */
        static Single Abs(const Single& value);

        /**
         * Returns the angle whose cosine is the specified number
         */
        static Single Acos(const Single& value);

        /**
         * Returns the angle whose sine is the specified number.
         */
        static Single Asin(const Single& value);

        /**
         * Returns the angle whose tangent is the specified number.
         */
        static Single Atan(const Single& value);

        /**
         * Returns the angle whose tangent is the quotient of two specified numbers.
         * @param x The x coordinate of a point.
         * @param y The y coordinate of a point.
         */
        static Single Atan2(const Single& x, const Single& y);

        /**
         * Returns the smallest integral value that is greater than or equal to the specified double-precision floating-point number.
         */
        static Double Ceiling(const Double& value);

        /**
         * Returns the cosine of the specified angle.
         */
        static Double Cos(const Double& value);

        /**
         * Returns the cosine of the specified angle.
         */
        static Single Cos(const Single& value);

        /**
         * Returns the hyperbolic cosine of the specified angle.
         */
        static Double Cosh(const Double& value);

        /**
        * Returns the hyperbolic cosine of the specified angle.
        */
        static Single Cosh(const Single& value);

        /**
         * Returns e raised to the specified power.
         */
        static Double Exp(const Double& d);

        /**
         * Returns the largest integer less than or equal to the specified double-precision floating-point number.
         */
        static Double Floor(const Double& value);

        /**
        * Returns the largest integer less than or equal to the specified double-precision floating-point number.
        */
        static Single Floor(const Single& value);

        /**
         * Returns the remainder resulting from the division of a specified number by another specified number.
         * @param x A dividend.
         * @param y A divisor.
         */
        static Double IEEERemainder(const Double& x, const Double& y);

        /**
         * Rounds a double-precision floating-point value to the nearest integral value.
         */
        static Double Round(const Double& a);

        /**
         * Returns the sine of the specified angle.
         */
        static Double Sin(const Double& value);

        /**
         * Returns the sine of the specified angle.
         */
        static Single Sin(const Single& value);

        /**
         * Returns the hyperbolic sine of the specified angle.
         */
        static Double Sinh(const Double& value);

        /**
         * Returns the square root of a specified number.
         */
        static Double Sqrt(const Double& value);

        /**
         * Returns the square root of a specified number.
         */
        static Single Sqrt(const Single& value);

        /**
         * Returns the tangent of the specified angle.
         */
        static Double Tan(const Double& value);

        /**
         * Returns the tangent of the specified angle.
         */
        static Single Tan(const Single& value);

        /**
         * Returns the hyperbolic tangent of the specified angle.
         */
        static Double Tanh(const Double& value);

        /**
         * Returns the hyperbolic tangent of the specified angle.
         */
        static Single Tanh(const Single& value);

        /*
        Log(Double)	Returns the natural (base e) logarithm of a specified number.
        Log(Double, Double)	Returns the logarithm of a specified number in a specified base.
        Log10	Returns the base 10 logarithm of a specified number.
        Max(Byte, Byte)	Returns the larger of two 8-bit unsigned integers.
        Max(Decimal, Decimal)	Returns the larger of two decimal numbers.
        Max(Double, Double)	Returns the larger of two double-precision floating-point numbers.
        Max(Int16, Int16)	Returns the larger of two 16-bit signed integers.
        Max(Int32, Int32)	Returns the larger of two 32-bit signed integers.
        Max(Int64, Int64)	Returns the larger of two 64-bit signed integers.
        Max(SByte, SByte)	Returns the larger of two 8-bit signed integers.
        Max(Single, Single)	Returns the larger of two single-precision floating-point numbers.
        Max(UInt16, UInt16)	Returns the larger of two 16-bit unsigned integers.
        Max(UInt32, UInt32)	Returns the larger of two 32-bit unsigned integers.
        Max(UInt64, UInt64)	Returns the larger of two 64-bit unsigned integers.
        Min(Byte, Byte)	Returns the smaller of two 8-bit unsigned integers.
        Min(Decimal, Decimal)	Returns the smaller of two decimal numbers.
        Min(Double, Double)	Returns the smaller of two double-precision floating-point numbers.
        Min(Int16, Int16)	Returns the smaller of two 16-bit signed integers.
        Min(Int32, Int32)	Returns the smaller of two 32-bit signed integers.
        Min(Int64, Int64)	Returns the smaller of two 64-bit signed integers.
        Min(SByte, SByte)	Returns the smaller of two 8-bit signed integers.
        Min(Single, Single)	Returns the smaller of two single-precision floating-point numbers.
        Min(UInt16, UInt16)	Returns the smaller of two 16-bit unsigned integers.
        Min(UInt32, UInt32)	Returns the smaller of two 32-bit unsigned integers.
        Min(UInt64, UInt64)	Returns the smaller of two 64-bit unsigned integers.
        Pow	Returns a specified number raised to the specified power.
        Round(Decimal)	Rounds a decimal value to the nearest integral value.
        Round(Double)	Rounds a double-precision floating-point value to the nearest integral value.
        Round(Decimal, Int32)	Rounds a decimal value to a specified number of fractional digits.
        Round(Decimal, MidpointRounding)	Rounds a decimal value to the nearest integer. A parameter specifies how to round the value if it is midway between two numbers.
        Round(Double, Int32)	Rounds a double-precision floating-point value to a specified number of fractional digits.
        Round(Double, MidpointRounding)	Rounds a double-precision floating-point value to the nearest integer. A parameter specifies how to round the value if it is midway between two numbers.
        Round(Decimal, Int32, MidpointRounding)	Rounds a decimal value to a specified number of fractional digits. A parameter specifies how to round the value if it is midway between two numbers.
        Round(Double, Int32, MidpointRounding)	Rounds a double-precision floating-point value to a specified number of fractional digits. A parameter specifies how to round the value if it is midway between two numbers.
        Sign(Decimal)	Returns a value indicating the sign of a decimal number.
        Sign(Double)	Returns a value indicating the sign of a double-precision floating-point number.
        Sign(Int16)	Returns a value indicating the sign of a 16-bit signed integer.
        Sign(Int32)	Returns a value indicating the sign of a 32-bit signed integer.
        Sign(Int64)	Returns a value indicating the sign of a 64-bit signed integer.
        Sign(SByte)	Returns a value indicating the sign of an 8-bit signed integer.
        Sign(Single)	Returns a value indicating the sign of a single-precision floating-point number.
        Sin	Returns the sine of the specified angle.
        Sinh	Returns the hyperbolic sine of the specified angle.
        Sqrt	Returns the square root of a specified number.
        Tan	Returns the tangent of the specified angle.
        Tanh	Returns the hyperbolic tangent of the specified angle.
        Truncate(Decimal)	Calculates the integral part of a specified decimal number.
        Truncate(Double)	Calculates the integral part of a specified double-precision floating-point number.
        */
    };
}

#endif /* MATH_HPP */
