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

#include <Framework/Plane.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>

using namespace System;
using namespace SceneR::Framework;

/**
 * Initializes a new instance of the Plane structure.
 */
Plane::Plane(const Single& a, const Single& b, const Single& c, const Single& d)
	: d(d), normal(Vector3(a, b, c))
{
}

Plane::Plane(const Vector3& normal, const System::Single& d)
	: d(d), normal(normal)
{
}

Plane::Plane(const Vector3& point1, const Vector3& point2, const Vector3& point3)
	: d(0.0f), normal()
{	
}

Plane::Plane(const Vector4& value)
	: d(value.W()), normal(Vector3::Normalize({ value.X(), value.Y(), value.Z() }))
{	
}

Plane::~Plane()
{
}

const System::Single& Plane::D()
{
    return this->d;
}

const Vector3& Plane::Normal()
{
    return this->normal;
}
