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

#ifndef VECTOR3_HPP
#define	VECTOR3_HPP

#include "Core/Core.hpp"
#include "Core/Matrix.hpp"

namespace SceneR
{
    namespace Core
    {
        /**
         * Represents an x-, y-, and z-coordinate vector.
         */
        class Vector3
        {
        public:
            /**
             * Returns a unit Vector3 designating backward in a right-handed coordinate system (0, 0, 1).
             */
            static const Vector3 Backward;

            /**
             * Returns a unit Vector3 designating down (0, −1, 0).
             */
            static const Vector3 Down;

            /**
             * Returns a unit Vector3 designating forward in a right-handed coordinate system(0, 0, −1).
             */
            static const Vector3 Forward;

            /**
             * Returns a unit Vector3 designating left (−1, 0, 0).
             */
            static const Vector3 Left;

            /**
             * Returns a Vector3 with ones in all of its components.
             */
            static const Vector3 One;

            /**
             * Returns a unit Vector3 pointing to the right (1, 0, 0).
             */
            static const Vector3 Right;

            /**
             * Returns the x unit Vector3 (1, 0, 0).
             */
            static const Vector3 UnitX;

            /**
             * Returns the y unit Vector3 (0, 1, 0).
             */
            static const Vector3 UnitY;

            /**
             * Returns the z unit Vector3 (0, 0, 1).
             */
            static const Vector3 UnitZ;

            /**
             * Returns a unit vector designating up (0, 1, 0).
             */
            static const Vector3 Up;

            /**
             * Returns a Vector3 with all of its components set to zero.
             */
            static const Vector3 Zero;

        public:
            /**
             * Performs a linear interpolation between two vectors.
             *
             * @param value1 first vector
             * @param value2 second vector
             * @param amount Value between 0 and 1 indicating the weight of value2.
             * @returns the linear interpolation of the two vectors.
             */
            static Vector3 Lerp(const Vector3& value1,
                                const Vector3& value2,
                                const Single&  amount);

            /**
             * Performs a cubic interpolation between two vectors.
             *
             * @param value1 first vector
             * @param value2 second vector
             * @param amount Weighting value.
             * @returns the linear interpolation of the two vectors.
             */
            static Vector3 SmoothStep(const Vector3& value1,
                                      const Vector3& value2,
                                      const Single&  amount);

        public:
            /**
             * Initializes a new instance of the Vector3 class.
             */
            Vector3();

            /**
             * Initializes a new instance of the Vector3 class.
             *
             * @param x    The X value of the new Vector3 structure.
             * @param x    The Y value of the new Vector3 structure.
             * @param z    The Z value of the new Vector3 structure.
             */
            Vector3(const Single& x, const Single& y, const Single& z);

            /**
             * Initializes a new instance of the Vector3 class (Copy constructor)
             *
             * @param vector The Vector3 to be copied.
             */
            Vector3(const Vector3& vector);

            /**
             * Default destructor
             */
            ~Vector3() = default;

        public:
            /**
             * Gets the x-coordinate value
             */
            const Single& X() const;

            /**
             * Gets the y-coordinate value
             */
            const Single& Y() const;

            /**
             * Gets the z-coordinate value
             */
            const Single& Z() const;

            /**
             * Gets the square of the length of this Vector3.
             * 
             * @return the square of the length of this Vector3.
             */
            const Single LengthSquared() const;

            /**
             * Gets the length of this Vector3.
             * 
             * @return the length of this Vector3.
             */
            const Single Length() const;

            /**
             * Negates a Vector3.
             * 
             * The vector has the same magnitude as before, but its direction is now opposite.
             */
            void Negate();

            /**
             * Calculates the cross product of two Vector3 structures.
             * 
             * @param vectorb The second Vector3 structure to evaluate.
             * @return The cross product of this Vector3 and vectorb.
             */
            const Vector3 CrossProduct(const Vector3& vectorb) const;

            /**
             * Calculates the dot product of two Vector3 structures.
             * 
             * @param vectorb The second Vector3 structure to evaluate.
             * @return The dot product of this Vector3 and vectorb.
             */
            const Single DotProduct(const Vector3& vectorb) const;

            /**
             * Retrieves the angle required to rotate the first specified Vector3 structure into the second specified Vector3 structure.
             * 
             * @param vectorb The second Vector3 to evaluate.
             * @return The angle in degrees needed to rotate this Vector3 into vectorb.
             */
            const Single AngleBetween(const Vector3& vectorb) const;

            /**
             * Normalizes the specified Vector3.
             * 
             * A normalized Vector3 maintains its direction but its magnitude becomes 1.
             * The resulting Vector3 is often called a unit vector.
             * A Vector3 is normalized by dividing the Vector3 by its magnitude.
             */
            void Normalize();

        public:
            Single& operator[](const Int32& index);
            const Single& operator[](const Int32& index) const;
            Vector3& operator=(const Vector3 &vector);
            bool operator==(const Vector3 &vector) const;
            bool operator!=(const Vector3 &vector) const;
            Vector3& operator*=(const Vector3 &vector);
            Vector3& operator*=(const Single &value);
            Vector3& operator/=(const Vector3 &vector);
            Vector3& operator/=(const Single &value);
            Vector3& operator-=(const Vector3 &vector);
            Vector3& operator+=(const Vector3 &vector);
            const Vector3 operator*(const Vector3 &vector) const;
            const Vector3 operator*(const Single &value) const;
            const Vector3 operator*(const Matrix &matrix) const;
            const Vector3 operator/(const Vector3 &vector) const;
            const Vector3 operator/(const Single &value) const;
            const Vector3 operator-(const Vector3 &vector) const;
            const Vector3 operator+(const Vector3 &vector) const;

        private:
            union
            {
                Single vector[3];
                struct
                {
                    Single xCoordinate;
                    Single yCoordinate;
                    Single zCoordinate;
                };
            };
        };
    }
}

#endif	/* VECTOR3_HPP */
