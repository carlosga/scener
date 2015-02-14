// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/BoundingSphere.hpp>

#include <cmath>
#include <stdexcept>

#include <Framework/BoundingFrustrum.hpp>
#include <Framework/BoundingBox.hpp>
#include <Framework/Ray.hpp>

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

BoundingSphere BoundingSphere::CreateMerged(const BoundingSphere& original, const BoundingSphere& additional)
{
    throw std::runtime_error("Not implemented");
}

BoundingSphere::BoundingSphere(const Vector3& center, const Single& radius)
    : center { center }
    , radius { radius }
{
}

BoundingSphere::BoundingSphere(const BoundingSphere& sphere)
    : center { sphere.center }
    , radius { sphere.radius }
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
    // Reference: http://www.gamedev.net/page/resources/_/technical/math-and-physics/intersection-math-algorithms-learn-to-derive-r3033
    auto rad2 = this->radius * this->radius;
    auto l    = this->center - ray.Position();

    auto tPX = Vector3::Dot(l, ray.Direction());

    if (tPX < 0.0)
    {
        return false;
    }

    auto dsq = Vector3::Dot(l, l) - tPX * tPX;

    if (dsq > rad2)
    {
        return false;
    }

    Single thit = std::sqrt(rad2 - dsq);
    Single t    = tPX - thit;

    if (t < 0.0f)
    {
        t = tPX + thit;
    }

    return (t < 0.0f);
}

BoundingSphere BoundingSphere::Transform(const Matrix& matrix) const
{
    throw std::runtime_error("Not implemented");
}

BoundingSphere& BoundingSphere::operator=(const BoundingSphere& sphere)
{
    if (this != &sphere)
    {
        this->center = sphere.center;
        this->radius = sphere.radius;
    }

    return *this;
}

bool BoundingSphere::operator==(const BoundingSphere& sphere) const
{
    return (this->center == sphere.center && this->radius == sphere.radius);
}

bool BoundingSphere::operator!=(const BoundingSphere& sphere) const
{
    return !(*this == sphere);
}
