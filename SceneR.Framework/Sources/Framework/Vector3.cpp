// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/Vector3.hpp>

#include <cassert>

#include <System/Math.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>

namespace SceneR
{
    namespace Framework
    {
        using System::Math;

        const Vector3 Vector3::backward { 0.0f , 0.0f , 1.0f  };
        const Vector3 Vector3::down     { 0.0f , -1.0f, 0.0f  };
        const Vector3 Vector3::forward  { 0.0f , 0.0f , -1.0f };
        const Vector3 Vector3::left     { -1.0f, 0.0f , 0.0f  };
        const Vector3 Vector3::one      { 1.0f , 1.0f , 1.0f  };
        const Vector3 Vector3::right    { 1.0f , 0.0f , 0.0f  };
        const Vector3 Vector3::unit_x   { 1.0f , 0.0f , 0.0f  };
        const Vector3 Vector3::unit_y   { 0.0f , 1.0f , 0.0f  };
        const Vector3 Vector3::unit_z   { 0.0f , 0.0f , 1.0f  };
        const Vector3 Vector3::up       { 0.0f , 1.0f , 0.0f  };
        const Vector3 Vector3::zero     { 0.0f , 0.0f , 0.0f  };

        Vector3 Vector3::abs(const Vector3& value)
        {
            return { Math::abs(value.x), Math::abs(value.y), Math::abs(value.z) };
        }

        float Vector3::angle_between(const Vector3& left, const Vector3& right)
        {
            float lengthSquared = left.length_squared() * right.length_squared();

            return Math::acos(Vector3::dot(left, right) / Math::sqrt(lengthSquared));
        }

        Vector3 Vector3::barycentric(const Vector3& value1
                                   , const Vector3& value2
                                   , const Vector3& value3
                                   , const float&   amount1
                                   , const float&   amount2)
        {
            return { Math::barycentric(value1.x, value2.x, value3.x, amount1, amount2)
                   , Math::barycentric(value1.y, value2.y, value3.y, amount1, amount2)
                   , Math::barycentric(value1.z, value2.z, value3.z, amount1, amount2) };
        }

        Vector3 Vector3::catmull_rom(const Vector3& value1
                                   , const Vector3& value2
                                   , const Vector3& value3
                                   , const Vector3& value4
                                   , const float&   amount)
        {
            return { Math::catmull_rom(value1.x, value2.x, value3.x, value4.x, amount)
                   , Math::catmull_rom(value1.y, value2.y, value3.y, value4.y, amount)
                   , Math::catmull_rom(value1.z, value2.z, value3.z, value4.z, amount) };
        }

        Vector3 Vector3::clamp(const Vector3& value1, const Vector3& min, const Vector3& max)
        {
            return { Math::clamp(value1.x, min.x, max.x)
                   , Math::clamp(value1.y, min.y, max.y)
                   , Math::clamp(value1.z, min.z, max.z) };
        }

        Vector3 Vector3::cross(const Vector3& left, const Vector3& right)
        {
            // Reference: http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector3cross(v=vs.85).aspx
            return { (left.y * right.z) - (left.z * right.y)
                   , (left.z * right.x) - (left.x * right.z)
                   , (left.x * right.y) - (left.y * right.x) };
        }

        float Vector3::distance(const Vector3& value1, const Vector3& value2)
        {
            auto d = value2 - value1;

            return d.length();
        }

        float Vector3::distance_squared(const Vector3& value1, const Vector3& value2)
        {
            auto d = value2 - value1;

            return d.length_squared();
        }

        float Vector3::dot(const Vector3& left, const Vector3& right)
        {
            // The definition of the scalar (dot) product is:
            // a · b = |a||b|cosθ
            //
            // The scalar product can also be written in terms of Cartesian components as:
            // a · b = x1x2 + y1y2 + z1z2

            auto dotProduct = left * right;

            return (dotProduct.x + dotProduct.y + dotProduct.z);
        }

        Vector3 Vector3::hermite(const Vector3& value1
                               , const Vector3& tangent1
                               , const Vector3& value2
                               , const Vector3& tangent2
                               , const float&   amount)
        {
            return { Math::hermite(value1.x, tangent1.x, value2.x, tangent2.x, amount)
                   , Math::hermite(value1.y, tangent1.y, value2.y, tangent2.y, amount)
                   , Math::hermite(value1.z, tangent1.z, value2.z, tangent2.z, amount) };
        }

        Vector3 Vector3::lerp(const Vector3& value1, const Vector3& value2, const float& amount)
        {
            return { Math::lerp(value1.x, value2.x, amount)
                   , Math::lerp(value1.y, value2.y, amount)
                   , Math::lerp(value1.z, value2.z, amount) };
        }

        Vector3 Vector3::min(const Vector3& value1, const Vector3& value2)
        {
            return { Math::min(value1.x, value2.x)
                   , Math::min(value1.y, value2.y)
                   , Math::min(value1.z, value2.z) };
        }

        Vector3 Vector3::max(const Vector3& value1, const Vector3& value2)
        {
            return { Math::max(value1.x, value2.x)
                   , Math::max(value1.y, value2.y)
                   , Math::max(value1.z, value2.z) };
        }

        Vector3 Vector3::negate(const Vector3& value)
        {
            return (value * -1.0f);
        }

        Vector3 Vector3::normalize(const Vector3& value)
        {
            // To find the unit vector of another vector, we use the modulus operator
            // and scalar multiplication like so:
            // b = a / |a|
            //
            // Where |a| is the modulus of a
            return (value / value.length());
        }

        Vector3 Vector3::reflect(const Vector3& vector, const Vector3& normal)
        {
            // Reference : http://mathworld.wolfram.com/Reflection.html
            // The position of the point reflected in the given plane is given by
            // r = v-2·Dn

            return vector - 2 * Vector3::dot(vector, normal) * normal;
        }

        Vector3 Vector3::smooth_step(const Vector3& value1, const Vector3& value2, const float& amount)
        {
            return { Math::smooth_step(value1.x, value2.x, amount)
                   , Math::smooth_step(value1.y, value2.y, amount)
                   , Math::smooth_step(value1.z, value2.z, amount) };
        }

        Vector3 Vector3::square_root(const Vector3& value)
        {
            return {Math::sqrt(value.x), Math::sqrt(value.y), Math::sqrt(value.z) };
        }

        Vector3 Vector3::transform(const Vector3& position, const Matrix& matrix)
        {
            return (position * matrix);
        }

        Vector3 Vector3::transform(const Vector3& value, const Quaternion& rotation)
        {
            return (value * Matrix::create_from_quaternion(rotation));
        }

        Vector3 Vector3::transform_normal(const Vector3& normal, const Matrix& matrix)
        {
            float x = (normal.x * matrix.m11)
                    + (normal.y * matrix.m21)
                    + (normal.z * matrix.m31);

            float y = (normal.x * matrix.m12)
                    + (normal.y * matrix.m22)
                    + (normal.z * matrix.m32);

            float z = (normal.x * matrix.m13)
                    + (normal.y * matrix.m23)
                    + (normal.z * matrix.m33);

            return { x, y, z };
        }

        Vector3::Vector3()
            : Vector3 { 0.0f, 0.0f, 0.0f }
        {
        }

        Vector3::Vector3(const float& value)
            : Vector3 { value, value, value }
        {
        }

        Vector3::Vector3(const Vector2& value, const float& z)
            : Vector3 { value.x, value.y, z }
        {
        }

        Vector3::Vector3(const float& x, const float& y, const float& z)
            : x { x }
            , y { y }
            , z { z }
        {
        }

        Vector3::Vector3(const Vector3& vector)
            : x { vector.x }
            , y { vector.y }
            , z { vector.z }
        {
        }

        Vector3::~Vector3()
        {
        }

        float Vector3::length_squared() const
        {
            return (x * x) + (y * y) + (z * z);
        }

        float Vector3::length() const
        {
            // The modulus or magnitude of a vector is simply its length.
            // This can easily be found using Pythagorean Theorem with the vector components.
            //
            // The modulus is written like:
            // a = |a|
            //
            // Given:
            // a = xi + yj + zk
            //
            // Then:
            //
            // |a| = sqrt(x^2 + y^2 + z^2)

            return Math::sqrt(length_squared());
        }

        float& Vector3::operator[](const std::size_t& index)
        {
            assert(index < 3);

            return (data[index]);
        }

        const float& Vector3::operator[](const std::size_t& index) const
        {
            assert(index < 3);

            return (data[index]);
        }

        Vector3& Vector3::operator=(const Vector3& vector)
        {
            if (this != &vector)
            {
                x = vector.x;
                y = vector.y;
                z = vector.z;
            }

            return *this;
        }

        bool Vector3::operator==(const Vector3& vector) const
        {
            return (Math::equal(x, vector.x)
                 && Math::equal(y, vector.y)
                 && Math::equal(z, vector.z));
        }

        bool Vector3::operator!=(const Vector3& vector) const
        {
            return !(*this == vector);
        }

        Vector3& Vector3::operator*=(const Vector3& vector)
        {
            x *= vector.x;
            y *= vector.y;
            z *= vector.z;

            return *this;
        }

        Vector3& Vector3::operator*=(const float& value)
        {
            x *= value;
            y *= value;
            z *= value;

            return *this;
        }

        Vector3& Vector3::operator/=(const Vector3& vector)
        {
            x /= vector.x;
            y /= vector.y;
            z /= vector.z;

            return *this;
        }

        Vector3& Vector3::operator/=(const float& value)
        {
            x /= value;
            y /= value;
            z /= value;

            return *this;
        }

        Vector3& Vector3::operator-=(const Vector3& vector)
        {
            x -= vector.x;
            y -= vector.y;
            z -= vector.z;

            return *this;
        }

        Vector3& Vector3::operator+=(const Vector3& vector)
        {
            x += vector.x;
            y += vector.y;
            z += vector.z;

            return *this;
        }

        const Vector3 Vector3::operator*(const Vector3& vector) const
        {
            auto result = *this;  // Make a copy of myself. Same as Vector3D result(*this)

            result *= vector;

            return result;
        }

        const Vector3 Vector3::operator*(const float& value) const
        {
            auto result = *this;

            result *= value;

            return result;
        }

        const Vector3 Vector3::operator*(const Matrix& matrix) const
        {
            // http://softimage.wiki.softimage.com/xsidocs/iceref_Multiply_Vector_by_Matrix.htm
            float vx = (x * matrix.m11)
                     + (y * matrix.m21)
                     + (z * matrix.m31)
                     +      matrix.m41;

            float vy = (x * matrix.m12)
                     + (y * matrix.m22)
                     + (z * matrix.m32)
                     +      matrix.m42;

            float vz = (x * matrix.m13)
                     + (y * matrix.m23)
                     + (z * matrix.m33)
                     +      matrix.m43;

            float vw = (x * matrix.m14)
                     + (y * matrix.m24)
                     + (z * matrix.m34)
                     +      matrix.m44;

            return { vx / vw, vy / vw, vz / vw };
        }

        const Vector3 Vector3::operator/(const Vector3& vector) const
        {
            auto result = *this;

            result /= vector;

            return result;
        }

        const Vector3 Vector3::operator/(const float& value) const
        {
            auto result = *this;

            result /= value;

            return result;
        }

        const Vector3 Vector3::operator-(const Vector3& vector) const
        {
            auto result = *this;

            result -= vector;

            return result;
        }

        const Vector3 Vector3::operator-() const
        {
            return *this * -1;
        }

        const Vector3 Vector3::operator+(const Vector3& vector) const
        {
            auto result = *this;

            result += vector;

            return result;
        }
    }
}
