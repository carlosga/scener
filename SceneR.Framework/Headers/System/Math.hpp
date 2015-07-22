// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>
#include <limits>

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
        constexpr static const float E = static_cast<float>(M_E);

        /**
         * Represents the log base ten of e.
         */
        constexpr static const float Log10E = static_cast<float>(M_LOG10E);

        /**
         * Represents the log base two of e.
         */
        constexpr static const float Log2E = static_cast<float>(M_LOG2E);

        /**
         * Represents the value of PI
         */
        constexpr static const float Pi = static_cast<float>(M_PI);

        /**
         * Represents the value of PI divided by 2
         */
        constexpr static const float PiOver2 = static_cast<float>(M_PI_2);

        /**
         * Represents the value of PI divided by 4
         */
        constexpr static const float PiOver4 = static_cast<float>(M_PI_4);

        /**
         * Represents the value of pi times two.
         */
        constexpr static const float TwoPi = static_cast<float>(M_2_PI);

        /**
         * Represents negative infinity.
         */
        constexpr static const float NegativeInfinity = -std::numeric_limits<float>::infinity();

        /**
         * Represents positive infinity.
         */
        constexpr static const float PositiveInfinity = std::numeric_limits<float>::infinity();

        /**
         * Represents not a number (NaN).
         */
        constexpr static const float NaN = std::numeric_limits<float>::quiet_NaN();

        /**
         * Represents the smallest positive Single value that is greater than zero.
         */
        constexpr static const float Epsilon = std::numeric_limits<float>::epsilon();

        /**
         * @brief MinValue Represents the smallest possible value of Single.
         */
        constexpr static const float MinValue = std::numeric_limits<float>::lowest();

        /**
         * @brief MaxValue Represents the largest possible value of Single. This field is constant.
         */
        constexpr static const float MaxValue = std::numeric_limits<float>::max();

    public:
        /**
         * Returns a value indicating whether the specified number evaluates to negative or positive infinity.
         * @param f A single-precision floating-point number.
         * @returns true if f evaluates to PositiveInfinity or NegativeInfinity; otherwise, false.
         */
        static bool IsInfinity(const float& f);

        /**
         * Returns a value indicating whether the specified number evaluates to positive infinity.
         * @param f A single-precision floating-point number.
         * @returns true if f evaluates to NegativeInfinity; otherwise, false.
         */
        static bool IsNegativeInfinity(const float& f);

        /**
         * Returns a value indicating whether the specified number evaluates to negative or positive infinity.
         * @param f A single-precision floating-point number.
         * @returns true if f evaluates to PositiveInfinity; otherwise, false.
         */
        static bool IsPositiveInfinity(const float& f);

        /**
         * Returns a value that indicates whether the specified value is not a number (NaN).
         * @param f A single-precision floating-point number.
         * @returns true if f evaluates to not a number (NaN); otherwise, false.
         */
        static bool IsNaN(const float& f);

    public:
        /**
         * Returns the absolute value of a single-precision floating-point number.
         */
        static float Abs(const float& value);

        /**
         * Returns the angle whose cosine is the specified number
         */
        static float Acos(const float& value);

        /**
         * Returns the angle whose sine is the specified number.
         */
        static float Asin(const float& value);

        /**
         * Returns the angle whose tangent is the specified number.
         */
        static float Atan(const float& value);

        /**
         * Returns the angle whose tangent is the quotient of two specified numbers.
         * @param x The x coordinate of a point.
         * @param y The y coordinate of a point.
         */
        static float Atan2(const float& x, const float& y);

        /**
         * Returns the smallest integral value that is greater than or equal to the specified double-precision floating-point number.
         */
        static float Ceiling(const float& value);

        /**
         * Returns the cosine of the specified angle.
         */
        static float Cos(const float& value);

        /**
        * Returns the hyperbolic cosine of the specified angle.
        */
        static float Cosh(const float& value);

        /**
         * Returns e raised to the specified power.
         */
        static float Exp(const float& d);

        /**
        * Returns the largest integer less than or equal to the specified double-precision floating-point number.
        */
        static float Floor(const float& value);

        /**
         * Returns the remainder resulting from the division of a specified number by another specified number.
         * @param x A dividend.
         * @param y A divisor.
         */
        static float IEEERemainder(const float& x, const float& y);

        /**
         * Rounds a double-precision floating-point value to the nearest integral value.
         */
        static float Round(const float & a);

        /**
         * Returns the sine of the specified angle.
         */
        static float Sin(const float& value);

        /**
         * Returns the hyperbolic sine of the specified angle.
         */
        static float Sinh(const float& value);

        /**
         * Returns the square root of a specified number.
         */
        static float Sqrt(const float& value);

        /**
         * Returns the tangent of the specified angle.
         */
        static float Tan(const float& value);

        /**
         * Returns the hyperbolic tangent of the specified angle.
         */
        static float Tanh(const float& value);

    public:
        static bool Equal(const float& a, const float& b);

    public:
        /**
         * Returns the Cartesian coordinate for one axis of a point that is defined by a given triangle and
         * two normalized barycentric (areal) coordinates.
         * @param value1 the coordinate on one axis of vertex 1 of the defining triangle.
         * @param value2 the coordinate on the same axis of vertex 2 of the defining triangle.
         * @param value3 the coordinate on the same axis of vertex 3 of the defining triangle.
         * @param amount1 the normalized barycentric (areal) coordinate b2, equal to the weighting factor for vertex 2,
         *                the coordinate of which is specified in value2.
         * @param amount2 the normalized barycentric (areal) coordinate b3, equal to the weighting factor for vertex 3,
         *                the coordinate of which is specified in value3.
         */
        static float Barycentric(const float& value1
                               , const float& value2
                               , const float& value3
                               , const float& amount1
                               , const float& amount2);

        /**
         * Performs a Catmull-Rom interpolation using the specified positions.
         * @param value1 the first position in the interpolation.
         * @param value2 the second position in the interpolation.
         * @param value3 the third position in the interpolation.
         * @param value4 the fourth position in the interpolation.
         * @param amount weighting factor.
         */
        static float CatmullRom(const float& value1
                              , const float& value2
                              , const float& value3
                              , const float& value4
                              , const float& amount);

        /**
         * Restricts a value to be within a specified range.
         * @param value the value to clamp.
         * @param min the min value.
         * @param max the max value.
         */
        static float Clamp(const float& value, const float& min, const float& max);

        /**
         * Calculates a hermite spline interpolation.
         * @param value1 source position 1.
         * @param tangent1 source tangent 1.
         * @param value2 source position 2.
         * @param tangent2 source tangent 2.
         * @param amount weighting factor.
         */
        static float Hermite(const float& value1
                           , const float& tangent1
                           , const float& value2
                           , const float& tangent2
                           , const float& amount);

        /**
         * Performs a linear interpolation between two vectors.
         * @param value1 first vector
         * @param value2 second vector
         * @param amount value between 0 and 1 indicating the weight of value2.
         * @returns the linear interpolation of the two vectors.
         */
        static float Lerp(const float& value1, const float& value2, const float& amount);

        /**
         * Returns the lesser of two values
         * @param value1 the first value
         * @param value2 the second value
         */
        static float Min(const float& value1, const float& value2);

        /**
         * Returns the greater of two values
         * @param value1 the first value
         * @param value2 the second value
         */
        static float Max(const float& value1, const float& value2);

        /**
         * Interpolates between two values using a cubic equation.
         * @param value1 first vector
         * @param value2 second vector
         * @param amount weighting value.
         */
        static float SmoothStep(const float& value1, const float& value2, const float& amount);

        /**
         * Converts the given value in degrees to radians.
         * @param degrees the angle in degress.
         */
        static float ToRadians(const float& degrees);

        /**
         * Converts the given value in radians to degrees.
         * @param radians the angle in radians.
         */
        static float ToDegrees(const float& radians);

        /**
         * Reduces a given angle to a value between π and -π.
         * @param angle The angle to reduce, in radians.
         */
        static float WrapAngle(const float& angle);

    private:
        Math() = delete;
        Math(const Math& math) = delete;
        Math& operator=(const Math& math) = delete;
    };
}

#endif /* MATH_HPP */
