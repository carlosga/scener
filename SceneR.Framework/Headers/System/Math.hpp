// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MATH_HPP
#define MATH_HPP

#include <System/Core.hpp>

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
        constexpr static const System::Single E = M_E;

        /**
         * Represents the log base ten of e.
         */
        constexpr static const System::Single Log10E = M_LOG10E;

        /**
         * Represents the log base two of e.
         */
        constexpr static const System::Single Log2E = M_LOG2E;

        /**
         * Represents the value of PI
         */
        constexpr static const System::Single Pi = M_PI;

        /**
         * Represents the value of PI divided by 2
         */
        constexpr static const System::Single PiOver2 = M_PI_2;

        /**
         * Represents the value of PI divided by 4
         */
        constexpr static const System::Single PiOver4 = M_PI_4;

        /**
         * Represents the value of pi times two.
         */
        constexpr static const System::Single TwoPi = M_2_PI;

        /**
         * Represents negative infinity.
         */
        constexpr static const System::Single NegativeInfinity = -std::numeric_limits<Single>::infinity();

        /**
         * Represents positive infinity.
         */
        constexpr static const System::Single PositiveInfinity = std::numeric_limits<Single>::infinity();

        /**
         * Represents not a number (NaN).
         */
        constexpr static const System::Single NaN = std::numeric_limits<Single>::quiet_NaN();

        /**
         * Represents the smallest positive Single value that is greater than zero.
         */
        constexpr static const System::Single Epsilon = std::numeric_limits<Single>::epsilon();

        /**
         * @brief MinValue Represents the smallest possible value of Single.
         */
        constexpr static const Single MinValue = std::numeric_limits<Single>::lowest();

        /**
         * @brief MaxValue Represents the largest possible value of Single. This field is constant.
         */
        constexpr static const Single MaxValue = std::numeric_limits<Single>::max();

    public:
        /**
         * Returns a value indicating whether the specified number evaluates to negative or positive infinity.
         * @param f A single-precision floating-point number.
         * @returns true if f evaluates to PositiveInfinity or NegativeInfinity; otherwise, false.
         */
        static bool IsInfinity(const System::Single& f);

        /**
         * Returns a value indicating whether the specified number evaluates to positive infinity.
         * @param f A single-precision floating-point number.
         * @returns true if f evaluates to NegativeInfinity; otherwise, false.
         */
        static bool IsNegativeInfinity(const System::Single& f);

        /**
         * Returns a value indicating whether the specified number evaluates to negative or positive infinity.
         * @param f A single-precision floating-point number.
         * @returns true if f evaluates to PositiveInfinity; otherwise, false.
         */
        static bool IsPositiveInfinity(const System::Single& f);

        /**
         * Returns a value that indicates whether the specified value is not a number (NaN).
         * @param f A single-precision floating-point number.
         * @returns true if f evaluates to not a number (NaN); otherwise, false.
         */
        static bool IsNaN(const System::Single& f);

    public:
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
        static Single Ceiling(const Single& value);

        /**
         * Returns the cosine of the specified angle.
         */
        static Single Cos(const Single& value);

        /**
        * Returns the hyperbolic cosine of the specified angle.
        */
        static Single Cosh(const Single& value);

        /**
         * Returns e raised to the specified power.
         */
        static Single Exp(const Single& d);

        /**
        * Returns the largest integer less than or equal to the specified double-precision floating-point number.
        */
        static Single Floor(const Single& value);

        /**
         * Returns the remainder resulting from the division of a specified number by another specified number.
         * @param x A dividend.
         * @param y A divisor.
         */
        static Single IEEERemainder(const Single& x, const Single& y);

        /**
         * Rounds a double-precision floating-point value to the nearest integral value.
         */
        static Single Round(const Single & a);

        /**
         * Returns the sine of the specified angle.
         */
        static Single Sin(const Single& value);

        /**
         * Returns the hyperbolic sine of the specified angle.
         */
        static Single Sinh(const Single& value);

        /**
         * Returns the square root of a specified number.
         */
        static Single Sqrt(const Single& value);

        /**
         * Returns the tangent of the specified angle.
         */
        static Single Tan(const Single& value);

        /**
         * Returns the hyperbolic tangent of the specified angle.
         */
        static Single Tanh(const Single& value);

    public:
        static bool Equal(const Single& a, const Single& b);

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
        static System::Single Barycentric(const System::Single& value1
                                        , const System::Single& value2
                                        , const System::Single& value3
                                        , const System::Single& amount1
                                        , const System::Single& amount2);

        /**
         * Performs a Catmull-Rom interpolation using the specified positions.
         * @param value1 the first position in the interpolation.
         * @param value2 the second position in the interpolation.
         * @param value3 the third position in the interpolation.
         * @param value4 the fourth position in the interpolation.
         * @param amount weighting factor.
         */
        static System::Single CatmullRom(const System::Single& value1
                                       , const System::Single& value2
                                       , const System::Single& value3
                                       , const System::Single& value4
                                       , const System::Single& amount);

        /**
         * Restricts a value to be within a specified range.
         * @param value the value to clamp.
         * @param min the min value.
         * @param max the max value.
         */
        static System::Single Clamp(const System::Single& value
                                  , const System::Single& min
                                  , const System::Single& max);

        /**
         * Calculates a hermite spline interpolation.
         * @param value1 source position 1.
         * @param tangent1 source tangent 1.
         * @param value2 source position 2.
         * @param tangent2 source tangent 2.
         * @param amount weighting factor.
         */
        static System::Single Hermite(const System::Single& value1
                                    , const System::Single& tangent1
                                    , const System::Single& value2
                                    , const System::Single& tangent2
                                    , const System::Single& amount);

        /**
         * Performs a linear interpolation between two vectors.
         * @param value1 first vector
         * @param value2 second vector
         * @param amount value between 0 and 1 indicating the weight of value2.
         * @returns the linear interpolation of the two vectors.
         */
        static System::Single Lerp(const System::Single& value1
                                 , const System::Single& value2
                                 , const System::Single& amount);

        /**
         * Returns the lesser of two values
         * @param value1 the first value
         * @param value2 the second value
         */
        static System::Single Min(const System::Single& value1, const System::Single& value2);

        /**
         * Returns the greater of two values
         * @param value1 the first value
         * @param value2 the second value
         */
        static System::Single Max(const System::Single& value1, const System::Single& value2);

        /**
         * Interpolates between two values using a cubic equation.
         * @param value1 first vector
         * @param value2 second vector
         * @param amount weighting value.
         */
        static System::Single SmoothStep(const System::Single& value1
                                       , const System::Single& value2
                                       , const System::Single& amount);

        /**
         * Converts the given value in degrees to radians.
         * @param degrees the angle in degress.
         */
        static System::Single ToRadians(const System::Single& degrees);

        /**
         * Converts the given value in radians to degrees.
         * @param radians the angle in radians.
         */
        static System::Single ToDegrees(const System::Single& radians);

        /**
         * Reduces a given angle to a value between π and -π.
         * @param angle The angle to reduce, in radians.
         */
        static System::Single WrapAngle(const System::Single& angle);

    private:
        Math() = delete;
        Math(const Math& math) = delete;
        Math& operator=(const Math& math) = delete;
    };
}

#endif /* MATH_HPP */
