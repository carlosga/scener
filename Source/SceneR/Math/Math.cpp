// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Math/Math.hpp"

namespace SceneR {  namespace Math {

bool is_infinity(float f) noexcept
{
    return is_positive_infinity(f) || is_negative_infinity(f);
}

bool is_negative_infinity(float f) noexcept
{
    return (equal(f, negative_infinity));
}

bool is_positive_infinity(float f) noexcept
{
    return (equal(f, positive_infinity));
}

bool is_nan(float f) noexcept
{
    return std::isnan(f);
}

float abs(float value) noexcept
{
    return std::abs(value);
}

float acos(float value) noexcept
{
    return std::acos(value);
}

float asin(float value) noexcept
{
    return std::asin(value);
}

float atan(float value) noexcept
{
    return std::atan(value);
}

float atan2(float x, float y) noexcept
{
    return std::atan2(x, y);
}

float ceiling(float value) noexcept
{
    return std::ceil(value);
}

float cos(float value) noexcept
{
    return std::cos(value);
}

float cosh(float value) noexcept
{
    return std::cosh(value);
}

float exp(float d) noexcept
{
    return std::exp(d);
}

float floor(float value) noexcept
{
    return std::floor(value);
}

float ieee_remainder(float x, float y) noexcept
{
    // Reference: https://msdn.microsoft.com/es-es/library/system.math.ieeeremainder%28v=vs.110%29.aspx
    // ieee_remainder = dividend - (divisor * Math.round(dividend / divisor))
    return x - (y * round(x / y));
}

float round(float a) noexcept
{
    return std::round(a);
}

float sin(float value) noexcept
{
    return std::sin(value);
}

float sinh(float value) noexcept
{
    return std::sinh(value);
}

float sqrt(float value) noexcept
{
    return std::sqrt(value);
}

float tan(float value) noexcept
{
    return std::tan(value);
}

float tanh(float value) noexcept
{
    return std::tanh(value);
}

bool equal(float a, float b) noexcept
{
    // TODO: Take a look at
    //
    // http://floating-point-gui.de/errors/comparison/
    // https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
    //
    // to take care for edge cases

    return (a == b);
}

float barycentric(float value1, float value2, float value3, float amount1, float amount2) noexcept
{
    // Reference: http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.Math.barycentric(v=xnagamestudio.40).aspx
    //  Pa = ((1 - b2 - b3) * V1a) + (b2 * V2a) + (b3 * V3a);
    //
    // NOTE: DirectX docs have a different formula. http://msdn.microsoft.com/en-us/library/windows/desktop/bb324330(v=vs.85).aspx
    //  v1 + f(v2 - v1) + g(v3 - v1)

    return ((1 - amount1 - amount2) * value1) + (amount1 * value2) + (amount2 * value3);
}

float catmull_rom(float value1, float value2, float value3, float value4, float amount) noexcept
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

float clamp(float value, float min, float max) noexcept
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

float hermite(float value1, float tangent1, float value2, float tangent2, float amount) noexcept
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

float lerp(float value1, float value2, float amount) noexcept
{
    // Reference: http://msdn.microsoft.com/en-us/library/bb197812.aspx
    return (value1 + (value2 - value1) * amount);
}

float min(float value1, float value2) noexcept
{
    return ((value1 < value2) ? value1 : value2);
}

float max(float value1, float value2) noexcept
{
    return ((value1 > value2) ? value1 : value2);
}

float smooth_step(float value1, float value2, float amount) noexcept
{
    // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorlerp(v=vs.85).aspx
    float t = clamp(amount, 0.0f, 1.0f);

    t = t * t * (3.0f - 2.0f * t);

    return lerp(value1, value2, t);
}

float to_radians(float degrees) noexcept
{
    return static_cast<float>(degrees * pi / 180.0);
}

float to_degrees(float radians) noexcept
{
    return static_cast<float>(radians * 180.0 / pi);
}

float wrap_angle(float angle) noexcept
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
