// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Math/BoundingSphere.hpp"

#include <stdexcept>

#include "SceneR/Math/BoundingFrustrum.hpp"
#include "SceneR/Math/BoundingBox.hpp"
#include "SceneR/Math/ContainmentType.hpp"
#include "SceneR/Math/PlaneIntersectionType.hpp"
#include "SceneR/Math/Ray.hpp"

namespace SceneR { namespace Math {

BoundingSphere BoundingSphere::create_from_bounding_box(const BoundingBox& box) noexcept
{
    throw std::runtime_error("Not implemented");
}

BoundingSphere BoundingSphere::create_from_frustum(const BoundingFrustum& frustum) noexcept
{
    throw std::runtime_error("Not implemented");
}

BoundingSphere BoundingSphere::create_from_points(const std::vector<Vector3>& points) noexcept
{
    throw std::runtime_error("Not implemented");
}

BoundingSphere BoundingSphere::create_merged(const BoundingSphere& original, const BoundingSphere& additional) noexcept
{
    throw std::runtime_error("Not implemented");
}

BoundingSphere::BoundingSphere(const Vector3& center, float radius) noexcept
    : _center { center }
    , _radius { radius }
{
}

const Vector3& BoundingSphere::center() const noexcept
{
    return _center;
}

float BoundingSphere::radius() const noexcept
{
    return _radius;
}

ContainmentType BoundingSphere::contains(const BoundingBox& boundingBox) const noexcept
{
    throw std::runtime_error("Not implemented");
}

ContainmentType BoundingSphere::contains(const BoundingFrustum& frustrum) const noexcept
{
    throw std::runtime_error("Not implemented");
}

ContainmentType BoundingSphere::contains(const BoundingSphere& sphere) const noexcept
{
    throw std::runtime_error("Not implemented");
}

ContainmentType BoundingSphere::contains(const Vector3& point) const noexcept
{
    throw std::runtime_error("Not implemented");
}

bool BoundingSphere::intersects(const BoundingBox& boundingBox) const noexcept
{
    throw std::runtime_error("Not implemented");
}

bool BoundingSphere::intersects(const BoundingFrustum& frustrum) const noexcept
{
    throw std::runtime_error("Not implemented");
}

bool BoundingSphere::intersects(const BoundingSphere& sphere) const noexcept
{
    throw std::runtime_error("Not implemented");
}

PlaneIntersectionType BoundingSphere::intersects(const Plane& plane) const noexcept
{
    throw std::runtime_error("Not implemented");
}

bool BoundingSphere::intersects(const Ray& ray) const noexcept
{
    // Reference: http://www.gamedev.net/page/resources/_/technical/math-and-physics/intersection-math-algorithms-learn-to-derive-r3033
    auto rad2 = _radius * _radius;
    auto l    = _center - ray.position;
    auto tPX  = Vector3::dot(l, ray.direction);

    if (tPX < 0.0)
    {
        return false;
    }

    auto dsq = Vector3::dot(l, l) - tPX * tPX;

    if (dsq > rad2)
    {
        return false;
    }

    auto thit = std::sqrt(rad2 - dsq);
    auto t    = tPX - thit;

    if (t < 0.0f)
    {
        t = tPX + thit;
    }

    return (t < 0.0f);
}

BoundingSphere BoundingSphere::transform(const Matrix& matrix) const noexcept
{
    throw std::runtime_error("Not implemented");
}

bool BoundingSphere::operator==(const BoundingSphere& sphere) const noexcept
{
    return (_center == sphere._center && Math::equal(_radius, sphere._radius));
}

bool BoundingSphere::operator!=(const BoundingSphere& sphere) const noexcept
{
    return !(*this == sphere);
}

}}
