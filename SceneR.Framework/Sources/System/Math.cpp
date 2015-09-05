// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <System/Math.hpp>

namespace System
{
    const float Math::e;
    const float Math::log_10E;
    const float Math::log_2E;
    const float Math::pi;
    const float Math::pi_over_2;
    const float Math::pi_over_4;
    const float Math::two_pi;
    const float Math::negative_infinity;
    const float Math::positive_infinity;
    const float Math::nan;
    const float Math::epsilon;
    const float Math::min_value;
    const float Math::max_value;

    bool Math::is_infinity(const float& f)
    {
        return Math::is_positive_infinity(f) || Math::is_negative_infinity(f);
    }

    bool Math::is_negative_infinity(const float& f)
    {
        return (Math::equal(f, Math::negative_infinity));
    }

    bool Math::is_positive_infinity(const float& f)
    {
        return (Math::equal(f, Math::positive_infinity));
    }

    bool Math::is_nan(const float& f)
    {
        return std::isnan(f);
    }

    float Math::abs(const float& value)
    {
        return std::abs(value);
    }

    float Math::acos(const float& value)
    {
        return std::acos(value);
    }

    float Math::asin(const float& value)
    {
        return std::asin(value);
    }

    float Math::atan(const float& value)
    {
        return std::atan(value);
    }

    float Math::atan2(const float& x, const float& y)
    {
        return std::atan2(x, y);
    }

    float Math::ceiling(const float& value)
    {
        return std::ceil(value);
    }

    float Math::cos(const float& value)
    {
        return std::cos(value);
    }

    float Math::cosh(const float& value)
    {
        return std::cosh(value);
    }

    float Math::exp(const float& d)
    {
        return std::exp(d);
    }

    float Math::floor(const float& value)
    {
        return std::floor(value);
    }

    float Math::ieee_remainder(const float& x, const float& y)
    {
        // Reference: https://msdn.microsoft.com/es-es/library/system.math.ieeeremainder%28v=vs.110%29.aspx
        // ieee_remainder = dividend - (divisor * Math.round(dividend / divisor))
        return x - (y * Math::round(x / y));
    }

    float Math::round(const float& a)
    {
        return std::round(a);
    }

    float Math::sin(const float& value)
    {
        return std::sin(value);
    }

    float Math::sinh(const float& value)
    {
        return std::sinh(value);
    }

    float Math::sqrt(const float& value)
    {
        return std::sqrt(value);
    }

    float Math::tan(const float& value)
    {
        return std::tan(value);
    }

    float Math::tanh(const float& value)
    {
        return std::tanh(value);
    }

    bool Math::equal(const float& a, const float& b)
    {
        // TODO: Take a look at
        //
        // http://floating-point-gui.de/errors/comparison/
        // https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
        //
        // to take care for edge cases

        return (a == b);
    }

    float Math::barycentric(const float& value1, const float& value2, const float& value3, const float& amount1,
                            const float& amount2)
    {
        // Reference: http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.Math.barycentric(v=xnagamestudio.40).aspx
        //  Pa = ((1 - b2 - b3) * V1a) + (b2 * V2a) + (b3 * V3a);
        //
        // NOTE: DirectX docs have a different formula. http://msdn.microsoft.com/en-us/library/windows/desktop/bb324330(v=vs.85).aspx
        //  v1 + f(v2 - v1) + g(v3 - v1)

        return ((1 - amount1 - amount2) * value1) + (amount1 * value2) + (amount2 * value3);
    }

    float Math::catmull_rom(const float& value1, const float& value2, const float& value3, const float& value4,
                            const float& amount)
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

    float Math::clamp(const float& value, const float& min, const float& max)
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

    float Math::hermite(const float& value1, const float& tangent1, const float& value2, const float& tangent2,
                        const float& amount)
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

    float Math::lerp(const float& value1, const float& value2, const float& amount)
    {
        // Reference: http://msdn.microsoft.com/en-us/library/bb197812.aspx
        return (value1 + (value2 - value1) * amount);
    }

    float Math::min(const float& value1, const float& value2)
    {
        return ((value1 < value2) ? value1 : value2);
    }

    float Math::max(const float& value1, const float& value2)
    {
        return ((value1 > value2) ? value1 : value2);
    }

    float Math::smooth_step(const float& value1, const float& value2, const float& amount)
    {
        // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorlerp(v=vs.85).aspx
        float t = Math::clamp(amount, 0.0f, 1.0f);

        t = t * t * (3.0f - 2.0f * t);

        return Math::lerp(value1, value2, t);
    }

    float Math::to_radians(const float& degrees)
    {
        return static_cast<float>(degrees * Math::pi / 180.0);
    }

    float Math::to_degrees(const float& radians)
    {
        return static_cast<float>(radians * 180.0 / Math::pi);
    }

    float Math::wrap_angle(const float& angle)
    {
        float result = Math::ieee_remainder(angle, Math::two_pi);

        if (result < -Math::pi)
        {
            result += Math::two_pi;
        }

        if (result > Math::pi)
        {
            result -= Math::two_pi;
        }

        return result;
    }
}
