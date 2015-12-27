// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Math/Plane.hpp"

#include <stdexcept>

#include "SceneR/Math/Math.hpp"
#include "SceneR/Math/BoundingFrustrum.hpp"
#include "SceneR/Math/BoundingSphere.hpp"
#include "SceneR/Math/BoundingBox.hpp"
#include "SceneR/Math/PlaneIntersectionType.hpp"
#include "SceneR/Math/Quaternion.hpp"
#include "SceneR/Math/Vector4.hpp"

namespace SceneR
{
    namespace Math
    {
        Plane Plane::create_from_vertices(const Vector3& point1, const Vector3& point2, const Vector3& point3)
        {
            // http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.plane.xmplanefrompoints(v=vs.85).aspx
            // http://en.wikipedia.org/wiki/Plane_%28geometry%29#Describing_a_plane_through_three_points

            // A plane can be described by a "point and a normal vector".
            // A suitable normal vector is given by the cross product
            // n = (p2 - p1) x (p3 - p1)
            // and the point r can be taken to be any of the given points p1, p2 or p3.
            //
            // The Hesse normal form for the equation of a plane relies on the parameter D. This form is:
            // n · r - D = 0
            // where n is a unit normal vector to the plane,
            // r a position vector of a point of the plane and D0 the distance of the plane from the origin.

            Vector3 n = Vector3::normalize(Vector3::cross(point2 - point1, point3 - point1));
            float   d = -Vector3::dot(n, point1);

            return { n, d };
        }

        float Plane::dot(const Plane& plane, const Vector4& value)
        {
            return Vector4::dot({ plane.normal, plane.d }, value);
        }

        float Plane::dot_normal(const Plane& p, const Vector3& v)
        {
            // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.plane.xmplanedotnormal(v=vs.85).aspx
            return Vector3::dot(p.normal, v);
        }

        float Plane::dot_coordinate(const Plane& p, const Vector3& value)
        {
            return Plane::dot_normal(p, value) + p.d;
        }

        Plane Plane::normalize(const Plane& value)
        {
            float reciprocalLength = 1.0f / value.normal.length();

            return { value.normal * reciprocalLength, value.d * reciprocalLength };
        }

        Plane Plane::transform(const Plane& plane, const Matrix& matrix)
        {
            return { Vector4 { plane.normal, plane.d } * Matrix::transpose(Matrix::invert(matrix)) };
        }

        Plane Plane::transform(const Plane& plane, const Quaternion& rotation)
        {
            // Reference: http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/transforms/
            //
            //      Pout = q * Pin * conj(q)
            //

            auto pout = (rotation * Quaternion(plane.normal, 0.0f) * Quaternion::conjugate(rotation));

            return { pout.x, pout.y, pout.z, pout.w };
        }

        Plane::Plane()
            : Plane { 0.0f, 0.0f, 0.0f, 0.0f }
        {
        }

        Plane::Plane(const float& a, const float& b, const float& c, const float& d)
            : normal { a, b, c }
            , d      { d }
        {
        }

        Plane::Plane(const Vector3& normal, const float& d)
            : normal { normal }
            , d      { d }
        {
        }

        Plane::Plane(const Vector4& value)
            : normal { value.x, value.y, value.z }
            , d      { value.w }
        {
        }

        PlaneIntersectionType Plane::intersects(const BoundingBox& box) const
        {
            throw std::runtime_error("Not implemented");
        }

        PlaneIntersectionType Plane::intersects(const BoundingFrustrum& frustrum) const
        {
            throw std::runtime_error("Not implemented");
        }

        PlaneIntersectionType Plane::intersects(const BoundingSphere& sphere) const
        {
            return sphere.intersects(*this);
        }

        bool Plane::operator==(const Plane& plane) const
        {
            return (normal == plane.normal && Math::equal(d, plane.d));
        }

        bool Plane::operator!=(const Plane& plane) const
        {
            return !(*this == plane);
        }
    }
}
