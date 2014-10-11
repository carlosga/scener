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

#include <Framework/Ray.hpp>

#include <cmath>
#include <stdexcept>

#include <Framework/BoundingFrustrum.hpp>
#include <Framework/BoundingSphere.hpp>
#include <Framework/BoundingBox.hpp>

using namespace System;
using namespace SceneR::Framework;

Ray::Ray(const Vector3& position, const Vector3& direction)
	: direction { direction }
    , position  { position }

{
}

Ray::Ray(const Ray& ray)
    : direction { ray.direction }
    , position  { ray.position }
{
}

const Vector3& Ray::Direction() const
{
    return this->direction;
}

const Vector3& Ray::Position() const
{
    return this->position;
}

Boolean Ray::Intersects(const BoundingBox& boundingBox)
{
    return (boundingBox.Intersects(*this) == 0.0f);
}

Boolean Ray::Intersects(const BoundingFrustum& frustum)
{
    throw std::runtime_error("Not implemented");
}

Boolean Ray::Intersects(const BoundingSphere& sphere)
{
    return sphere.Intersects(*this);
}

Boolean Ray::Intersects(const Plane& plane)
{
    // Reference: http://www.gamedev.net/page/resources/_/technical/math-and-physics/intersection-math-algorithms-learn-to-derive-r3033
    auto denom = Vector3::DotProduct(plane.Normal(), this->direction);

    if (std::abs(denom) == 0.0f) // ray and plane are parallel so there is no intersection
    {
        return false;
    }

    auto t = -(Vector3::DotProduct(this->position, plane.Normal()) + plane.D()) / denom;

    return (t > 0.0f);
}

Ray& Ray::operator=(const Ray& ray)
{
    if (this != &ray)
    {
        this->direction = ray.direction;
        this->position  = ray.position;
    }

    return *this;
}

bool Ray::operator ==(const Ray& ray) const
{
    return (this->direction == ray.direction && this->position == ray.position);
}

bool Ray::operator !=(const Ray& ray) const
{
    return (this->direction != ray.direction || this->position != ray.position);
}
