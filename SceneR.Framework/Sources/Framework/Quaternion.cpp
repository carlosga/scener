// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/Quaternion.hpp>

#include <cassert>

#include <System/Math.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Matrix.hpp>

using namespace System;
using namespace SceneR::Framework;

const Quaternion Quaternion::Identity { 0.0f, 0.0f, 0.0f, 1.0f };

Quaternion Quaternion::Conjugate(const Quaternion& quaternion)
{
    // The conjugate of a quaternion is defined by
    // q* = (w + xi + yj + zk) = w -xi -yj -zk
    return { -quaternion.x, -quaternion.y, -quaternion.z, quaternion.w };
}

Quaternion Quaternion::CreateFromAxisAngle(const Vector3& axisOfRotation, const Single& angle)
{
    // The quaternion in terms of axis-angle is:
    // q = cos(a/2) + i ( x * sin(a/2)) + j (y * sin(a/2)) + k ( z * sin(a/2))

    Single theta = angle / 2;
    Single rSin  = Math::Sin(theta);

    return { axisOfRotation.X() * rSin
           , axisOfRotation.Y() * rSin
           , axisOfRotation.Z() * rSin
           , Math::Cos(theta) };
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

    auto qy = Quaternion::CreateFromAxisAngle(Vector3::UnitY, yaw);
    auto qx = Quaternion::CreateFromAxisAngle(Vector3::UnitX, pitch);
    auto qz = Quaternion::CreateFromAxisAngle(Vector3::UnitZ, roll);

    return (qy * qx) * qz; // yaw * pitch * roll
}

System::Single Quaternion::Dot(const Quaternion& quaternion1, const Quaternion& quaternion2)
{
    return (quaternion1.x * quaternion2.x)
         + (quaternion1.y * quaternion2.y)
         + (quaternion1.z * quaternion2.z)
         + (quaternion1.w * quaternion2.w);
}

Quaternion Quaternion::CreateFromRotationMatrix(const Matrix& matrix)
{
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm

    auto   result = Quaternion { };
    Single tr     = matrix.M11() + matrix.M22() + matrix.M33();

    if (tr > 0.0f)
    {
        Single s = Math::Sqrt(tr + 1.0f);
        result.w = s * 0.5f;
        s = 0.5f / s;
        result.x = (matrix.M23() - matrix.M32()) * s;
        result.y = (matrix.M31() - matrix.M13()) * s;
        result.z = (matrix.M12() - matrix.M21()) * s;
    }
    else
    {
        if ((matrix.M11() >= matrix.M22()) && (matrix.M11() >= matrix.M33()))
        {
            Single s  = Math::Sqrt(1.0f + matrix.M11() - matrix.M22() - matrix.M33());
            Single s2 = 0.5f / s;
            result.w  = (matrix.M23() - matrix.M32()) * s2;
            result.x  = 0.5f * s;
            result.y  = (matrix.M12() + matrix.M21()) * s2;
            result.z  = (matrix.M13() + matrix.M31()) * s2;
        }
        else if (matrix.M22() > matrix.M33())
        {
            Single s  = Math::Sqrt(1.0f + matrix.M22() - matrix.M11() - matrix.M33());
            Single s2 = 0.5f / s;
            result.w  = (matrix.M31() - matrix.M13()) * s2;
            result.x  = (matrix.M21() + matrix.M12()) * s2;
            result.y  = 0.5f * s;
            result.z  = (matrix.M32() + matrix.M23()) * s2;
        }
        else
        {
            Single s  = Math::Sqrt(1.0f + matrix.M33() - matrix.M11() - matrix.M22());
            Single s2 = 0.5f / s;
            result.w  = (matrix.M12() - matrix.M21()) * s2;
            result.x  = (matrix.M31() + matrix.M13()) * s2;
            result.y  = (matrix.M32() + matrix.M23()) * s2;
            result.z  = 0.5f * s;
        }
    }

    return result;
}

Quaternion Quaternion::Inverse(const Quaternion& value)
{
    // The multiplicative inverse of a quaternion q is constructed as
    // q^-1 = q* / N(q)
    //
    // Where:
    //  q* is the quaternion Conjugate
    //  N(q) is the quaternion norm
    return Quaternion::Conjugate(value) / value.LengthSquared();
}

Quaternion Quaternion::Lerp(const Quaternion& quaternion1, const Quaternion& quaternion2, const Single& amount)
{
    Single amount1 = 1.0f - amount;
    Single amount2 = amount;

    if (Quaternion::Dot(quaternion1, quaternion2) < 0.0f)
    {
        amount2 = -amount2;
    }

    return Quaternion::Normalize(quaternion1 * amount1 + quaternion2 * amount2);
}

Quaternion Quaternion::Negate(const Quaternion & value)
{
    return value * -1.0f;
}

Quaternion Quaternion::Normalize(const Quaternion& value)
{
    return value / value.Length();
}

Quaternion Quaternion::Slerp(const Quaternion& quaternion1, const Quaternion& quaternion2, const Single& amount)
{
    Single  w1;
    Single  w2;
    Single  cosTheta = Quaternion::Dot(quaternion1, quaternion2);
    Boolean bFlip    = false;

    if (cosTheta < 0.0f)
    {
        // We need to flip a quaternion for shortest path interpolation
        cosTheta = -cosTheta;
        bFlip    = true;
    }

    Single theta    = Math::Acos(cosTheta);
    Single sinTheta = Math::Sin(theta);

    if (sinTheta > 0.005f)
    {
        w1 = Math::Sin((1.0f - amount) * theta) / sinTheta;
        w2 = Math::Sin(amount * theta) / sinTheta;
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
    : Quaternion { 0.0f, 0.0f, 0.0f, 0.0f }
{
}

Quaternion::Quaternion(const Vector3& value, const Single& w)
    : Quaternion { value.X(), value.Y(), value.Z(), w }
{
}

Quaternion::Quaternion(const Single& x, const Single& y, const Single& z, const Single& w)
    : x { x }
    , y { y }
    , z { z }
    , w { w }
{
}

Quaternion::Quaternion(const Quaternion& quaternion)
    : x { quaternion.x }
    , y { quaternion.y }
    , z { quaternion.z }
    , w { quaternion.w }
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

void Quaternion::X(const Single& x)
{
    this->x = x;
}

void Quaternion::Y(const Single& y)
{
    this->y = y;
}

void Quaternion::Z(const Single& z)
{
    this->z = z;
}

void Quaternion::W(const Single& w)
{
    this->w = w;
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
    return Math::Sqrt(this->LengthSquared());
}

Single& Quaternion::operator[](const Size& index)
{
    assert(index < 4);

    return (this->quaternion[index]);
}

const Single& Quaternion::operator[](const Size& index) const
{
    assert(index < 4);

    return (this->quaternion[index]);
}

Quaternion& Quaternion::operator=(const Quaternion& value)
{
    if (this != &value)
    {
        this->x = value.x;
        this->y = value.y;
        this->z = value.z;
        this->w = value.w;
    }

    return *this;
}

bool Quaternion::operator==(const Quaternion& value) const
{
    return (this->x == value.x
         && this->y == value.y
         && this->z == value.z
         && this->w == value.w);
}

bool Quaternion::operator!=(const Quaternion& value) const
{
    return !(*this == value);
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

Quaternion& Quaternion::operator/=(const Quaternion& value)
{
    this->x /= value.x;
    this->y /= value.y;
    this->z /= value.z;
    this->w /= value.w;

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

Quaternion& Quaternion::operator-=(const Quaternion& value)
{
    this->x -= value.x;
    this->y -= value.y;
    this->z -= value.z;
    this->w -= value.w;

    return *this;
}

Quaternion& Quaternion::operator+=(const Quaternion& value)
{
    this->x += value.x;
    this->y += value.y;
    this->z += value.z;
    this->w += value.w;

    return *this;
}

const Quaternion Quaternion::operator*(const Quaternion& value) const
{
    auto result = *this;

    result *= value;

    return result;
}

const Quaternion Quaternion::operator*(const Single& value) const
{
    auto result = *this;

    result *= value;

    return result;
}

const Quaternion Quaternion::operator/(const Quaternion& r) const
{
    // http://es.mathworks.com/help/aeroblks/quaterniondivision.html
    auto q              = *this;
    auto lengthSuquared = r.LengthSquared();

    auto x = (r.x * q.x + r.y * q.y + r.z * q.z + r.w * q.w) / lengthSuquared;
    auto y = (r.x * q.y - r.y * q.x - r.z * q.w + r.w * q.z) / lengthSuquared;
    auto z = (r.x * q.z + r.y * q.w - r.z * q.x - r.w * q.y) / lengthSuquared;
    auto w = (r.x * q.w - r.y * q.z + r.z * q.y - r.w * q.x) / lengthSuquared;

    return Quaternion::Conjugate({ w, z, y, x });
}

const Quaternion Quaternion::operator/(const Single& value) const
{
    auto result = *this;

    result /= value;

    return result;
}

const Quaternion Quaternion::operator-(const Quaternion& value) const
{
    auto result = *this;

    result -= value;

    return result;
}

const Quaternion Quaternion::operator-() const
{
    return Quaternion { -this->x, -this->y, -this->z, -this->w };
}

const Quaternion Quaternion::operator+(const Quaternion& value) const
{
    auto result = *this;

    result += value;

    return result;
}
