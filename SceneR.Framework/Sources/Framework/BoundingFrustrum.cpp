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
            : bottom { 0.0f, 0.0f, 0.0f, 0.0f }
            , far    { 0.0f, 0.0f, 0.0f, 0.0f }
            , left   { 0.0f, 0.0f, 0.0f, 0.0f }
            , near   { 0.0f, 0.0f, 0.0f, 0.0f }
            , right  { 0.0f, 0.0f, 0.0f, 0.0f }
            , top    { 0.0f, 0.0f, 0.0f, 0.0f }
            , value  { value }
        {
            this->UpdatePlanes();
        }

        BoundingFrustrum::BoundingFrustrum(const BoundingFrustrum& frustrum)
            : bottom { frustrum.bottom }
            , far    { frustrum.far }
            , left   { frustrum.left }
            , near   { frustrum.near }
            , right  { frustrum.right }
            , top    { frustrum.top }
            , value  { frustrum.value }
        {
        }

        BoundingFrustrum::~BoundingFrustrum()
        {
        }

        const Plane& BoundingFrustrum::Bottom() const
        {
            return this->bottom;
        }

        const Plane& BoundingFrustrum::Far() const
        {
            return this->far;
        }

        const Plane& BoundingFrustrum::Left() const
        {
            return this->left;
        }

        const SceneR::Framework::Matrix& BoundingFrustrum::Matrix() const
        {
            return this->value;
        }

        void BoundingFrustrum::Matrix(const SceneR::Framework::Matrix& matrix)
        {
            this->value = matrix;
            this->UpdatePlanes();
        }

        const Plane& BoundingFrustrum::Near() const
        {
            return this->near;
        }

        const Plane& BoundingFrustrum::Right() const
        {
            return this->right;
        }

        const Plane& BoundingFrustrum::Top() const
        {
            return this->top;
        }

        ContainmentType BoundingFrustrum::Contains(const BoundingBox& box) const
        {
            throw std::runtime_error("Not implemented");
        }

        ContainmentType BoundingFrustrum::Contains(const BoundingFrustrum& frustrum) const
        {
            throw std::runtime_error("Not implemented");
        }

        ContainmentType BoundingFrustrum::Contains(const BoundingSphere& sphere) const
        {
            throw std::runtime_error("Not implemented");
        }

        ContainmentType BoundingFrustrum::Contains(const Vector3& point) const
        {
            throw std::runtime_error("Not implemented");
        }

        std::vector<Vector3> BoundingFrustrum::GetCorners()
        {
            throw std::runtime_error("Not implemented");
        }

        bool BoundingFrustrum::Intersects(const BoundingBox& box) const
        {
            throw std::runtime_error("Not implemented");
        }

        bool BoundingFrustrum::Intersects(const BoundingFrustrum& frustrum) const
        {
            throw std::runtime_error("Not implemented");
        }

        bool BoundingFrustrum::Intersects(const BoundingSphere& sphere) const
        {
            throw std::runtime_error("Not implemented");
        }

        PlaneIntersectionType BoundingFrustrum::Intersects(const Plane& plane) const
        {
            throw std::runtime_error("Not implemented");
        }

        float BoundingFrustrum::Intersects(const Ray& ray) const
        {
            throw std::runtime_error("Not implemented");
        }

        BoundingFrustrum& BoundingFrustrum::operator=(const BoundingFrustrum& frustrum)
        {
            if (this != &frustrum)
            {
                this->value = frustrum.value;
            }

            return *this;
        }

        bool BoundingFrustrum::operator==(const BoundingFrustrum& frustrum) const
        {
            return (this->value == frustrum.value);
        }

        bool BoundingFrustrum::operator!=(const BoundingFrustrum& frustrum) const
        {
            return !(*this == frustrum);
        }

        void BoundingFrustrum::UpdatePlanes()
        {
            // http://www.chadvernon.com/blog/resources/directx9/frustum-culling/

            // Left plane
            this->left = Plane::Normalize({ this->value.M14() + this->value.M11()
                                          , this->value.M24() + this->value.M21()
                                          , this->value.M34() + this->value.M31()
                                          , this->value.M44() + this->value.M41() });

            // Right plane
            this->right = Plane::Normalize({ this->value.M14() - this->value.M11()
                                           , this->value.M24() - this->value.M21()
                                           , this->value.M34() - this->value.M31()
                                           , this->value.M44() - this->value.M41() });

            // Top plane
            this->top = Plane::Normalize({ this->value.M14() - this->value.M12()
                                         , this->value.M24() - this->value.M22()
                                         , this->value.M34() - this->value.M32()
                                         , this->value.M44() - this->value.M42() });

            // Bottom plane
            this->bottom = Plane::Normalize({ this->value.M14() + this->value.M12()
                                            , this->value.M24() + this->value.M22()
                                            , this->value.M34() + this->value.M32()
                                            , this->value.M44() + this->value.M42() });

            // Near plane
            this->near = Plane::Normalize({ this->value.M13(), this->value.M23(), this->value.M33(), this->value.M43() });


            // Far plane
            this->far = Plane::Normalize({ this->value.M14() - this->value.M13()
                                         , this->value.M24() - this->value.M23()
                                         , this->value.M34() - this->value.M33()
                                         , this->value.M44() - this->value.M43() });
        }
    }
}
