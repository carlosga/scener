// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/Vector4.hpp>

#include <cassert>

#include <System/Math.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>

namespace SceneR
{
    namespace Framework
    {
        using System::Math;

        const Vector4 Vector4::One   { 1.0f, 1.0f, 1.0f, 1.0f };
        const Vector4 Vector4::UnitX { 1.0f, 0.0f, 0.0f, 0.0f };
        const Vector4 Vector4::UnitY { 0.0f, 1.0f, 0.0f, 0.0f };
        const Vector4 Vector4::UnitZ { 0.0f, 0.0f, 1.0f, 0.0f };
        const Vector4 Vector4::UnitW { 0.0f, 0.0f, 0.0f, 1.0f };
        const Vector4 Vector4::Zero  { 0.0f, 0.0f, 0.0f, 0.0f };

        Vector4 Vector4::Abs(const Vector4 &value)
        {
            return { Math::Abs(value.X()), Math::Abs(value.Y()), Math::Abs(value.Z()), Math::Abs(value.W()) };
        }

        Vector4 Vector4::Barycentric(const Vector4& value1
                                   , const Vector4& value2
                                   , const Vector4& value3
                                   , const float&   amount1
                                   , const float&   amount2)
        {
            return { Math::Barycentric(value1.x, value2.x, value3.x, amount1, amount2)
                   , Math::Barycentric(value1.y, value2.y, value3.y, amount1, amount2)
                   , Math::Barycentric(value1.z, value2.z, value3.z, amount1, amount2)
                   , Math::Barycentric(value1.w, value2.w, value3.w, amount1, amount2) };
        }

        Vector4 Vector4::CatmullRom(const Vector4& value1
                                  , const Vector4& value2
                                  , const Vector4& value3
                                  , const Vector4& value4
                                  , const float&   amount)
        {
            return { Math::CatmullRom(value1.x, value2.x, value3.x, value4.x, amount)
                   , Math::CatmullRom(value1.y, value2.y, value3.y, value4.y, amount)
                   , Math::CatmullRom(value1.z, value2.z, value3.z, value4.z, amount)
                   , Math::CatmullRom(value1.w, value2.w, value3.w, value4.w, amount) };
        }

        Vector4 Vector4::Clamp(const Vector4& value1, const Vector4& min, const Vector4& max)
        {
            return { Math::Clamp(value1.x, min.x, max.x)
                   , Math::Clamp(value1.y, min.y, max.y)
                   , Math::Clamp(value1.z, min.z, max.z)
                   , Math::Clamp(value1.w, min.w, max.w) };
        }

        float Vector4::Distance(const Vector4& value1, const Vector4& value2)
        {
            auto d = value2 - value1;

            return d.Length();
        }

        float Vector4::DistanceSquared(const Vector4& value1, const Vector4& value2)
        {
            auto d = value2 - value1;

            return d.LengthSquared();
        }

        float Vector4::Dot(const Vector4& value1, const Vector4& value2)
        {
            auto dotProduct = value1 * value2;

            return (dotProduct.x + dotProduct.y + dotProduct.z + dotProduct.w);
        }

        Vector4 Vector4::Hermite(const Vector4& value1
                               , const Vector4& tangent1
                               , const Vector4& value2
                               , const Vector4& tangent2
                               , const float&   amount)
        {
            return { Math::Hermite(value1.x, tangent1.x, value2.x, tangent2.x, amount)
                   , Math::Hermite(value1.y, tangent1.y, value2.y, tangent2.y, amount)
                   , Math::Hermite(value1.z, tangent1.z, value2.z, tangent2.z, amount)
                   , Math::Hermite(value1.w, tangent1.w, value2.w, tangent2.w, amount) };
        }

        Vector4 Vector4::Lerp(const Vector4& value1
                            , const Vector4& value2
                            , const float&   amount)
        {
            return { Math::Lerp(value1.x, value2.x, amount)
                   , Math::Lerp(value1.y, value2.y, amount)
                   , Math::Lerp(value1.z, value2.z, amount)
                   , Math::Lerp(value1.w, value2.w, amount) };
        }

        Vector4 Vector4::Min(const Vector4& value1, const Vector4& value2)
        {
            return { Math::Min(value1.x, value2.x)
                   , Math::Min(value1.y, value2.y)
                   , Math::Min(value1.z, value2.z)
                   , Math::Min(value1.w, value2.w)};
        }

        Vector4 Vector4::Max(const Vector4& value1, const Vector4& value2)
        {
            return { Math::Max(value1.x, value2.x)
                   , Math::Max(value1.y, value2.y)
                   , Math::Max(value1.z, value2.z)
                   , Math::Max(value1.w, value2.w)};
        }

        Vector4 Vector4::Negate(const Vector4& value)
        {
            return value * -1;
        }

        Vector4 Vector4::Normalize(const Vector4& value)
        {
            return (value / value.Length());
        }

        Vector4 Vector4::SquareRoot(const Vector4 &value)
        {
            return { Math::Sqrt(value.X()), Math::Sqrt(value.Y()), Math::Sqrt(value.Z()), Math::Sqrt(value.W()) };
        }

        Vector4 Vector4::Transform(const Vector2& position, const Matrix& matrix)
        {
            return (Vector4 { position, 0.0f, 1.0f } * matrix);
        }

        Vector4 Vector4::Transform(const Vector3& position, const Matrix& matrix)
        {
            return (Vector4 { position, 1.0f } * matrix);
        }

        Vector4 Vector4::Transform(const Vector4& position, const Matrix& matrix)
        {
            return (position * matrix);
        }

        Vector4 Vector4::Transform(const Vector2& value, const Quaternion& rotation)
        {
            return (Vector4 { value, 0.0f, 1.0f } * Matrix::CreateFromQuaternion(rotation));
        }

        Vector4 Vector4::Transform(const Vector3& value, const Quaternion& rotation)
        {
            return (Vector4 { value, 1.0f } * Matrix::CreateFromQuaternion(rotation));
        }

        Vector4 Vector4::Transform(const Vector4& value, const Quaternion& rotation)
        {
            return (value* Matrix::CreateFromQuaternion(rotation));
        }

        Vector4 Vector4::SmoothStep(const Vector4& value1, const Vector4& value2, const float& amount)
        {
            return { Math::SmoothStep(value1.x, value2.x, amount)
                   , Math::SmoothStep(value1.y, value2.y, amount)
                   , Math::SmoothStep(value1.z, value2.z, amount)
                   , Math::SmoothStep(value1.w, value2.w, amount) };
        }

        Vector4::Vector4()
            : Vector4 { 0.0f, 0.0f, 0.0f, 0.0f }
        {
        }

        Vector4::Vector4(const float& value)
            : Vector4 { value, value, value, value }
        {
        }

        Vector4::Vector4(const Vector3& value, const float& w)
            : Vector4 { value.X(), value.Y(), value.Z(), w }
        {
        }

        Vector4::Vector4(const float& x, const float& y, const float& z)
            : Vector4 { x, y, z, 0.0f }
        {
        }

        Vector4::Vector4(const Vector2& value, const float& z, const float& w)
            : Vector4 { value.X(), value.Y(), z, w }
        {
        }

        Vector4::Vector4(const float& x, const float& y, const float& z, const float& w)
            : x { x }
            , y { y }
            , z { z }
            , w { w }
        {
        }

        Vector4::Vector4(const Vector4& vector)
            : x { vector.x }
            , y { vector.y }
            , z { vector.z }
            , w { vector.w }
        {
        }

        Vector4::~Vector4()
        {
        }

        float Vector4::X() const
        {
            return this->x;
        }

        float Vector4::Y() const
        {
            return this->y;
        }

        float Vector4::Z() const
        {
            return this->z;
        }

        float Vector4::W() const
        {
            return this->w;
        }

        void Vector4::X(const float& x)
        {
            this->x = x;
        }

        void Vector4::Y(const float& y)
        {
            this->y = y;
        }

        void Vector4::Z(const float& z)
        {
            this->z = z;
        }

        void Vector4::W(const float& w)
        {
            this->w = w;
        }

        float Vector4::LengthSquared() const
        {
            return (this->x * this->x)
                 + (this->y * this->y)
                 + (this->z * this->z)
                 + (this->w * this->w);
        }

        float Vector4::Length() const
        {
            return Math::Sqrt(this->LengthSquared());
        }

        float& Vector4::operator[](const std::size_t& index)
        {
            assert(index < 4);

            return (this->vector[index]);
        }

        const float& Vector4::operator[](const std::size_t& index) const
        {
            assert(index < 4);

            return (this->vector[index]);
        }

        Vector4& Vector4::operator=(const Vector4& vector)
        {
            if (this != &vector)
            {
                this->x = vector.x;
                this->y = vector.y;
                this->z = vector.z;
                this->w = vector.w;
            }

            return *this;
        }

        bool Vector4::operator==(const Vector4& vector) const
        {
            return (Math::Equal(this->x, vector.x)
                 && Math::Equal(this->y, vector.y)
                 && Math::Equal(this->z, vector.z)
                 && Math::Equal(this->w, vector.w));
        }

        bool Vector4::operator!=(const Vector4& vector) const
        {
            return !(*this == vector);
        }

        Vector4& Vector4::operator*=(const Vector4& vector)
        {
            this->x *= vector.x;
            this->y *= vector.y;
            this->z *= vector.z;
            this->w *= vector.w;

            return *this;
        }

        Vector4& Vector4::operator*=(const float& value)
        {
            this->x *= value;
            this->y *= value;
            this->z *= value;
            this->w *= value;

            return *this;
        }

        Vector4& Vector4::operator/=(const Vector4& vector)
        {
            this->x /= vector.x;
            this->y /= vector.y;
            this->z /= vector.z;
            this->w /= vector.w;

            return *this;
        }

        Vector4& Vector4::operator/=(const float& value)
        {
            this->x /= value;
            this->y /= value;
            this->z /= value;
            this->w /= value;

            return *this;
        }

        Vector4& Vector4::operator-=(const Vector4& vector)
        {
            this->x -= vector.x;
            this->y -= vector.y;
            this->z -= vector.z;
            this->w -= vector.w;

            return *this;
        }

        Vector4& Vector4::operator+=(const Vector4& vector)
        {
            this->x += vector.x;
            this->y += vector.y;
            this->z += vector.z;
            this->w += vector.w;

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
            float x = (this->x * matrix.M11())
                    + (this->y * matrix.M21())
                    + (this->z * matrix.M31())
                    + (this->w * matrix.M41());

            float y = (this->x * matrix.M12())
                    + (this->y * matrix.M22())
                    + (this->z * matrix.M32())
                    + (this->w * matrix.M42());

            float z = (this->x * matrix.M13())
                    + (this->y * matrix.M23())
                    + (this->z * matrix.M33())
                    + (this->w * matrix.M43());

            float w = (this->x * matrix.M14())
                    + (this->y * matrix.M24())
                    + (this->z * matrix.M34())
                    + (this->w * matrix.M44());

            return { x, y, z, w };
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
