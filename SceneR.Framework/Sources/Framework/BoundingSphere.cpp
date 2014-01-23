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
#include <Framework/Ray.hpp>
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

BoundingSphere::BoundingSphere(const BoundingSphere& sphere)
    : center(sphere.center), radius(sphere.radius)
{
}

BoundingSphere::~BoundingSphere()
{
}

const Vector3& BoundingSphere::Center() const
{
    return this->center;
}

const System::Single& BoundingSphere::Radius() const
{
    return this->radius;
}

ContainmentType BoundingSphere::Contains(const BoundingBox& boundingBox) const
{
    throw std::runtime_error("Not implemented");
}

ContainmentType BoundingSphere::Contains(const BoundingFrustum& frustrum) const
{
    throw std::runtime_error("Not implemented");
}

ContainmentType BoundingSphere::Contains(const BoundingSphere& sphere) const
{
    throw std::runtime_error("Not implemented");
}

ContainmentType BoundingSphere::Contains(const Vector3& point) const
{
    throw std::runtime_error("Not implemented");
}

System::Boolean BoundingSphere::Intersects(const BoundingBox& boundingBox) const
{
    throw std::runtime_error("Not implemented");
}

System::Boolean BoundingSphere::Intersects(const BoundingFrustum& frustrum) const
{
    throw std::runtime_error("Not implemented");
}

System::Boolean BoundingSphere::Intersects(const BoundingSphere& sphere) const
{
    throw std::runtime_error("Not implemented");
}

PlaneIntersectionType BoundingSphere::Intersects(const Plane& plane) const
{
    throw std::runtime_error("Not implemented");
}

System::Boolean BoundingSphere::Intersects(const Ray& ray) const
{
    throw std::runtime_error("Not implemented");
}

BoundingSphere BoundingSphere::Transform(const Matrix& matrix) const
{
    throw std::runtime_error("Not implemented");
}

bool BoundingSphere::operator==(const BoundingSphere& sphere) const
{
    throw std::runtime_error("Not implemented");
}

bool BoundingSphere::operator!=(const BoundingSphere& sphere) const
{
    throw std::runtime_error("Not implemented");
}
