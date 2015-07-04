// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <cstddef>

namespace SceneR
{
    namespace Framework
    {
        struct Matrix;

        /**
         * Represents an x and y-coordinate vector.
         */
        struct Vector2
        {
        public:
            /**
             * Returns a Vector2 with ones in all of its components.
             */
            static const Vector2 One;

            /**
             * Returns the x unit Vector2 (1, 0).
             */
            static const Vector2 UnitX;

            /**
             * Returns the y unit Vector2 (0, 1).
             */
            static const Vector2 UnitY;

            /**
             * Returns a Vector2 with all of its components set to zero.
             */
            static const Vector2 Zero;

        public:
            /**
             * @brief Returns a vector whose elements are the absolute values of each of the specified vector's elements.
             * @param value A vector.
             * @return The absolute value vector.
             */
            static Vector2 Abs(const Vector2& value);

            /**
             * @brief Returns a vector whose elements are the square root of each of a specified vector's elements.
             * @param value A vector.
             * @return The square root vector.
             */
            static Vector2 SquareRoot(const Vector2& value);

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
            static Vector2 Barycentric(const Vector2& value1
                                     , const Vector2& value2
                                     , const Vector2& value3
                                     , const float&   amount1
                                     , const float&   amount2);

            /**
             * Performs a Catmull-Rom interpolation using the specified positions.
             * @param value1 the first position in the interpolation.
             * @param value2 the second position in the interpolation.
             * @param value3 the third position in the interpolation.
             * @param value4 the fourth position in the interpolation.
             * @param amount weighting factor.
             */
            static Vector2 CatmullRom(const Vector2& value1
                                    , const Vector2& value2
                                    , const Vector2& value3
                                    , const Vector2& value4
                                    , const float&   amount);

            /**
             * Restricts a value to be within a specified range.
             */
            static Vector2 Clamp(const Vector2& value1, const Vector2& min, const Vector2& max);

            /**
             * Calculates the distance between two vectors.
             */
            static float Distance(const Vector2& value1, const Vector2& value2);

            /**
             * Calculates the distance between two vectors squared.
             */
            static float DistanceSquared(const Vector2& value1, const Vector2& value2);

            /**
            * Calculates the dot product of two Vector2 structures.
            * @param left The first Vector2 to evaluate.
            * @param right The second Vector2 to evaluate.
            * @return The dot product of the given vectors.
            */
            static float DotProduct(const Vector2& left, const Vector2& right);

            /**
             * Calculates a hermite spline interpolation.
             * @param value1 source position 1.
             * @param tangent1 source tangent 1.
             * @param value2 source position 2.
             * @param tangent2 source tangent 2.
             * @param amount weighting factor.
             */
            static Vector2 Hermite(const Vector2& value1
                                 , const Vector2& tangent1
                                 , const Vector2& value2
                                 , const Vector2& tangent2
                                 , const float&   amount);

            /**
             * Performs a linear interpolation between two vectors.
             * @param value1 first vector
             * @param value2 second vector
             * @param amount Value between 0 and 1 indicating the weight of value2.
             * @returns the linear interpolation of the two vectors.
             */
            static Vector2 Lerp(const Vector2& value1
                              , const Vector2& value2
                              , const float&   amount);

            /**
            * Returns a vector that contains the lowest value from each matching pair of components.
            * @param value1 the first vector
            * @param value2 the second vector
            */
            static Vector2 Min(const Vector2& value1, const Vector2& value2);

            /**
            * Returns a vector that contains the highest value from each matching pair of components.
            * @param value1 the first vector
            * @param value2 the second vector
            */
            static Vector2 Max(const Vector2& value1, const Vector2& value2);

            /**
             * Negates a Vector2.
             * The vector has the same magnitude as before, but its direction is now opposite.
             */
            static Vector2 Negate(const Vector2& value);

            /**
            * Normalizes the specified 2D Vector.
            *
            * A normalized Vector2 maintains its direction but its magnitude becomes 1.
            * The resulting Vector2 is often called a unit vector.
            * A Vector2 is normalized by dividing the Vector2 by its magnitude.
            * @param value the vector to be normalized.
            * @returns the normalized vector.
            */
            static Vector2 Normalize(const Vector2& value);

            /**
             * Performs a cubic interpolation between two vectors.
             * @param value1 first vector
             * @param value2 second vector
             * @param amount Weighting value.
             * @returns the linear interpolation of the two vectors.
             */
            static Vector2 SmoothStep(const Vector2& value1
                                    , const Vector2& value2
                                    , const float&   amount);

            /**
            * Transforms a 2D vector by the given matrix.
            * @param position the 2D Vector to be transformed.
            * @param matrix the transformation matrix.
            * @return the transformed vector.
            */
            static Vector2 Transform(const Vector2& position, const Matrix& matrix);

            /**
            * This method transforms the vector normal (x, y, 0) of the source vector,
            * or the array of vector structures, by the sourceMatrix matrix.
            * If you transform a normal by a non-affine matrix, the matrix you pass to this
            * function should be the transpose of the inverse of the matrix you would use to
            * transform a coordinate.
            */
            static Vector2 TransformNormal(const Vector2& normal, const Matrix& matrix);

        public:
            /**
             * Initializes a new instance of the Vector2 class.
             */
            Vector2();

            /**
            * Initializes a new instance of the Vector2 class with the given value.
            * @param value value value for the x and y components of the vector.
            */
            Vector2(const float& value);

            /**
             * Initializes a new instance of the Vector2 class with the given texture coordinates.
             * @param x the x-coordinate value.
             * @param y the y-coordinate value.
             */
            Vector2(const float& x, const float& y);

            /**
             * Initializes a new instance of the Vector2 class (Copy constructor)
             * @param vector The Vector2 to be copied.
             */
            Vector2(const Vector2& vector);

            /**
             * Destructor
             */
            ~Vector2();

        public:
            /**
             * Gets the x-coordinate value.
             */
            float X() const;

            /**
             * Gets the y-coordinate value.
             */
            float Y() const;

            /**
             * Gets the square of the length of this Vector2.
             *
             * @return the square of the length of this Vector2.
             */
            float LengthSquared() const;

            /**
             * Gets the length of this Vector2.
             *
             * @return the length of this Vector2.
             */
            float Length() const;

        public:
            float& operator[](const std::size_t& index);
            const float& operator[](const std::size_t& index) const;
            Vector2& operator=(const Vector2& vector);
            bool operator==(const Vector2& vector) const;
            bool operator!=(const Vector2& vector) const;
            Vector2& operator*=(const Vector2& vector);
            Vector2& operator*=(const float& value);
            Vector2& operator/=(const Vector2& vector);
            Vector2& operator/=(const float& value);
            Vector2& operator-=(const Vector2& vector);
            Vector2& operator+=(const Vector2& vector);
            const Vector2 operator*(const Vector2& vector) const;
            const Vector2 operator*(const float& value) const;
            const Vector2 operator/(const Vector2& vector) const;
            const Vector2 operator/(const float& value) const;
            const Vector2 operator-(const Vector2& vector) const;
            const Vector2 operator-() const;
            const Vector2 operator+(const Vector2& vector) const;

        private:
            union
            {
                float coords[2];
                struct
                {
                    float x;
                    float y;
                };
            };
        };
    }
}

#endif  /* VECTOR2_HPP */
