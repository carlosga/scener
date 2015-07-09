// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/BoundingBox.hpp>

#include <stdexcept>

#include <System/Math.hpp>
#include <Framework/BoundingFrustrum.hpp>
#include <Framework/BoundingSphere.hpp>
#include <Framework/Ray.hpp>

namespace SceneR
{
    namespace Framework
    {
        using System::Math;

        const std::uint32_t BoundingBox::CornerCount = 8;

        BoundingBox::BoundingBox(const Vector3& min, const Vector3& max)
            : min { min }
            , max { max }
        {
        }

        BoundingBox::BoundingBox(const BoundingBox& boundingBox)
            : min { boundingBox.min }
            , max { boundingBox.max }
        {
        }

        BoundingBox::~BoundingBox()
        {
        }

        const Vector3& BoundingBox::Max() const
        {
            return max;
        }

        void BoundingBox::Max(const Vector3& max)
        {
            this->max = max;
        }

        const Vector3& BoundingBox::Min() const
        {
            return min;
        }

        void BoundingBox::Min(const Vector3& min)
        {
            this->min = min;
        }

        ContainmentType BoundingBox::Contains(const BoundingBox& box) const
        {
            throw std::runtime_error("Not implemented");
        }

        ContainmentType BoundingBox::Contains(const BoundingFrustrum& frustrum) const
        {
            throw std::runtime_error("Not implemented");
        }

        ContainmentType BoundingBox::Contains(const BoundingSphere& sphere) const
        {
            throw std::runtime_error("Not implemented");
        }

        ContainmentType BoundingBox::Contains(const Vector3& point) const
        {
            throw std::runtime_error("Not implemented");
        }

        std::vector<Vector3> BoundingBox::GetCorners() const
        {
            throw std::runtime_error("Not implemented");
        }

        bool BoundingBox::Intersects(const BoundingBox& box) const
        {
            throw std::runtime_error("Not implemented");
        }

        bool BoundingBox::Intersects(const BoundingFrustrum& frustrum) const
        {
            throw std::runtime_error("Not implemented");
        }

        bool BoundingBox::Intersects(const BoundingSphere& sphere) const
        {
            throw std::runtime_error("Not implemented");
        }

        PlaneIntersectionType BoundingBox::Intersects(const Plane& plane) const
        {
            throw std::runtime_error("Not implemented");
        }

        float BoundingBox::Intersects(const Ray& ray) const
        {
            // Reference: http://www.gamedev.net/page/resources/_/technical/math-and-physics/intersection-math-algorithms-learn-to-derive-r3033
            auto tmin = (this->min - ray.Position()) / ray.Direction();
            auto tmax = (this->max - ray.Position()) / ray.Direction();

            auto tnear = Vector3::Min(tmin, tmax);
            auto tfar  = Vector3::Min(tmin, tmax);

            auto enter = Math::Max(Math::Max(tnear.X(), 0.0f), Math::Max(tnear.Y(), tnear.Z()));
            auto exit  = Math::Min(tfar.X(), Math::Min(tfar.Y(), tfar.Z()));

            return (enter - exit);
        }

        BoundingBox& BoundingBox::operator=(const BoundingBox& box)
        {
            if (this != &box)
            {
                this->min = box.min;
                this->max = box.max;
            }

            return *this;
        }

        bool BoundingBox::operator==(const BoundingBox& box) const
        {
            return (this->min == box.min && this->max == box.max);
        }

        bool BoundingBox::operator!=(const BoundingBox& box) const
        {
            return !(*this == box);
        }
    }
}
