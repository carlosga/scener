// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef FRAMEWORK_COLOR_HPP
#define FRAMEWORK_COLOR_HPP

#include <cstddef>
#include <cstdint>

#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>

namespace SceneR
{
    namespace Framework
    {
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
            Color();

            /**
             * Initializes a new instance of the Color class.
             * @param vector A three-component color.
             */
            Color(const Vector3& vector);

            /**
             * Initializes a new instance of the Color class.
             * @param vector A four-component color.
             */
            Color(const Vector4& vector);

            /**
             * Initializes a new instance of the Color class with the given red, green and blue components.
             * @param r The red component value of the color.
             * @param g The green component value of the color.
             * @param b The blue component value of the color.
             */
            Color(const float& r, const float& g, const float& b);

            /**
             * Initializes a new instance of the Color class with the given red, green, blue and alpha components.
             * @param r The red component value of the color.
             * @param g The green component value of the color.
             * @param b The blue component value of the color.
             * @param a The alpha component value of the color.
             */
            Color(const float& r, const float& g, const float& b, const float& a);

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
                SceneR::Framework::Vector3 rgb;
                SceneR::Framework::Vector4 rgba;
            };
        };
    }
}

#endif  // FRAMEWORK_COLOR_HPP
