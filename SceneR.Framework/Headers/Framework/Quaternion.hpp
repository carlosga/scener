// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include <cstddef>

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
             * Returns the conjugate of a specified Quaternion.
             *
             * @param quaternion the Quaternion of which to return the conjugate.
             * @returns the quaternion conjugate
             */
            static Quaternion conjugate(const Quaternion& data);

            /**
             * Creates a Quaternion from a vector and an angle to rotate about the vector.
             *
             * @param axisOfRotation Vector3 that represents the axis of rotation.
             * @param angle Angle to rotate around the specified axis, in radians.
             */
            static Quaternion create_from_axis_angle(const Vector3& axisOfRotation, const float& angle);

            /**
             * Creates a Quaternion from a rotation Matrix.
             * @param matrix the rotation matrix
             */
            static Quaternion create_from_rotation_matrix(const Matrix& matrix);

            /**
             * Creates a new quaternion with a specified yaw, pitch, and roll.
             *
             * @param yaw Yaw around the y-axis, in radians.
             * @param pitch Pitch around the x-axis, in radians.
             * @param roll Roll around the z-axis, in radians.
             */
            static Quaternion create_from_yaw_pitch_roll(const float& yaw
                                                   , const float& pitch
                                                   , const float& roll);

            /**
             * Calculates the dot product oof two quaternions
             */
            static float dot(const Quaternion& quaternion1, const Quaternion& quaternion2);

            /**
             * Calculates the invers of the specified quaternion.
             */
            static Quaternion inverse(const Quaternion& value);

            /**
             * Calculates the linear interpolation between two quaternions.
             *
             * @param quaternion1 first quaternion
             * @param quaternion2 second quaternion
             * @param amount Value indicating how far to interpolate between the quaternions.
             */
            static Quaternion lerp(const Quaternion& quaternion1
                                 , const Quaternion& quaternion2
                                 , const float&      amount);

            /**
             * Negates the specified Quaternion.
             */
            static Quaternion negate(const Quaternion& value);

            /**
             * Normalizes the specified Quaternion.
             *
             * A normalized Quaternion maintains its direction but its magnitude becomes 1.
             * The resulting Quaternion is often called a unit vector.
             * @param value the quaternion to normalize.
             * @returns A Quaternion is normalized by dividing the Quaternion by its magnitude.
             */
            static Quaternion normalize(const Quaternion& value);

            /**
             * Calculates the spherical interpolation between two quaternions.
             *
             * @param quaternion1 first quaternion
             * @param quaternion2 second quaternion
             * @param amount Value indicating how far to interpolate between the quaternions.
             */
            static Quaternion slerp(const Quaternion& quaternion1
                                  , const Quaternion& quaternion2
                                  , const float&      amount);

        public:
            /**
             * Initializes a new instance of the Quaternion class.
             */
            Quaternion();

            /**
             * Initializes a new instance of the Quaternion class.
             * @param value a vector containing the values to initialize x, y, and z components with.
             * @param w value for the w-component of the vector.
             */
            Quaternion(const Vector3& value, const float& w);

            /**
             * Initializes a new instance of the Quaternion class.
             * @param x    The X value of the new Quaternion structure.
             * @param y    The Y value of the new Quaternion structure.
             * @param z    The Z value of the new Quaternion structure.
             * @param w    The W value of the new Quaternion structure.
             */
            Quaternion(const float& x, const float& y, const float& z, const float& w);

            /**
             * Initializes a new instance of the Quaternion class (Copy constructor)
             * @param vector The Quaternion to be copied.
             */
            Quaternion(const Quaternion& vector);

            /**
             * Destructor
             */
            ~Quaternion();

        public:
            /**
             * Gets a value that indicates whether the specified quaternion is an Identity quaternion.
             * @return a value that indicates whether the specified quaternion is an Identity quaternion.
             */
            bool is_identity() const;

            /**
             * Gets the square of the length of this Quaternion.
             *
             * @return the square of the length of this Quaternion.
             */
            float length_squared() const;

            /**
             * Gets the length of this Quaternion.
             *
             * @return the length of this Quaternion.
             */
            float length() const;

        public:
            float& operator[](const std::size_t& index);
            const float& operator[](const std::size_t& index) const;
            Quaternion& operator=(const Quaternion& value);
            bool operator==(const Quaternion& value) const;
            bool operator!=(const Quaternion& value) const;
            Quaternion& operator*=(const Quaternion& value);
            Quaternion& operator*=(const float& value);
            Quaternion& operator/=(const Quaternion& value);
            Quaternion& operator/=(const float& value);
            Quaternion& operator-=(const Quaternion& value);
            Quaternion& operator+=(const Quaternion& value);
            const Quaternion operator*(const Quaternion& value) const;
            const Quaternion operator*(const float& value) const;
            const Quaternion operator/(const Quaternion& value) const;
            const Quaternion operator/(const float& value) const;
            const Quaternion operator-(const Quaternion& value) const;
            const Quaternion operator-() const;
            const Quaternion operator+(const Quaternion& value) const;

        public:
            union
            {
                float data[4];
                struct
                {
                    float x;
                    float y;
                    float z;
                    float w;
                };
            };
        };
    }
}

#endif  /* QUATERNION_HPP */
