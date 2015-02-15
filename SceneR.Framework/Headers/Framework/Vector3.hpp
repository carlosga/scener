// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <System/Core.hpp>

namespace SceneR
{
    namespace Framework
    {
        struct Matrix;
        struct Vector2;

        /**
         * Represents an x-, y-, and z-coordinate vector.
         */
        struct Vector3
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
             * Retrieves the angle required to rotate the first specified Vector3 structure into the second specified
             * Vector3 structure.
             * @param left The first Vector3 to evaluate.
             * @param right The second Vector3 to evaluate.
             * @return The angle, in radians, needed to rotate the left vector into the right vector.
             */
            static System::Single AngleBetween(const Vector3& left, const Vector3& right);

            /**
             * Returns the Cartesian coordinate for one axis of a point that is defined by a given triangle and
             * two normalized barycentric (areal) coordinates.
             * @param value1 the coordinate on one axis of vertex 1 of the defining triangle.
             * @param value2 the coordinate on the same axis of vertex 2 of the defining triangle.
             * @param value3 the coordinate on the same axis of vertex 3 of the defining triangle.
             * @param amount1 the normalized barycentric (areal) coordinate b2, equal to the weighting factor for vertex 2,
             *                the coordinate of which is specified in value2.
             * @param amount2 the normalized barycentric (areal) coordinate b3, equal to the weighting factor for vertex 3,
             *                the coordinate of which is specified in value3.
             */
            static Vector3 Barycentric(const Vector3&        value1
                                     , const Vector3&        value2
                                     , const Vector3&        value3
                                     , const System::Single& amount1
                                     , const System::Single& amount2);

            /**
             * Performs a Catmull-Rom interpolation using the specified positions.
             * @param value1 the first position in the interpolation.
             * @param value2 the second position in the interpolation.
             * @param value3 the third position in the interpolation.
             * @param value4 the fourth position in the interpolation.
             * @param amount weighting factor.
             */
            static Vector3 CatmullRom(const Vector3&        value1
                                    , const Vector3&        value2
                                    , const Vector3&        value3
                                    , const Vector3&        value4
                                    , const System::Single& amount);

            /**
             * Restricts a value to be within a specified range.
             */
            static Vector3 Clamp(const Vector3& value1, const Vector3& min, const Vector3& max);

            /**
             * Calculates the cross product of two Vector3 structures.
             * @param left The first Vector3 to evaluate.
             * @param right The second Vector3 to evaluate.
             * @return The cross product of this Vector3 and vectorb.
             */
            static Vector3 Cross(const Vector3& left, const Vector3& right);

            /**
             * Calculates the distance between two vectors.
             */
            static System::Single Distance(const Vector3& value1, const Vector3& value2);

            /**
             * Calculates the distance between two vectors squared.
             */
            static System::Single DistanceSquared(const Vector3& value1, const Vector3& value2);

            /**
             * Calculates the dot product of two Vector3 structures.
             * @param left The first Vector3 to evaluate.
             * @param right The second Vector3 to evaluate.
             * @return The dot product of the given vectors.
             */
            static System::Single Dot(const Vector3& left, const Vector3& right);

            /**
             * Calculates a hermite spline interpolation.
             * @param value1 source position 1.
             * @param tangent1 source tangent 1.
             * @param value2 source position 2.
             * @param tangent2 source tangent 2.
             * @param amount weighting factor.
             */
            static Vector3 Hermite(const Vector3&        value1
                                 , const Vector3&        tangent1
                                 , const Vector3&        value2
                                 , const Vector3&        tangent2
                                 , const System::Single& amount);

            /**
             * Performs a linear interpolation between two vectors.
             * @param value1 first vector
             * @param value2 second vector
             * @param amount Value between 0 and 1 indicating the weight of value2.
             * @returns the linear interpolation of the two vectors.
             */
            static Vector3 Lerp(const Vector3&        value1
                              , const Vector3&        value2
                              , const System::Single& amount);

            /**
             * Returns a vector that contains the lowest value from each matching pair of components.
             * @param value the first vector
             * @param value the second vector
             */
            static Vector3 Min(const Vector3& value1, const Vector3& value2);

            /**
             * Returns a vector that contains the highest value from each matching pair of components.
             * @param value the first vector
             * @param value the second vector
             */
            static Vector3 Max(const Vector3& value1, const Vector3& value2);

            /**
             * Negates a Vector3. The vector has the same magnitude as before, but its direction is now opposite.
             * @param value the vector to be negated.
             * @returns the negated vector.
             */
            static Vector3 Negate(const Vector3& value);

            /**
             * Normalizes the specified 3D Vector.
             *
             * A normalized Vector3 maintains its direction but its magnitude becomes 1.
             * The resulting Vector3 is often called a unit vector.
             * A Vector3 is normalized by dividing the Vector3 by its magnitude.
             * @param value the vector to be normalized.
             * @returns the normalized vector.
             */
            static Vector3 Normalize(const Vector3& value);

            /**
             * Performs a cubic interpolation between two vectors.
             * @param value1 first vector
             * @param value2 second vector
             * @param amount Weighting value.
             * @returns the linear interpolation of the two vectors.
             */
            static Vector3 SmoothStep(const Vector3&        value1
                                    , const Vector3&        value2
                                    , const System::Single& amount);

            /**
             * Transforms a 3D vector by the given matrix.
             * @param position the 3D Vector to be transformed.
             * @param matrix the transformation matrix.
             * @return the transformed vector.
             */
            static Vector3 Transform(const Vector3& position, const Matrix& matrix);

            /**
             * This method transforms the vector normal (x, y, z, 0) of the source vector,
             * or the array of vector structures, by the sourceMatrix matrix.
             * If you transform a normal by a non-affine matrix, the matrix you pass to this
             * function should be the transpose of the inverse of the matrix you would use to
             * transform a coordinate.
             */
            static Vector3 TransformNormal(const Vector3& normal, const Matrix& matrix);

        public:
            /**
             * Initializes a new instance of the Vector3 class.
             */
            Vector3();

            /**
             * Initializes a new instance of the Vector3 class.
             * @param value a vector containing the values to initialize x and y components with.
             * @param z value for the z-component of the vector.
             */
            Vector3(const Vector2& value, const System::Single& z);

            /**
             * Initializes a new instance of the Vector3 class.
             * @param x The X value of the new Vector3 structure.
             * @param y The Y value of the new Vector3 structure.
             * @param z The Z value of the new Vector3 structure.
             */
            Vector3(const System::Single& x, const System::Single& y, const System::Single& z);

            /**
             * Initializes a new instance of the Vector3 class (Copy constructor)
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
            const System::Single& X() const;

            /**
             * Gets the y-coordinate value
             */
            const System::Single& Y() const;

            /**
             * Gets the z-coordinate value
             */
            const System::Single& Z() const;

        public:
            /**
             * Sets the x-coordinate value.
             */
            void X(const System::Single& x);

            /**
             * Sets the y-coordinate value.
             */
            void Y(const System::Single& y);

            /**
             * Sets the z-coordinate value.
             */
            void Z(const System::Single& z);

        public:

            /**
             * Gets the square of the length of this Vector3.
             *
             * @return the square of the length of this Vector3.
             */
            System::Single LengthSquared() const;

            /**
             * Gets the length of this Vector3.
             *
             * @return the length of this Vector3.
             */
            System::Single Length() const;

        public:
            System::Single& operator[](const System::Size& index);
            const System::Single& operator[](const System::Size& index) const;
            Vector3& operator=(const Vector3& vector);
            bool operator==(const Vector3& vector) const;
            bool operator!=(const Vector3& vector) const;
            Vector3& operator*=(const Vector3& vector);
            Vector3& operator*=(const System::Single& value);
            Vector3& operator/=(const Vector3& vector);
            Vector3& operator/=(const System::Single& value);
            Vector3& operator-=(const Vector3& vector);
            Vector3& operator+=(const Vector3& vector);
            const Vector3 operator*(const Vector3& vector) const;
            const Vector3 operator*(const System::Single& value) const;
            const Vector3 operator*(const Matrix& matrix) const;
            const Vector3 operator/(const Vector3& vector) const;
            const Vector3 operator/(const System::Single& value) const;
            const Vector3 operator-(const Vector3& vector) const;
            const Vector3 operator-() const;
            const Vector3 operator+(const Vector3& vector) const;

        private:
            union
            {
                System::Single vector[3];
                struct
                {
                    System::Single x;
                    System::Single y;
                    System::Single z;
                };
            };
        };

        inline Vector3 operator*(const System::Single& value, const Vector3& vector)
        {
            return { value * vector.X(), value * vector.Y(), value * vector.Z() };
        }
    }
}

#endif /* VECTOR3_HPP */
