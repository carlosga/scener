// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/Vector2.hpp>

#include <gsl.h>

#include <System/Math.hpp>
#include <Framework/Matrix.hpp>

namespace SceneR
{
    namespace Framework
    {
        using System::Math;

        const Vector2 Vector2::one    { 1.0f, 1.0f };
        const Vector2 Vector2::unit_x { 1.0f, 0.0f };
        const Vector2 Vector2::unit_y { 0.0f, 1.0f };
        const Vector2 Vector2::zero   { 0.0f, 0.0f };

        Vector2 Vector2::abs(const Vector2& value) noexcept
        {
            return { Math::abs(value.x), Math::abs(value.y) };
        }

        Vector2 Vector2::square_root(const Vector2& value) noexcept
        {
            return { Math::sqrt(value.x), Math::sqrt(value.y) };
        }

        Vector2 Vector2::barycentric(const Vector2& value1
                                   , const Vector2& value2
                                   , const Vector2& value3
                                   , const float&   amount1
                                   , const float&   amount2) noexcept
        {
            return { Math::barycentric(value1.x, value2.x, value3.x, amount1, amount2)
                   , Math::barycentric(value1.y, value2.y, value3.y, amount1, amount2) };
        }

        Vector2 Vector2::catmull_rom(const Vector2& value1
                                   , const Vector2& value2
                                   , const Vector2& value3
                                   , const Vector2& value4
                                   , const float&   amount) noexcept
        {
            return { Math::catmull_rom(value1.x, value2.x, value3.x, value4.x, amount)
                   , Math::catmull_rom(value1.y, value2.y, value3.y, value4.y, amount) };
        }

        Vector2 Vector2::clamp(const Vector2& value1, const Vector2& min, const Vector2& max) noexcept
        {
            return { Math::clamp(value1.x, min.x, max.x)
                   , Math::clamp(value1.y, min.y, max.y) };
        }

        float Vector2::distance(const Vector2& value1, const Vector2& value2) noexcept
        {
            auto d = value2 - value1;

            return d.length();
        }

        float Vector2::distance_squared(const Vector2& value1, const Vector2& value2) noexcept
        {
            auto d = value2 - value1;

            return d.length_squared();
        }

        float Vector2::dot(const Vector2& left, const Vector2& right) noexcept
        {
            auto dotProduct = left * right;

            return (dotProduct.x + dotProduct.y);
        }

        Vector2 Vector2::hermite(const Vector2& value1
                               , const Vector2& tangent1
                               , const Vector2& value2
                               , const Vector2& tangent2
                               , const float&   amount) noexcept
        {
            return { Math::hermite(value1.x, tangent1.x, value2.x, tangent2.x, amount)
                   , Math::hermite(value1.y, tangent1.y, value2.y, tangent2.y, amount) };
        }

        Vector2 Vector2::lerp(const Vector2& value1, const Vector2& value2, const float& amount) noexcept
        {
            return { Math::lerp(value1.x, value2.x, amount)
                   , Math::lerp(value1.y, value2.y, amount) };
        }

        Vector2 Vector2::min(const Vector2& value1, const Vector2& value2) noexcept
        {
            return { Math::min(value1.x, value2.x)
                   , Math::min(value1.y, value2.y) };
        }

        Vector2 Vector2::max(const Vector2& value1, const Vector2& value2) noexcept
        {
            return { Math::max(value1.x, value2.x)
                   , Math::max(value1.y, value2.y) };
        }

        Vector2 Vector2::negate(const Vector2& value) noexcept
        {
            return value * -1;
        }

        Vector2 Vector2::normalize(const Vector2& value) noexcept
        {
            // To find the unit vector of another vector, we use the modulus operator
            // and scalar multiplication like so:
            // b = a / |a|
            //
            // Where |a| is the modulus of a
            return (value / value.length());
        }

        Vector2 Vector2::smooth_step(const Vector2& value1, const Vector2& value2, const float& amount) noexcept
        {
            return { Math::smooth_step(value1.x, value2.x, amount)
                   , Math::smooth_step(value1.y, value2.y, amount) };
        }

        Vector2 Vector2::transform(const Vector2& position, const Matrix& matrix) noexcept
        {
            float x = (position.x * matrix.m11)
                    + (position.y * matrix.m21)
                    +               matrix.m41;

            float y = (position.x * matrix.m12)
                    + (position.y * matrix.m22)
                    +               matrix.m42;

            return { x, y };
        }

        Vector2 Vector2::transform_normal(const Vector2& normal, const Matrix& matrix) noexcept
        {
            float x = (normal.x * matrix.m11)
                    + (normal.y * matrix.m21);

            float y = (normal.x * matrix.m12)
                    + (normal.y * matrix.m22);

            return { x, y };
        }

        Vector2::Vector2() noexcept
            : Vector2 { 0.0f, 0.0f }
        {
        }

        Vector2::Vector2(const float& value) noexcept
            : Vector2 { value, value }
        {
        }

        Vector2::Vector2(const float& x, const float& y) noexcept
            : x { x }
            , y { y }
        {
        }

        float Vector2::length_squared() const noexcept
        {
            return (x * x) + (y * y);
        }

        float Vector2::length() const noexcept
        {
            return Math::sqrt(length_squared());
        }

        float& Vector2::operator[](const std::size_t& index)
        {
            Expects(index < 2);

            return (data[index]);
        }

        const float& Vector2::operator[](const std::size_t& index) const
        {
            Expects(index < 2);

            return (data[index]);
        }

        bool Vector2::operator==(const Vector2& vector) const
        {
            return (Math::equal(x, vector.x) && Math::equal(y, vector.y));
        }

        bool Vector2::operator!=(const Vector2& vector) const
        {
            return !(*this == vector);
        }

        Vector2& Vector2::operator*=(const Vector2& vector)
        {
            x *= vector.x;
            y *= vector.y;

            return *this;
        }

        Vector2& Vector2::operator*=(const float& value)
        {
            x *= value;
            y *= value;

            return *this;
        }

        Vector2& Vector2::operator/=(const Vector2& vector)
        {
            x /= vector.x;
            y /= vector.y;

            return *this;
        }

        Vector2& Vector2::operator/=(const float& value)
        {
            x /= value;
            y /= value;

            return *this;
        }

        Vector2& Vector2::operator-=(const Vector2& vector)
        {
            x -= vector.x;
            y -= vector.y;

            return *this;
        }

        Vector2& Vector2::operator+=(const Vector2& vector)
        {
            x += vector.x;
            y += vector.y;

            return *this;
        }

        const Vector2 Vector2::operator*(const Vector2& vector) const
        {
            auto result = *this;

            result *= vector;

            return result;
        }

        const Vector2 Vector2::operator*(const float& value) const
        {
            auto result = *this;

            result *= value;

            return result;
        }

        const Vector2 Vector2::operator/(const Vector2& vector) const
        {
            auto result = *this;

            result /= vector;

            return result;
        }

        const Vector2 Vector2::operator/(const float& value) const
        {
            auto result = *this;

            result /= value;

            return result;
        }

        const Vector2 Vector2::operator-(const Vector2& vector) const
        {
            auto result = *this;

            result -= vector;

            return result;
        }

        const Vector2 Vector2::operator-() const
        {
            return Vector2 { -x, -y };
        }

        const Vector2 Vector2::operator+(const Vector2& vector) const
        {
            auto result = *this;

            result += vector;

            return result;
        }
    }
}
