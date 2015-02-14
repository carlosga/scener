// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/Vector4.hpp>

#include <cassert>
#include <cmath>

#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/MathHelper.hpp>

using namespace System;
using namespace SceneR::Framework;

const Vector4 Vector4::One   { 1.0f, 1.0f, 1.0f, 1.0f };
const Vector4 Vector4::UnitX { 1.0f, 0.0f, 0.0f, 0.0f };
const Vector4 Vector4::UnitY { 0.0f, 1.0f, 0.0f, 0.0f };
const Vector4 Vector4::UnitZ { 0.0f, 0.0f, 1.0f, 0.0f };
const Vector4 Vector4::UnitW { 0.0f, 0.0f, 0.0f, 1.0f };
const Vector4 Vector4::Zero  { 0.0f, 0.0f, 0.0f, 0.0f };

Vector4 Vector4::Barycentric(const Vector4& value1
                           , const Vector4& value2
                           , const Vector4& value3
                           , const Single&  amount1
                           , const Single&  amount2)
{
    return { MathHelper::Barycentric(value1.x, value2.x, value3.x, amount1, amount2)
           , MathHelper::Barycentric(value1.y, value2.y, value3.y, amount1, amount2)
           , MathHelper::Barycentric(value1.z, value2.z, value3.z, amount1, amount2)
           , MathHelper::Barycentric(value1.w, value2.w, value3.w, amount1, amount2) };
}

Vector4 Vector4::CatmullRom(const Vector4& value1
                          , const Vector4& value2
                          , const Vector4& value3
                          , const Vector4& value4
                          , const Single&  amount)
{
    return { MathHelper::CatmullRom(value1.x, value2.x, value3.x, value4.x, amount)
           , MathHelper::CatmullRom(value1.y, value2.y, value3.y, value4.y, amount)
           , MathHelper::CatmullRom(value1.z, value2.z, value3.z, value4.z, amount)
           , MathHelper::CatmullRom(value1.w, value2.w, value3.w, value4.w, amount) };
}

Vector4 Vector4::Clamp(const Vector4& value1, const Vector4& min, const Vector4& max)
{
    return { MathHelper::Clamp(value1.x, min.x, max.x)
           , MathHelper::Clamp(value1.y, min.y, max.y)
           , MathHelper::Clamp(value1.z, min.z, max.z)
           , MathHelper::Clamp(value1.w, min.w, max.w) };
}

Single Vector4::Distance(const Vector4& value1, const Vector4& value2)
{
    auto d = value2 - value1;

    return d.Length();
}

Single Vector4::DistanceSquared(const Vector4& value1, const Vector4& value2)
{
    auto d = value2 - value1;

    return d.LengthSquared();
}

Single Vector4::Dot(const Vector4& value1, const Vector4& value2)
{
    auto dotProduct = value1 * value2;

    return (dotProduct.x + dotProduct.y + dotProduct.z + dotProduct.w);
}

Vector4 Vector4::Hermite(const Vector4& value1
                       , const Vector4& tangent1
                       , const Vector4& value2
                       , const Vector4& tangent2
                       , const Single&  amount)
{
    return { MathHelper::Hermite(value1.x, tangent1.x, value2.x, tangent2.x, amount)
           , MathHelper::Hermite(value1.y, tangent1.y, value2.y, tangent2.y, amount)
           , MathHelper::Hermite(value1.z, tangent1.z, value2.z, tangent2.z, amount)
           , MathHelper::Hermite(value1.w, tangent1.w, value2.w, tangent2.w, amount) };
}

Vector4 Vector4::Lerp(const Vector4& value1
                    , const Vector4& value2
                    , const Single&  amount)
{
    assert(amount >= 0.0f && amount < 1.0f);

    return { MathHelper::Lerp(value1.x, value2.x, amount)
           , MathHelper::Lerp(value1.y, value2.y, amount)
           , MathHelper::Lerp(value1.z, value2.z, amount)
           , MathHelper::Lerp(value1.w, value2.w, amount) };
}

Vector4 Vector4::Negate(const Vector4& value)
{
    return value * -1;
}

Vector4 Vector4::Normalize(const Vector4& value)
{
    return (value / value.Length());
}

Vector4 Vector4::SmoothStep(const Vector4& value1
                          , const Vector4& value2
                          , const Single&  amount)
{
    return { MathHelper::SmoothStep(value1.x, value2.x, amount)
           , MathHelper::SmoothStep(value1.y, value2.y, amount)
           , MathHelper::SmoothStep(value1.z, value2.z, amount)
           , MathHelper::SmoothStep(value1.w, value2.w, amount) };
}

Vector4::Vector4()
    : Vector4 { 0.0f, 0.0f, 0.0f, 1.0f }
{
}

Vector4::Vector4(const System::Single& value)
    : Vector4 { value, value, value, value }
{
}

Vector4::Vector4(const Vector3& value, const System::Single& w)
    : Vector4 { value.X(), value.Y(), value.Z(), w }
{
}

Vector4::Vector4(const Single& x, const Single& y, const Single& z)
    : Vector4 { x, y, z, 1.0f }
{
}

Vector4::Vector4(const Vector2& value, const System::Single& z, const Single& w)
    : Vector4 { value.X(), value.Y(), z, w }
{
}

Vector4::Vector4(const Single& x, const Single& y, const Single& z, const Single& w)
    : x { x }
    , y { y }
    , z { z }
    , w { w }
{
}

Vector4::Vector4(const Vector4& vector)
    : x { vector.x }
    , y { vector.y }
    , z { vector.z }
    , w { vector.w }
{
}

const Single& Vector4::X() const
{
    return this->x;
}

const Single& Vector4::Y() const
{
    return this->y;
}

const Single& Vector4::Z() const
{
    return this->z;
}

const Single& Vector4::W() const
{
    return this->w;
}

Single Vector4::LengthSquared() const
{
    return (this->x * this->x)
         + (this->y * this->y)
         + (this->z * this->z)
         + (this->w * this->w);
}

Single Vector4::Length() const
{
    return std::sqrt(this->LengthSquared());
}

Single& Vector4::operator[](const Size& index)
{
    assert(index < 4);

    return (this->vector[index]);
}

const Single& Vector4::operator[](const Size& index) const
{
    assert(index < 4);

    return (this->vector[index]);
}

Vector4& Vector4::operator=(const Vector4& vector)
{
    if (this != &vector)
    {
        this->x = vector.x;
        this->y = vector.y;
        this->z = vector.z;
        this->w = vector.w;
    }

    return *this;
}

bool Vector4::operator==(const Vector4& vector) const
{
    return (this->x == vector.x
         && this->y == vector.y
         && this->z == vector.z
         && this->w == vector.w);
}

bool Vector4::operator!=(const Vector4& vector) const
{
    return !(*this == vector);
}

Vector4& Vector4::operator*=(const Vector4& vector)
{
    this->x *= vector.x;
    this->y *= vector.y;
    this->z *= vector.z;
    this->w *= vector.w;

    return *this;
}

Vector4& Vector4::operator*=(const Single& value)
{
    this->x *= value;
    this->y *= value;
    this->z *= value;
    this->w *= value;

    return *this;
}

Vector4& Vector4::operator/=(const Vector4& vector)
{
    this->x /= vector.x;
    this->y /= vector.y;
    this->z /= vector.z;
    this->w /= vector.w;

    return *this;
}

Vector4& Vector4::operator/=(const Single& value)
{
    this->x /= value;
    this->y /= value;
    this->z /= value;
    this->w /= value;

    return *this;
}

Vector4& Vector4::operator-=(const Vector4& vector)
{
    this->x -= vector.x;
    this->y -= vector.y;
    this->z -= vector.z;
    this->w -= vector.w;

    return *this;
}

Vector4& Vector4::operator+=(const Vector4& vector)
{
    this->x += vector.x;
    this->y += vector.y;
    this->z += vector.z;
    this->w += vector.w;

    return *this;
}

const Vector4 Vector4::operator*(const Vector4& vector) const
{
    auto result = *this;

    result *= vector;

    return result;
}

const Vector4 Vector4::operator*(const Single& value) const
{
    auto result = *this;

    result *= value;

    return result;
}

const Vector4 Vector4::operator*(const Matrix& matrix) const
{
    Single x = (this->x * matrix.M11())
             + (this->y * matrix.M21())
             + (this->z * matrix.M31())
             + (this->w * matrix.M41());

    Single y = (this->x * matrix.M12())
             + (this->y * matrix.M22())
             + (this->z * matrix.M32())
             + (this->w * matrix.M42());

    Single z = (this->x * matrix.M13())
             + (this->y * matrix.M23())
             + (this->z * matrix.M33())
             + (this->w * matrix.M43());

    Single w = (this->x * matrix.M14())
             + (this->y * matrix.M24())
             + (this->z * matrix.M34())
             + (this->w * matrix.M44());

    return { x, y, z, w };
}

const Vector4 Vector4::operator/(const Vector4& vector) const
{
    auto result = *this;

    result /= vector;

    return result;
}

const Vector4 Vector4::operator/(const Single& value) const
{
    auto result = *this;

    result /= value;

    return result;
}

const Vector4 Vector4::operator-(const Vector4& vector) const
{
    auto result = *this;

    result -= vector;

    return result;
}

const Vector4 Vector4::operator+(const Vector4& vector) const
{
    auto result = *this;

    result += vector;

    return result;
}
