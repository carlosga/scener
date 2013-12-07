//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#include <Framework/MathHelper.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Vector3.hpp>
#include <cassert>
#include <cmath>

using namespace System;
using namespace SceneR::Framework;

const Vector3 Vector3::Backward(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::Down(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::Forward(0.0f, 0.0f, -1.0f);
const Vector3 Vector3::Left(-10.0f, 0.0f, 0.0f);
const Vector3 Vector3::One(1.0f, 1.0f, 1.0f);
const Vector3 Vector3::Right(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UnitX(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UnitY(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UnitZ(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::Up(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);

const Single Vector3::AngleBetween(const Vector3& left, const Vector3& right)
{
    Single lengthSquared = left.LengthSquared() * right.LengthSquared();
    Single acos          = std::acos(Vector3::DotProduct(left, right) / std::sqrt(lengthSquared));

    return MathHelper::ToDegrees(acos);
}

Vector3 Vector3::Barycentric(const Vector3& value1,
                             const Vector3& value2,
                             const Vector3& value3,
                             const Single&  amount1,
                             const Single&  amount2)
{
    return Vector3(MathHelper::Barycentric(value1.X(), value2.X(), value3.X(), amount1, amount2)
                 , MathHelper::Barycentric(value1.Y(), value2.Y(), value3.Y(), amount1, amount2)
                 , MathHelper::Barycentric(value1.Z(), value2.Z(), value3.Z(), amount1, amount2));
}

Vector3 Vector3::CatmullRom(const Vector3& value1,
                            const Vector3& value2,
                            const Vector3& value3,
                            const Vector3& value4,
                            const System::Single& amount)
{
    return Vector3(MathHelper::CatmullRom(value1.X(), value2.X(), value3.X(), value4.X(), amount)
                 , MathHelper::CatmullRom(value1.Y(), value2.Y(), value3.Y(), value4.Y(), amount)
                 , MathHelper::CatmullRom(value1.Z(), value2.Z(), value3.Z(), value4.Z(), amount));
}

Vector3 Vector3::Clamp(const Vector3& value1, const Vector3& min, const Vector3& max)
{
    return Vector3(MathHelper::Clamp(value1.X(), min.X(), max.X())
                 , MathHelper::Clamp(value1.Y(), min.Y(), max.Y())
                 , MathHelper::Clamp(value1.Z(), min.Z(), max.Z()));
}

const Vector3 Vector3::CrossProduct(const Vector3& left, const Vector3& right)
{
    // The vector cross product in expanded form can be defined as:
    // a x b = (y1z2 - z1y2)i (x1z2 - z1x2)j (x1y2 - y1x2)k

    Single x = (left.Y() * right.Z()) - (left.Z() * right.Y());
    Single y = (left.Z() * right.X()) - (left.X() * right.Z());
    Single z = (left.X() * right.Y()) - (left.Y() * right.X());

    return Vector3(x, y, z);
}

Single Vector3::Distance(const Vector3& value1, const Vector3& value2)
{
    Vector3 d = value2 - value1;

    return d.Length();
}

Single Vector3::DistanceSquared(const Vector3& value1, const Vector3& value2)
{
    Vector3 d = value2 - value1;

    return d.LengthSquared();
}

const Single Vector3::DotProduct(const Vector3& left, const Vector3& right)
{
    // The definition of the scalar (dot) product is:
    // a · b = |a||b|cosθ
    //
    // The scalar product can also be written in terms of Cartesian components as:
    // a · b = x1x2 + y1y2 + z1z2

    Vector3 dotProduct = left * right;

    return (dotProduct.X() + dotProduct.Y() + dotProduct.Z());
}

Vector3 Vector3::Hermite(const Vector3& value1,
                         const Vector3& tangent1,
                         const Vector3& value2,
                         const Vector3& tangent2,
                         const System::Single& amount)
{
    return Vector3(MathHelper::Hermite(value1.X(), tangent1.X(), value2.X(), tangent2.X(), amount)
                 , MathHelper::Hermite(value1.Y(), tangent1.Y(), value2.Y(), tangent2.Y(), amount)
                 , MathHelper::Hermite(value1.Z(), tangent1.Z(), value2.Z(), tangent2.Z(), amount));
}

Vector3 Vector3::Lerp(const Vector3& value1, const Vector3& value2, const Single& amount)
{
    assert(amount >= 0.0f && amount < 1.0f);

    return Vector3(MathHelper::Lerp(value1.X(), value2.X(), amount)
                 , MathHelper::Lerp(value1.Y(), value2.Y(), amount)
                 , MathHelper::Lerp(value1.Z(), value2.Z(), amount));
}

Vector3 Vector3::SmoothStep(const Vector3& value1, const Vector3& value2, const Single& amount)
{
    return Vector3(MathHelper::SmoothStep(value1.X(), value2.X(), amount)
                 , MathHelper::SmoothStep(value1.Y(), value2.Y(), amount)
                 , MathHelper::SmoothStep(value1.Z(), value2.Z(), amount));
}

Vector3 Vector3::Normalize(const Vector3& value)
{
    Vector3 normalized(value);

    normalized.Normalize();

    return normalized;
}

Vector3 Vector3::Transform(const Vector3& position, const Matrix& matrix)
{
    return (position * matrix);
}

Vector3 Vector3::TransformNormal(const Vector3& normal, const Matrix& matrix)
{
    Single x = (normal.X() * matrix.M11())
             + (normal.Y() * matrix.M21())
             + (normal.Z() * matrix.M31());

    Single y = (normal.X() * matrix.M12())
             + (normal.Y() * matrix.M22())
             + (normal.Z() * matrix.M32());

    Single z = (normal.X() * matrix.M13())
             + (normal.Y() * matrix.M23())
             + (normal.Z() * matrix.M33());

    return Vector3(x, y, z);
}

Vector3::Vector3()
    : Vector3(0.0f, 0.0f, 0.0f)
{
}

Vector3::Vector3(const Single& x, const Single& y, const Single& z)
    : x(x), y(y), z(z)
{
}

Vector3::Vector3(const Vector3& vector)
    : x(vector.X()), y(vector.Y()), z(vector.Z())
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

const Single Vector3::LengthSquared() const
{
    return (this->x * this->x)
         + (this->y * this->y)
         + (this->z * this->z);
}

const Single Vector3::Length() const
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

void Vector3::Negate()
{
   (*this *= -1.0f);
}

void Vector3::Normalize()
{
    // To find the unit vector of another vector, we use the modulus operator
    // and scalar multiplication like so:
    // b = a / |a|
    //
    // Where |a| is the modulus of a
    (*this /= this->Length());
}

Single& Vector3::operator[](const Int32& index)
{
    assert(index >= 0 && index < 3);

    return (this->vector[index]);
}

const Single& Vector3::operator[](const Int32& index) const
{
    assert(index >= 0 && index < 3);

    return (this->vector[index]);
}

Vector3& Vector3::operator=(const Vector3& vector)
{
    if (this != &vector)
    {
        this->x = vector.X();
        this->y = vector.Y();
        this->z = vector.Z();
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
    Vector3 result = *this;  // Make a copy of myself. Same as Vector3D result(*this)

    result *= vector;

    return result;
}

const Vector3 Vector3::operator*(const Single& value) const
{
    Vector3 result = *this;

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

    return Vector3(x / w, y / w, z / w);
}

const Vector3 Vector3::operator/(const Vector3& vector) const
{
    Vector3 result = *this;

    result /= vector;

    return result;
}

const Vector3 Vector3::operator/(const Single& value) const
{
    Vector3 result = *this;

    result /= value;

    return result;
}

const Vector3 Vector3::operator-(const Vector3& vector) const
{
    Vector3 result = *this;

    result -= vector;

    return result;
}

const Vector3 Vector3::operator+(const Vector3& vector) const
{
    Vector3 result = *this;

    result += vector;

    return result;
}
