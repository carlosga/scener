// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <System/Math.hpp>

#include <cmath>

using namespace System;

const Single& Math::E  = M_E;
const Single& Math::Pi = M_PI;

Double Math::Abs(const Double& value)
{
    return std::abs(value);
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

Double Math::Ceiling(const Double& value)
{
    return std::ceil(value);
}

Double Math::Cos(const Double& value)
{
    return std::cos(value);
}

Single Math::Cos(const Single& value)
{
    return std::cos(value);
}

Double Math::Cosh(const Double& value)
{
    return std::cosh(value);
}

Single Math::Cosh(const Single& value)
{
    return std::cosh(value);
}

Double Math::Exp(const Double& d)
{
    return std::exp(d);
}

Double Math::Floor(const Double& value)
{
    return std::floor(value);
}

Single Math::Floor(const Single& value)
{
    return std::floor(value);
}

Double Math::IEEERemainder(const Double& x, const Double& y)
{
    // Reference: https://msdn.microsoft.com/es-es/library/system.math.ieeeremainder%28v=vs.110%29.aspx
    // IEEERemainder = dividend - (divisor * Math.Round(dividend / divisor))
    return x - (y * Math::Round(x / y));
}

Double Math::Round(const Double& a)
{
    return std::round(a);
}

Double Math::Sin(const Double& value)
{
    return std::sin(value);
}

Single Math::Sin(const Single& value)
{
    return std::sin(value);
}

Double Math::Sinh(const Double& value)
{
    return std::sinh(value);
}

Double Math::Sqrt(const Double& value)
{
    return std::sqrt(value);
}

Single Math::Sqrt(const Single& value)
{
    return std::sqrt(value);
}

Double Math::Tan(const Double& value)
{
    return std::tan(value);
}

Single Math::Tan(const Single& value)
{
    return std::tan(value);
}

Double Math::Tanh(const Double& value)
{
    return std::tanh(value);
}

Single Math::Tanh(const Single& value)
{
    return std::tanh(value);
}
