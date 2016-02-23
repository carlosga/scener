// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Math/Ray.hpp"

#include "SceneR/Math/BoundingFrustrum.hpp"
#include "SceneR/Math/BoundingSphere.hpp"
#include "SceneR/Math/BoundingBox.hpp"

namespace SceneR { namespace Math {

Ray::Ray(const Vector3& rposition, const Vector3& rdirection) noexcept
    : direction { rdirection }
    , position  { rposition }

{
}

bool Ray::intersects(const BoundingBox& boundingBox) noexcept
{
    return (boundingBox.intersects(*this) == 0.0f);
}

bool Ray::intersects(const BoundingFrustum& frustum) noexcept
{
    throw std::runtime_error("Not implemented");
}

bool Ray::intersects(const BoundingSphere& sphere) noexcept
{
    return sphere.intersects(*this);
}

bool Ray::intersects(const Plane& plane) noexcept
{
    // Reference: http://www.gamedev.net/page/resources/_/technical/math-and-physics/intersection-math-algorithms-learn-to-derive-r3033
    auto denom = Vector3::dot(plane.normal, direction);

    if (std::abs(denom) == 0.0f) // ray and plane are parallel so there is no intersection
    {
        return false;
    }

    auto t = -(Vector3::dot(position, plane.normal) + plane.d) / denom;

    return (t > 0.0f);
}

bool Ray::operator ==(const Ray& ray) const noexcept
{
    return (direction == ray.direction && position == ray.position);
}

bool Ray::operator !=(const Ray& ray) const noexcept
{
    return (direction != ray.direction || position != ray.position);
}

}}
