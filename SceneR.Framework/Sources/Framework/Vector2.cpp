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

const Vector2 Vector2::One   { 1.0f, 1.0f };
const Vector2 Vector2::UnitX { 1.0f, 0.0f };
const Vector2 Vector2::UnitY { 0.0f, 1.0f };
const Vector2 Vector2::Zero  { 0.0f, 0.0f };

Vector2 Vector2::Barycentric(const Vector2& value1
                           , const Vector2& value2
                           , const Vector2& value3
                           , const Single&  amount1
                           , const Single&  amount2)
{
    return { MathHelper::Barycentric(value1.x, value2.x, value3.x, amount1, amount2)
           , MathHelper::Barycentric(value1.y, value2.y, value3.y, amount1, amount2) };
}

Vector2 Vector2::CatmullRom(const Vector2& value1
                          , const Vector2& value2
                          , const Vector2& value3
                          , const Vector2& value4
                          , const Single&  amount)
{
    return { MathHelper::CatmullRom(value1.x, value2.x, value3.x, value4.x, amount)
           , MathHelper::CatmullRom(value1.y, value2.y, value3.y, value4.y, amount) };
}

Vector2 Vector2::Clamp(const Vector2& value1, const Vector2& min, const Vector2& max)
{
    return { MathHelper::Clamp(value1.x, min.x, max.x)
           , MathHelper::Clamp(value1.y, min.y, max.y) };
}

Single Vector2::Distance(const Vector2& value1, const Vector2& value2)
{
    auto d = value2 - value1;

    return d.Length();
}

Single Vector2::DistanceSquared(const Vector2& value1, const Vector2& value2)
{
    auto d = value2 - value1;

    return d.LengthSquared();
}

Vector2 Vector2::Hermite(const Vector2& value1
                       , const Vector2& tangent1
                       , const Vector2& value2
                       , const Vector2& tangent2
                       , const Single&  amount)
{
    return { MathHelper::Hermite(value1.x, tangent1.x, value2.x, tangent2.x, amount)
           , MathHelper::Hermite(value1.y, tangent1.y, value2.y, tangent2.y, amount) };
}

Vector2 Vector2::Lerp(const Vector2& value1
                    , const Vector2& value2
                    , const Single&  amount)
{
    return { MathHelper::Lerp(value1.x, value2.x, amount)
           , MathHelper::Lerp(value1.y, value2.y, amount) };
}

Vector2 Vector2::SmoothStep(const Vector2& value1
                          , const Vector2& value2
                          , const Single&  amount)
{
    return { MathHelper::SmoothStep(value1.x, value2.x, amount)
           , MathHelper::SmoothStep(value1.y, value2.y, amount) };
}

Vector2::Vector2()
    : Vector2 { 0.0f, 0.0f }
{
}

Vector2::Vector2(const Single& x, const Single& y)
    : x { x }
    , y { y }
{
}

Vector2::Vector2(const Vector2& vector)
    : x { vector.x }
    , y { vector.y }
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

Single Vector2::LengthSquared() const
{
    return (this->x * this->x)
         + (this->y * this->y);
}

Single Vector2::Length() const
{
    return std::sqrt(this->LengthSquared());
}

void Vector2::Negate()
{
    (*this *= -1.0f);
}

Single& Vector2::operator[](const Size& index)
{
    assert(index < 2);

    return (this->coords[index]);
}

const Single& Vector2::operator[](const Size& index) const
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
    auto result = *this;

    result *= vector;

    return result;
}

const Vector2 Vector2::operator*(const Single& value) const
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

const Vector2 Vector2::operator/(const Single& value) const
{
    auto result = *this;

    result *= value;

    return result;
}

const Vector2 Vector2::operator-(const Vector2& vector) const
{
    auto result = *this;

    result -= vector;

    return result;
}

const Vector2 Vector2::operator+(const Vector2& vector) const
{
    auto result = *this;

    result += vector;

    return result;
}
