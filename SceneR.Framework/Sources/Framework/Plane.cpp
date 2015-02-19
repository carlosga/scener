// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/Plane.hpp>

#include <stdexcept>

#include <Framework/BoundingFrustrum.hpp>
#include <Framework/BoundingSphere.hpp>
#include <Framework/BoundingBox.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector4.hpp>

using namespace System;
using namespace SceneR::Framework;

Plane Plane::CreateFromVertices(const Vector3& point1, const Vector3& point2, const Vector3& point3)
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

    Vector3 n = Vector3::Normalize(Vector3::Cross(point2 - point1, point3 - point1));
    Single  d = -Vector3::Dot(n, point1);

    return { n, d };
}

Single Plane::Dot(const Plane& plane, const Vector4& value)
{
    return Vector4::Dot({ plane.Normal(), plane.D() }, value);
}

Single Plane::DotNormal(const Plane& p, const Vector3& v)
{
    // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.plane.xmplanedotnormal(v=vs.85).aspx
    return Vector3::Dot(p.Normal(), v);
}

Single Plane::DotCoordinate(const Plane& p, const Vector3& value)
{
    return Plane::DotNormal(p, value) + p.D();
}

Plane Plane::Normalize(const Plane& value)
{
    Single reciprocalLength = 1.0f / value.normal.Length();

    return { value.normal * reciprocalLength, value.d * reciprocalLength };
}

Plane Plane::Transform(const Plane& plane, const Matrix& matrix)
{
    return { Vector4 { plane.normal, plane.d } * Matrix::Transpose(Matrix::Invert(matrix)) };
}

Plane Plane::Transform(const Plane& plane, const Quaternion& rotation)
{
    // Reference: http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/transforms/
    //
    //      Pout = q * Pin * conj(q)
    //

    auto pout = (rotation * Quaternion(plane.normal, 0.0f) * Quaternion::Conjugate(rotation));

    return { pout.X(), pout.Y(), pout.Z(), pout.W() };
}

Plane::Plane()
    : Plane { 0.0f, 0.0f, 0.0f, 0.0f }
{
}

Plane::Plane(const Single& a, const Single& b, const Single& c, const Single& d)
    : normal { a, b, c }
    , d      { d }
{
}

Plane::Plane(const Vector3& normal, const System::Single& d)
    : normal { normal }
    , d      { d }
{
}

Plane::Plane(const Vector4& value)
    : normal { value.X(), value.Y(), value.Z() },
      d      { value.W() }
{
}

Plane::Plane(const Plane& value)
    : normal { value.normal }
    , d      { value.d }
{
}

const Vector3& Plane::Normal() const
{
    return this->normal;
}

void Plane::Normal(const Vector3& normal)
{
    this->normal = normal;
}

const System::Single& Plane::D() const
{
    return this->d;
}

void Plane::D(const Single& d)
{
    this->d = d;
}

PlaneIntersectionType Plane::Intersects(const BoundingBox& box) const
{
    throw std::runtime_error("Not implemented");
}

PlaneIntersectionType Plane::Intersects(const BoundingFrustrum& frustrum) const
{
    throw std::runtime_error("Not implemented");
}

PlaneIntersectionType Plane::Intersects(const BoundingSphere& sphere) const
{
    return sphere.Intersects(*this);
}

Plane& Plane::operator=(const Plane& plane)
{
    if (this != &plane)
    {
        this->normal = plane.normal;
        this->d      = plane.d;
    }

    return *this;
}

bool Plane::operator==(const Plane& plane) const
{
    return (this->normal == plane.normal
         && this->d      == plane.d);
}

bool Plane::operator!=(const Plane& plane) const
{
    return !(*this == plane);
}
