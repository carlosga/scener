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

#include <Framework/BoundingBox.hpp>
#include <Framework/BoundingFrustrum.hpp>
#include <Framework/BoundingSphere.hpp>
#include <Framework/Plane.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Ray.hpp>
#include <Framework/Vector3.hpp>
#include <stdexcept>

using namespace System;
using namespace SceneR::Framework;

BoundingSphere BoundingSphere::CreateFromBoundingBox(const BoundingBox& box)
{
    throw std::runtime_error("Not implemented");
}

BoundingSphere BoundingSphere::CreateFromFrustum(const BoundingFrustum& frustum)
{
    throw std::runtime_error("Not implemented");
}

BoundingSphere BoundingSphere::CreateFromPoints(const std::vector<Vector3>& points)
{
    throw std::runtime_error("Not implemented");
}

BoundingSphere BoundingSphere::CreateMerged(const BoundingSphere& original,
                                            const BoundingSphere& additional)
{
    throw std::runtime_error("Not implemented");
}

BoundingSphere::BoundingSphere(const Vector3& center, const Single& radius)
    : center(center), radius(radius)
{
}

BoundingSphere::~BoundingSphere()
{
}

const Vector3& BoundingSphere::Center()
{
    return this->center;
}

const System::Single& BoundingSphere::Radius()
{
    return this->radius;
}

ContainmentType BoundingSphere::Contains(const BoundingBox& boundingBox)
{
    throw std::runtime_error("Not implemented");
}

ContainmentType BoundingSphere::Contains(const BoundingFrustum& frustrum)
{
    throw std::runtime_error("Not implemented");
}

ContainmentType BoundingSphere::Contains(const BoundingSphere& sphere)
{
    throw std::runtime_error("Not implemented");
}

ContainmentType BoundingSphere::Contains(const Vector3& point)
{
    throw std::runtime_error("Not implemented");
}

System::Boolean BoundingSphere::Intersects(const BoundingBox& boundingBox)
{
    throw std::runtime_error("Not implemented");
}

System::Boolean BoundingSphere::Intersects(const BoundingFrustum& frustrum)
{
    throw std::runtime_error("Not implemented");
}

System::Boolean BoundingSphere::Intersects(const BoundingSphere& sphere)
{
    throw std::runtime_error("Not implemented");
}

System::Boolean BoundingSphere::Intersects(const Plane& plane)
{
    throw std::runtime_error("Not implemented");
}

System::Boolean BoundingSphere::Intersects(const Plane& plane,
                                           const PlaneIntersectionType& intersectionType)
{
    throw std::runtime_error("Not implemented");
}

System::Boolean BoundingSphere::Intersects(const Ray& ray)
{
    throw std::runtime_error("Not implemented");
}

BoundingSphere BoundingSphere::Transform(const Matrix& matrix)
{
    throw std::runtime_error("Not implemented");
}

bool BoundingSphere::operator ==(const BoundingSphere& sphere) const
{
    throw std::runtime_error("Not implemented");
}

bool BoundingSphere::operator !=(const BoundingSphere& sphere) const
{
    throw std::runtime_error("Not implemented");
}
