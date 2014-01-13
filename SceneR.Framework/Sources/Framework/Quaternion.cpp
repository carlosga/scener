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

#include <Framework/MathHelper.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector3.hpp>
#include <cassert>
#include <cmath>

using namespace System;
using namespace SceneR::Framework;

const Quaternion Quaternion::Identity(0.0f, 0.0f, 0.0f, 1.0f);

Quaternion Quaternion::Conjugate(const Quaternion& quaternion)
{
    Quaternion result(quaternion);

    result.Conjugate();

    return result;
}

Quaternion Quaternion::CreateFromAxisAngle(const Vector3& axisOfRotation, const Single& angle)
{
    // The quaternion in terms of axis-angle is:
    // q = cos(a/2) + i ( x * sin(a/2)) + j (y * sin(a/2)) + k ( z * sin(a/2))

    Single theta = angle / 2;
    Single rSin  = sin(theta);

    return Quaternion(axisOfRotation.X() * rSin,
                      axisOfRotation.Y() * rSin,
                      axisOfRotation.Z() * rSin,
                      cos(theta));
}

Quaternion Quaternion::CreateFromYawPitchRoll(const Single& yaw, const Single& pitch, const Single& roll)
{
    // http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q60
    // VECTOR3 vx = { 1, 0, 0 }, vy = { 0, 1, 0 }, vz = { 0, 0, 1 };
    // QUATERNION qx, qy, qz, qt;
    // quaternion_from_axisangle( qx, &vx, rx );
    // quaternion_from_axisangle( qy, &vy, ry );
    // quaternion_from_axisangle( qz, &vz, rz );
    // quaternion_multiply( &qt, &qx, &qy );
    // quaternion_multiply( &q,  &qt, &qz );

    Quaternion qx = Quaternion::CreateFromAxisAngle(Vector3::UnitX, roll);
    Quaternion qy = Quaternion::CreateFromAxisAngle(Vector3::UnitY, yaw);
    Quaternion qz = Quaternion::CreateFromAxisAngle(Vector3::UnitZ, pitch);
    Quaternion qt = qx * qy;

    return qt * qz;
}

Quaternion Quaternion::CreateFromRotationMatrix(const Matrix& matrix)
{
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm

    Quaternion result;
    Single     tr = matrix.M11() + matrix.M22() + matrix.M33();

    if (tr > 0.0f)
    {
        Single s = std::sqrt(tr + 1.0f);
        result.w = s * 0.5f;
        s = 0.5f / s;
        result.x = (matrix.M23() - matrix.M32()) * s;
        result.y = (matrix.M31() - matrix.M13()) * s;
        result.z = (matrix.M12() - matrix.M21()) * s;
    }
    else if ((matrix.M11() >= matrix.M22()) && (matrix.M11() >= matrix.M33()))
    {
        Single s  = std::sqrt(1.0f + matrix.M11() - matrix.M22() - matrix.M33());
        Single s2 = 0.5f / s;
        result.w  = (matrix.M23() - matrix.M32()) * s2;
        result.x  = 0.5f * s;
        result.y  = (matrix.M12() + matrix.M21()) * s2;
        result.z  = (matrix.M13() + matrix.M31()) * s2;
    }
    else if (matrix.M22() > matrix.M33())
    {
        Single s  = std::sqrt(1.0f + matrix.M22() - matrix.M11() - matrix.M33());
        Single s2 = 0.5f / s;
        result.w  = (matrix.M31() - matrix.M13()) * s2;
        result.x  = (matrix.M21() + matrix.M12()) * s2;
        result.y  = 0.5f * s;
        result.z  = (matrix.M32() + matrix.M23()) * s2;
    }
    else
    {
        Single s  = std::sqrt(1.0f + matrix.M33() - matrix.M11() - matrix.M22());
        Single ss = 0.5f / s;
        result.w  = (matrix.M12() - matrix.M21()) * ss;
        result.x  = (matrix.M31() + matrix.M13()) * ss;
        result.y  = (matrix.M32() + matrix.M23()) * ss;
        result.z  = 0.5f * s;
    }

    return result;
}

Quaternion Quaternion::Lerp(const Quaternion& quaternion1, const Quaternion& quaternion2, const Single& amount)
{
    Single amount1 = 1.0f - amount;
    Single amount2 = amount;

    if (quaternion1.DotProduct(quaternion2) < 0.0f)
    {
        amount2 = -amount2;
    }

    return Quaternion::Normalize(quaternion1 * amount1 + quaternion2 * amount2);
}

Quaternion Quaternion::Normalize(const Quaternion& quaternion)
{
    Quaternion result(quaternion);

    result.Normalize();

    return result;
}

Quaternion Quaternion::Slerp(const Quaternion& quaternion1, const Quaternion& quaternion2, const Single& amount)
{
    Single  w1;
    Single  w2;
    Single  cosTheta = quaternion1.DotProduct(quaternion2);
    Boolean bFlip    = false;

    if (cosTheta < 0.0f)
    {
        // We need to flip a quaternion for shortest path interpolation
        cosTheta = -cosTheta;
        bFlip    = true;
    }

    Single theta    = std::acos(cosTheta);
    Single sinTheta = std::sin(theta);

    if (sinTheta > 0.005f)
    {
        w1 = std::sin((1.0f - amount) * theta) / sinTheta;
        w2 = std::sin(amount * theta) / sinTheta;
    }
    else
    {
        // They're almost the same quaternion
        w1 = 1.0f - amount;
        w2 = amount;
    }

    if (bFlip)
    {
        w2 = -w2;
    }

    return (quaternion1 * w1 + quaternion2 * w2);
}

Quaternion::Quaternion()
    : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
}

Quaternion::Quaternion(const Single&  x, const Single&  y, const Single&  z, const Single& w)
    : x(x), y(y), z(z), w(w)
{
}

Quaternion::Quaternion(const Vector3& value, const System::Single& w)
    : x(value.X()), y(value.Y()), z(value.Z()), w(w)
{
}

Quaternion::Quaternion(const Quaternion& quaternion)
    : x(quaternion.X()), y(quaternion.Y()), z(quaternion.Z()), w(quaternion.W())
{
}

const Single& Quaternion::X() const
{
    return this->x;
}

const Single& Quaternion::Y() const
{
    return this->y;
}

const Single& Quaternion::Z() const
{
    return this->z;
}

const Single& Quaternion::W() const
{
    return this->w;
}

Single Quaternion::DotProduct(const Quaternion& quaternion) const
{
    return ((this->x * quaternion.x)
          + (this->y * quaternion.y)
          + (this->z * quaternion.z)
          + (this->w * quaternion.w));
}

void Quaternion::Conjugate()
{
    // The conjugate of a quaternion is defined by
    // q* = (w + xi + yj + zk) = w -xi  -yj -zk
    this->x = -this->x;
    this->y = -this->y;
    this->z = -this->z;
}

void Quaternion::Invert()
{
    // The multiplicative inverse of a quaternion q is constructed as
    // q^-1 = q* / N(q)
    //
    // Where:
    //  q* is the quaternion Conjugate
    //  N(q) is the quaternion norm
    this->Conjugate();

    *this /= this->LengthSquared();
}

bool Quaternion::IsIdentity() const
{
    return (*this == Quaternion::Identity);
}

Single Quaternion::LengthSquared() const
{
    return (this->x * this->x)
         + (this->y * this->y)
         + (this->z * this->z)
         + (this->w * this->w);
}

Single Quaternion::Length() const
{
    return std::sqrt(this->LengthSquared());
}

void Quaternion::Normalize()
{
    (*this /= this->Length());
}

Single& Quaternion::operator[](const Int32& index)
{
    assert(index >= 0 && index < 4);

    return (this->quaternion[index]);
}

const Single& Quaternion::operator[](const Int32& index) const
{
    assert(index >= 0 && index < 4);

    return (this->quaternion[index]);
}

Quaternion& Quaternion::operator=(const Quaternion& quaternion)
{
    if (this != &quaternion)
    {
        this->x = quaternion.X();
        this->y = quaternion.Y();
        this->z = quaternion.Z();
        this->w = quaternion.W();
    }

    return *this;
}

bool Quaternion::operator==(const Quaternion& quaternion) const
{
    return (this->x == quaternion.x
         && this->y == quaternion.y
         && this->z == quaternion.z
         && this->w == quaternion.w);
}

bool Quaternion::operator!=(const Quaternion& quaternion) const
{
    return !(*this == quaternion);
}

Quaternion& Quaternion::operator*=(const Quaternion& q1)
{
    // Multiplication of quaternions is defined by
    // q0q1 = (w0 + x0i + y0j + z0k)(w1 + x1i + y1j + z1k) = (w0w1 - x0x1 - y0y1 - z0z1)
    //                                                     + (w0x1 + x0w1 + y0z1 - z0y1)i
    //                                                     + (w0y1 - x0z1 + y0w1 + z0x1)j
    //                                                     + (w0z1 + x0y1 - y0x1 + z0w1)k

    Quaternion q0 = *this;

    this->w = (q0.w * q1.w - q0.x * q1.x - q0.y * q1.y - q0.z * q1.z);
    this->x = (q0.w * q1.x + q0.x * q1.w + q0.y * q1.z - q0.z * q1.y);
    this->y = (q0.w * q1.y - q0.x * q1.z + q0.y * q1.w + q0.z * q1.x);
    this->z = (q0.w * q1.z + q0.x * q1.y - q0.y * q1.x + q0.z * q1.w);

    return *this;
}

Quaternion& Quaternion::operator*=(const Single& value)
{
    this->x *= value;
    this->y *= value;
    this->z *= value;
    this->w *= value;

    return *this;
}

Quaternion& Quaternion::operator/=(const Quaternion& quaternion)
{
    this->x /= quaternion.x;
    this->y /= quaternion.y;
    this->z /= quaternion.z;
    this->w /= quaternion.w;

    return *this;
}

Quaternion& Quaternion::operator/=(const Single& value)
{
    this->x /= value;
    this->y /= value;
    this->z /= value;
    this->w /= value;

    return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& quaternion)
{
    this->x -= quaternion.x;
    this->y -= quaternion.y;
    this->z -= quaternion.z;
    this->w -= quaternion.w;

    return *this;
}

Quaternion& Quaternion::operator+=(const Quaternion& quaternion)
{
    this->x += quaternion.x;
    this->y += quaternion.y;
    this->z += quaternion.z;
    this->w += quaternion.w;

    return *this;
}

const Quaternion Quaternion::operator*(const Quaternion& quaternion) const
{
    Quaternion result = *this;

    result *= quaternion;

    return result;
}

const Quaternion Quaternion::operator*(const Single& value) const
{
    Quaternion result = *this;

    result *= value;

    return result;
}

const Quaternion Quaternion::operator/(const Quaternion& quaternion) const
{
    Quaternion result = *this;

    result /= quaternion;

    return result;
}

const Quaternion Quaternion::operator/(const Single& value) const
{
    Quaternion result = *this;

    result /= value;

    return result;
}

const Quaternion Quaternion::operator-(const Quaternion& quaternion) const
{
    Quaternion result = *this;

    result -= quaternion;

    return result;
}

const Quaternion Quaternion::operator+(const Quaternion& quaternion) const
{
    Quaternion result = *this;

    result += quaternion;

    return result;
}
