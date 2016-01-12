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
    static constexpr T pi() noexcept
    {
        return static_cast<T>(180);
    }
};

template <typename T>
struct RadiansUnit
{
    static constexpr T pi() noexcept
    {
        return static_cast<T>(Math::pi);
    }
};

template <typename T, typename Unit = RadiansUnit<T>, typename = std::enable_if_t<std::is_floating_point<T>::value>>
class Angle
{
public:
    typedef T    value_type;
    typedef Unit unit_type;

public:
   inline Angle(T value = static_cast<T>(0)) noexcept
        : _value(value)
    {
    }

    Angle(const Angle& value) = default;
    ~Angle() = default;

public:
   inline  Angle wrap() const noexcept
    {
        return Angle<T, Unit>(Math::wrap_angle(_value));
    }

    inline T value() const noexcept
    {
        return _value;
    }

public:
    Angle& operator=(const Angle& angle) = default;

    inline bool operator==(const Angle& angle) const noexcept
    {
        return _value == angle._value;
    }

    inline bool operator!=(const Angle& angle) const noexcept
    {
        return !(*this == angle);
    }

    inline Angle& operator*=(const Angle& angle) noexcept
    {
        _value *= angle._value;

        return *this;
    }

    inline Angle& operator*=(const T& value) noexcept
    {
        _value *= value;

        return *this;
    }

    inline Angle& operator/=(const Angle& angle) noexcept
    {
        _value /= angle.value;

        return *this;
    }

    inline Angle& operator/=(const T& value) noexcept
    {
        _value /= value;

        return *this;
    }

    inline Angle& operator-=(const Angle& angle) noexcept
    {
        _value -= angle.value;

        return *this;
    }

    inline Angle& operator+=(const Angle& angle) noexcept
    {
        _value += angle.value;
    }

    inline const Angle operator*(const Angle& angle) const noexcept
    {
        auto result = *this;

        result *= angle;

        return result;
    }

    inline const Angle operator*(const T& value) const noexcept
    {
        auto result = *this;

        result *= value;

        return result;
    }

    inline const Angle operator/(const Angle& angle) const noexcept
    {
        auto result = *this;

        result /= angle;

        return result;
    }

    inline const Angle operator/(const T& value) const noexcept
    {
        auto result = *this;

        result /= value;

        return result;
    }

    inline const Angle operator-(const Angle& angle) const noexcept
    {
        auto result = *this;

        result -= angle;

        return result;
    }

    inline const Angle operator-() const noexcept
    {
        auto result = *this;

        result *= -1;

        return result;
    }

    inline const Angle operator+(const Angle& angle) const noexcept
    {
        auto result = *this;

        result += angle;

        return result;
    }

    template <typename K, typename Unit2>
    inline operator Angle<K, Unit2>() const noexcept
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
