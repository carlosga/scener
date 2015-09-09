// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SYSTEM_MATH_HPP
#define SYSTEM_MATH_HPP

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
        constexpr static const float e = static_cast<float>(M_E);

        /**
         * Represents the log base ten of e.
         */
        constexpr static const float log_10E = static_cast<float>(M_LOG10E);

        /**
         * Represents the log base two of e.
         */
        constexpr static const float log_2E = static_cast<float>(M_LOG2E);

        /**
         * Represents the value of PI
         */
        constexpr static const float pi = static_cast<float>(M_PI);

        /**
         * Represents the value of PI divided by 2
         */
        constexpr static const float pi_over_2 = static_cast<float>(M_PI_2);

        /**
         * Represents the value of PI divided by 4
         */
        constexpr static const float pi_over_4 = static_cast<float>(M_PI_4);

        /**
         * Represents the value of pi times two.
         */
        constexpr static const float two_pi = static_cast<float>(M_2_PI);

        /**
         * Represents negative infinity.
         */
        constexpr static const float negative_infinity = -std::numeric_limits<float>::infinity();

        /**
         * Represents positive infinity.
         */
        constexpr static const float positive_infinity = std::numeric_limits<float>::infinity();

        /**
         * Represents not a number (NaN).
         */
        constexpr static const float nan = std::numeric_limits<float>::quiet_NaN();

        /**
         * Represents the smallest positive Single value that is greater than zero.
         */
        constexpr static const float epsilon = std::numeric_limits<float>::epsilon();

        /**
         * @brief min_value Represents the smallest possible value of Single.
         */
        constexpr static const float min_value = std::numeric_limits<float>::lowest();

        /**
         * @brief max_value Represents the largest possible value of Single. This field is constant.
         */
        constexpr static const float max_value = std::numeric_limits<float>::max();

    public:
        /**
         * Returns a value indicating whether the specified number evaluates to negative or positive infinity.
         * @param f A single-precision floating-point number.
         * @returns true if f evaluates to negative_infinity or negative_infinity; otherwise, false.
         */
        static bool is_infinity(const float& f);

        /**
         * Returns a value indicating whether the specified number evaluates to positive infinity.
         * @param f A single-precision floating-point number.
         * @returns true if f evaluates to negative_infinity; otherwise, false.
         */
        static bool is_negative_infinity(const float& f);

        /**
         * Returns a value indicating whether the specified number evaluates to negative or positive infinity.
         * @param f A single-precision floating-point number.
         * @returns true if f evaluates to negative_infinity; otherwise, false.
         */
        static bool is_positive_infinity(const float& f);

        /**
         * Returns a value that indicates whether the specified value is not a number (NaN).
         * @param f A single-precision floating-point number.
         * @returns true if f evaluates to not a number (NaN); otherwise, false.
         */
        static bool is_nan(const float& f);

    public:
        /**
         * Returns the absolute value of a single-precision floating-point number.
         */
        static float abs(const float& value);

        /**
         * Returns the angle whose cosine is the specified number
         */
        static float acos(const float& value);

        /**
         * Returns the angle whose sine is the specified number.
         */
        static float asin(const float& value);

        /**
         * Returns the angle whose tangent is the specified number.
         */
        static float atan(const float& value);

        /**
         * Returns the angle whose tangent is the quotient of two specified numbers.
         * @param x The x coordinate of a point.
         * @param y The y coordinate of a point.
         */
        static float atan2(const float& x, const float& y);

        /**
         * Returns the smallest integral value that is greater than or equal to the specified double-precision floating-point number.
         */
        static float ceiling(const float& value);

        /**
         * Returns the cosine of the specified angle.
         */
        static float cos(const float& value);

        /**
        * Returns the hyperbolic cosine of the specified angle.
        */
        static float cosh(const float& value);

        /**
         * Returns e raised to the specified power.
         */
        static float exp(const float& d);

        /**
        * Returns the largest integer less than or equal to the specified double-precision floating-point number.
        */
        static float floor(const float& value);

        /**
         * Returns the remainder resulting from the division of a specified number by another specified number.
         * @param x A dividend.
         * @param y A divisor.
         */
        static float ieee_remainder(const float& x, const float& y);

        /**
         * Rounds a double-precision floating-point value to the nearest integral value.
         */
        static float round(const float& a);

        /**
         * Returns the sine of the specified angle.
         */
        static float sin(const float& value);

        /**
         * Returns the hyperbolic sine of the specified angle.
         */
        static float sinh(const float& value);

        /**
         * Returns the square root of a specified number.
         */
        static float sqrt(const float& value);

        /**
         * Returns the tangent of the specified angle.
         */
        static float tan(const float& value);

        /**
         * Returns the hyperbolic tangent of the specified angle.
         */
        static float tanh(const float& value);

    public:
        static bool equal(const float& a, const float& b);

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
        static float barycentric(const float& value1
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
        static float catmull_rom(const float& value1
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
        static float clamp(const float& value, const float& min, const float& max);

        /**
         * Calculates a hermite spline interpolation.
         * @param value1 source position 1.
         * @param tangent1 source tangent 1.
         * @param value2 source position 2.
         * @param tangent2 source tangent 2.
         * @param amount weighting factor.
         */
        static float hermite(const float& value1
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
        static float lerp(const float& value1, const float& value2, const float& amount);

        /**
         * Returns the lesser of two values
         * @param value1 the first value
         * @param value2 the second value
         */
        static float min(const float& value1, const float& value2);

        /**
         * Returns the greater of two values
         * @param value1 the first value
         * @param value2 the second value
         */
        static float max(const float& value1, const float& value2);

        /**
         * Interpolates between two values using a cubic equation.
         * @param value1 first vector
         * @param value2 second vector
         * @param amount weighting value.
         */
        static float smooth_step(const float& value1, const float& value2, const float& amount);

        /**
         * Converts the given value in degrees to radians.
         * @param degrees the angle in degress.
         */
        static float to_radians(const float& degrees);

        /**
         * Converts the given value in radians to degrees.
         * @param radians the angle in radians.
         */
        static float to_degrees(const float& radians);

        /**
         * Reduces a given angle to a value between π and -π.
         * @param angle The angle to reduce, in radians.
         */
        static float wrap_angle(const float& angle);

    private:
        Math() = delete;
        Math(const Math& math) = delete;
        Math& operator=(const Math& math) = delete;
    };
}

#endif  // SYSTEM_MATH_HPP
