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
#include <Framework/Vector2.hpp>
#include <cassert>
#include <cmath>

using namespace System;
using namespace SceneR::Framework;

const Vector2 Vector2::One(1.0f, 1.0f);
const Vector2 Vector2::UnitX(1.0f, 0.0f);
const Vector2 Vector2::UnitY(0.0f, 1.0f);
const Vector2 Vector2::Zero(0.0f, 0.0f);

Vector2 Vector2::Barycentric(const Vector2& value1,
                             const Vector2& value2,
                             const Vector2& value3,
                             const Single& amount1,
                             const Single& amount2)
{
    return Vector2(MathHelper::Barycentric(value1.X(), value2.X(), value3.X(), amount1, amount2)
                 , MathHelper::Barycentric(value1.Y(), value2.Y(), value3.Y(), amount1, amount2));
}

Vector2 Vector2::CatmullRom(const Vector2& value1,
                            const Vector2& value2,
                            const Vector2& value3,
                            const Vector2& value4,
                            const Single& amount)
{
    return Vector2(MathHelper::CatmullRom(value1.X(), value2.X(), value3.X(), value4.X(), amount)
                 , MathHelper::CatmullRom(value1.Y(), value2.Y(), value3.Y(), value4.Y(), amount));
}

Vector2 Vector2::Clamp(const Vector2& value1, const Vector2& min, const Vector2& max)
{
    return Vector2(MathHelper::Clamp(value1.X(), min.X(), max.X())
                 , MathHelper::Clamp(value1.Y(), min.Y(), max.Y()));
}

Single Vector2::Distance(const Vector2& value1, const Vector2& value2)
{
    Vector2 d = value2 - value1;

    return d.Length();
}

Single Vector2::DistanceSquared(const Vector2& value1, const Vector2& value2)
{
    Vector2 d = value2 - value1;

    return d.LengthSquared();
}

Vector2 Vector2::Hermite(const Vector2& value1,
                         const Vector2& tangent1,
                         const Vector2& value2,
                         const Vector2& tangent2,
                         const Single& amount)
{
    return Vector2(MathHelper::Hermite(value1.X(), tangent1.X(), value2.X(), tangent2.X(), amount)
                 , MathHelper::Hermite(value1.Y(), tangent1.Y(), value2.Y(), tangent2.Y(), amount));
}

Vector2 Vector2::Lerp(const Vector2& value1,
                      const Vector2& value2,
                      const Single&  amount)
{
    return Vector2(MathHelper::Lerp(value1.X(), value2.X(), amount)
                 , MathHelper::Lerp(value1.Y(), value2.Y(), amount));
}

Vector2 Vector2::SmoothStep(const Vector2& value1,
                            const Vector2& value2,
                            const Single& amount)
{
    return Vector2(MathHelper::SmoothStep(value1.X(), value2.X(), amount)
                 , MathHelper::SmoothStep(value1.Y(), value2.Y(), amount));
}

Vector2::Vector2()
    : x(0.0f), y(0.0f)
{
}

Vector2::Vector2(const Single& x, const Single& y)
    : x(x), y(y)
{
}

Vector2::Vector2(const Vector2& vector)
    : x(vector.X()), y(vector.Y())
{
}

const Single& Vector2::X() const
{
    return this->x;
}

const Single& Vector2::Y() const
{
    return this->y;
}

const Single Vector2::LengthSquared() const
{
    return (this->x * this->x)
         + (this->y * this->y);
}

const Single Vector2::Length() const
{
    return std::sqrt(this->LengthSquared());
}

void Vector2::Negate()
{
    (*this *= -1.0f);
}

Single& Vector2::operator[](const Int32& index)
{
    assert(index >= 0 && index < 2);

    return (this->coords[index]);
}

const Single& Vector2::operator[](const Int32& index) const
{
    assert(index >= 0 && index < 2);

    return (this->coords[index]);
}

Vector2& Vector2::operator=(const Vector2& vector)
{
    if (this != &vector)
    {
        this->x = vector.X();
        this->y = vector.Y();
    }

    return *this;
}

bool Vector2::operator==(const Vector2& vector) const
{
    return (this->x == vector.x
         && this->y == vector.y);
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

Vector2& Vector2::operator*=(const Single& value)
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

Vector2& Vector2::operator/=(const Single& value)
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
    Vector2 result = *this;

    result *= vector;

    return result;
}

const Vector2 Vector2::operator*(const Single& value) const
{
    Vector2 result = *this;

    result *= value;

    return result;
}

const Vector2 Vector2::operator/(const Vector2& vector) const
{
    Vector2 result = *this;

    result /= vector;

    return result;
}

const Vector2 Vector2::operator/(const Single& value) const
{
    Vector2 result = *this;

    result *= value;

    return result;
}

const Vector2 Vector2::operator-(const Vector2& vector) const
{
    Vector2 result = *this;

    result -= vector;

    return result;
}

const Vector2 Vector2::operator+(const Vector2& vector) const
{
    Vector2 result = *this;

    result += vector;

    return result;
}
