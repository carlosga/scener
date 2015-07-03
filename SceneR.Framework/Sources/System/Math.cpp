// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <System/Math.hpp>

using namespace System;

const Single Math::E;
const Single Math::Log10E;
const Single Math::Log2E;
const Single Math::Pi;
const Single Math::PiOver2;
const Single Math::PiOver4;
const Single Math::TwoPi;
const Single Math::NegativeInfinity;
const Single Math::PositiveInfinity;
const Single Math::NaN;
const Single Math::Epsilon;
const Single Math::MinValue;
const Single Math::MaxValue;

bool Math::IsInfinity(const System::Single& f)
{
    return Math::IsPositiveInfinity(f) || Math::IsNegativeInfinity(f);
}

bool Math::IsNegativeInfinity(const System::Single& f)
{
    return (Math::Equal(f, Math::NegativeInfinity));
}

bool Math::IsPositiveInfinity(const System::Single& f)
{
    return (Math::Equal(f, Math::PositiveInfinity));
}

bool Math::IsNaN(const System::Single& f)
{
    return std::isnan(f);
}

Single Math::Abs(const Single& value)
{
    return std::abs(value);
}

Single Math::Acos(const Single& value)
{
    return std::acos(value);
}

Single Math::Asin(const Single& value)
{
    return std::asin(value);
}

Single Math::Atan(const Single& value)
{
    return std::atan(value);
}

Single Math::Atan2(const Single& x, const Single& y)
{
    return std::atan2(x, y);
}

Single Math::Ceiling(const Single& value)
{
    return std::ceil(value);
}

Single Math::Cos(const Single& value)
{
    return std::cos(value);
}

Single Math::Cosh(const Single& value)
{
    return std::cosh(value);
}

Single Math::Exp(const Single& d)
{
    return std::exp(d);
}

Single Math::Floor(const Single& value)
{
    return std::floor(value);
}

Single Math::IEEERemainder(const Single& x, const Single& y)
{
    // Reference: https://msdn.microsoft.com/es-es/library/system.math.ieeeremainder%28v=vs.110%29.aspx
    // IEEERemainder = dividend - (divisor * Math.Round(dividend / divisor))
    return x - (y * Math::Round(x / y));
}

Single Math::Round(const Single& a)
{
    return std::round(a);
}

Single Math::Sin(const Single& value)
{
    return std::sin(value);
}

Single Math::Sinh(const Single& value)
{
    return std::sinh(value);
}

Single Math::Sqrt(const Single& value)
{
    return std::sqrt(value);
}

Single Math::Tan(const Single& value)
{
    return std::tan(value);
}

Single Math::Tanh(const Single& value)
{
    return std::tanh(value);
}

bool Math::Equal(const Single& a, const Single& b)
{
    // TODO: Take a look at
    //
    // http://floating-point-gui.de/errors/comparison/
    // https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
    //
    // to take care for edge cases

    return (a == b);
}

Single Math::Barycentric(const Single& value1
                       , const Single& value2
                       , const Single& value3
                       , const Single& amount1
                       , const Single& amount2)
{
    // Reference: http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.Math.barycentric(v=xnagamestudio.40).aspx
    //  Pa = ((1 - b2 - b3) * V1a) + (b2 * V2a) + (b3 * V3a);
    //
    // NOTE: DirectX docs have a different formula. http://msdn.microsoft.com/en-us/library/windows/desktop/bb324330(v=vs.85).aspx
    //  v1 + f(v2 - v1) + g(v3 - v1)

    return ((1 - amount1 - amount2) * value1) + (amount1 * value2) + (amount2 * value3);
}

Single Math::CatmullRom(const Single& value1
                      , const Single& value2
                      , const Single& value3
                      , const Single& value4
                      , const Single& amount)
{
    // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/bb324331(v=vs.85).aspx
    // Q(s) = [(-s3 + 2s2 - s)p1 + (3s3 - 5s2 + 2)p2 + (-3s3 + 4s2 + s)p3 + (s3 - s2)p4] / 2;

    Single s3 = amount * amount * amount;
    Single s2 = amount * amount;
    Single s  = amount;

    return ((-s3 + 2.0f * s2 - s)          * value1
          + (3.0f * s3 - 5.0f * s2 + 2.0f) * value2
          + (-3.0f * s3 + 4.0f * s2 + s)   * value3
          + (s3 - s2) * value4) / 2;
}

Single Math::Clamp(const Single& value, const Single& min, const Single& max)
{
    Single maxValue = ((max < min) ? min : max);

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

Single Math::Hermite(const Single& value1
                   , const Single& tangent1
                   , const Single& value2
                   , const Single& tangent2
                   , const Single& amount)
{
    // Reference: http://cubic.org/docs/hermite.htm
    // h1(s) =  2s^3 - 3s^2 + 1
    // h2(s) = -2s^3 + 3s^2
    // h3(s) =   s^3 - 2s^2 + s
    // h4(s) =   s^3 -  s^2
    //
    // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/bb324340(v=vs.85).aspx
    // Q(s) = (2s3 - 3s2 + 1)v1 + (-2s3 + 3s2)v2 + (s3 - 2s2 + s)t1 + (s3 - s2)t2.

    Single s3 = amount * amount * amount;
    Single s2 = amount * amount;

    return (2.0f  * s3 - 3.0f * s2 + 1.0f) * value1
         + (-2.0f * s3 + 3.0f * s2)        * value2
         + (s3    - 2.0f  * s2 + amount)   * tangent1
         + (s3    - s2)                    * tangent2;
}

Single Math::Lerp(const Single& value1, const Single& value2, const Single& amount)
{
    // Reference: http://msdn.microsoft.com/en-us/library/bb197812.aspx
    return (value1 + (value2 - value1) * amount);
}

Single Math::Min(const Single& value1, const Single& value2)
{
    return ((value1 < value2) ? value1 : value2);
}

Single Math::Max(const Single& value1, const Single& value2)
{
    return ((value1 > value2) ? value1 : value2);
}

Single Math::SmoothStep(const Single& value1, const Single& value2, const Single& amount)
{
    // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorlerp(v=vs.85).aspx
    Single t = Math::Clamp(amount, 0.0f, 1.0f);

    t = t * t * (3.0f - 2.0f * t);

    return Math::Lerp(value1, value2, t);
}

Single Math::ToRadians(const Single& degrees)
{
    return (degrees * Math::Pi / 180.0);
}

Single Math::ToDegrees(const Single& radians)
{
    return (radians * 180.0 / Math::Pi);
}

System::Single Math::WrapAngle(const System::Single& angle)
{
    Single result = Math::IEEERemainder(angle, Math::TwoPi);

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
