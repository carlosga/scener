// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/MathHelper.hpp>

#include <cassert>
#include <cmath>
#include <limits>

#include <System/Math.hpp>

using namespace System;
using namespace SceneR::Framework;

const Single& MathHelper::E                = M_E;
const Single& MathHelper::Log10E           = M_LOG10E;
const Single& MathHelper::Log2E            = M_LOG2E;
const Single& MathHelper::Pi               = M_PI;
const Single& MathHelper::PiOver2          = M_PI_2;
const Single& MathHelper::PiOver4          = M_PI_4;
const Single& MathHelper::TwoPi            = M_2_PI;
const Single& MathHelper::NegativeInfinity = -std::numeric_limits<Single>::infinity();
const Single& MathHelper::PositiveInfinity = std::numeric_limits<Single>::infinity();
const Single& MathHelper::NaN              = std::numeric_limits<Single>::quiet_NaN();

Boolean MathHelper::IsInfinity(const System::Single& f)
{
    return MathHelper::IsPositiveInfinity(f) || MathHelper::IsNegativeInfinity(f);
}

Boolean MathHelper::IsNegativeInfinity(const System::Single& f)
{
    return (f == MathHelper::NegativeInfinity);
}

Boolean MathHelper::IsPositiveInfinity(const System::Single& f)
{
    return (f == MathHelper::PositiveInfinity);
}

Boolean MathHelper::IsNaN(const System::Single& f)
{
    return std::isnan(f);
}

Single MathHelper::Barycentric(const Single& value1
                             , const Single& value2
                             , const Single& value3
                             , const Single& amount1
                             , const Single& amount2)
{
    // Reference: http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.mathhelper.barycentric(v=xnagamestudio.40).aspx
    //  Pa = ((1 - b2 - b3) * V1a) + (b2 * V2a) + (b3 * V3a);
    //
    // NOTE: DirectX docs have a different formula. http://msdn.microsoft.com/en-us/library/windows/desktop/bb324330(v=vs.85).aspx
    //  v1 + f(v2 - v1) + g(v3 - v1)

    return ((1 - amount1 - amount2) * value1) + (amount1 * value2) + (amount2 * value3);
}

Single MathHelper::CatmullRom(const Single& value1
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

Single MathHelper::Clamp(const Single& value, const Single& min, const Single& max)
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

Single MathHelper::Hermite(const Single& value1
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

Single MathHelper::Lerp(const Single& value1, const Single& value2, const Single& amount)
{
    // Reference: http://msdn.microsoft.com/en-us/library/bb197812.aspx
    return (value1 + (value2 - value1) * amount);
}

Single MathHelper::Min(const Single& value1, const Single& value2)
{
    return ((value1 < value2) ? value1 : value2);
}

Single MathHelper::Max(const Single& value1, const Single& value2)
{
    return ((value1 > value2) ? value1 : value2);
}

Single MathHelper::SmoothStep(const Single& value1, const Single& value2, const Single& amount)
{
    // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorlerp(v=vs.85).aspx
    Single t = MathHelper::Clamp(amount, 0.0f, 1.0f);

    t = t * t * (3.0f - 2.0f * t);

    return MathHelper::Lerp(value1, value2, t);
}

Single MathHelper::ToRadians(const Single& degrees)
{
    return (degrees * MathHelper::Pi / 180.0);
}

Single MathHelper::ToDegrees(const Single& radians)
{
    return (radians * 180.0 / MathHelper::Pi);
}

System::Single MathHelper::WrapAngle(const System::Single& angle)
{
    Single result = Math::IEEERemainder(angle, MathHelper::TwoPi);

    if (result < -MathHelper::Pi)
    {
        result += MathHelper::TwoPi;
    }

    if (result > MathHelper::Pi)
    {
        result -= MathHelper::TwoPi;
    }

    return result;
}
