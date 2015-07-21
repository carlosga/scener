// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <System/Math.hpp>

namespace System
{
    const float Math::E;
    const float Math::Log10E;
    const float Math::Log2E;
    const float Math::Pi;
    const float Math::PiOver2;
    const float Math::PiOver4;
    const float Math::TwoPi;
    const float Math::NegativeInfinity;
    const float Math::PositiveInfinity;
    const float Math::NaN;
    const float Math::Epsilon;
    const float Math::MinValue;
    const float Math::MaxValue;

    bool Math::IsInfinity(const float& f)
    {
        return Math::IsPositiveInfinity(f) || Math::IsNegativeInfinity(f);
    }

    bool Math::IsNegativeInfinity(const float& f)
    {
        return (Math::Equal(f, Math::NegativeInfinity));
    }

    bool Math::IsPositiveInfinity(const float& f)
    {
        return (Math::Equal(f, Math::PositiveInfinity));
    }

    bool Math::IsNaN(const float& f)
    {
        return std::isnan(f);
    }

    float Math::Abs(const float& value)
    {
        return std::abs(value);
    }

    float Math::Acos(const float& value)
    {
        return std::acos(value);
    }

    float Math::Asin(const float& value)
    {
        return std::asin(value);
    }

    float Math::Atan(const float& value)
    {
        return std::atan(value);
    }

    float Math::Atan2(const float& x, const float& y)
    {
        return std::atan2(x, y);
    }

    float Math::Ceiling(const float& value)
    {
        return std::ceil(value);
    }

    float Math::Cos(const float& value)
    {
        return std::cos(value);
    }

    float Math::Cosh(const float& value)
    {
        return std::cosh(value);
    }

    float Math::Exp(const float& d)
    {
        return std::exp(d);
    }

    float Math::Floor(const float& value)
    {
        return std::floor(value);
    }

    float Math::IEEERemainder(const float& x, const float& y)
    {
        // Reference: https://msdn.microsoft.com/es-es/library/system.math.ieeeremainder%28v=vs.110%29.aspx
        // IEEERemainder = dividend - (divisor * Math.Round(dividend / divisor))
        return x - (y * Math::Round(x / y));
    }

    float Math::Round(const float& a)
    {
        return std::round(a);
    }

    float Math::Sin(const float& value)
    {
        return std::sin(value);
    }

    float Math::Sinh(const float& value)
    {
        return std::sinh(value);
    }

    float Math::Sqrt(const float& value)
    {
        return std::sqrt(value);
    }

    float Math::Tan(const float& value)
    {
        return std::tan(value);
    }

    float Math::Tanh(const float& value)
    {
        return std::tanh(value);
    }

    bool Math::Equal(const float& a, const float& b)
    {
        // TODO: Take a look at
        //
        // http://floating-point-gui.de/errors/comparison/
        // https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
        //
        // to take care for edge cases

        return (Math::Abs(a - b) < 1e-5);
    }

    float Math::Barycentric(const float& value1
                          , const float& value2
                          , const float& value3
                          , const float& amount1
                          , const float& amount2)
    {
        // Reference: http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.Math.barycentric(v=xnagamestudio.40).aspx
        //  Pa = ((1 - b2 - b3) * V1a) + (b2 * V2a) + (b3 * V3a);
        //
        // NOTE: DirectX docs have a different formula. http://msdn.microsoft.com/en-us/library/windows/desktop/bb324330(v=vs.85).aspx
        //  v1 + f(v2 - v1) + g(v3 - v1)

        return ((1 - amount1 - amount2) * value1) + (amount1 * value2) + (amount2 * value3);
    }

    float Math::CatmullRom(const float& value1
                         , const float& value2
                         , const float& value3
                         , const float& value4
                         , const float& amount)
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

    float Math::Clamp(const float& value, const float& min, const float& max)
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

    float Math::Hermite(const float& value1
                      , const float& tangent1
                      , const float& value2
                      , const float& tangent2
                      , const float& amount)
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

    float Math::Lerp(const float& value1, const float& value2, const float& amount)
    {
        // Reference: http://msdn.microsoft.com/en-us/library/bb197812.aspx
        return (value1 + (value2 - value1) * amount);
    }

    float Math::Min(const float& value1, const float& value2)
    {
        return ((value1 < value2) ? value1 : value2);
    }

    float Math::Max(const float& value1, const float& value2)
    {
        return ((value1 > value2) ? value1 : value2);
    }

    float Math::SmoothStep(const float& value1, const float& value2, const float& amount)
    {
        // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorlerp(v=vs.85).aspx
        float t = Math::Clamp(amount, 0.0f, 1.0f);

        t = t * t * (3.0f - 2.0f * t);

        return Math::Lerp(value1, value2, t);
    }

    float Math::ToRadians(const float& degrees)
    {
        return static_cast<float>(degrees * Math::Pi / 180.0);
    }

    float Math::ToDegrees(const float& radians)
    {
        return static_cast<float>(radians * 180.0 / Math::Pi);
    }

    float Math::WrapAngle(const float& angle)
    {
        float result = Math::IEEERemainder(angle, Math::TwoPi);

        if (result < -Math::Pi)
        {
            result += Math::TwoPi;
        }

        if (result > Math::Pi)
        {
            result -= Math::TwoPi;
        }

        return result;
    }
}
