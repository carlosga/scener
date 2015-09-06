// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/Ray.hpp>

#include <stdexcept>

#include <System/Math.hpp>
#include <Framework/BoundingFrustrum.hpp>
#include <Framework/BoundingSphere.hpp>
#include <Framework/BoundingBox.hpp>

namespace SceneR
{
    namespace Framework
    {
        using System::Math;

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

        bool Ray::intersects(const BoundingBox& boundingBox)
        {
            return (boundingBox.intersects(*this) == 0.0f);
        }

        bool Ray::intersects(const BoundingFrustum& frustum)
        {
            throw std::runtime_error("Not implemented");
        }

        bool Ray::intersects(const BoundingSphere& sphere)
        {
            return sphere.intersects(*this);
        }

        bool Ray::intersects(const Plane& plane)
        {
            // Reference: http://www.gamedev.net/page/resources/_/technical/math-and-physics/intersection-math-algorithms-learn-to-derive-r3033
            auto denom = Vector3::dot(plane.normal, direction);

            if (Math::abs(denom) == 0.0f) // ray and plane are parallel so there is no intersection
            {
                return false;
            }

            auto t = -(Vector3::dot(position, plane.normal) + plane.d) / denom;

            return (t > 0.0f);
        }

        Ray& Ray::operator=(const Ray& ray)
        {
            if (this != &ray)
            {
                direction = ray.direction;
                position  = ray.position;
            }

            return *this;
        }

        bool Ray::operator ==(const Ray& ray) const
        {
            return (direction == ray.direction && position == ray.position);
        }

        bool Ray::operator !=(const Ray& ray) const
        {
            return (direction != ray.direction || position != ray.position);
        }
    }
}
