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

#include <cassert>
#include "Core/Vector2.hpp"

using namespace SceneR::Core;

Vector2::Vector2()
    : x(0.0f), y(0.0f)
{
}

Vector2::Vector2(const Single& x, const Single& y)
    : x(x), y(y)
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
