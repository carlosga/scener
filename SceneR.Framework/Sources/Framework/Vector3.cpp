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
#include <stdexcept>

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

Vector3 Vector3::Lerp(const Vector3& value1, const Vector3& value2, const Single& amount)
{
    // Formula: http://msdn.microsoft.com/en-us/library/bb197812.aspx
    assert(amount >= 0.0f && amount < 1.0f);

    return (value1 + (value2 - value1) * amount);
}

Vector3 Vector3::SmoothStep(const Vector3& value1, const Vector3& value2, const Single& amount)
{
    // TODO: Implement Hermite y Clamp. See XNA MathHelper at MSDN
    throw std::runtime_error("Not  implemented");
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
    return   (this->x * this->x)
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

const Vector3 Vector3::CrossProduct(const Vector3& vectorb) const
{
    // The vector cross product in expanded form can be defined as:
    // a x b = (y1z2 - z1y2)i - (x1z2 - z1x2)j + (x1y2 - y1x2)k

    Single x = (this->y * vectorb.Z()) - (vectorb.Y() * this->z);
    Single y = (this->z * vectorb.X()) - (vectorb.Z() * this->x);
    Single z = (this->x * vectorb.Y()) - (vectorb.X() * this->y);

    return Vector3(x, y, z);
}

const Single Vector3::DotProduct(const Vector3& vectorb) const
{
    // The definition of the scalar (dot) product is:
    // a · b = |a||b|cosθ
    //
    // The scalar product can also be written in terms of Cartesian components as:
    // a · b = x1x2 + y1y2 + z1z2

    Vector3 dotProduct = *this * vectorb;

    return (dotProduct.X() + dotProduct.Y() + dotProduct.Z());
}

const Single Vector3::AngleBetween(const Vector3& vectorb) const
{
    Single lengthSquared = this->LengthSquared() * vectorb.LengthSquared();
    Single acos          = std::acos(this->DotProduct(vectorb) / std::sqrt(lengthSquared));

    return MathHelper::ToDegrees(acos);
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
    return (this->x    == vector.x
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
    Single x = (this->x * matrix.M11())
             + (this->y * matrix.M21())
             + (this->z * matrix.M31());

    Single y = (this->x * matrix.M12())
             + (this->y * matrix.M22())
             + (this->z * matrix.M32());

    Single z = (this->x * matrix.M13())
             + (this->y * matrix.M23())
             + (this->z * matrix.M33());

    return Vector3(x, y, z);
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
