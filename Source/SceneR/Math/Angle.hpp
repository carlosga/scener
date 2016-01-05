// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_ANGLE_HPP
#define SCENER_MATH_ANGLE_HPP

#include <cmath>

#include "SceneR/Math/Math.hpp"

namespace SceneR { namespace Math {

template <typename T>
struct DegreesUnit
{
    static const T pi() noexcept
    {
        return static_cast<T>(180);
    }
};

template <typename T>
struct RadiansUnit
{
    static const T pi() noexcept
    {
        return std::acos(-1);
    }
};

template <typename T, typename Unit = RadiansUnit<T>>
class Angle
{
public:
    typedef T    value_type;
    typedef Unit unit_type;

public:
    Angle(T value = static_cast<T>(0)) noexcept
        : _value(value)
    {
    }

    Angle(const Angle& value) = default;
    ~Angle() = default;

public:
    Angle wrap() const noexcept
    {
        return Angle<T, Unit>(Math::wrap_angle(_value));
    }

    T value() const noexcept
    {
        return _value;
    }

public:
    Angle& operator=(const Angle& angle) = default;

    bool operator==(const Angle& angle) const noexcept
    {
        return _value == angle._value;
    }

    bool operator!=(const Angle& angle) const noexcept
    {
        return !(*this == angle);
    }

    Angle& operator*=(const Angle& angle) noexcept
    {
        _value *= angle._value;

        return *this;
    }

    Angle& operator*=(const T& value) noexcept
    {
        _value *= value;

        return *this;
    }

    Angle& operator/=(const Angle& angle) noexcept
    {
        _value /= angle.value;

        return *this;
    }

    Angle& operator/=(const T& value) noexcept
    {
        _value /= value;

        return *this;
    }

    Angle& operator-=(const Angle& angle) noexcept
    {
        _value -= angle.value;

        return *this;
    }

    Angle& operator+=(const Angle& angle) noexcept
    {
        _value += angle.value;
    }

    const Angle operator*(const Angle& angle) const noexcept
    {
        auto result = *this;

        result *= angle;

        return result;
    }

    const Angle operator*(const T& value) const noexcept
    {
        auto result = *this;

        result *= value;

        return result;
    }

    const Angle operator/(const Angle& angle) const noexcept
    {
        auto result = *this;

        result /= angle;

        return result;
    }

    const Angle operator/(const T& value) const noexcept
    {
        auto result = *this;

        result /= value;

        return result;
    }

    const Angle operator-(const Angle& angle) const noexcept
    {
        auto result = *this;

        result -= angle;

        return result;
    }

    const Angle operator-() const noexcept
    {
        auto result = *this;

        result *= -1;

        return result;
    }

    const Angle operator+(const Angle& angle) const noexcept
    {
        auto result = *this;

        result += angle;

        return result;
    }

    template <typename K, typename Unit2>
    operator Angle<K, Unit2>() const noexcept
    {
        return Angle<K, Unit2>(_value * Unit2::pi() / Unit::pi());
    }

private:
    T _value;
};

using Radians = Angle<float, RadiansUnit<float>>;
using Degrees = Angle<float, DegreesUnit<float>>;

}}

#endif // SCENER_MATH_ANGLE_HPP
