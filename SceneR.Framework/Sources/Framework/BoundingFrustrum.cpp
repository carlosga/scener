// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/BoundingFrustrum.hpp>

#include <stdexcept>

#include <Framework/BoundingBox.hpp>
#include <Framework/Ray.hpp>

namespace SceneR
{
    namespace Framework
    {
        const std::uint32_t BoundingFrustrum::CornerCount = 8;

        BoundingFrustrum::BoundingFrustrum(const SceneR::Framework::Matrix& value)
            : _bottom { 0.0f, 0.0f, 0.0f, 0.0f }
            , _far    { 0.0f, 0.0f, 0.0f, 0.0f }
            , _left   { 0.0f, 0.0f, 0.0f, 0.0f }
            , _near   { 0.0f, 0.0f, 0.0f, 0.0f }
            , _right  { 0.0f, 0.0f, 0.0f, 0.0f }
            , _top    { 0.0f, 0.0f, 0.0f, 0.0f }
            , _value  { value }
        {
            update_planes();
        }

        BoundingFrustrum::BoundingFrustrum(const BoundingFrustrum& frustrum)
            : _bottom { frustrum._bottom }
            , _far    { frustrum._far }
            , _left   { frustrum._left }
            , _near   { frustrum._near }
            , _right  { frustrum._right }
            , _top    { frustrum._top }
            , _value  { frustrum._value }
        {
        }

        BoundingFrustrum::~BoundingFrustrum()
        {
        }

        const Plane& BoundingFrustrum::bottom() const
        {
            return _bottom;
        }

        const Plane& BoundingFrustrum::far() const
        {
            return _far;
        }

        const Plane& BoundingFrustrum::left() const
        {
            return _left;
        }

        const Matrix& BoundingFrustrum::matrix() const
        {
            return _value;
        }

        void BoundingFrustrum::matrix(const Matrix& matrix)
        {
            _value = matrix;
            update_planes();
        }

        const Plane& BoundingFrustrum::near() const
        {
            return _near;
        }

        const Plane& BoundingFrustrum::right() const
        {
            return _right;
        }

        const Plane& BoundingFrustrum::top() const
        {
            return _top;
        }

        ContainmentType BoundingFrustrum::contains(const BoundingBox& box) const
        {
            throw std::runtime_error("Not implemented");
        }

        ContainmentType BoundingFrustrum::contains(const BoundingFrustrum& frustrum) const
        {
            throw std::runtime_error("Not implemented");
        }

        ContainmentType BoundingFrustrum::contains(const BoundingSphere& sphere) const
        {
            throw std::runtime_error("Not implemented");
        }

        ContainmentType BoundingFrustrum::contains(const Vector3& point) const
        {
            throw std::runtime_error("Not implemented");
        }

        std::vector<Vector3> BoundingFrustrum::get_corners()
        {
            throw std::runtime_error("Not implemented");
        }

        bool BoundingFrustrum::intersects(const BoundingBox& box) const
        {
            throw std::runtime_error("Not implemented");
        }

        bool BoundingFrustrum::intersects(const BoundingFrustrum& frustrum) const
        {
            throw std::runtime_error("Not implemented");
        }

        bool BoundingFrustrum::intersects(const BoundingSphere& sphere) const
        {
            throw std::runtime_error("Not implemented");
        }

        PlaneIntersectionType BoundingFrustrum::intersects(const Plane& plane) const
        {
            throw std::runtime_error("Not implemented");
        }

        float BoundingFrustrum::intersects(const Ray& ray) const
        {
            throw std::runtime_error("Not implemented");
        }

        BoundingFrustrum& BoundingFrustrum::operator=(const BoundingFrustrum& frustrum)
        {
            if (this != &frustrum)
            {
                _value = frustrum._value;

                update_planes();
            }

            return *this;
        }

        bool BoundingFrustrum::operator==(const BoundingFrustrum& frustrum) const
        {
            return (_value == frustrum._value);
        }

        bool BoundingFrustrum::operator!=(const BoundingFrustrum& frustrum) const
        {
            return !(*this == frustrum);
        }

        void BoundingFrustrum::update_planes()
        {
            // http://www.chadvernon.com/blog/resources/directx9/frustum-culling/

            // Left plane
            _left = Plane::Normalize({ _value.M14() + _value.M11()
                                     , _value.M24() + _value.M21()
                                     , _value.M34() + _value.M31()
                                     , _value.M44() + _value.M41() });

            // Right plane
            _right = Plane::Normalize({ _value.M14() - _value.M11()
                                      , _value.M24() - _value.M21()
                                      , _value.M34() - _value.M31()
                                      , _value.M44() - _value.M41() });

            // Top plane
            _top = Plane::Normalize({ _value.M14() - _value.M12()
                                    , _value.M24() - _value.M22()
                                    , _value.M34() - _value.M32()
                                    , _value.M44() - _value.M42() });

            // Bottom plane
            _bottom = Plane::Normalize({ _value.M14() + _value.M12()
                                       , _value.M24() + _value.M22()
                                       , _value.M34() + _value.M32()
                                       , _value.M44() + _value.M42() });

            // Near plane
            _near = Plane::Normalize({ _value.M13(), _value.M23(), _value.M33(), _value.M43() });


            // Far plane
            _far = Plane::Normalize({ _value.M14() - _value.M13()
                                    , _value.M24() - _value.M23()
                                    , _value.M34() - _value.M33()
                                    , _value.M44() - _value.M43() });
        }
    }
}
