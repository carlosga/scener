// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_QUATERNION_HPP
#define SCENER_MATH_QUATERNION_HPP

#include <cstddef>

#include "SceneR/Math/Angle.hpp"

namespace SceneR { namespace Math {

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
    static const Quaternion identity;

public:
    /**
     * Returns the conjugate of a specified Quaternion.
     *
     * @param quaternion the Quaternion of which to return the conjugate.
     * @returns the quaternion conjugate
     */
    static Quaternion conjugate(const Quaternion& data) noexcept;

    /**
     * Creates a Quaternion from a vector and an angle to rotate about the vector.
     *
     * @param axisOfRotation Vector3 that represents the axis of rotation.
     * @param angle Angle to rotate around the specified axis, in radians.
     */
    static Quaternion create_from_axis_angle(const Vector3& axisOfRotation, const Radians& angle) noexcept;

    /**
     * Creates a Quaternion from a rotation Matrix.
     * @param matrix the rotation matrix
     */
    static Quaternion create_from_rotation_matrix(const Matrix& matrix) noexcept;

    /**
     * Creates a new quaternion with a specified yaw, pitch, and roll.
     *
     * @param yaw Yaw around the y-axis, in radians.
     * @param pitch Pitch around the x-axis, in radians.
     * @param roll Roll around the z-axis, in radians.
     */
    static Quaternion create_from_yaw_pitch_roll(const Radians& yaw, const Radians& pitch, const Radians& roll) noexcept;

    /**
     * Calculates the dot product oof two quaternions
     */
    static float dot(const Quaternion& quaternion1, const Quaternion& quaternion2) noexcept;

    /**
     * Calculates the invers of the specified quaternion.
     */
    static Quaternion inverse(const Quaternion& value) noexcept;

    /**
     * Calculates the linear interpolation between two quaternions.
     *
     * @param quaternion1 first quaternion
     * @param quaternion2 second quaternion
     * @param amount Value indicating how far to interpolate between the quaternions.
     */
    static Quaternion lerp(const Quaternion& quaternion1, const Quaternion& quaternion2, float amount) noexcept;

    /**
     * Negates the specified Quaternion.
     */
    static Quaternion negate(const Quaternion& value) noexcept;

    /**
     * Normalizes the specified Quaternion.
     *
     * A normalized Quaternion maintains its direction but its magnitude becomes 1.
     * The resulting Quaternion is often called a unit vector.
     * @param value the quaternion to normalize.
     * @returns A Quaternion is normalized by dividing the Quaternion by its magnitude.
     */
    static Quaternion normalize(const Quaternion& value) noexcept;

    /**
     * Calculates the spherical interpolation between two quaternions.
     *
     * @param quaternion1 first quaternion
     * @param quaternion2 second quaternion
     * @param amount Value indicating how far to interpolate between the quaternions.
     */
    static Quaternion slerp(const Quaternion& quaternion1, const Quaternion& quaternion2, float amount) noexcept;

public:
    /**
     * Initializes a new instance of the Quaternion class.
     */
    Quaternion() noexcept;

    /**
     * Initializes a new instance of the Quaternion class.
     * @param value a vector containing the values to initialize x, y, and z components with.
     * @param w value for the w-component of the vector.
     */
    Quaternion(const Vector3& value, float w) noexcept;

    /**
     * Initializes a new instance of the Quaternion class.
     * @param x The X value of the new Quaternion structure.
     * @param y The Y value of the new Quaternion structure.
     * @param z The Z value of the new Quaternion structure.
     * @param w The W value of the new Quaternion structure.
     */
    Quaternion(float x, float y, float z, float w) noexcept;

    /**
     * Initializes a new instance of the Quaternion class (Copy constructor)
     * @param quaternion The Quaternion to be copied.
     */
    Quaternion(const Quaternion& quaternion) = default;

    /**
     * Destructor
     */
    ~Quaternion() = default;

public:
    /**
     * Gets a value that indicates whether the specified quaternion is an Identity quaternion.
     * @return a value that indicates whether the specified quaternion is an Identity quaternion.
     */
    bool is_identity() const noexcept;

    /**
     * Gets the square of the length of this Quaternion.
     *
     * @return the square of the length of this Quaternion.
     */
    float length_squared() const noexcept;

    /**
     * Gets the length of this Quaternion.
     *
     * @return the length of this Quaternion.
     */
    float length() const noexcept;

public:
    Quaternion& operator=(const Quaternion& value) = default;

    float& operator[](const std::size_t& index) noexcept;
    const float& operator[](const std::size_t& index) const noexcept;
    bool operator==(const Quaternion& value) const noexcept;
    bool operator!=(const Quaternion& value) const noexcept;
    Quaternion& operator*=(const Quaternion& q1) noexcept;
    Quaternion& operator*=(const float& value) noexcept;
    Quaternion& operator/=(const Quaternion& value) noexcept;
    Quaternion& operator/=(const float& value) noexcept;
    Quaternion& operator-=(const Quaternion& value) noexcept;
    Quaternion& operator+=(const Quaternion& value) noexcept;
    const Quaternion operator*(const Quaternion& value) const noexcept;
    const Quaternion operator*(const float& value) const noexcept;
    const Quaternion operator/(const Quaternion& r) const noexcept;
    const Quaternion operator/(const float& value) const noexcept;
    const Quaternion operator-(const Quaternion& value) const noexcept;
    const Quaternion operator-() const noexcept;
    const Quaternion operator+(const Quaternion& value) const noexcept;

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

}}

#endif // SCENER_MATH_QUATERNION_HPP
