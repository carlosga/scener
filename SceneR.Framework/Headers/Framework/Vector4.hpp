// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef VECTOR4_HPP
#define VECTOR4_HPP

#include <System/Core.hpp>

namespace SceneR
{
    namespace Framework
    {
        struct Matrix;
        struct Quaternion;
        struct Vector2;
        struct Vector3;

        /**
         * Represents an x-, y-, z- and w-coordinate vector.
         */
        struct Vector4
        {
        public:
            /**
             * Returns a Vector4 with ones in all of its components.
             */
            static const Vector4 One;

            /**
             * Returns the x unit Vector4 (1, 0, 0, 0).
             */
            static const Vector4 UnitX;

            /**
             * Returns the y unit Vector4 (0, 1, 0, 0).
             */
            static const Vector4 UnitY;

            /**
             * Returns the z unit Vector4 (0, 0, 1, 0).
             */
            static const Vector4 UnitZ;

            /**
             * Returns the w unit Vector4 (0, 0, 0, 1).
             */
            static const Vector4 UnitW;

            /**
             * Returns a Vector4 with all of its components set to zero.
             */
            static const Vector4 Zero;

        public:
            /**
             * @brief Returns a vector whose elements are the absolute values of each of the specified vector's elements.
             * @param value A vector.
             * @return The absolute value vector.
             */
            static Vector4 Abs(const Vector4& value);

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
            static Vector4 Barycentric(const Vector4&        value1
                                     , const Vector4&        value2
                                     , const Vector4&        value3
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
            static Vector4 CatmullRom(const Vector4&        value1
                                    , const Vector4&        value2
                                    , const Vector4&        value3
                                    , const Vector4&        value4
                                    , const System::Single& amount);

            /**
             * Restricts a value to be within a specified range.
             */
            static Vector4 Clamp(const Vector4& value1, const Vector4& min, const Vector4& max);

            /**
             * Calculates the distance between two vectors.
             */
            static System::Single Distance(const Vector4& value1, const Vector4& value2);

            /**
             * Calculates the distance between two vectors squared.
             */
            static System::Single DistanceSquared(const Vector4& value1, const Vector4& value2);

            /**
             * Calculates the dot product of two Vector4 structures.
             * @param vectora the first Vector4 structure to evaluate
             * @param vectorb The second Vector4 structure to evaluate.
             * @return The dot product of the given vectors.
             */
            static System::Single Dot(const Vector4& value1, const Vector4& value2);

            /**
             * Calculates a hermite spline interpolation.
             * @param value1 source position 1.
             * @param tangent1 source tangent 1.
             * @param value2 source position 2.
             * @param tangent2 source tangent 2.
             * @param amount weighting factor.
             */
            static Vector4 Hermite(const Vector4&        value1
                                 , const Vector4&        tangent1
                                 , const Vector4&        value2
                                 , const Vector4&        tangent2
                                 , const System::Single& amount);

            /**
             * Performs a linear interpolation between two vectors.
             * @param value1 first vector
             * @param value2 second vector
             * @param amount Value between 0 and 1 indicating the weight of value2.
             * @returns the linear interpolation of the two vectors.
             */
            static Vector4 Lerp(const Vector4&        value1
                              , const Vector4&        value2
                              , const System::Single& amount);


            /**
             * Returns a vector that contains the lowest value from each matching pair of components.
             * @param value the first vector
             * @param value the second vector
             */
            static Vector4 Min(const Vector4& value1, const Vector4& value2);

            /**
             * Returns a vector that contains the highest value from each matching pair of components.
             * @param value the first vector
             * @param value the second vector
             */
            static Vector4 Max(const Vector4& value1, const Vector4& value2);

            /**
             * Negates a Vector4.
             *
             * The vector has the same magnitude as before, but its direction is now opposite.
             * @param value the vector to be negated
             */
            static Vector4 Negate(const Vector4& value);

            /**
             * Normalizes the specified Vector4.
             *
             * A normalized Vector4 maintains its direction but its magnitude becomes 1.
             * The resulting Vector4 is often called a unit vector.
             * A Vector4 is normalized by dividing the Vector4 by its magnitude.
             * @param value the vector to normalize
             */
            static Vector4 Normalize(const Vector4& value);

            /**
             * @brief Returns a vector whose elements are the square root of each of a specified vector's elements.
             * @param value A vector.
             * @return The square root vector.
             */
            static Vector4 SquareRoot(const Vector4& value);

            /**
             * @brief Transforms a two-dimensional vector by a specified 4x4 matrix.
             * @param position The vector to transform.
             * @param matrix The transformation matrix.
             * @return The transformed vector
             */
            static Vector4 Transform(const Vector2& position, const Matrix& matrix);

            /**
             * @brief Transforms a three-dimensional vector by a specified 4x4 matrix.
             * @param position The vector to transform.
             * @param matrix The transformation matrix.
             * @return The transformed vector
             */
            static Vector4 Transform(const Vector3& position, const Matrix& matrix);

            /**
             * @brief Transforms a four-dimensional vector by a specified 4x4 matrix.
             * @param position The vector to transform.
             * @param matrix The transformation matrix.
             * @return The transformed vector
             */
            static Vector4 Transform(const Vector4& position, const Matrix& matrix);

            /**
             * @brief Transforms a two-dimensional vector by a specified quaternion.
             * @param position The vector to transform.
             * @param rotation The transformation quaternion.
             * @return The transformed vector
             */
            static Vector4 Transform(const Vector2& value, const Quaternion& rotation);

            /**
             * @brief Transforms a three-dimensional vector by a specified quaternion.
             * @param position The vector to transform.
             * @param rotation The transformation quaternion.
             * @return The transformed vector
             */
            static Vector4 Transform(const Vector3& value, const Quaternion& rotation);

            /**
             * @brief Transforms a four-dimensional vector by a specified quaternion.
             * @param position The vector to transform.
             * @param rotation The transformation quaternion.
             * @return The transformed vector
             */
            static Vector4 Transform(const Vector4& value, const Quaternion& rotation);

            /**
             * Performs a cubic interpolation between two vectors.
             * @param value1 first vector
             * @param value2 second vector
             * @param amount Weighting value.
             * @returns the linear interpolation of the two vectors.
             */
            static Vector4 SmoothStep(const Vector4&        value1
                                    , const Vector4&        value2
                                    , const System::Single& amount);

        public:
            /**
             * Initializes a new instance of the Vector4 class.
             */
            Vector4();

            /**
             * Initializes a new instance of the Vector4 class.
             * @param w value to initialize each component to.
             */
            Vector4(const System::Single& value);

            /**
             * Initializes a new instance of the Vector4 class.
             * @param value a vector containing the values to initialize x, y, and z components with.
             * @param w value for the w-component of the vector.
             */
            Vector4(const Vector3& value, const System::Single& w);

            /**
             * Initializes a new instance of the Vector4 class.
             * @param x The X value of the new Vector4 structure.
             * @param y The Y value of the new Vector4 structure.
             * @param z The Z value of the new Vector4 structure.
             */
            Vector4(const System::Single& x, const System::Single& y, const System::Single& z);

            /**
             * Initializes a new instance of the Vector4 class.
             * @param value a vector containing the values to initialize x and y components with.
             * @param z value for the z-component of the vector.
             * @param w value for the w-component of the vector.
             */
            Vector4(const Vector2& value, const System::Single& z, const System::Single& w);

            /**
             * Initializes a new instance of the Vector4 class.
             * @param x The X value of the new Vector4 structure.
             * @param y The Y value of the new Vector4 structure.
             * @param z The Z value of the new Vector4 structure.
             * @param w The W value of the new Vector4 structure.
             */
            Vector4(const System::Single& x
                  , const System::Single& y
                  , const System::Single& z
                  , const System::Single& w);

            /**
             * Initializes a new instance of the Vector4 class (Copy constructor)
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

            /**
             * Sets the w-coordinate value.
             */
            void W(const System::Single& w);

        public:
            /**
             * Gets the square of the length of this Vector4.
             *
             * @return the square of the length of this Vector4.
             */
            System::Single LengthSquared() const;

            /**
             * Gets the length of this Vector4.
             *
             * @return the length of this Vector4.
             */
            System::Single Length() const;

        public:
            System::Single& operator[](const System::Size& index);
            const System::Single& operator[](const System::Size& index) const;
            Vector4& operator=(const Vector4& vector);
            bool operator==(const Vector4& vector) const;
            bool operator!=(const Vector4& vector) const;
            Vector4& operator*=(const Vector4& vector);
            Vector4& operator*=(const System::Single& value);
            Vector4& operator/=(const Vector4& vector);
            Vector4& operator/=(const System::Single& value);
            Vector4& operator-=(const Vector4& vector);
            Vector4& operator+=(const Vector4& vector);
            const Vector4 operator*(const Vector4& vector) const;
            const Vector4 operator*(const System::Single& value) const;
            const Vector4 operator*(const Matrix& matrix) const;
            const Vector4 operator/(const Vector4& vector) const;
            const Vector4 operator/(const System::Single& value) const;
            const Vector4 operator-(const Vector4& vector) const;
            const Vector4 operator-() const;
            const Vector4 operator+(const Vector4& vector) const;

        private:
            union
            {
                System::Single vector[4];
                struct
                {
                    System::Single x;
                    System::Single y;
                    System::Single z;
                    System::Single w;
                };
            };
        };

        inline Vector4 operator*(const System::Single& value, const Vector4& vector)
        {
            return { value * vector.X(), value * vector.Y(), value * vector.Z(), value * vector.W() };
        }
    }
}

#endif  /* VECTOR4_HPP */
