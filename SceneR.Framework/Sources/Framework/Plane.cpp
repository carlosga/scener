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

    auto r = (rotation * Quaternion(plane.normal, 0.0f) * Quaternion::Conjugate(rotation));

    return { r.X(), r.Y(), r.Z(), r.W() };
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

Plane::Plane(const Vector3& point1, const Vector3& point2, const Vector3& point3)
    : normal { }
    , d      { 0.0f }
{
    // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.plane.xmplanefrompoints(v=vs.85).aspx
    auto v21 = point1 - point2;
    auto v31 = point1 - point3;
    auto n   = Vector3::Normalize(Vector3::Cross(v21, v31));
    auto d   = Vector3::Dot(n, point1);

    this->normal = n;
    this->d      = -d;
}

Plane::Plane(const Vector4& value)
	: normal { Vector3::Normalize({ value.X(), value.Y(), value.Z() }) },
      d      { value.W() }
{
}

Plane::Plane(const Plane& value)
    : normal { value.normal }
    , d      { value.d }
{
}

const System::Single& Plane::D() const
{
    return this->d;
}

const Vector3& Plane::Normal() const
{
    return this->normal;
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
