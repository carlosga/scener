// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/BoundingSphere.hpp>

#include <stdexcept>

#include <System/Math.hpp>
#include <Framework/BoundingFrustrum.hpp>
#include <Framework/BoundingBox.hpp>
#include <Framework/Ray.hpp>

namespace SceneR
{
    namespace Framework
    {
        using System::Math;

        BoundingSphere BoundingSphere::create_from_bounding_box(const BoundingBox& box)
        {
            throw std::runtime_error("Not implemented");
        }

        BoundingSphere BoundingSphere::create_from_frustum(const BoundingFrustum& frustum)
        {
            throw std::runtime_error("Not implemented");
        }

        BoundingSphere BoundingSphere::create_from_points(const std::vector<Vector3>& points)
        {
            throw std::runtime_error("Not implemented");
        }

        BoundingSphere BoundingSphere::create_merged(const BoundingSphere& original, const BoundingSphere& additional)
        {
            throw std::runtime_error("Not implemented");
        }

        BoundingSphere::BoundingSphere(const Vector3& center, const float& radius)
            : _center { center }
            , _radius { radius }
        {
        }

        BoundingSphere::BoundingSphere(const BoundingSphere& sphere)
            : _center { sphere._center }
            , _radius { sphere._radius }
        {
        }

        BoundingSphere::~BoundingSphere()
        {
        }

        const Vector3& BoundingSphere::center() const
        {
            return _center;
        }

        float BoundingSphere::radius() const
        {
            return _radius;
        }

        ContainmentType BoundingSphere::contains(const BoundingBox& boundingBox) const
        {
            throw std::runtime_error("Not implemented");
        }

        ContainmentType BoundingSphere::contains(const BoundingFrustum& frustrum) const
        {
            throw std::runtime_error("Not implemented");
        }

        ContainmentType BoundingSphere::contains(const BoundingSphere& sphere) const
        {
            throw std::runtime_error("Not implemented");
        }

        ContainmentType BoundingSphere::contains(const Vector3& point) const
        {
            throw std::runtime_error("Not implemented");
        }

        bool BoundingSphere::intersects(const BoundingBox& boundingBox) const
        {
            throw std::runtime_error("Not implemented");
        }

        bool BoundingSphere::intersects(const BoundingFrustum& frustrum) const
        {
            throw std::runtime_error("Not implemented");
        }

        bool BoundingSphere::intersects(const BoundingSphere& sphere) const
        {
            throw std::runtime_error("Not implemented");
        }

        PlaneIntersectionType BoundingSphere::intersects(const Plane& plane) const
        {
            throw std::runtime_error("Not implemented");
        }

        bool BoundingSphere::intersects(const Ray& ray) const
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

            auto thit = Math::sqrt(rad2 - dsq);
            auto t    = tPX - thit;

            if (t < 0.0f)
            {
                t = tPX + thit;
            }

            return (t < 0.0f);
        }

        BoundingSphere BoundingSphere::transform(const Matrix& matrix) const
        {
            throw std::runtime_error("Not implemented");
        }

        BoundingSphere& BoundingSphere::operator=(const BoundingSphere& sphere)
        {
            if (this != &sphere)
            {
                _center = sphere._center;
                _radius = sphere._radius;
            }

            return *this;
        }

        bool BoundingSphere::operator==(const BoundingSphere& sphere) const
        {
            return (_center == sphere._center && Math::equal(_radius, sphere._radius));
        }

        bool BoundingSphere::operator!=(const BoundingSphere& sphere) const
        {
            return !(*this == sphere);
        }
    }
}
