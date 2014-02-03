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

Ray::~Ray()
{	

}

const Vector3& Ray::Direction()
{
    return this->direction;
}

const Vector3& Ray::Position()
{
    return this->position;
}

Boolean Ray::Intersects(const BoundingBox& boundingBox)
{
    throw std::runtime_error("Not implemented");
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
    throw std::runtime_error("Not implemented");
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
