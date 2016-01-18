// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Math/Vector2.hpp"

#include <gsl.h>

#include "SceneR/Math/Math.hpp"
#include "SceneR/Math/Matrix.hpp"

namespace SceneR { namespace Math {

const Vector2 Vector2::one    { 1.0f, 1.0f };
const Vector2 Vector2::unit_x { 1.0f, 0.0f };
const Vector2 Vector2::unit_y { 0.0f, 1.0f };
const Vector2 Vector2::zero   { 0.0f, 0.0f };

Vector2 Vector2::abs(const Vector2& value) noexcept
{
    return { std::abs(value.x), std::abs(value.y) };
}

Vector2 Vector2::square_root(const Vector2& value) noexcept
{
    return { std::sqrt(value.x), std::sqrt(value.y) };
}

Vector2 Vector2::barycentric(const Vector2& value1
                           , const Vector2& value2
                           , const Vector2& value3
                           , float          amount1
                           , float          amount2) noexcept
{
    return { Math::barycentric(value1.x, value2.x, value3.x, amount1, amount2)
           , Math::barycentric(value1.y, value2.y, value3.y, amount1, amount2) };
}

Vector2 Vector2::catmull_rom(const Vector2& value1
                           , const Vector2& value2
                           , const Vector2& value3
                           , const Vector2& value4
                           , float          amount) noexcept
{
    return { Math::catmull_rom(value1.x, value2.x, value3.x, value4.x, amount)
           , Math::catmull_rom(value1.y, value2.y, value3.y, value4.y, amount) };
}

Vector2 Vector2::clamp(const Vector2& value1, const Vector2& min, const Vector2& max) noexcept
{
    return { Math::clamp(value1.x, min.x, max.x)
           , Math::clamp(value1.y, min.y, max.y) };
}

float Vector2::distance(const Vector2& value1, const Vector2& value2) noexcept
{
    auto d = value2 - value1;

    return d.length();
}

float Vector2::distance_squared(const Vector2& value1, const Vector2& value2) noexcept
{
    auto d = value2 - value1;

    return d.length_squared();
}

float Vector2::dot(const Vector2& left, const Vector2& right) noexcept
{
    auto dotProduct = left * right;

    return (dotProduct.x + dotProduct.y);
}

Vector2 Vector2::hermite(const Vector2& value1
                       , const Vector2& tangent1
                       , const Vector2& value2
                       , const Vector2& tangent2
                       , float          amount) noexcept
{
    return { Math::hermite(value1.x, tangent1.x, value2.x, tangent2.x, amount)
           , Math::hermite(value1.y, tangent1.y, value2.y, tangent2.y, amount) };
}

Vector2 Vector2::lerp(const Vector2& value1, const Vector2& value2, float amount) noexcept
{
    return { Math::lerp(value1.x, value2.x, amount)
           , Math::lerp(value1.y, value2.y, amount) };
}

Vector2 Vector2::min(const Vector2& value1, const Vector2& value2) noexcept
{
    return { std::min(value1.x, value2.x)
           , std::min(value1.y, value2.y) };
}

Vector2 Vector2::max(const Vector2& value1, const Vector2& value2) noexcept
{
    return { std::max(value1.x, value2.x)
           , std::max(value1.y, value2.y) };
}

Vector2 Vector2::negate(const Vector2& value) noexcept
{
    return value * -1;
}

Vector2 Vector2::normalize(const Vector2& value) noexcept
{
    // To find the unit vector of another vector, we use the modulus operator
    // and scalar multiplication like so:
    // b = a / |a|
    //
    // Where |a| is the modulus of a
    return (value / value.length());
}

Vector2 Vector2::smooth_step(const Vector2& value1, const Vector2& value2, float amount) noexcept
{
    return { Math::smooth_step(value1.x, value2.x, amount)
           , Math::smooth_step(value1.y, value2.y, amount) };
}

Vector2 Vector2::transform(const Vector2& position, const Matrix& matrix) noexcept
{
    float x = (position.x * matrix.m11)
            + (position.y * matrix.m21)
            +               matrix.m41;

    float y = (position.x * matrix.m12)
            + (position.y * matrix.m22)
            +               matrix.m42;

    return { x, y };
}

Vector2 Vector2::transform_normal(const Vector2& normal, const Matrix& matrix) noexcept
{
    float x = (normal.x * matrix.m11)
            + (normal.y * matrix.m21);

    float y = (normal.x * matrix.m12)
            + (normal.y * matrix.m22);

    return { x, y };
}

Vector2::Vector2() noexcept
    : Vector2 { 0.0f, 0.0f }
{
}

Vector2::Vector2(float value) noexcept
    : Vector2 { value, value }
{
}

Vector2::Vector2(float x, float y) noexcept
    : x { x }
    , y { y }
{
}

float Vector2::length_squared() const noexcept
{
    return (x * x) + (y * y);
}

float Vector2::length() const noexcept
{
    return std::sqrt(length_squared());
}

float& Vector2::operator[](const std::size_t& index) noexcept
{
    Expects(index < 2);

    return (data[index]);
}

const float& Vector2::operator[](const std::size_t& index) const noexcept
{
    Expects(index < 2);

    return (data[index]);
}

bool Vector2::operator==(const Vector2& vector) const noexcept
{
    return (Math::equal(x, vector.x) && Math::equal(y, vector.y));
}

bool Vector2::operator!=(const Vector2& vector) const noexcept
{
    return !(*this == vector);
}

Vector2& Vector2::operator*=(const Vector2& vector) noexcept
{
    x *= vector.x;
    y *= vector.y;

    return *this;
}

Vector2& Vector2::operator*=(const float& value) noexcept
{
    x *= value;
    y *= value;

    return *this;
}

Vector2& Vector2::operator/=(const Vector2& vector) noexcept
{
    x /= vector.x;
    y /= vector.y;

    return *this;
}

Vector2& Vector2::operator/=(const float& value) noexcept
{
    x /= value;
    y /= value;

    return *this;
}

Vector2& Vector2::operator-=(const Vector2& vector) noexcept
{
    x -= vector.x;
    y -= vector.y;

    return *this;
}

Vector2& Vector2::operator+=(const Vector2& vector) noexcept
{
    x += vector.x;
    y += vector.y;

    return *this;
}

Vector2 Vector2::operator*(const Vector2& vector) const noexcept
{
    auto result = *this;

    result *= vector;

    return result;
}

Vector2 Vector2::operator*(const float& value) const noexcept
{
    auto result = *this;

    result *= value;

    return result;
}

Vector2 Vector2::operator/(const Vector2& vector) const noexcept
{
    auto result = *this;

    result /= vector;

    return result;
}

Vector2 Vector2::operator/(const float& value) const noexcept
{
    auto result = *this;

    result /= value;

    return result;
}

Vector2 Vector2::operator-(const Vector2& vector) const noexcept
{
    auto result = *this;

    result -= vector;

    return result;
}

Vector2 Vector2::operator+(const Vector2& vector) const noexcept
{
    auto result = *this;

    result += vector;

    return result;
}

Vector2 Vector2::operator-() const noexcept
{
    return Vector2 { -x, -y };
}

}}
