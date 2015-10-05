// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/Vector4.hpp>

#include <functional>
#include <gsl.h>

#include <System/Math.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>

namespace SceneR
{
    namespace Framework
    {
        using System::Math;

        const Vector4 Vector4::one    { 1.0f, 1.0f, 1.0f, 1.0f };
        const Vector4 Vector4::unit_x { 1.0f, 0.0f, 0.0f, 0.0f };
        const Vector4 Vector4::unit_y { 0.0f, 1.0f, 0.0f, 0.0f };
        const Vector4 Vector4::unit_z { 0.0f, 0.0f, 1.0f, 0.0f };
        const Vector4 Vector4::unit_w { 0.0f, 0.0f, 0.0f, 1.0f };
        const Vector4 Vector4::zero   { 0.0f, 0.0f, 0.0f, 0.0f };

        Vector4 Vector4::abs(const Vector4 &value) noexcept
        {
            return { Math::abs(value.x), Math::abs(value.y), Math::abs(value.z), Math::abs(value.w) };
        }

        Vector4 Vector4::barycentric(const Vector4& value1
                                   , const Vector4& value2
                                   , const Vector4& value3
                                   , const float&   amount1
                                   , const float&   amount2) noexcept
        {
            return { Math::barycentric(value1.x, value2.x, value3.x, amount1, amount2)
                   , Math::barycentric(value1.y, value2.y, value3.y, amount1, amount2)
                   , Math::barycentric(value1.z, value2.z, value3.z, amount1, amount2)
                   , Math::barycentric(value1.w, value2.w, value3.w, amount1, amount2) };
        }

        Vector4 Vector4::catmull_rom(const Vector4& value1
                                   , const Vector4& value2
                                   , const Vector4& value3
                                   , const Vector4& value4
                                   , const float&   amount) noexcept
        {
            return { Math::catmull_rom(value1.x, value2.x, value3.x, value4.x, amount)
                   , Math::catmull_rom(value1.y, value2.y, value3.y, value4.y, amount)
                   , Math::catmull_rom(value1.z, value2.z, value3.z, value4.z, amount)
                   , Math::catmull_rom(value1.w, value2.w, value3.w, value4.w, amount) };
        }

        Vector4 Vector4::clamp(const Vector4& value1, const Vector4& min, const Vector4& max) noexcept
        {
            return { Math::clamp(value1.x, min.x, max.x)
                   , Math::clamp(value1.y, min.y, max.y)
                   , Math::clamp(value1.z, min.z, max.z)
                   , Math::clamp(value1.w, min.w, max.w) };
        }

        float Vector4::distance(const Vector4& value1, const Vector4& value2) noexcept
        {
            auto d = value2 - value1;

            return d.length();
        }

        float Vector4::distance_squared(const Vector4& value1, const Vector4& value2) noexcept
        {
            auto d = value2 - value1;

            return d.length_squared();
        }

        float Vector4::dot(const Vector4& value1, const Vector4& value2) noexcept
        {
            auto dotProduct = value1 * value2;

            return (dotProduct.x + dotProduct.y + dotProduct.z + dotProduct.w);
        }

        Vector4 Vector4::hermite(const Vector4& value1
                               , const Vector4& tangent1
                               , const Vector4& value2
                               , const Vector4& tangent2
                               , const float&   amount) noexcept
        {
            return { Math::hermite(value1.x, tangent1.x, value2.x, tangent2.x, amount)
                   , Math::hermite(value1.y, tangent1.y, value2.y, tangent2.y, amount)
                   , Math::hermite(value1.z, tangent1.z, value2.z, tangent2.z, amount)
                   , Math::hermite(value1.w, tangent1.w, value2.w, tangent2.w, amount) };
        }

        Vector4 Vector4::lerp(const Vector4& value1, const Vector4& value2, const float& amount) noexcept
        {
            return { Math::lerp(value1.x, value2.x, amount)
                   , Math::lerp(value1.y, value2.y, amount)
                   , Math::lerp(value1.z, value2.z, amount)
                   , Math::lerp(value1.w, value2.w, amount) };
        }

        Vector4 Vector4::min(const Vector4& value1, const Vector4& value2) noexcept
        {
            return { Math::min(value1.x, value2.x)
                   , Math::min(value1.y, value2.y)
                   , Math::min(value1.z, value2.z)
                   , Math::min(value1.w, value2.w)};
        }

        Vector4 Vector4::max(const Vector4& value1, const Vector4& value2) noexcept
        {
            return { Math::max(value1.x, value2.x)
                   , Math::max(value1.y, value2.y)
                   , Math::max(value1.z, value2.z)
                   , Math::max(value1.w, value2.w) };
        }

        Vector4 Vector4::negate(const Vector4& value) noexcept
        {
            return value * -1;
        }

        Vector4 Vector4::normalize(const Vector4& value) noexcept
        {
            return (value / value.length());
        }

        Vector4 Vector4::square_root(const Vector4 &value) noexcept
        {
            return { Math::sqrt(value.x), Math::sqrt(value.y), Math::sqrt(value.z), Math::sqrt(value.w) };
        }

        Vector4 Vector4::transform(const Vector2& position, const Matrix& matrix) noexcept
        {
            return (Vector4 { position, 0.0f, 1.0f } * matrix);
        }

        Vector4 Vector4::transform(const Vector3& position, const Matrix& matrix) noexcept
        {
            return (Vector4 { position, 1.0f } * matrix);
        }

        Vector4 Vector4::transform(const Vector4& position, const Matrix& matrix) noexcept
        {
            return (position * matrix);
        }

        Vector4 Vector4::transform(const Vector2& value, const Quaternion& rotation) noexcept
        {
            return (Vector4 { value, 0.0f, 1.0f } * Matrix::create_from_quaternion(rotation));
        }

        Vector4 Vector4::transform(const Vector3& value, const Quaternion& rotation) noexcept
        {
            return (Vector4 { value, 1.0f } * Matrix::create_from_quaternion(rotation));
        }

        Vector4 Vector4::transform(const Vector4& value, const Quaternion& rotation) noexcept
        {
            return (value* Matrix::create_from_quaternion(rotation));
        }

        Vector4 Vector4::smooth_step(const Vector4& value1, const Vector4& value2, const float& amount) noexcept
        {
            return { Math::smooth_step(value1.x, value2.x, amount)
                   , Math::smooth_step(value1.y, value2.y, amount)
                   , Math::smooth_step(value1.z, value2.z, amount)
                   , Math::smooth_step(value1.w, value2.w, amount) };
        }

        Vector4::Vector4() noexcept
            : Vector4 { 0.0f, 0.0f, 0.0f, 0.0f }
        {
        }

        Vector4::Vector4(const float& value) noexcept
            : Vector4 { value, value, value, value }
        {
        }

        Vector4::Vector4(const Vector3& value, const float& w) noexcept
            : Vector4 { value.x, value.y, value.z, w }
        {
        }

        Vector4::Vector4(const float& x, const float& y, const float& z) noexcept
            : Vector4 { x, y, z, 0.0f }
        {
        }

        Vector4::Vector4(const Vector2& value, const float& z, const float& w) noexcept
            : Vector4 { value.x, value.y, z, w }
        {
        }

        Vector4::Vector4(const float& x, const float& y, const float& z, const float& w) noexcept
            : x { x }
            , y { y }
            , z { z }
            , w { w }
        {
        }

        float Vector4::length_squared() const noexcept
        {
            return (x * x)
                 + (y * y)
                 + (z * z)
                 + (w * w);
        }

        float Vector4::length() const noexcept
        {
            return Math::sqrt(length_squared());
        }

        float& Vector4::operator[](const std::size_t& index)
        {
            Expects(index < 4);

            return data[index];
        }

        const float& Vector4::operator[](const std::size_t& index) const
        {
            Expects(index < 4);

            return data[index];
        }

        bool Vector4::operator==(const Vector4& vector) const
        {
            return (Math::equal(x, vector.x)
                 && Math::equal(y, vector.y)
                 && Math::equal(z, vector.z)
                 && Math::equal(w, vector.w));
        }

        bool Vector4::operator!=(const Vector4& vector) const
        {
            return !(*this == vector);
        }

        Vector4& Vector4::operator*=(const Vector4& vector)
        {
            x *= vector.x;
            y *= vector.y;
            z *= vector.z;
            w *= vector.w;

            return *this;
        }

        Vector4& Vector4::operator*=(const float& value)
        {
            x *= value;
            y *= value;
            z *= value;
            w *= value;

            return *this;
        }

        Vector4& Vector4::operator/=(const Vector4& vector)
        {
            x /= vector.x;
            y /= vector.y;
            z /= vector.z;
            w /= vector.w;

            return *this;
        }

        Vector4& Vector4::operator/=(const float& value)
        {
            x /= value;
            y /= value;
            z /= value;
            w /= value;

            return *this;
        }

        Vector4& Vector4::operator-=(const Vector4& vector)
        {
            x -= vector.x;
            y -= vector.y;
            z -= vector.z;
            w -= vector.w;

            return *this;
        }

        Vector4& Vector4::operator+=(const Vector4& vector)
        {
            x += vector.x;
            y += vector.y;
            z += vector.z;
            w += vector.w;

            return *this;
        }

        const Vector4 Vector4::operator*(const Vector4& vector) const
        {
            auto result = *this;

            result *= vector;

            return result;
        }

        const Vector4 Vector4::operator*(const float& value) const
        {
            auto result = *this;

            result *= value;

            return result;
        }

        const Vector4 Vector4::operator*(const Matrix& matrix) const
        {
            float vx = (x * matrix.m11)
                     + (y * matrix.m21)
                     + (z * matrix.m31)
                     + (w * matrix.m41);

            float vy = (x * matrix.m12)
                     + (y * matrix.m22)
                     + (z * matrix.m32)
                     + (w * matrix.m42);

            float vz = (x * matrix.m13)
                     + (y * matrix.m23)
                     + (z * matrix.m33)
                     + (w * matrix.m43);

            float vw = (x * matrix.m14)
                     + (y * matrix.m24)
                     + (z * matrix.m34)
                     + (w * matrix.m44);

            return { vx, vy, vz, vw };
        }

        const Vector4 Vector4::operator/(const Vector4& vector) const
        {
            auto result = *this;

            result /= vector;

            return result;
        }

        const Vector4 Vector4::operator/(const float& value) const
        {
            auto result = *this;

            result /= value;

            return result;
        }

        const Vector4 Vector4::operator-(const Vector4& vector) const
        {
            auto result = *this;

            result -= vector;

            return result;
        }

        const Vector4 Vector4::operator-() const
        {
            auto result = *this;

            result *= -1;

            return result;
        }

        const Vector4 Vector4::operator+(const Vector4& vector) const
        {
            auto result = *this;

            result += vector;

            return result;
        }
    }
}
