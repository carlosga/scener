//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#ifndef COLOR_HPP
#define COLOR_HPP

#include <System/Core.hpp>

namespace SceneR
{
    namespace Framework
    {
        /**
         * Describes a color in terms of red, green, blue and alpha components.
         */
        class Color
        {
        public:
            /**
             * Initializes a new instance of the Color class.
             */
            Color();

            /**
             * Initializes a new instance of the Color class with the given red, green and blue components.
             * @param r The red component value of the color.
             * @param g The green component value of the color.
             * @param b The blue component value of the color.
             */
            Color(const Single& r, const Single& g, const Single& b);

            /**
             * Initializes a new instance of the Color class with the given red, green, blue and alpha components.
             * @param r The red component value of the color.
             * @param g The green component value of the color.
             * @param b The blue component value of the color.
             * @param a The alpha component value of the color.
             */
            Color(const Single& r, const Single& g, const Single& b, const Single& a);

            /**
             * Initializes a new instance of the Color class (Copy constructor)
             * @param color The Color to be copied.
             */
            Color(const Color& color);

            /**
             * Default destructor
             */
            ~Color() = default;

        public:
            /**
             * Gets the red component value of the color.
             * @return the red component value of the color.
             */
            const Single& R() const;

            /**
             * Gets the green component value of the color.
             * @return the green component value of the color.
             */
            const Single& G() const;

            /**
             * Gets the blue component value of the color.
             * @return the blue component value of the color.
             */
            const Single& B() const;

            /**
             * Gets the alpha component value of the color.
             * @return the alpha component value of the color.
             */
            const Single& A() const;

            /**
             * Gets the color packed value.
             */
            const UInt32 PackedValue() const;

        public:
            Single& operator[](const Int32& index);
            const Single& operator[](const Int32& index) const;
            bool operator==(const Color& color) const;
            bool operator!=(const Color& color) const;
            Color& operator*=(const Color& color);
            Color& operator*=(const Single& value);
            Color& operator-=(const Color& color);
            Color& operator+=(const Color& color);
            const Color operator*(const Color& color) const;
            const Color operator*(const Single& value) const;
            const Color operator-(const Color& color) const;
            const Color operator+(const Color& color) const;

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

        private:
            union
            {
                Single color[4];
                struct
                {
                    Single r;
                    Single g;
                    Single b;
                    Single a;
                };
            };
        };
    }
}

#endif  /* COLOR_HPP */
