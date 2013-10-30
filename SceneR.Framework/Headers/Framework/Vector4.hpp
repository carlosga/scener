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

#ifndef VECTOR4_HPP
#define VECTOR4_HPP

#include <System/Core.hpp>

namespace SceneR
{
    namespace Framework
    {
        class Matrix;

        /**
         * Represents an x-, y-, z- and w-coordinate vector.
         */
        class Vector4
        {
        public:
            /**
             * Initializes a new instance of the Vector4 class.
             */
            Vector4();

            /**
             * Initializes a new instance of the Vector4 class.
             *
             * @param x The X value of the new Vector4 structure.
             * @param y The Y value of the new Vector4 structure.
             * @param z The Z value of the new Vector4 structure.
             */
            Vector4(const Single& x, const Single& y, const Single& z);

            /**
             * Initializes a new instance of the Vector4 class.
             *
             * @param x The X value of the new Vector4 structure.
             * @param y The Y value of the new Vector4 structure.
             * @param z The Z value of the new Vector4 structure.
             * @param w The W value of the new Vector4 structure.
             */
            Vector4(const Single& x, const Single& y, const Single& z, const Single& w);

            /**
             * Initializes a new instance of the Vector4 class (Copy constructor)
             *
             * @param vector The Vector4 to be copied.
             */
            Vector4(const Vector4& vector);

            /**
             * Default destructor
             */
            ~Vector4() = default;

        public:
            /**
             * Gets the x-coordinate value.
             */
            const Single& X() const;

            /**
             * Gets the y-coordinate value.
             */
            const Single& Y() const;

            /**
             * Gets the z-coordinate value.
             */
            const Single& Z() const;

            /**
             * Gets the w-coordinate value.
             */
            const Single& W() const;

            /**
             * Gets the square of the length of this Vector4.
             *
             * @return the square of the length of this Vector4.
             */
            const Single LengthSquared() const;

            /**
             * Gets the length of this Vector4.
             *
             * @return the length of this Vector4.
             */
            const Single Length() const;

            /**
             * Negates a Vector4.
             *
             * The vector has the same magnitude as before, but its direction is now opposite.
             */
            void Negate();

            /**
             * Calculates the dot product of two Vector4 structures.
             *
             * @param vectorb The second Vector4 structure to evaluate.
             * @return The dot product of this Vector4 and vectorb.
             */
            const Single DotProduct(const Vector4& vectorb) const;

            /**
             * Normalizes the specified Vector4.
             *
             * A normalized Vector4 maintains its direction but its magnitude becomes 1.
             * The resulting Vector4 is often called a unit vector.
             * A Vector4 is normalized by dividing the Vector4 by its magnitude.
             */
            void Normalize();

        public:
            Single& operator[](const Int32& index);
            const Single& operator[](const Int32& index) const;
            Vector4& operator=(const Vector4 &vector);
            bool operator==(const Vector4 &vector) const;
            bool operator!=(const Vector4 &vector) const;
            Vector4& operator*=(const Vector4 &vector);
            Vector4& operator*=(const Single &value);
            Vector4& operator/=(const Vector4 &vector);
            Vector4& operator/=(const Single &value);
            Vector4& operator-=(const Vector4 &vector);
            Vector4& operator+=(const Vector4 &vector);
            const Vector4 operator*(const Vector4 &vector) const;
            const Vector4 operator*(const Single &value) const;
            const Vector4 operator*(const Matrix &matrix) const;
            const Vector4 operator/(const Vector4 &vector) const;
            const Vector4 operator/(const Single &value) const;
            const Vector4 operator-(const Vector4 &vector) const;
            const Vector4 operator+(const Vector4 &vector) const;

        private:
            union
            {
                Single vector[4];
                struct
                {
                    Single xCoordinate;
                    Single yCoordinate;
                    Single zCoordinate;
                    Single wCoordinate;
                };
            };
        };
    }
}

#endif  /* VECTOR4_HPP */
