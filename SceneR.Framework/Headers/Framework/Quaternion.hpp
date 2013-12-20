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

#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include <System/Core.hpp>

namespace SceneR
{
    namespace Framework
    {
        struct Vector3;
        struct Matrix;

        /**
         * Class that represents a rotation in three dimensions.
         */
        struct Quaternion
        {
        public:
            /**
             * Returns the identity quaternion.
             */
            static const Quaternion Identity;

        public:
            /**
             * Creates a Quaternion from a vector and an angle to rotate about the vector.
             *
             * @param axisOfRotation Vector3 that represents the axis of rotation.
             * @param angle Angle to rotate around the specified axis, in degrees.
             */
            static Quaternion CreateFromAxisAngle(const Vector3& axisOfRotation, const System::Single& angle);

            /**
             * Creates a Quaternion from a rotation Matrix.
             * @param matrix the rotation matrix
             */
            static Quaternion CreateFromRotationMatrix(const Matrix& matrix);

            /**
             * Creates a new quaternion with a specified yaw, pitch, and roll.
             * The order of transformations is yaw first, then pitch, then roll
             *
             * @param yaw Yaw around the y-axis, in degrees.
             * @param pitch Pitch around the z-axis, in degrees.
             * @param roll Roll around the x-axis, in degrees.
             */
            static Quaternion CreateFromYawPitchRoll(const System::Single& yaw,
                                                     const System::Single& pitch,
                                                     const System::Single& roll);

            /**
             * Calculates the linear interpolation between two quaternions.
             *
             * @param quaternion1 first quaternion
             * @param quaternion2 second quaternion
             * @param amount Value indicating how far to interpolate between the quaternions.
             */
            static Quaternion Lerp(const Quaternion& quaternion1,
                                   const Quaternion& quaternion2,
                                   const System::Single&     amount);

            /**
             * Calculates the spherical interpolation between two quaternions.
             *
             * @param quaternion1 first quaternion
             * @param quaternion2 second quaternion
             * @param amount Value indicating how far to interpolate between the quaternions.
             */
            static Quaternion Slerp(const Quaternion& quaternion1,
                                    const Quaternion& quaternion2,
                                    const System::Single&     amount);

        public:
            /**
             * Initializes a new instance of the Quaternion class.
             */
            Quaternion();

            /**
             * Initializes a new instance of the Quaternion class.
             *
             * @param x    The X value of the new Quaternion structure.
             * @param x    The Y value of the new Quaternion structure.
             * @param z    The Z value of the new Quaternion structure.
             * @param w    The W value of the new Quaternion structure.
             */
            Quaternion(const System::Single& x, const System::Single& y, const System::Single& z, const System::Single& w);

            /**
             * Initializes a new instance of the Quaternion class (Copy constructor)
             *
             * @param vector The Quaternion to be copied.
             */
            Quaternion(const Quaternion& vector);

            /**
             * Default destructor
             */
            ~Quaternion() = default;

        public:
            /**
             * Gets the x-coordinate value.
             */
            const System::Single& X() const;

            /**
             * Gets the y-coordinate value.
             */
            const System::Single& Y() const;

            /**
             * Gets the z-coordinate value.
             */
            const System::Single& Z() const;

            /**
             * Gets the w-coordinate value.
             */
            const System::Single& W() const;

            /**
             * Calculates the quaternion dot product
             */
            const System::Single DotProduct(const Quaternion& quaternion) const;

            /**
             * Replaces a quaternion with its conjugate.
             */
            void Conjugate();

            /**
             * Replaces the specified quaternion with its inverse.
             */
            void Invert();

            /**
             * Gets a value that indicates whether the specified quaternion is an Identity quaternion.
             * @return a value that indicates whether the specified quaternion is an Identity quaternion.
             */
            bool IsIdentity() const;

            /**
             * Gets the square of the length of this Quaternion.
             *
             * @return the square of the length of this Quaternion.
             */
            const System::Single LengthSquared() const;

            /**
             * Gets the length of this Quaternion.
             *
             * @return the length of this Quaternion.
             */
            const System::Single Length() const;

            /**
             * Normalizes the specified Quaternion.
             *
             * A normalized Quaternion maintains its direction but its magnitude becomes 1.
             * The resulting Quaternion is often called a unit vector.
             * A Quaternion is normalized by dividing the Quaternion by its magnitude.
             */
            void Normalize();

        public:
            System::Single& operator[](const System::Int32& index);
            const System::Single& operator[](const System::Int32& index) const;
            Quaternion& operator=(const Quaternion& vector);
            bool operator==(const Quaternion& vector) const;
            bool operator!=(const Quaternion& vector) const;
            Quaternion& operator*=(const Quaternion& vector);
            Quaternion& operator*=(const System::Single& value);
            Quaternion& operator/=(const Quaternion& vector);
            Quaternion& operator/=(const System::Single& value);
            Quaternion& operator-=(const Quaternion& vector);
            Quaternion& operator+=(const Quaternion& vector);
            const Quaternion operator*(const Quaternion& vector) const;
            const Quaternion operator*(const System::Single& value) const;
            const Quaternion operator/(const Quaternion& vector) const;
            const Quaternion operator/(const System::Single& value) const;
            const Quaternion operator-(const Quaternion& vector) const;
            const Quaternion operator+(const Quaternion& vector) const;

        private:
            union
            {
                System::Single quaternion[4];
                struct
                {
                    System::Single x;
                    System::Single y;
                    System::Single z;
                    System::Single w;
                };
            };
        };
    }
}

#endif  /* QUATERNION_HPP */
