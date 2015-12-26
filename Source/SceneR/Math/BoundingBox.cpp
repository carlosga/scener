// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Math/BoundingBox.hpp>

#include <stdexcept>

#include <Math/Math.hpp>
#include <Math/BoundingFrustrum.hpp>
#include <Math/BoundingSphere.hpp>
#include <Math/Ray.hpp>

namespace SceneR
{
    namespace Math
    {
        const std::uint32_t BoundingBox::CornerCount = 8;

        BoundingBox::BoundingBox(const Vector3& min, const Vector3& max)
            : min { min }
            , max { max }
        {
        }

        ContainmentType BoundingBox::contains(const BoundingBox& box) const
        {
            throw std::runtime_error("Not implemented");
        }

        ContainmentType BoundingBox::contains(const BoundingFrustrum& frustrum) const
        {
            throw std::runtime_error("Not implemented");
        }

        ContainmentType BoundingBox::contains(const BoundingSphere& sphere) const
        {
            throw std::runtime_error("Not implemented");
        }

        ContainmentType BoundingBox::contains(const Vector3& point) const
        {
            throw std::runtime_error("Not implemented");
        }

        std::vector<Vector3> BoundingBox::get_corners() const
        {
            throw std::runtime_error("Not implemented");
        }

        bool BoundingBox::intersects(const BoundingBox& box) const
        {
            throw std::runtime_error("Not implemented");
        }

        bool BoundingBox::intersects(const BoundingFrustrum& frustrum) const
        {
            throw std::runtime_error("Not implemented");
        }

        bool BoundingBox::intersects(const BoundingSphere& sphere) const
        {
            throw std::runtime_error("Not implemented");
        }

        PlaneIntersectionType BoundingBox::intersects(const Plane& plane) const
        {
            throw std::runtime_error("Not implemented");
        }

        float BoundingBox::intersects(const Ray& ray) const
        {
            // Reference: http://www.gamedev.net/page/resources/_/technical/math-and-physics/intersection-math-algorithms-learn-to-derive-r3033
            auto tmin = (min - ray.position) / ray.direction;
            auto tmax = (max - ray.position) / ray.direction;

            auto tnear = Vector3::min(tmin, tmax);
            auto tfar  = Vector3::min(tmin, tmax);

            auto enter = Math::max(Math::max(tnear.x, 0.0f), Math::max(tnear.y, tnear.z));
            auto exit  = Math::min(tfar.x, Math::min(tfar.y, tfar.z));

            return (enter - exit);
        }

        bool BoundingBox::operator==(const BoundingBox& box) const
        {
            return (min == box.min && max == box.max);
        }

        bool BoundingBox::operator!=(const BoundingBox& box) const
        {
            return !(*this == box);
        }
    }
}
