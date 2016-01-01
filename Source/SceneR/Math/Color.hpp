// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_COLOR_HPP
#define SCENER_MATH_COLOR_HPP

#include <cstddef>
#include <cstdint>

namespace SceneR { namespace Math {

struct Vector3;
struct Vector4;

/**
 * Describes a color in terms of red, green, blue and alpha components.
 */
struct Color
{
public:
    static const Color black;
    static const Color white;

public:
    /**
     * Initializes a new instance of the Color class.
     */
    Color() noexcept;

    /**
     * Initializes a new instance of the Color class.
     * @param vector A three-component color.
     */
    Color(const Vector3& vector) noexcept;

    /**
     * Initializes a new instance of the Color class.
     * @param vector A four-component color.
     */
    Color(const Vector4& vector) noexcept;

    /**
     * Initializes a new instance of the Color class with the given red, green and blue components.
     * @param r The red component value of the color.
     * @param g The green component value of the color.
     * @param b The blue component value of the color.
     */
    Color(float r, float g, float b) noexcept;

    /**
     * Initializes a new instance of the Color class with the given red, green, blue and alpha components.
     * @param r The red component value of the color.
     * @param g The green component value of the color.
     * @param b The blue component value of the color.
     * @param a The alpha component value of the color.
     */
    Color(float r, float g, float b, float a) noexcept;

    /**
     * Initializes a new instance of the Color class (Copy constructor)
     * @param color The Color to be copied.
     */
    Color(const Color& color) = default;

    /**
     * Destructor
     */
    ~Color() = default;

public:
    /**
     * Gets the color packed value.
     */
    std::uint32_t packed_value() const noexcept;

public:
    float& operator[](const std::size_t& index);
    const float& operator[](const std::size_t& index) const;
    Color& operator=(const Color& color);
    bool operator==(const Color& color) const;
    bool operator!=(const Color& color) const;
    Color& operator*=(const Color& color);
    Color& operator*=(const float& value);
    Color& operator-=(const Color& color);
    Color& operator+=(const Color& color);
    const Color operator*(const Color& color) const;
    const Color operator*(const float& value) const;
    const Color operator-(const Color& color) const;
    const Color operator+(const Color& color) const;

public:
    union
    {
        float data[4];
        struct
        {
            float r;
            float g;
            float b;
            float a;
        };
    };
};

}}

#endif  // SCENER_MATH_COLOR_HPP
