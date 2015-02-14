// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/Vector3.hpp>

#include <cassert>
#include <cmath>

#include <Framework/Vector2.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/MathHelper.hpp>

using namespace System;
using namespace SceneR::Framework;

const Vector3 Vector3::Backward { 0.0f , 0.0f , 1.0f  };
const Vector3 Vector3::Down     { 0.0f , -1.0f, 0.0f  };
const Vector3 Vector3::Forward  { 0.0f , 0.0f , -1.0f };
const Vector3 Vector3::Left     { -1.0f, 0.0f , 0.0f  };
const Vector3 Vector3::One      { 1.0f , 1.0f , 1.0f  };
const Vector3 Vector3::Right    { 1.0f , 0.0f , 0.0f  };
const Vector3 Vector3::UnitX    { 1.0f , 0.0f , 0.0f  };
const Vector3 Vector3::UnitY    { 0.0f , 1.0f , 0.0f  };
const Vector3 Vector3::UnitZ    { 0.0f , 0.0f , 1.0f  };
const Vector3 Vector3::Up       { 0.0f , 1.0f , 0.0f  };
const Vector3 Vector3::Zero     { 0.0f , 0.0f , 0.0f  };

Single Vector3::AngleBetween(const Vector3& left, const Vector3& right)
{
    Single lengthSquared = left.LengthSquared() * right.LengthSquared();

    return std::acos(Vector3::Dot(left, right) / std::sqrt(lengthSquared));
}

Vector3 Vector3::Barycentric(const Vector3& value1
                           , const Vector3& value2
                           , const Vector3& value3
                           , const Single&  amount1
                           , const Single&  amount2)
{
    return { MathHelper::Barycentric(value1.x, value2.x, value3.x, amount1, amount2)
           , MathHelper::Barycentric(value1.y, value2.y, value3.y, amount1, amount2)
           , MathHelper::Barycentric(value1.z, value2.z, value3.z, amount1, amount2) };
}

Vector3 Vector3::CatmullRom(const Vector3& value1
                          , const Vector3& value2
                          , const Vector3& value3
                          , const Vector3& value4
                          , const System::Single& amount)
{
    return { MathHelper::CatmullRom(value1.x, value2.x, value3.x, value4.x, amount)
           , MathHelper::CatmullRom(value1.y, value2.y, value3.y, value4.y, amount)
           , MathHelper::CatmullRom(value1.z, value2.z, value3.z, value4.z, amount) };
}

Vector3 Vector3::Clamp(const Vector3& value1, const Vector3& min, const Vector3& max)
{
    return { MathHelper::Clamp(value1.x, min.x, max.x)
           , MathHelper::Clamp(value1.y, min.y, max.y)
           , MathHelper::Clamp(value1.z, min.z, max.z) };
}

Vector3 Vector3::Cross(const Vector3& left, const Vector3& right)
{
    // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector3cross(v=vs.85).aspx
    return { (left.y * right.z) - (left.z * right.y)
           , (left.z * right.x) - (left.x * right.z)
           , (left.x * right.y) - (left.y * right.x) };
}

Single Vector3::Distance(const Vector3& value1, const Vector3& value2)
{
    auto d = value2 - value1;

    return d.Length();
}

Single Vector3::DistanceSquared(const Vector3& value1, const Vector3& value2)
{
    auto d = value2 - value1;

    return d.LengthSquared();
}

Single Vector3::Dot(const Vector3& left, const Vector3& right)
{
    // The definition of the scalar (dot) product is:
    // a · b = |a||b|cosθ
    //
    // The scalar product can also be written in terms of Cartesian components as:
    // a · b = x1x2 + y1y2 + z1z2

    auto dotProduct = left * right;

    return (dotProduct.x + dotProduct.y + dotProduct.z);
}

Vector3 Vector3::Hermite(const Vector3& value1
                       , const Vector3& tangent1
                       , const Vector3& value2
                       , const Vector3& tangent2
                       , const Single&  amount)
{
    return { MathHelper::Hermite(value1.x, tangent1.x, value2.x, tangent2.x, amount)
           , MathHelper::Hermite(value1.y, tangent1.y, value2.y, tangent2.y, amount)
           , MathHelper::Hermite(value1.z, tangent1.z, value2.z, tangent2.z, amount) };
}

Vector3 Vector3::Lerp(const Vector3& value1, const Vector3& value2, const Single& amount)
{
    assert(amount >= 0.0f && amount < 1.0f);

    return { MathHelper::Lerp(value1.x, value2.x, amount)
           , MathHelper::Lerp(value1.y, value2.y, amount)
           , MathHelper::Lerp(value1.z, value2.z, amount) };
}

Vector3 Vector3::Min(const Vector3& value1, const Vector3& value2)
{
    return { MathHelper::Min(value1.x, value2.x)
           , MathHelper::Min(value1.y, value2.y)
           , MathHelper::Min(value1.z, value2.z) };
}

Vector3 Vector3::Max(const Vector3& value1, const Vector3& value2)
{
    return { MathHelper::Max(value1.x, value2.x)
           , MathHelper::Max(value1.y, value2.y)
           , MathHelper::Max(value1.z, value2.z) };
}

Vector3 Vector3::Negate(const Vector3& value)
{
    return (value * -1.0f);
}

Vector3 Vector3::Normalize(const Vector3& value)
{
    // To find the unit vector of another vector, we use the modulus operator
    // and scalar multiplication like so:
    // b = a / |a|
    //
    // Where |a| is the modulus of a
    return (value / value.Length());
}

Vector3 Vector3::SmoothStep(const Vector3& value1, const Vector3& value2, const Single& amount)
{
    return { MathHelper::SmoothStep(value1.x, value2.x, amount)
           , MathHelper::SmoothStep(value1.y, value2.y, amount)
           , MathHelper::SmoothStep(value1.z, value2.z, amount) };
}

Vector3 Vector3::Transform(const Vector3& position, const Matrix& matrix)
{
    return (position * matrix);
}

Vector3 Vector3::TransformNormal(const Vector3& normal, const Matrix& matrix)
{
    Single x = (normal.x * matrix.M11())
             + (normal.y * matrix.M21())
             + (normal.z * matrix.M31());

    Single y = (normal.x * matrix.M12())
             + (normal.y * matrix.M22())
             + (normal.z * matrix.M32());

    Single z = (normal.x * matrix.M13())
             + (normal.y * matrix.M23())
             + (normal.z * matrix.M33());

    return { x, y, z };
}

Vector3::Vector3()
    : Vector3 { 0.0f, 0.0f, 0.0f }
{
}

Vector3::Vector3(const Vector2& value, const Single& z)
    : Vector3 { value.X(), value.Y(), z }
{
}

Vector3::Vector3(const Single& x, const Single& y, const Single& z)
    : x { x }
    , y { y }
    , z { z }
{
}

Vector3::Vector3(const Vector3& vector)
    : x { vector.x }
    , y { vector.y }
    , z { vector.z }
{
}

const Single& Vector3::X() const
{
    return this->x;
}

const Single& Vector3::Y() const
{
    return this->y;
}

const Single& Vector3::Z() const
{
    return this->z;
}

Single Vector3::LengthSquared() const
{
    return (this->x * this->x)
         + (this->y * this->y)
         + (this->z * this->z);
}

Single Vector3::Length() const
{
    // The modulus or magnitude of a vector is simply its length.
    // This can easily be found using Pythagorean Theorem with the vector components.
    //
    // The modulus is written like:
    // a = |a|
    //
    // Given:
    // a = xi + yj + zk
    //
    // Then:
    //
    // |a| = sqrt(x^2 + y^2 + z^2)

    return std::sqrt(this->LengthSquared());
}

Single& Vector3::operator[](const Size& index)
{
    assert(index < 3);

    return (this->vector[index]);
}

const Single& Vector3::operator[](const Size& index) const
{
    assert(index < 3);

    return (this->vector[index]);
}

Vector3& Vector3::operator=(const Vector3& vector)
{
    if (this != &vector)
    {
        this->x = vector.x;
        this->y = vector.y;
        this->z = vector.z;
    }

    return *this;
}

bool Vector3::operator==(const Vector3& vector) const
{
    return (this->x == vector.x
         && this->y == vector.y
         && this->z == vector.z);
}

bool Vector3::operator!=(const Vector3& vector) const
{
    return !(*this == vector);
}

Vector3& Vector3::operator*=(const Vector3& vector)
{
    this->x *= vector.x;
    this->y *= vector.y;
    this->z *= vector.z;

    return *this;
}

Vector3& Vector3::operator*=(const Single& value)
{
    this->x *= value;
    this->y *= value;
    this->z *= value;

    return *this;
}

Vector3& Vector3::operator/=(const Vector3& vector)
{
    this->x /= vector.x;
    this->y /= vector.y;
    this->z /= vector.z;

    return *this;
}

Vector3& Vector3::operator/=(const Single& value)
{
    this->x /= value;
    this->y /= value;
    this->z /= value;

    return *this;
}

Vector3& Vector3::operator-=(const Vector3& vector)
{
    this->x -= vector.x;
    this->y -= vector.y;
    this->z -= vector.z;

    return *this;
}

Vector3& Vector3::operator+=(const Vector3& vector)
{
    this->x += vector.x;
    this->y += vector.y;
    this->z += vector.z;

    return *this;
}

const Vector3 Vector3::operator*(const Vector3& vector) const
{
    auto result = *this;  // Make a copy of myself. Same as Vector3D result(*this)

    result *= vector;

    return result;
}

const Vector3 Vector3::operator*(const Single& value) const
{
    auto result = *this;

    result *= value;

    return result;
}

const Vector3 Vector3::operator*(const Matrix& matrix) const
{
    // http://softimage.wiki.softimage.com/xsidocs/iceref_Multiply_Vector_by_Matrix.htm
    Single x = (this->x * matrix.M11())
             + (this->y * matrix.M21())
             + (this->z * matrix.M31())
             +            matrix.M41();

    Single y = (this->x * matrix.M12())
             + (this->y * matrix.M22())
             + (this->z * matrix.M32())
             +            matrix.M42();

    Single z = (this->x * matrix.M13())
             + (this->y * matrix.M23())
             + (this->z * matrix.M33())
             +            matrix.M43();

    Single w = (this->x * matrix.M14())
             + (this->y * matrix.M24())
             + (this->z * matrix.M34())
             +            matrix.M44();

    return { x / w, y / w, z / w };
}

const Vector3 Vector3::operator/(const Vector3& vector) const
{
    auto result = *this;

    result /= vector;

    return result;
}

const Vector3 Vector3::operator/(const Single& value) const
{
    auto result = *this;

    result /= value;

    return result;
}

const Vector3 Vector3::operator-(const Vector3& vector) const
{
    auto result = *this;

    result -= vector;

    return result;
}

const Vector3 Vector3::operator+(const Vector3& vector) const
{
    auto result = *this;

    result += vector;

    return result;
}
