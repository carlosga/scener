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

const System::Int32& BoundingBox::CornerCount = 8;

BoundingBox::BoundingBox(const Vector3& min, const Vector3& max)
    : min(min)
    , max(max)
{	
}

BoundingBox::BoundingBox(const BoundingBox& boundingBox)
    : min(boundingBox.min)
    , max(boundingBox.max)
{
}

BoundingBox::~BoundingBox()
{	
}

const Vector3& BoundingBox::Max() const
{
    return max;
}

void BoundingBox::Max(const Vector3& max)
{
    this->max = max;
}

const Vector3& BoundingBox::Min() const
{
    return min;
}

void BoundingBox::Min(const Vector3& min)
{
    this->min = min;
}

ContainmentType BoundingBox::Contains(const BoundingBox& box) const
{
    throw std::runtime_error("Not implemented");
}

ContainmentType BoundingBox::Contains(const BoundingFrustrum& frustrum) const
{
    throw std::runtime_error("Not implemented");
}

ContainmentType BoundingBox::Contains(const BoundingSphere& sphere) const
{
    throw std::runtime_error("Not implemented");
}

ContainmentType BoundingBox::Contains(const Vector3& point) const
{
    throw std::runtime_error("Not implemented");
}

std::vector<Vector3> BoundingBox::GetCorners()
{
    throw std::runtime_error("Not implemented");
}

bool BoundingBox::Intersects(const BoundingBox& box) const
{
    throw std::runtime_error("Not implemented");
}

bool BoundingBox::Intersects(const BoundingFrustrum& frustrum) const
{
    throw std::runtime_error("Not implemented");
}

bool BoundingBox::Intersects(const BoundingSphere& sphere) const
{
    throw std::runtime_error("Not implemented");
}

PlaneIntersectionType BoundingBox::Intersects(const Plane& plane) const
{
    throw std::runtime_error("Not implemented");
}

Single BoundingBox::Intersects(const Ray& ray) const
{
    throw std::runtime_error("Not implemented");
}

BoundingBox& BoundingBox::operator=(const BoundingBox& box)
{
    if (this != &box)
    {
        this->min = box.min;
        this->max = box.max;
    }

    return *this;
}

bool BoundingBox::operator==(const BoundingBox& box) const
{
    return (this->min == box.min && this->max == box.max);
}

bool BoundingBox::operator!=(const BoundingBox& box) const
{
    return !(*this == box);
}
