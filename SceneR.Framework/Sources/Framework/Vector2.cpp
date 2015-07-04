// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/Vector2.hpp>

#include <cassert>

#include <System/Math.hpp>
#include <Framework/Matrix.hpp>

using namespace System;
using namespace SceneR::Framework;

const Vector2 Vector2::One   { 1.0f, 1.0f };
const Vector2 Vector2::UnitX { 1.0f, 0.0f };
const Vector2 Vector2::UnitY { 0.0f, 1.0f };
const Vector2 Vector2::Zero  { 0.0f, 0.0f };

Vector2 Vector2::Abs(const Vector2& value)
{
    return Vector2 { Math::Abs(value.X()), Math::Abs(value.Y()) };
}

Vector2 Vector2::SquareRoot(const Vector2& value)
{
    return Vector2 { Math::Sqrt(value.X()), Math::Sqrt(value.Y()) };
}

Vector2 Vector2::Barycentric(const Vector2& value1
                           , const Vector2& value2
                           , const Vector2& value3
                           , const float&   amount1
                           , const float&   amount2)
{
    return { Math::Barycentric(value1.x, value2.x, value3.x, amount1, amount2)
           , Math::Barycentric(value1.y, value2.y, value3.y, amount1, amount2) };
}

Vector2 Vector2::CatmullRom(const Vector2& value1
                          , const Vector2& value2
                          , const Vector2& value3
                          , const Vector2& value4
                          , const float&   amount)
{
    return { Math::CatmullRom(value1.x, value2.x, value3.x, value4.x, amount)
           , Math::CatmullRom(value1.y, value2.y, value3.y, value4.y, amount) };
}

Vector2 Vector2::Clamp(const Vector2& value1, const Vector2& min, const Vector2& max)
{
    return { Math::Clamp(value1.x, min.x, max.x)
           , Math::Clamp(value1.y, min.y, max.y) };
}

float Vector2::Distance(const Vector2& value1, const Vector2& value2)
{
    auto d = value2 - value1;

    return d.Length();
}

float Vector2::DistanceSquared(const Vector2& value1, const Vector2& value2)
{
    auto d = value2 - value1;

    return d.LengthSquared();
}

float Vector2::DotProduct(const Vector2& left, const Vector2& right)
{
    auto dotProduct = left * right;

    return (dotProduct.x + dotProduct.y);
}

Vector2 Vector2::Hermite(const Vector2& value1
                       , const Vector2& tangent1
                       , const Vector2& value2
                       , const Vector2& tangent2
                       , const float&   amount)
{
    return { Math::Hermite(value1.x, tangent1.x, value2.x, tangent2.x, amount)
           , Math::Hermite(value1.y, tangent1.y, value2.y, tangent2.y, amount) };
}

Vector2 Vector2::Lerp(const Vector2& value1
                    , const Vector2& value2
                    , const float&   amount)
{
    return { Math::Lerp(value1.x, value2.x, amount)
           , Math::Lerp(value1.y, value2.y, amount) };
}

Vector2 Vector2::Min(const Vector2& value1, const Vector2& value2)
{
    return { Math::Min(value1.x, value2.x)
           , Math::Min(value1.y, value2.y) };
}

Vector2 Vector2::Max(const Vector2& value1, const Vector2& value2)
{
    return { Math::Max(value1.x, value2.x)
           , Math::Max(value1.y, value2.y) };
}

Vector2 Vector2::Negate(const Vector2& value)
{
    return value * -1;
}

Vector2 Vector2::Normalize(const Vector2& value)
{
    // To find the unit vector of another vector, we use the modulus operator
    // and scalar multiplication like so:
    // b = a / |a|
    //
    // Where |a| is the modulus of a
    return (value / value.Length());
}

Vector2 Vector2::SmoothStep(const Vector2& value1
                          , const Vector2& value2
                          , const float&   amount)
{
    return { Math::SmoothStep(value1.x, value2.x, amount)
           , Math::SmoothStep(value1.y, value2.y, amount) };
}

Vector2 Vector2::Transform(const Vector2& position, const Matrix& matrix)
{
    float x = (position.X() * matrix.M11())
            + (position.Y() * matrix.M21())
            +                 matrix.M41();

    float y = (position.X() * matrix.M12())
            + (position.Y() * matrix.M22())
            +                 matrix.M42();

    return { x, y };
}

Vector2 Vector2::TransformNormal(const Vector2& normal, const Matrix& matrix)
{
    float x = (normal.x * matrix.M11())
            + (normal.y * matrix.M21());

    float y = (normal.x * matrix.M12())
            + (normal.y * matrix.M22());

    return { x, y };
}

Vector2::Vector2()
    : Vector2 { 0.0f, 0.0f }
{
}

Vector2::Vector2(const float& value)
    : Vector2 { value, value }
{
}

Vector2::Vector2(const float& x, const float& y)
    : x { x }
    , y { y }
{
}

Vector2::Vector2(const Vector2& vector)
    : x { vector.x }
    , y { vector.y }
{
}

Vector2::~Vector2()
{
}

float Vector2::X() const
{
    return this->x;
}

float Vector2::Y() const
{
    return this->y;
}

float Vector2::LengthSquared() const
{
    return (this->x * this->x)
         + (this->y * this->y);
}

float Vector2::Length() const
{
    return Math::Sqrt(this->LengthSquared());
}

float& Vector2::operator[](const std::size_t& index)
{
    assert(index < 2);

    return (this->coords[index]);
}

const float& Vector2::operator[](const std::size_t& index) const
{
    assert(index < 2);

    return (this->coords[index]);
}

Vector2& Vector2::operator=(const Vector2& vector)
{
    if (this != &vector)
    {
        this->x = vector.x;
        this->y = vector.y;
    }

    return *this;
}

bool Vector2::operator==(const Vector2& vector) const
{
    return (Math::Equal(this->x, vector.x) && Math::Equal(this->y, vector.y));
}

bool Vector2::operator!=(const Vector2& vector) const
{
    return !(*this == vector);
}

Vector2& Vector2::operator*=(const Vector2& vector)
{
    this->x *= vector.x;
    this->y *= vector.y;

    return *this;
}

Vector2& Vector2::operator*=(const float& value)
{
    this->x *= value;
    this->y *= value;

    return *this;
}

Vector2& Vector2::operator/=(const Vector2& vector)
{
    this->x /= vector.x;
    this->y /= vector.y;

    return *this;
}

Vector2& Vector2::operator/=(const float& value)
{
    this->x /= value;
    this->y /= value;

    return *this;
}

Vector2& Vector2::operator-=(const Vector2& vector)
{
    this->x -= vector.x;
    this->y -= vector.y;

    return *this;
}

Vector2& Vector2::operator+=(const Vector2& vector)
{
    this->x += vector.x;
    this->y += vector.y;

    return *this;
}

const Vector2 Vector2::operator*(const Vector2& vector) const
{
    auto result = *this;

    result *= vector;

    return result;
}

const Vector2 Vector2::operator*(const float& value) const
{
    auto result = *this;

    result *= value;

    return result;
}

const Vector2 Vector2::operator/(const Vector2& vector) const
{
    auto result = *this;

    result /= vector;

    return result;
}

const Vector2 Vector2::operator/(const float& value) const
{
    auto result = *this;

    result /= value;

    return result;
}

const Vector2 Vector2::operator-(const Vector2& vector) const
{
    auto result = *this;

    result -= vector;

    return result;
}

const Vector2 Vector2::operator-() const
{
    return Vector2 { -this->x, -this->y };
}

const Vector2 Vector2::operator+(const Vector2& vector) const
{
    auto result = *this;

    result += vector;

    return result;
}
