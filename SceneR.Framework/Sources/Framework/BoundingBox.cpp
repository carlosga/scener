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
            : _min { min }
            , _max { max }
        {
        }

        BoundingBox::BoundingBox(const BoundingBox& boundingBox)
            : _min { boundingBox._min }
            , _max { boundingBox._max }
        {
        }

        BoundingBox::~BoundingBox()
        {
        }

        const Vector3& BoundingBox::max() const
        {
            return _max;
        }

        void BoundingBox::max(const Vector3& max)
        {
            _max = max;
        }

        const Vector3& BoundingBox::min() const
        {
            return _min;
        }

        void BoundingBox::min(const Vector3& min)
        {
            _min = min;
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
            auto tmin = (_min - ray.Position()) / ray.Direction();
            auto tmax = (_max - ray.Position()) / ray.Direction();

            auto tnear = Vector3::Min(tmin, tmax);
            auto tfar  = Vector3::Min(tmin, tmax);

            auto enter = Math::max(Math::max(tnear.X(), 0.0f), Math::max(tnear.Y(), tnear.Z()));
            auto exit  = Math::min(tfar.X(), Math::min(tfar.Y(), tfar.Z()));

            return (enter - exit);
        }

        BoundingBox& BoundingBox::operator=(const BoundingBox& box)
        {
            if (this != &box)
            {
                _min = box._min;
                _max = box._max;
            }

            return *this;
        }

        bool BoundingBox::operator==(const BoundingBox& box) const
        {
            return (_min == box._min && _max == box._max);
        }

        bool BoundingBox::operator!=(const BoundingBox& box) const
        {
            return !(*this == box);
        }
    }
}
