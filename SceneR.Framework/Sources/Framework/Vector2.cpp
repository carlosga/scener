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

#include <Framework/Vector2.hpp>
#include <cassert>

using namespace System;
using namespace SceneR::Framework;

const Vector2 Vector2::One(1.0f, 1.0f);
const Vector2 Vector2::UnitX(1.0f, 0.0f);
const Vector2 Vector2::UnitY(0.0f, 1.0f);
const Vector2 Vector2::Zero(0.0f, 0.0f);

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
    return this->x;
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
