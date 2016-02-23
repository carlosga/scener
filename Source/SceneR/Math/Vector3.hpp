// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_VECTOR3_HPP
#define SCENER_MATH_VECTOR3_HPP

#include <cstddef>

#include "SceneR/Math/Angle.hpp"

namespace SceneR { namespace Math {

struct Matrix;
struct Quaternion;
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
    static const Vector3 backward;

    /**
     * Returns a unit Vector3 designating down (0, −1, 0).
     */
    static const Vector3 down;

    /**
     * Returns a unit Vector3 designating forward in a right-handed coordinate system(0, 0, −1).
     */
    static const Vector3 forward;

    /**
     * Returns a unit Vector3 designating left (−1, 0, 0).
     */
    static const Vector3 left;

    /**
     * Returns a Vector3 with ones in all of its components.
     */
    static const Vector3 one;

    /**
     * Returns a unit Vector3 pointing to the right (1, 0, 0).
     */
    static const Vector3 right;

    /**
     * Returns the x unit Vector3 (1, 0, 0).
     */
    static const Vector3 unit_x;

    /**
     * Returns the y unit Vector3 (0, 1, 0).
     */
    static const Vector3 unit_y;

    /**
     * Returns the z unit Vector3 (0, 0, 1).
     */
    static const Vector3 unit_z;

    /**
     * Returns a unit vector designating up (0, 1, 0).
     */
    static const Vector3 up;

    /**
     * Returns a Vector3 with all of its components set to zero.
     */
    static const Vector3 zero;

public:
    /**
     * @brief Returns a vector whose elements are the absolute values of each of the specified vector's elements.
     * @param value A vector.
     * @return The absolute value vector.
     */
    static Vector3 abs(const Vector3& value) noexcept;

    /**
     * Retrieves the angle required to rotate the first specified Vector3 structure into the second specified
     * Vector3 structure.
     * @param value1 The first Vector3 to evaluate.
     * @param value2 The second Vector3 to evaluate.
     * @return The angle, in radians, needed to rotate the left vector into the right vector.
     */
    static Radians angle_between(const Vector3& value1, const Vector3& value2) noexcept;

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
    static Vector3 barycentric(const Vector3& value1
                             , const Vector3& value2
                             , const Vector3& value3
                             , float          amount1
                             , float          amount2) noexcept;

    /**
     * Performs a Catmull-Rom interpolation using the specified positions.
     * @param value1 the first position in the interpolation.
     * @param value2 the second position in the interpolation.
     * @param value3 the third position in the interpolation.
     * @param value4 the fourth position in the interpolation.
     * @param amount weighting factor.
     */
    static Vector3 catmull_rom(const Vector3& value1
                             , const Vector3& value2
                             , const Vector3& value3
                             , const Vector3& value4
                             , float          amount) noexcept;

    /**
     * Restricts a value to be within a specified range.
     */
    static Vector3 clamp(const Vector3& value1, const Vector3& min, const Vector3& max) noexcept;

    /**
     * Calculates the cross product of two Vector3 structures.
     * @param value1 The first Vector3 to evaluate.
     * @param value2 The second Vector3 to evaluate.
     * @return The cross product of this Vector3 and vectorb.
     */
    static Vector3 cross(const Vector3& value1, const Vector3& value2) noexcept;

    /**
     * Calculates the distance between two vectors.
     */
    static float distance(const Vector3& value1, const Vector3& value2) noexcept;

    /**
     * Calculates the distance between two vectors squared.
     */
    static float distance_squared(const Vector3& value1, const Vector3& value2) noexcept;

    /**
     * Calculates the dot product of two Vector3 structures.
     * @param value1 The first Vector3 to evaluate.
     * @param value2 The second Vector3 to evaluate.
     * @return The dot product of the given vectors.
     */
    static float dot(const Vector3& value1, const Vector3& value2) noexcept;

    /**
     * Calculates a hermite spline interpolation.
     * @param value1 source position 1.
     * @param tangent1 source tangent 1.
     * @param value2 source position 2.
     * @param tangent2 source tangent 2.
     * @param amount weighting factor.
     */
    static Vector3 hermite(const Vector3& value1
                         , const Vector3& tangent1
                         , const Vector3& value2
                         , const Vector3& tangent2
                         , float          amount) noexcept;

    /**
     * Performs a linear interpolation between two vectors.
     * @param value1 first vector
     * @param value2 second vector
     * @param amount Value between 0 and 1 indicating the weight of value2.
     * @returns the linear interpolation of the two vectors.
     */
    static Vector3 lerp(const Vector3& value1, const Vector3& value2, float amount) noexcept;

    /**
     * Returns a vector that contains the lowest value from each matching pair of components.
     * @param value1 the first vector
     * @param value2 the second vector
     */
    static Vector3 min(const Vector3& value1, const Vector3& value2) noexcept;

    /**
     * Returns a vector that contains the highest value from each matching pair of components.
     * @param value1 the first vector
     * @param value2 the second vector
     */
    static Vector3 max(const Vector3& value1, const Vector3& value2) noexcept;

    /**
     * Negates a Vector3. The vector has the same magnitude as before, but its direction is now opposite.
     * @param value the vector to be negated.
     * @returns the negated vector.
     */
    static Vector3 negate(const Vector3& value) noexcept;

    /**
     * Normalizes the specified 3D Vector.
     *
     * A normalized Vector3 maintains its direction but its magnitude becomes 1.
     * The resulting Vector3 is often called a unit vector.
     * A Vector3 is normalized by dividing the Vector3 by its magnitude.
     * @param value the vector to be normalized.
     * @returns the normalized vector.
     */
    static Vector3 normalize(const Vector3& value) noexcept;

    /**
     * @brief Returns the reflection of a vector off a surface that has the specified normal.
     * @param vector Source vector.
     * @param normal Normal of the surface.
     * @return The reflected vector.
     */
    static Vector3 reflect(const Vector3& vector, const Vector3& normal) noexcept;

    /**
     * Performs a cubic interpolation between two vectors.
     * @param value1 first vector
     * @param value2 second vector
     * @param amount Weighting value.
     * @returns the linear interpolation of the two vectors.
     */
    static Vector3 smooth_step(const Vector3& value1, const Vector3& value2, float amount) noexcept;

    /**
     * @brief Returns a vector whose elements are the square root of each of a specified vector's elements.
     * @param value A vector.
     * @return The square root vector.
     */
    static Vector3 square_root(const Vector3& value) noexcept;

    /**
     * Transforms a 3D vector by the given matrix.
     * @param position the 3D Vector to be transformed.
     * @param matrix the transformation matrix.
     * @return the transformed vector.
     */
    static Vector3 transform(const Vector3& position, const Matrix& matrix) noexcept;

    /**
     * @brief Transforms a vector by the specified Quaternion rotation value.
     * @param value The vector to rotate.
     * @param rotation The rotation to apply.
     * @return The transformed vector.
     */
    static Vector3 transform(const Vector3& value, const Quaternion& rotation) noexcept;

    /**
     * This method transforms the vector normal (x, y, z, 0) of the source vector,
     * or the array of vector structures, by the sourceMatrix matrix.
     * If you transform a normal by a non-affine matrix, the matrix you pass to this
     * function should be the transpose of the inverse of the matrix you would use to
     * transform a coordinate.
     */
    static Vector3 transform_normal(const Vector3& normal, const Matrix& matrix) noexcept;

public:
    /**
     * Initializes a new instance of the Vector3 class.
     */
    Vector3() noexcept;

    /**
     * Initializes a new instance of the Vector3 class.
     * @param value the value for the x, y and z components of the vector.
     */
    Vector3(float value) noexcept;

    /**
     * Initializes a new instance of the Vector3 class.
     * @param value a vector containing the values to initialize x and y components with.
     * @param z value for the z-component of the vector.
     */
    Vector3(const Vector2& value, float z) noexcept;

    /**
     * Initializes a new instance of the Vector3 class.
     * @param x The X value of the new Vector3 structure.
     * @param y The Y value of the new Vector3 structure.
     * @param z The Z value of the new Vector3 structure.
     */
    Vector3(float x, float y, float z) noexcept;

    /**
     * Initializes a new instance of the Vector3 class (Copy constructor)
     * @param vector The Vector3 to be copied.
     */
    Vector3(const Vector3& data) = default;

    /**
     * Destructor
     */
    ~Vector3() = default;

public:
    /**
     * Gets the square of the length of this Vector3.
     *
     * @return the square of the length of this Vector3.
     */
    float length_squared() const noexcept;

    /**
     * Gets the length of this Vector3.
     *
     * @return the length of this Vector3.
     */
    float length() const noexcept;

public:
    Vector3& operator=(const Vector3& vector) = default;

    float& operator[](const std::size_t& index) noexcept;
    const float& operator[](const std::size_t& index) const noexcept;
    bool operator==(const Vector3& vector) const noexcept;
    bool operator!=(const Vector3& vector) const noexcept;
    Vector3& operator*=(const Vector3& vector) noexcept;
    Vector3& operator*=(const float& value) noexcept;
    Vector3& operator/=(const Vector3& vector) noexcept;
    Vector3& operator/=(const float& value) noexcept;
    Vector3& operator-=(const Vector3& vector) noexcept;
    Vector3& operator+=(const Vector3& vector) noexcept;
    Vector3 operator*(const Vector3& vector) const noexcept;
    Vector3 operator*(const float& value) const noexcept;
    Vector3 operator*(const Matrix& matrix) const noexcept;
    Vector3 operator/(const Vector3& vector) const noexcept;
    Vector3 operator/(const float& value) const noexcept;
    Vector3 operator-(const Vector3& vector) const noexcept;
    Vector3 operator+(const Vector3& vector) const noexcept;
    Vector3 operator-() const noexcept;

public:
    union
    {
        float data[3];
        struct
        {
            float x;
            float y;
            float z;
        };
    };
};

inline Vector3 operator*(const float& value, const Vector3& vector)
{
    return { value * vector.x, value * vector.y, value * vector.z };
}

}}

#endif // SCENER_MATH_VECTOR3_HPP
