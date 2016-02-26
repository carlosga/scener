// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/math/Ray.hpp"

#include "scener/math/BoundingFrustrum.hpp"
#include "scener/math/BoundingSphere.hpp"
#include "scener/math/BoundingBox.hpp"
#include "scener/math/plane.hpp"
#include "scener/math/vector.hpp"

namespace scener { namespace math {

Ray::Ray(const vector3& rposition, const vector3& rdirection) noexcept
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

bool Ray::intersects(const plane_t& plane) noexcept
{
    // Reference: http://www.gamedev.net/page/resources/_/technical/math-and-physics/intersection-math-algorithms-learn-to-derive-r3033
    auto denom = vector::dot(plane.normal, direction);

    if (std::abs(denom) == 0.0f) // ray and plane are parallel so there is no intersection
    {
        return false;
    }

    auto t = -(vector::dot(position, plane.normal) + plane.d) / denom;

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
