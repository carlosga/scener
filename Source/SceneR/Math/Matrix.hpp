// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_MATRIX_HPP
#define SCENER_MATH_MATRIX_HPP

#include <cstddef>
#include <cstdint>
#include <string>

#include "SceneR/Math/Angle.hpp"

namespace SceneR { namespace Math {

struct Plane;
struct Vector3;
struct Vector4;
struct Quaternion;

/**
 * Represents a 4 x 4 matrix.
 */
struct Matrix
{
public:
    /**
     * Returns the identity matrix.
     */
    static const Matrix identity;

public:
    /**
     * Creates a new Matrix that rotates around an arbitrary axis.
     *
     * @param axis Vector3 that specifies the axis around which to rotate.
     * @param angle Value that specifies the angle of rotation, in radians.
     */
    static Matrix create_from_axis_angle(const Vector3& axis, const Radians& angle) noexcept;

    /**
     * Creates a rotation Matrix from a Quaternion.
     *
     * @param quaternion Quaternion to create the Matrix from.
     */
    static Matrix create_from_quaternion(const Quaternion& quaternion) noexcept;

    /**
     * Creates a new matrix with a specified yaw, pitch, and roll.
     * The order of transformations is yaw first, then pitch, then roll
     *
     * @param yaw Yaw around the y-axis.
     * @param pitch Pitch around the z-axis.
     * @param roll Roll around the x-axis.
     */
    static Matrix create_from_yaw_pitch_roll(const Radians& yaw, const Radians& pitch, const Radians& roll) noexcept;

    /**
     * Creates a perspective projection matrix.
     *
     * @param left The coordinate for the left-vertical clipping plane.
     * @param right The coordinate for the right-vertical clipping plane.
     * @param bottom The coordinate for the bottom-horizontal clipping plane.
     * @param top The coordinate for the top-horizontal clipping plane.
     * @param zNear The distances to the near-depth clipping plane. Must be positive.
     * @param zFar The distances to the far-depth clipping plane. Must be positive.
     */
    static Matrix create_frustum(float left, float right, float bottom, float top, float zNear, float zFar) noexcept;

    /**
     * Creates a view matrix
     *
     * @param cameraPosition The position of the camera.
     * @param cameraTarget The target towards which the camera is pointing.
     * @param cameraUpVector The direction that is "up" from the camera's point of view.
     */
    static Matrix create_look_at(const Vector3& cameraPosition
                               , const Vector3& cameraTarget
                               , const Vector3& cameraUpVector) noexcept;

    /**
     * Creates an orthogonal matrix
     *
     * @param width Width of the view volume.
     * @param height Height of the view volume.
     * @param zNear Minimum z-value of the view volume.
     * @param zFar Maximun z-value of the view volume.
     */
    static Matrix create_orthographic(float width, float height, float zNear, float zFar) noexcept;

    /**
     * Builds a customized, orthogonal projection matrix.
     *
     * @param left Minimum x-value of the view volume.
     * @param right Maximum x-value of the view volume.
     * @param bottom Minimum y-value of the view volume.
     * @param top Maximum y-value of the view volume.
     * @param zNear Minimum z-value of the view volume.
     * @param zFar Maximun z-value of the view volume.
     */
    static Matrix create_orthographic_off_center(float left  , float right
                                               , float bottom, float top
                                               , float zNear , float zFar) noexcept;

    /**
     * Builds a perspective projection matrix.
     *
     * @param width Width of the view volume at the near view plane.
     * @param height Height of the view volume at the near view plane.
     * @param zNear Distance to the near view plane.
     * @param zFar Distance to the far view plane.
     */
    static Matrix create_perspective(float width, float height, float zNear, float zFar) noexcept;

    /**
     * Builds a perspective projection matrix based on a field of view and returns by value.
     *
     * @param fieldOfView Field of view in the y direction.
     * @param aspectRatio Aspect ratio, defined as view space width divided by height.
     * @param zNear Distance to the near view plane.
     * @param zFar Distance to the far view plane.
     */
    static Matrix create_perspective_field_of_view(const Radians& fieldOfView, float aspectRatio
                                                 , float          zNear      , float zFar) noexcept;

    /**
     * Builds a customized, right-handed perspective projection matrix.
     * @param left Minimum x-value of the view volume.
     * @param right Maximum x-value of the view volume.
     * @param bottom Minimum y-value of the view volume.
     * @param top Maximum y-value of the view volume.
     * @param zNear Minimum z-value of the view volume.
     * @param zFar Maximun z-value of the view volume.
     */
    static Matrix create_perspective_off_center(float left  , float right
                                              , float bottom, float top
                                              , float zNear , float zFar) noexcept;

    /**
     * Returns a matrix that can be used to rotate a set of vertices around the x-axis.
     *
     * @param angle Value that specifies the angle of rotation.
     */
    static Matrix create_rotation_x(const Radians& angle) noexcept;

    /**
     * Creates a matrix for rotating points around the X-axis, from a center point.
     * @param angle The amount by which to rotate around the X-axis.
     * @param center The center point.
     * @returns The rotation matrix.
     */
    static Matrix create_rotation_x(const Radians& angle, const Vector3& center) noexcept;

    /**
     * Returns a matrix that can be used to rotate a set of vertices around the y-axis.
     *
     * @param angle Value that specifies the angle of rotation.
     */
    static Matrix create_rotation_y(const Radians& angle) noexcept;

    /**
     * Creates a matrix for rotating points around the Y-axis, from a center point.
     * @param angle The amount, by which to rotate around the Y-axis.
     * @param center The center point.
     * @returns The rotation matrix.
     */
    static Matrix create_rotation_y(const Radians& angle, const Vector3& center) noexcept;

    /**
     * Returns a matrix that can be used to rotate a set of vertices around the z-axis.
     *
     * @param angle Value that specifies the angle of rotation.
     */
    static Matrix create_rotation_z(const Radians& angle) noexcept;

    /**
     * Creates a matrix for rotating points around the Z-axis, from a center point.
     * @param angle The amount by which to rotate around the Z-axis.
     * @param center The center point.
     * @returns The rotation matrix.
     */
    static Matrix create_rotation_z(const Radians& angle, const Vector3& center) noexcept;

    /**
     * Creates a uniform scaling matrix that scales equally on each axis.
     *
     * @param scale Amount to scale by.
     */
    static Matrix create_scale(float scale) noexcept;

    /**
     * Creates a uniform scaling matrix that scales equally on each axis with a center point.
     *
     * @param scale Amount to scale by.
     * @param center The center point
     */
    static Matrix create_scale(float scale, const Vector3& center) noexcept;

    /**
     * Creates a scaling matrix from the specified vector scale.
     *
     * @param scales Amounts to scale by on the x, y, and z axes.
     */
    static Matrix create_scale(const Vector3& scales) noexcept;

    /**
     * Creates a scaling matrix from the specified X, Y, and Z components.
     *
     * @param xScale The value to scale by on the X axis.
     * @param yScale The value to scale by on the Y axis.
     * @param zScale The value to scale by on the Z axis.
     */
    static Matrix create_scale(float xScale, float yScale, float zScale) noexcept;

    /**
     * Creates a scaling matrix with a center point.
     *
     * @param scales The vector that contains the amount to scale on each axis.
     * @param center The center point
     */
    static Matrix create_scale(const Vector3& scales, const Vector3& center) noexcept;

    /**
     * Creates a scaling matrix that is offset by a given center point.
     *
     * @param xScale The value to scale by on the X axis.
     * @param yScale The value to scale by on the Y axis.
     * @param zScale The value to scale by on the Z axis.
     * @param center The center point.
     */
    static Matrix create_scale(float xScale, float yScale, float zScale, const Vector3& center) noexcept;

    /**
     * Creates a translation Matrix
     *
     * @param position Amounts to translate by on the x, y, and z-axis.
     */
    static Matrix create_translation(const Vector3& position) noexcept;

    /**
     * Creates a translation Matrix
     *
     * @param xPosition Value to translate by on the x-axis.
     * @param yPosition Value to translate by on the y-axis.
     * @param zPosition Value to translate by on the z-axis.
     */
    static Matrix create_translation(float xPosition, float yPosition, float zPosition) noexcept;


    /**
     * @brief Creates a matrix that reflects the coordinate system about a specified plane.
     * @param plane The plane
     * @return A new matrix expressing the reflection.
     */
    static Matrix create_reflection(const Plane& plane) noexcept;

    /**
     * Creates a matrix that flattens geometry into a specified plane as if casting a shadow from a specified light source.
     * @param lightDirection The direction from which the light that will cast the shadow is coming.
     * @param plane The plane onto which the new matrix should flatten geometry so as to cast a shadow.
     * @return A new matrix that can be used to flatten geometry onto the specified plane from the specified direction.
     */
    static Matrix create_shadow(const Vector3& lightDirection, const Plane& plane) noexcept;

    /**
     * Creates a World Matrix
     *
     * @param position Position of the object. This value is used in translation operations.
     * @param forward Forward direction of the object.
     * @param up Upward direction of the object; usually [0, 1, 0].
     */
    static Matrix create_world(const Vector3& position, const Vector3& forward, const Vector3& up) noexcept;

    /**
    * Extracts the scalar, translation, and rotation components from a 3D scale/rotate/translate (SRT) Matrix.
    *
    * @param matrix The source matrix.
    * @param scale The scalar component of the transform matrix, expressed as a Vector3.
    * @param rotation The rotation component of the transform matrix, expressed as a Quaternion.
    * @param translation The translation component of the transform matrix, expressed as a Vector3.
    *
    * @returns true if the Matrix can be decomposed; false otherwise.
    */
    static bool decompose(const Matrix& data, Vector3& scale, Quaternion& rotation, Vector3& translation) noexcept;

    /**
     * Inverts the given Matrix structure.
     * @param matrix the matrix to invert.
     */
    static Matrix invert(const Matrix& data) noexcept;

    /**
    * Negates the given Matrix structure.
    * @param matrix the matrix to negate.
    */
    static Matrix negate(const Matrix& data) noexcept;

    /**
     * Transforms a Matrix by applying a Quaternion rotation.
     *
     * @param value the matrix to transform
     * @param rotation the quaternion rotation
     * @returns thr transformed matrix
     */
    static Matrix transform(const Matrix& value, const Quaternion& rotation) noexcept;

    /**
     * Returns the tranpose of the given matrix.
     * @param source the source matrix.
     * @returns Transposed matrix.
     */
    static Matrix transpose(const Matrix& source) noexcept;

public:
    /**
     * Initializes a new instance of the Matrix class.
     */
    Matrix() noexcept;

    /**
     * Initializes a new instance of the Matrix class with the given initial values.
     *
     * @param m11 Value of the (1,1) field of the new matrix.
     * @param m12 Value of the (1,2) field of the new matrix.
     * @param m13 Value of the (1,3) field of the new matrix.
     * @param m14 Value of the (1,4) field of the new matrix.
     * @param m21 Value of the (2,1) field of the new matrix.
     * @param m22 Value of the (2,2) field of the new matrix.
     * @param m23 Value of the (2,3) field of the new matrix.
     * @param m24 Value of the (2,4) field of the new matrix.
     * @param m31 Value of the (3,1) field of the new matrix.
     * @param m32 Value of the (3,2) field of the new matrix.
     * @param m33 Value of the (3,3) field of the new matrix.
     * @param m34 Value of the (3,4) field of the new matrix.
     * @param m41 Value of the (4,1) field of the new matrix.
     * @param m42 Value of the (4,2) field of the new matrix.
     * @param m43 Value of the (4,3) field of the new matrix.
     * @param m44 Value of the (4,4) field of the new matrix.
     */
    Matrix(float m11, float m12, float m13, float m14
         , float m21, float m22, float m23, float m24
         , float m31, float m32, float m33, float m34
         , float m41, float m42, float m43, float m44) noexcept;

    /**
     * Initializes a new instance of the Vector3 class (Copy constructor)
     *
     * @param matrix The Matrix to be copied.
     */
    Matrix(const Matrix& data) = default;

    /**
     * Destructor
     */
    ~Matrix() = default;

public:
    /**
     * Gets the translation component of this matrix.
     * @returns The translation component of the current instance.
    */
    Vector3 translation() const noexcept;

    /**
     * Sets the translation component of this matrix.
     * @param translation the translation component for this matrix.
    */
    void translation(const Vector3& translation) noexcept;

public:
    /**
     * Retrieves the determinant of this Matrix.
     * @return the determinant of this Matrix.
     */
    float determinant() const noexcept;

    /**
     * Gets a value that indicates whether this Matrix is invertible.
     * @return a value that indicates whether this Matrix is invertible.
     */
    bool has_inverse() const noexcept;

    /**
     * Determines whether this Matrix structure is an identity Matrix.
     * @return a value indicating wheter the current matix is an identity matrix.
     */
    bool is_identity() const noexcept;

    std::string to_string() const noexcept;

public:
    Matrix& operator=(const Matrix& data) = default;

    float& operator[](const std::size_t& index);
    const float& operator[](const std::size_t& index) const;
    bool operator==(const Matrix& data) const;
    bool operator!=(const Matrix& data) const;
    Matrix& operator*=(const Matrix& data);
    Matrix& operator*=(const float& value);
    Matrix& operator+=(const Matrix& data);
    Matrix& operator-=(const Matrix& data);
    const Matrix operator*(const Matrix& data) const;
    const Matrix operator*(const float& value) const;
    const Matrix operator+(const Matrix& data) const;
    const Matrix operator-(const Matrix& data) const;
    const Matrix operator-() const;

private:
    float sub_matrix_determinant();
    Matrix sub_matrix(std::uint32_t row, std::uint32_t column) const;

public:
    union
    {
        float data[16];
        struct
        {
            float m11;
            float m12;
            float m13;
            float m14;
            float m21;
            float m22;
            float m23;
            float m24;
            float m31;
            float m32;
            float m33;
            float m34;
            float m41;
            float m42;
            float m43;
            float m44;
        };
    };
};

}}

#endif  // SCENER_MATH_MATRIX_HPP
