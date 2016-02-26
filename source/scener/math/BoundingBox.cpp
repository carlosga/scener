// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Math/BoundingBox.hpp"

#include <stdexcept>

#include "SceneR/Math/BoundingFrustrum.hpp"
#include "SceneR/Math/BoundingSphere.hpp"
#include "SceneR/Math/Ray.hpp"

namespace scener { namespace math {

BoundingBox::BoundingBox(const vector3& minPoint, const vector3& maxPoint) noexcept
    : min { minPoint }
    , max { maxPoint }
{
}

ContainmentType BoundingBox::contains(const BoundingBox& box) const noexcept
{
    throw std::runtime_error("Not implemented");
}

ContainmentType BoundingBox::contains(const BoundingFrustrum& frustrum) const noexcept
{
    throw std::runtime_error("Not implemented");
}

ContainmentType BoundingBox::contains(const BoundingSphere& sphere) const noexcept
{
    throw std::runtime_error("Not implemented");
}

ContainmentType BoundingBox::contains(const vector3& point) const noexcept
{
    throw std::runtime_error("Not implemented");
}

std::vector<vector3> BoundingBox::get_corners() const noexcept
{
    throw std::runtime_error("Not implemented");
}

bool BoundingBox::intersects(const BoundingBox& box) const noexcept
{
    throw std::runtime_error("Not implemented");
}

bool BoundingBox::intersects(const BoundingFrustrum& frustrum) const noexcept
{
    throw std::runtime_error("Not implemented");
}

bool BoundingBox::intersects(const BoundingSphere& sphere) const noexcept
{
    throw std::runtime_error("Not implemented");
}

plane_intersection_type BoundingBox::intersects(const plane_t& plane) const noexcept
{
    throw std::runtime_error("Not implemented");
}

float BoundingBox::intersects(const Ray& ray) const noexcept
{
    // Reference: http://www.gamedev.net/page/resources/_/technical/math-and-physics/intersection-math-algorithms-learn-to-derive-r3033
    auto tmin = (min - ray.position) / ray.direction;
    auto tmax = (max - ray.position) / ray.direction;

    auto tnear = vector::min(tmin, tmax);
    auto tfar  = vector::min(tmin, tmax);

    auto enter = std::max(std::max(tnear.x, 0.0f), std::max(tnear.y, tnear.z));
    auto exit  = std::min(tfar.x, std::min(tfar.y, tfar.z));

    return (enter - exit);
}

bool BoundingBox::operator==(const BoundingBox& box) const noexcept
{
    return (min == box.min && max == box.max);
}

bool BoundingBox::operator!=(const BoundingBox& box) const noexcept
{
    return !(*this == box);
}

}}
