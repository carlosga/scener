// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/Color.hpp>

#include <gsl.h>

#include <System/Math.hpp>

namespace SceneR
{
    namespace Framework
    {
        using System::Math;

        const Color Color::black { 0x00, 0x00, 0x00, 0xFF };
        const Color Color::white { 0xFF, 0xFF, 0xFF, 0xFF };

        Color::Color()
            : Color ( 0.0f, 0.0f, 0.0f, 0.0f )
        {
        }

        Color::Color(const Vector3& vector)
            : Color ( vector.x, vector.y, vector.z, 1.0f )
        {
        }

        Color::Color(const Vector4& vector)
            : Color ( vector.x, vector.y, vector.z, vector.w )
        {
        }

        Color::Color(const float& r, const float& g, const float& b)
            : Color ( r, g, b, 1.0f )
        {
        }

        Color::Color(const float& r, const float& g, const float& b, const float& a)
            : r { r }
            , g { g }
            , b { b }
            , a { a }
        {
        }

        std::uint32_t Color::packed_value() const noexcept
        {
            return ((static_cast<std::uint32_t>(r) * 255) << 24)
                 + ((static_cast<std::uint32_t>(g) * 255) << 16)
                 + ((static_cast<std::uint32_t>(b) * 255) << 8)
                 +  (static_cast<std::uint32_t>(a) * 255);
        }

        float& Color::operator[](const std::size_t& index)
        {
            Expects(index < 4);

            return (data[index]);
        }

        const float& Color::operator[](const std::size_t& index) const
        {
            Expects(index < 4);

            return (data[index]);
        }

        Color& Color::operator=(const Color& color)
        {
            if (this != &color)
            {
                r = color.r;
                g = color.g;
                b = color.b;
                a = color.a;
            }

            return *this;
        }

        bool Color::operator==(const Color& color) const
        {
            return (Math::equal(r, color.r)
                 && Math::equal(g, color.g)
                 && Math::equal(b, color.b)
                 && Math::equal(a, color.a));
        }

        bool Color::operator!=(const Color& color) const
        {
            return !(*this == color);
        }

        Color& Color::operator*=(const Color& color)
        {
            r *= color.r;
            g *= color.g;
            b *= color.b;
            a *= color.a;

            return *this;
        }

        Color& Color::operator*=(const float& value)
        {
            r *= value;
            g *= value;
            b *= value;
            a *= value;

            return *this;
        }

        Color& Color::operator-=(const Color& color)
        {
            r -= color.r;
            g -= color.g;
            b -= color.b;
            a -= color.a;

            return *this;
        }

        Color& Color::operator+=(const Color& color)
        {
            r += color.r;
            g += color.g;
            b += color.b;
            a += color.a;

            return *this;
        }

        const Color Color::operator*(const Color& color) const
        {
            auto result = *this;

            result *= color;

            return result;
        }

        const Color Color::operator*(const float& value) const
        {
            auto result = *this;

            result *= value;

            return result;
        }

        const Color Color::operator-(const Color& color) const
        {
            auto result = *this;

            result -= color;

            return result;
        }

        const Color Color::operator+(const Color& color) const
        {
            auto result = *this;

            result += color;

            return result;
        }
    }
}
