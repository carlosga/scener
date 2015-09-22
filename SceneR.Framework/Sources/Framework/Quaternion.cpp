// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/Quaternion.hpp>

#include <cassert>

#include <System/Math.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Matrix.hpp>

namespace SceneR
{
    namespace Framework
    {
        using System::Math;

        const Quaternion Quaternion::identity { 0.0f, 0.0f, 0.0f, 1.0f };

        Quaternion Quaternion::conjugate(const Quaternion& quaternion)
        {
            // The conjugate of a quaternion is defined by
            // q* = (w + xi + yj + zk) = w -xi -yj -zk
            return { -quaternion.x, -quaternion.y, -quaternion.z, quaternion.w };
        }

        Quaternion Quaternion::create_from_axis_angle(const Vector3& axisOfRotation, const float& angle)
        {
            // The quaternion in terms of axis-angle is:
            // q = cos(a/2) + i ( x * sin(a/2)) + j (y * sin(a/2)) + k ( z * sin(a/2))

            float theta = angle / 2;
            float rSin  = Math::sin(theta);

            return { axisOfRotation.x * rSin
                   , axisOfRotation.y * rSin
                   , axisOfRotation.z * rSin
                   , Math::cos(theta) };
        }

        Quaternion Quaternion::create_from_yaw_pitch_roll(const float& yaw, const float& pitch, const float& roll)
        {
            // http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q60
            // VECTOR3 vx = { 1, 0, 0 }, vy = { 0, 1, 0 }, vz = { 0, 0, 1 };
            // QUATERNION qx, qy, qz, qt;
            // quaternion_from_axisangle( qx, &vx, rx );
            // quaternion_from_axisangle( qy, &vy, ry );
            // quaternion_from_axisangle( qz, &vz, rz );
            // quaternion_multiply( &qt, &qx, &qy );
            // quaternion_multiply( &q,  &qt, &qz );

            auto qy = Quaternion::create_from_axis_angle(Vector3::unit_y, yaw);
            auto qx = Quaternion::create_from_axis_angle(Vector3::unit_x, pitch);
            auto qz = Quaternion::create_from_axis_angle(Vector3::unit_z, roll);

            return (qy * qx) * qz; // yaw * pitch * roll
        }

        float Quaternion::dot(const Quaternion& quaternion1, const Quaternion& quaternion2)
        {
            return (quaternion1.x * quaternion2.x)
                 + (quaternion1.y * quaternion2.y)
                 + (quaternion1.z * quaternion2.z)
                 + (quaternion1.w * quaternion2.w);
        }

        Quaternion Quaternion::create_from_rotation_matrix(const Matrix& matrix)
        {
            // http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm

            auto  result = Quaternion { };
            float tr     = matrix.m11 + matrix.m22 + matrix.m33;

            if (tr > 0.0f)
            {
                float s = Math::sqrt(tr + 1.0f);
                result.w = s * 0.5f;
                s = 0.5f / s;
                result.x = (matrix.m23 - matrix.m32) * s;
                result.y = (matrix.m31 - matrix.m13) * s;
                result.z = (matrix.m12 - matrix.m21) * s;
            }
            else
            {
                if ((matrix.m11 >= matrix.m22) && (matrix.m11 >= matrix.m33))
                {
                    float s  = Math::sqrt(1.0f + matrix.m11 - matrix.m22 - matrix.m33);
                    float s2 = 0.5f / s;
                    result.w  = (matrix.m23 - matrix.m32) * s2;
                    result.x  = 0.5f * s;
                    result.y  = (matrix.m12 + matrix.m21) * s2;
                    result.z  = (matrix.m13 + matrix.m31) * s2;
                }
                else if (matrix.m22 > matrix.m33)
                {
                    float s  = Math::sqrt(1.0f + matrix.m22 - matrix.m11 - matrix.m33);
                    float s2 = 0.5f / s;
                    result.w  = (matrix.m31 - matrix.m13) * s2;
                    result.x  = (matrix.m21 + matrix.m12) * s2;
                    result.y  = 0.5f * s;
                    result.z  = (matrix.m32 + matrix.m23) * s2;
                }
                else
                {
                    float s  = Math::sqrt(1.0f + matrix.m33 - matrix.m11 - matrix.m22);
                    float s2 = 0.5f / s;
                    result.w  = (matrix.m12 - matrix.m21) * s2;
                    result.x  = (matrix.m31 + matrix.m13) * s2;
                    result.y  = (matrix.m32 + matrix.m23) * s2;
                    result.z  = 0.5f * s;
                }
            }

            return result;
        }

        Quaternion Quaternion::inverse(const Quaternion& value)
        {
            // The multiplicative inverse of a quaternion q is constructed as
            // q^-1 = q* / N(q)
            //
            // Where:
            //  q* is the quaternion Conjugate
            //  N(q) is the quaternion norm
            return Quaternion::conjugate(value) / value.length_squared();
        }

        Quaternion Quaternion::lerp(const Quaternion& quaternion1, const Quaternion& quaternion2, const float& amount)
        {
            float amount1 = 1.0f - amount;
            float amount2 = amount;

            if (Quaternion::dot(quaternion1, quaternion2) < 0.0f)
            {
                amount2 = -amount2;
            }

            return Quaternion::normalize(quaternion1 * amount1 + quaternion2 * amount2);
        }

        Quaternion Quaternion::negate(const Quaternion & value)
        {
            return value * -1.0f;
        }

        Quaternion Quaternion::normalize(const Quaternion& value)
        {
            return value / value.length();
        }

        Quaternion Quaternion::slerp(const Quaternion& quaternion1, const Quaternion& quaternion2, const float& amount)
        {
            float w1;
            float w2;
            float cosTheta = Quaternion::dot(quaternion1, quaternion2);
            bool  flip     = false;

            if (cosTheta < 0.0f)
            {
                // We need to flip a quaternion for shortest path interpolation
                cosTheta = -cosTheta;
                flip     = true;
            }

            float theta    = Math::acos(cosTheta);
            float sinTheta = Math::sin(theta);

            if (sinTheta > 0.005f)
            {
                w1 = Math::sin((1.0f - amount) * theta) / sinTheta;
                w2 = Math::sin(amount * theta) / sinTheta;
            }
            else
            {
                // They're almost the same quaternion
                w1 = 1.0f - amount;
                w2 = amount;
            }

            if (flip)
            {
                w2 = -w2;
            }

            return (quaternion1 * w1 + quaternion2 * w2);
        }

        Quaternion::Quaternion()
            : Quaternion { 0.0f, 0.0f, 0.0f, 0.0f }
        {
        }

        Quaternion::Quaternion(const Vector3& value, const float& w)
            : Quaternion { value.x, value.y, value.z, w }
        {
        }

        Quaternion::Quaternion(const float& x, const float& y, const float& z, const float& w)
            : x { x }
            , y { y }
            , z { z }
            , w { w }
        {
        }

        bool Quaternion::is_identity() const
        {
            return (*this == Quaternion::identity);
        }

        float Quaternion::length_squared() const
        {
            return (this->x * this->x)
                 + (this->y * this->y)
                 + (this->z * this->z)
                 + (this->w * this->w);
        }

        float Quaternion::length() const
        {
            return Math::sqrt(this->length_squared());
        }

        float& Quaternion::operator[](const std::size_t& index)
        {
            assert(index < 4);

            return (this->data[index]);
        }

        const float& Quaternion::operator[](const std::size_t& index) const
        {
            assert(index < 4);

            return (this->data[index]);
        }

        bool Quaternion::operator==(const Quaternion& value) const
        {
            return (Math::equal(this->x, value.x)
                 && Math::equal(this->y, value.y)
                 && Math::equal(this->z, value.z)
                 && Math::equal(this->w, value.w));
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

            w = (q0.w * q1.w - q0.x * q1.x - q0.y * q1.y - q0.z * q1.z);
            x = (q0.w * q1.x + q0.x * q1.w + q0.y * q1.z - q0.z * q1.y);
            y = (q0.w * q1.y - q0.x * q1.z + q0.y * q1.w + q0.z * q1.x);
            z = (q0.w * q1.z + q0.x * q1.y - q0.y * q1.x + q0.z * q1.w);

            return *this;
        }

        Quaternion& Quaternion::operator*=(const float& value)
        {
            x *= value;
            y *= value;
            z *= value;
            w *= value;

            return *this;
        }

        Quaternion& Quaternion::operator/=(const Quaternion& value)
        {
            x /= value.x;
            y /= value.y;
            z /= value.z;
            w /= value.w;

            return *this;
        }

        Quaternion& Quaternion::operator/=(const float& value)
        {
            x /= value;
            y /= value;
            z /= value;
            w /= value;

            return *this;
        }

        Quaternion& Quaternion::operator-=(const Quaternion& value)
        {
            x -= value.x;
            y -= value.y;
            z -= value.z;
            w -= value.w;

            return *this;
        }

        Quaternion& Quaternion::operator+=(const Quaternion& value)
        {
            x += value.x;
            y += value.y;
            z += value.z;
            w += value.w;

            return *this;
        }

        const Quaternion Quaternion::operator*(const Quaternion& value) const
        {
            auto result = *this;

            result *= value;

            return result;
        }

        const Quaternion Quaternion::operator*(const float& value) const
        {
            auto result = *this;

            result *= value;

            return result;
        }

        const Quaternion Quaternion::operator/(const Quaternion& r) const
        {
            // http://es.mathworks.com/help/aeroblks/quaterniondivision.html
            auto q             = *this;
            auto lengthSquared = r.length_squared();

            auto qx = (r.x * q.x + r.y * q.y + r.z * q.z + r.w * q.w) / lengthSquared;
            auto qy = (r.x * q.y - r.y * q.x - r.z * q.w + r.w * q.z) / lengthSquared;
            auto qz = (r.x * q.z + r.y * q.w - r.z * q.x - r.w * q.y) / lengthSquared;
            auto qw = (r.x * q.w - r.y * q.z + r.z * q.y - r.w * q.x) / lengthSquared;

            return Quaternion::conjugate({ qw, qz, qy, qx });
        }

        const Quaternion Quaternion::operator/(const float& value) const
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
            return Quaternion { -x, -y, -z, -w };
        }

        const Quaternion Quaternion::operator+(const Quaternion& value) const
        {
            auto result = *this;

            result += value;

            return result;
        }
    }
}
