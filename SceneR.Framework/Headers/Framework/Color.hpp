// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstddef>
#include <cstdint>

namespace SceneR
{
    namespace Framework
    {
        struct Vector3;
        struct Vector4;

        /**
         * Describes a color in terms of red, green, blue and alpha components.
         */
        struct Color
        {
        public:
            static const Color AliceBlue;
            static const Color AntiqueWhite;
            static const Color Aqua;
            static const Color Aquamarine;
            static const Color Azure;
            static const Color Beige;
            static const Color Bisque;
            static const Color Black;
            static const Color BlanchedAlmond;
            static const Color Blue;
            static const Color BlueViolet;
            static const Color Brown;
            static const Color BurlyWood;
            static const Color CadetBlue;
            static const Color Chartreuse;
            static const Color Chocolate;
            static const Color Coral;
            static const Color CornflowerBlue;
            static const Color Cornsilk;
            static const Color Crimson;
            static const Color Cyan;
            static const Color DarkBlue;
            static const Color DarkCyan;
            static const Color DarkGoldenrod;
            static const Color DarkGray;
            static const Color DarkGreen;
            static const Color DarkKhaki;
            static const Color DarkMagenta;
            static const Color DarkOliveGreen;
            static const Color DarkOrange;
            static const Color DarkOrchid;
            static const Color DarkRed;
            static const Color DarkSalmon;
            static const Color DarkSeaGreen;
            static const Color DarkSlateBlue;
            static const Color White;

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
            Color(const Color& color);

            /**
             * Destructor
             */
            ~Color();

        public:
            /**
             * Gets the red component value of the color.
             * @return the red component value of the color.
             */
            float R() const;

            /**
             * Gets the green component value of the color.
             * @return the green component value of the color.
             */
            float G() const;

            /**
             * Gets the blue component value of the color.
             * @return the blue component value of the color.
             */
            float B() const;

            /**
             * Gets the alpha component value of the color.
             * @return the alpha component value of the color.
             */
            float A() const;

            /**
             * Gets the color packed value.
             */
            std::uint32_t PackedValue() const;

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

        private:
            union
            {
                float color[4];
                struct
                {
                    float r;
                    float g;
                    float b;
                    float a;
                };
            };
        };
    }
}

#endif  /* COLOR_HPP */
