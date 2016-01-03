// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_HPP
#define SCENER_MATH_HPP

#include <cmath>
#include <limits>

namespace SceneR { namespace Math {

/**
 * Represents the mathematical constant e.
 */
constexpr const float e = static_cast<float>(M_E);

/**
 * Represents the log base ten of e.
 */
constexpr const float log_10E = static_cast<float>(M_LOG10E);

/**
 * Represents the log base two of e.
 */
constexpr const float log_2E = static_cast<float>(M_LOG2E);

/**
 * Represents the value of PI
 */
constexpr const float pi = static_cast<float>(M_PI);

/**
 * Represents the value of PI divided by 2
 */
constexpr const float pi_over_2 = static_cast<float>(M_PI_2);

/**
 * Represents the value of PI divided by 4
 */
constexpr const float pi_over_4 = static_cast<float>(M_PI_4);

/**
 * Represents the value of pi times two.
 */
constexpr const float two_pi = static_cast<float>(M_2_PI);

/**
 * Represents negative infinity.
 */
constexpr const float negative_infinity = -std::numeric_limits<float>::infinity();

/**
 * Represents positive infinity.
 */
constexpr const float positive_infinity = std::numeric_limits<float>::infinity();

/**
 * Represents not a number (NaN).
 */
constexpr const float nan = std::numeric_limits<float>::quiet_NaN();

/**
 * Represents the smallest positive Single value that is greater than zero.
 */
constexpr const float epsilon = std::numeric_limits<float>::epsilon();

/**
 * @brief min_value Represents the smallest possible value of Single.
 */
constexpr const float min_value = std::numeric_limits<float>::lowest();

/**
 * @brief max_value Represents the largest possible value of Single. This field is constant.
 */
constexpr const float max_value = std::numeric_limits<float>::max();

constexpr bool equal(float a, float b) noexcept
{
    // TODO: Take a look at
    //
    // http://floating-point-gui.de/errors/comparison/
    // https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
    //
    // to take care for edge cases

    return (a == b);
}

/**
 * Returns a value indicating whether the specified number evaluates to positive infinity.
 * @param f A single-precision floating-point number.
 * @returns true if f evaluates to negative_infinity; otherwise, false.
 */
constexpr bool is_negative_infinity(float f) noexcept
{
    return equal(f, negative_infinity);
}

/**
 * Returns a value indicating whether the specified number evaluates to negative or positive infinity.
 * @param f A single-precision floating-point number.
 * @returns true if f evaluates to negative_infinity; otherwise, false.
 */
constexpr bool is_positive_infinity(float f) noexcept
{
    return (equal(f, positive_infinity));
}

/**
 * Returns a value indicating whether the specified number evaluates to negative or positive infinity.
 * @param f A single-precision floating-point number.
 * @returns true if f evaluates to negative_infinity or negative_infinity; otherwise, false.
 */
constexpr bool is_infinity(float f) noexcept
{
    return is_positive_infinity(f) || is_negative_infinity(f);
}

/**
 * Returns a value that indicates whether the specified value is not a number (NaN).
 * @param f A single-precision floating-point number.
 * @returns true if f evaluates to not a number (NaN); otherwise, false.
 */
inline bool is_nan(float f) noexcept
{
    return std::isnan(f);
}

/**
 * Returns the absolute value of a single-precision floating-point number.
 */
inline float abs(float value) noexcept
{
    return std::abs(value);
}

/**
 * Returns the angle whose cosine is the specified number
 */
inline float acos(float value) noexcept
{
    return std::acos(value);
}

/**
 * Returns the angle whose sine is the specified number.
 */
inline float asin(float value) noexcept
{
    return std::asin(value);
}

/**
 * Returns the angle whose tangent is the specified number.
 */
inline float atan(float value) noexcept
{
    return std::atan(value);
}

/**
 * Returns the angle whose tangent is the quotient of two specified numbers.
 * @param x The x coordinate of a point.
 * @param y The y coordinate of a point.
 */
inline float atan2(float x, float y) noexcept
{
    return std::atan2(x, y);
}

/**
 * Returns the smallest integral value that is greater than or equal to the specified double-precision floating-point number.
 */
inline float ceiling(float value) noexcept
{
    return std::ceil(value);
}

/**
 * Returns the cosine of the specified angle.
 */
inline float cos(float value) noexcept
{
    return std::cos(value);
}

/**
* Returns the hyperbolic cosine of the specified angle.
*/
inline float cosh(float value) noexcept
{
    return std::cosh(value);
}

/**
 * Returns e raised to the specified power.
 */
inline float exp(float d) noexcept
{
    return std::exp(d);
}

/**
* Returns the largest integer less than or equal to the specified double-precision floating-point number.
*/
inline float floor(float value) noexcept
{
    return std::floor(value);
}

/**
 * Rounds a double-precision floating-point value to the nearest integral value.
 */
inline float round(float a) noexcept
{
    return std::round(a);
}

/**
 * Returns the sine of the specified angle.
 */
inline float sin(float value) noexcept
{
    return std::sin(value);
}

/**
 * Returns the hyperbolic sine of the specified angle.
 */
inline float sinh(float value) noexcept
{
    return std::sinh(value);
}

/**
 * Returns the square root of a specified number.
 */
inline float sqrt(float value) noexcept
{
    return std::sqrt(value);
}

/**
 * Returns the tangent of the specified angle.
 */
inline float tan(float value) noexcept
{
    return std::tan(value);
}

/**
 * Returns the hyperbolic tangent of the specified angle.
 */
inline float tanh(float value) noexcept
{
    return std::tanh(value);
}

/**
 * Returns the remainder resulting from the division of a specified number by another specified number.
 * @param x A dividend.
 * @param y A divisor.
 */
inline float ieee_remainder(float x, float y) noexcept
{
    // Reference: https://msdn.microsoft.com/es-es/library/system.math.ieeeremainder%28v=vs.110%29.aspx
    // ieee_remainder = dividend - (divisor * Math.round(dividend / divisor))
    return x - (y * round(x / y));
}

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
constexpr float barycentric(float value1, float value2, float value3, float amount1, float amount2) noexcept
{
    // Reference: http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.Math.barycentric(v=xnagamestudio.40).aspx
    //  Pa = ((1 - b2 - b3) * V1a) + (b2 * V2a) + (b3 * V3a);
    //
    // NOTE: DirectX docs have a different formula. http://msdn.microsoft.com/en-us/library/windows/desktop/bb324330(v=vs.85).aspx
    //  v1 + f(v2 - v1) + g(v3 - v1)

    return ((1 - amount1 - amount2) * value1) + (amount1 * value2) + (amount2 * value3);
}

/**
 * Performs a Catmull-Rom interpolation using the specified positions.
 * @param value1 the first position in the interpolation.
 * @param value2 the second position in the interpolation.
 * @param value3 the third position in the interpolation.
 * @param value4 the fourth position in the interpolation.
 * @param amount weighting factor.
 */
constexpr float catmull_rom(float value1, float value2, float value3, float value4, float amount) noexcept
{
    // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/bb324331(v=vs.85).aspx
    // Q(s) = [(-s3 + 2s2 - s)p1 + (3s3 - 5s2 + 2)p2 + (-3s3 + 4s2 + s)p3 + (s3 - s2)p4] / 2;

    float s3 = amount * amount * amount;
    float s2 = amount * amount;
    float s  = amount;

    return ((-s3 + 2.0f * s2 - s)          * value1
          + (3.0f * s3 - 5.0f * s2 + 2.0f) * value2
          + (-3.0f * s3 + 4.0f * s2 + s)   * value3
          + (s3 - s2) * value4) / 2;
}

/**
 * Restricts a value to be within a specified range.
 * @param value the value to clamp.
 * @param min the min value.
 * @param max the max value.
 */
constexpr float clamp(float value, float min, float max) noexcept
{
    float maxValue = ((max < min) ? min : max);

    if (value < min)
    {
        return min;
    }
    else if (value > maxValue)
    {
        return maxValue;
    }

    return value;
}

/**
 * Calculates a hermite spline interpolation.
 * @param value1 source position 1.
 * @param tangent1 source tangent 1.
 * @param value2 source position 2.
 * @param tangent2 source tangent 2.
 * @param amount weighting factor.
 */
constexpr float hermite(float value1, float tangent1, float value2, float tangent2, float amount) noexcept
{
    // Reference: http://cubic.org/docs/hermite.htm
    // h1(s) =  2s^3 - 3s^2 + 1
    // h2(s) = -2s^3 + 3s^2
    // h3(s) =   s^3 - 2s^2 + s
    // h4(s) =   s^3 -  s^2
    //
    // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/bb324340(v=vs.85).aspx
    // Q(s) = (2s3 - 3s2 + 1)v1 + (-2s3 + 3s2)v2 + (s3 - 2s2 + s)t1 + (s3 - s2)t2.

    float s3 = amount * amount * amount;
    float s2 = amount * amount;

    return (2.0f  * s3 - 3.0f * s2 + 1.0f) * value1
         + (-2.0f * s3 + 3.0f * s2)        * value2
         + (s3    - 2.0f  * s2 + amount)   * tangent1
         + (s3    - s2)                    * tangent2;
}

/**
 * Performs a linear interpolation between two vectors.
 * @param value1 first vector
 * @param value2 second vector
 * @param amount value between 0 and 1 indicating the weight of value2.
 * @returns the linear interpolation of the two vectors.
 */
constexpr float lerp(float value1, float value2, float amount) noexcept
{
    // Reference: http://msdn.microsoft.com/en-us/library/bb197812.aspx
    return (value1 + (value2 - value1) * amount);
}

/**
 * Returns the lesser of two values
 * @param value1 the first value
 * @param value2 the second value
 */
constexpr float min(float value1, float value2) noexcept
{
    return ((value1 < value2) ? value1 : value2);
}

/**
 * Returns the greater of two values
 * @param value1 the first value
 * @param value2 the second value
 */
constexpr float max(float value1, float value2) noexcept
{
    return ((value1 > value2) ? value1 : value2);
}

/**
 * Interpolates between two values using a cubic equation.
 * @param value1 first vector
 * @param value2 second vector
 * @param amount weighting value.
 */
constexpr float smooth_step(float value1, float value2, float amount) noexcept
{
    // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorlerp(v=vs.85).aspx
    float t = clamp(amount, 0.0f, 1.0f);

    t = t * t * (3.0f - 2.0f * t);

    return lerp(value1, value2, t);
}

/**
 * Converts the given value in degrees to radians.
 * @param degrees the angle in degress.
 */
constexpr float to_radians(float degrees) noexcept
{
    return static_cast<float>(degrees * pi / 180.0);
}

/**
 * Converts the given value in radians to degrees.
 * @param radians the angle in radians.
 */
constexpr float to_degrees(float radians) noexcept
{
    return static_cast<float>(radians * 180.0 / pi);
}

/**
 * Reduces a given angle to a value between π and -π.
 * @param angle The angle to reduce, in radians.
 */
inline float wrap_angle(float angle) noexcept
{
    float result = ieee_remainder(angle, two_pi);

    if (result < -pi)
    {
        result += two_pi;
    }

    if (result > pi)
    {
        result -= two_pi;
    }

    return result;
}

}}

#endif // SCENER_MATH_HPP
