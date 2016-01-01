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

/**
 * Returns a value indicating whether the specified number evaluates to negative or positive infinity.
 * @param f A single-precision floating-point number.
 * @returns true if f evaluates to negative_infinity or negative_infinity; otherwise, false.
 */
bool is_infinity(float f) noexcept;

/**
 * Returns a value indicating whether the specified number evaluates to positive infinity.
 * @param f A single-precision floating-point number.
 * @returns true if f evaluates to negative_infinity; otherwise, false.
 */
bool is_negative_infinity(float f) noexcept;

/**
 * Returns a value indicating whether the specified number evaluates to negative or positive infinity.
 * @param f A single-precision floating-point number.
 * @returns true if f evaluates to negative_infinity; otherwise, false.
 */
bool is_positive_infinity(float f) noexcept;

/**
 * Returns a value that indicates whether the specified value is not a number (NaN).
 * @param f A single-precision floating-point number.
 * @returns true if f evaluates to not a number (NaN); otherwise, false.
 */
bool is_nan(float f) noexcept;

/**
 * Returns the absolute value of a single-precision floating-point number.
 */
float abs(float value) noexcept;

/**
 * Returns the angle whose cosine is the specified number
 */
float acos(float value) noexcept;

/**
 * Returns the angle whose sine is the specified number.
 */
float asin(float value) noexcept;

/**
 * Returns the angle whose tangent is the specified number.
 */
float atan(float value) noexcept;

/**
 * Returns the angle whose tangent is the quotient of two specified numbers.
 * @param x The x coordinate of a point.
 * @param y The y coordinate of a point.
 */
float atan2(float x, float y) noexcept;

/**
 * Returns the smallest integral value that is greater than or equal to the specified double-precision floating-point number.
 */
float ceiling(float value) noexcept;

/**
 * Returns the cosine of the specified angle.
 */
float cos(float value) noexcept;

/**
* Returns the hyperbolic cosine of the specified angle.
*/
float cosh(float value) noexcept;

/**
 * Returns e raised to the specified power.
 */
float exp(float d) noexcept;

/**
* Returns the largest integer less than or equal to the specified double-precision floating-point number.
*/
float floor(float value) noexcept;

/**
 * Returns the remainder resulting from the division of a specified number by another specified number.
 * @param x A dividend.
 * @param y A divisor.
 */
float ieee_remainder(float x, float y) noexcept;

/**
 * Rounds a double-precision floating-point value to the nearest integral value.
 */
float round(float a) noexcept;

/**
 * Returns the sine of the specified angle.
 */
float sin(float value) noexcept;

/**
 * Returns the hyperbolic sine of the specified angle.
 */
float sinh(float value) noexcept;

/**
 * Returns the square root of a specified number.
 */
float sqrt(float value) noexcept;

/**
 * Returns the tangent of the specified angle.
 */
float tan(float value) noexcept;

/**
 * Returns the hyperbolic tangent of the specified angle.
 */
float tanh(float value) noexcept;

bool equal(float a, float b) noexcept;

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
float barycentric(float value1, float value2, float value3, float amount1, float amount2) noexcept;

/**
 * Performs a Catmull-Rom interpolation using the specified positions.
 * @param value1 the first position in the interpolation.
 * @param value2 the second position in the interpolation.
 * @param value3 the third position in the interpolation.
 * @param value4 the fourth position in the interpolation.
 * @param amount weighting factor.
 */
float catmull_rom(float value1, float value2, float value3, float value4, float amount) noexcept;

/**
 * Restricts a value to be within a specified range.
 * @param value the value to clamp.
 * @param min the min value.
 * @param max the max value.
 */
float clamp(float value, float min, float max) noexcept;

/**
 * Calculates a hermite spline interpolation.
 * @param value1 source position 1.
 * @param tangent1 source tangent 1.
 * @param value2 source position 2.
 * @param tangent2 source tangent 2.
 * @param amount weighting factor.
 */
float hermite(float value1, float tangent1, float value2, float tangent2, float amount) noexcept;

/**
 * Performs a linear interpolation between two vectors.
 * @param value1 first vector
 * @param value2 second vector
 * @param amount value between 0 and 1 indicating the weight of value2.
 * @returns the linear interpolation of the two vectors.
 */
float lerp(float value1, float value2, float amount) noexcept;

/**
 * Returns the lesser of two values
 * @param value1 the first value
 * @param value2 the second value
 */
float min(float value1, float value2) noexcept;

/**
 * Returns the greater of two values
 * @param value1 the first value
 * @param value2 the second value
 */
float max(float value1, float value2) noexcept;

/**
 * Interpolates between two values using a cubic equation.
 * @param value1 first vector
 * @param value2 second vector
 * @param amount weighting value.
 */
float smooth_step(float value1, float value2, float amount) noexcept;

/**
 * Converts the given value in degrees to radians.
 * @param degrees the angle in degress.
 */
float to_radians(float degrees) noexcept;

/**
 * Converts the given value in radians to degrees.
 * @param radians the angle in radians.
 */
float to_degrees(float radians) noexcept;

/**
 * Reduces a given angle to a value between π and -π.
 * @param angle The angle to reduce, in radians.
 */
float wrap_angle(float angle) noexcept;

}}

#endif // SCENER_MATH_HPP
