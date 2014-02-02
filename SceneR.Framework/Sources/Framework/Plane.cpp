//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#include <Framework/BoundingBox.hpp>
#include <Framework/BoundingFrustrum.hpp>
#include <Framework/BoundingSphere.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Plane.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector4.hpp>
#include <stdexcept>

using namespace System;
using namespace SceneR::Framework;

Vector4 Plane::DotNormal(const Vector3& p, const Vector3& v)
{
    // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.plane.xmplanedotnormal(v=vs.85).aspx
    return { Vector3::DotProduct(p, v)  };
}

Plane Plane::Normalize(const Plane& value)
{
    auto result = Plane(value);

    result.Normalize();

    return result;
}

Plane Plane::Transform(const Plane& plane, const Matrix& matrix)
{
    return { Vector4(plane.normal, plane.d) * Matrix::Transpose(Matrix::Invert(matrix)) };
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
	: d(d)
    , normal({ a, b, c })
{
}

Plane::Plane(const Vector3& normal, const System::Single& d)
	: d(d)
    , normal(normal)
{
}

Plane::Plane(const Vector3& point1, const Vector3& point2, const Vector3& point3)
    : d(0.0f)
    , normal()
{
    // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.plane.xmplanefrompoints(v=vs.85).aspx
    auto v21 = point1 - point2;
    auto v31 = point1 - point3;
    auto n   = Vector3::Normalize(Vector3::Cross(v21, v31));
    auto d   = Plane::DotNormal(n, point1);

    this->normal = n;
    this->d      = -d.W();
}

Plane::Plane(const Vector4& value)
	: d(value.W())
    , normal(Vector3::Normalize({ value.X(), value.Y(), value.Z() }))
{	
}

Plane::Plane(const Plane& value)
    : d(value.d)
    , normal(value.normal)
{
}

Plane::~Plane()
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

System::Single Plane::Dot(const Vector4& value) const
{
    auto v = Vector4(this->normal, this->d);

    return v.DotProduct(value);
}

System::Single Plane::DotCoordinate(const Vector3& value) const
{
    return Vector3::DotProduct(this->normal, value);
}

System::Single Plane::DotNormal(const Vector3& value) const
{
    auto tmp = Plane::DotNormal(this->normal, value);

    return (tmp.X() + tmp.Y() + tmp.Z() + tmp.W());
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

void Plane::Normalize()
{
    Single reciprocalLength = 1.0f / this->normal.Length();

    this->normal *= reciprocalLength;
    this->d      *= reciprocalLength;
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
