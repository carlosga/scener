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

        const Vector3& Ray::Direction() const
        {
            return this->direction;
        }

        const Vector3& Ray::Position() const
        {
            return this->position;
        }

        bool Ray::Intersects(const BoundingBox& boundingBox)
        {
            return (boundingBox.Intersects(*this) == 0.0f);
        }

        bool Ray::Intersects(const BoundingFrustum& frustum)
        {
            throw std::runtime_error("Not implemented");
        }

        bool Ray::Intersects(const BoundingSphere& sphere)
        {
            return sphere.Intersects(*this);
        }

        bool Ray::Intersects(const Plane& plane)
        {
            // Reference: http://www.gamedev.net/page/resources/_/technical/math-and-physics/intersection-math-algorithms-learn-to-derive-r3033
            auto denom = Vector3::Dot(plane.Normal(), this->direction);

            if (Math::Abs(denom) == 0.0f) // ray and plane are parallel so there is no intersection
            {
                return false;
            }

            auto t = -(Vector3::Dot(this->position, plane.Normal()) + plane.D()) / denom;

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
    }
}
