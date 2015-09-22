// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef FRAMEWORK_MATRIX_HPP
#define FRAMEWORK_MATRIX_HPP

#include <cstddef>
#include <cstdint>

#include <Framework/Vector4.hpp>

namespace SceneR
{
    namespace Framework
    {
        struct Plane;
        struct Vector3;
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
            static Matrix create_from_axis_angle(const Vector3& axis, const float& angle);

            /**
             * Creates a rotation Matrix from a Quaternion.
             *
             * @param quaternion Quaternion to create the Matrix from.
             */
            static Matrix create_from_quaternion(const Quaternion& quaternion);

            /**
             * Creates a new matrix with a specified yaw, pitch, and roll.
             * The order of transformations is yaw first, then pitch, then roll
             *
             * @param yaw Yaw around the y-axis, in radians.
             * @param pitch Pitch around the z-axis, in radians.
             * @param roll Roll around the x-axis, in radians.
             */
            static Matrix create_from_yaw_pitch_roll(const float& yaw, const float& pitch, const float& roll);

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
            static Matrix create_frustum(const float& left  , const float& right
                                       , const float& bottom, const float& top
                                       , const float& zNear , const float& zFar);

            /**
             * Creates a view matrix
             *
             * @param cameraPosition The position of the camera.
             * @param cameraTarget The target towards which the camera is pointing.
             * @param cameraUpVector The direction that is "up" from the camera's point of view.
             */
            static Matrix create_look_at(const Vector3& cameraPosition
                                       , const Vector3& cameraTarget
                                       , const Vector3& cameraUpVector);

            /**
             * Creates an orthogonal matrix
             *
             * @param width Width of the view volume.
             * @param height Height of the view volume.
             * @param zNear Minimum z-value of the view volume.
             * @param zFar Maximun z-value of the view volume.
             */
            static Matrix create_orthographic(const float& width
                                            , const float& height
                                            , const float& zNear
                                            , const float& zFar);

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
            static Matrix create_orthographic_off_center(const float& left
                                                       , const float& right
                                                       , const float& bottom
                                                       , const float& top
                                                       , const float& zNear
                                                       , const float& zFar);

            /**
             * Builds a perspective projection matrix.
             *
             * @param width Width of the view volume at the near view plane.
             * @param height Height of the view volume at the near view plane.
             * @param zNear Distance to the near view plane.
             * @param zFar Distance to the far view plane.
             */
            static Matrix create_perspective(const float& width
                                           , const float& height
                                           , const float& zNear
                                           , const float& zFar);

            /**
             * Builds a perspective projection matrix based on a field of view and returns by value.
             *
             * @param fieldOfView Field of view in the y direction, in radians.
             * @param aspectRatio Aspect ratio, defined as view space width divided by height.
             * @param zNear Distance to the near view plane.
             * @param zFar Distance to the far view plane.
             */
            static Matrix create_perspective_field_of_view(const float& fieldOfView
                                                         , const float& aspectRatio
                                                         , const float& zNear
                                                         , const float& zFar);

            /**
             * Builds a customized, right-handed perspective projection matrix.
             * @param left Minimum x-value of the view volume.
             * @param right Maximum x-value of the view volume.
             * @param bottom Minimum y-value of the view volume.
             * @param top Maximum y-value of the view volume.
             * @param zNear Minimum z-value of the view volume.
             * @param zFar Maximun z-value of the view volume.
             */
            static Matrix create_perspective_off_center(const float& left
                                                      , const float& right
                                                      , const float& bottom
                                                      , const float& top
                                                      , const float& zNear
                                                      , const float& zFar);

            /**
             * Returns a matrix that can be used to rotate a set of vertices around the x-axis.
             *
             * @param angle Value that specifies the angle of rotation, in radians.
             */
            static Matrix create_rotation_x(const float& angle);

            /**
             * Creates a matrix for rotating points around the X-axis, from a center point.
             * @param angle The amount, in radians, by which to rotate around the X-axis.
             * @param center The center point.
             * @returns The rotation matrix.
             */
            static Matrix create_rotation_x(const float& angle, const Vector3& center);

            /**
             * Returns a matrix that can be used to rotate a set of vertices around the y-axis.
             *
             * @param angle Value that specifies the angle of rotation, in radians.
             */
            static Matrix create_rotation_y(const float& angle);

            /**
             * Creates a matrix for rotating points around the Y-axis, from a center point.
             * @param angle The amount, in radians, by which to rotate around the Y-axis.
             * @param center The center point.
             * @returns The rotation matrix.
             */
            static Matrix create_rotation_y(const float& angle, const Vector3& center);

            /**
             * Returns a matrix that can be used to rotate a set of vertices around the z-axis.
             *
             * @param angle Value that specifies the angle of rotation, in radians.
             */
            static Matrix create_rotation_z(const float& angle);

            /**
             * Creates a matrix for rotating points around the Z-axis, from a center point.
             * @param angle The amount, in radians, by which to rotate around the Z-axis.
             * @param center The center point.
             * @returns The rotation matrix.
             */
            static Matrix create_rotation_z(const float& angle, const Vector3& center);

            /**
             * Creates a uniform scaling matrix that scales equally on each axis.
             *
             * @param scale Amount to scale by.
             */
            static Matrix create_scale(const float& scale);

            /**
             * Creates a uniform scaling matrix that scales equally on each axis with a center point.
             *
             * @param scale Amount to scale by.
             * @param center The center point
             */
            static Matrix create_scale(const float& scale, const Vector3& center);

            /**
             * Creates a scaling matrix from the specified vector scale.
             *
             * @param scales Amounts to scale by on the x, y, and z axes.
             */
            static Matrix create_scale(const Vector3& scales);

            /**
             * Creates a scaling matrix from the specified X, Y, and Z components.
             *
             * @param xScale The value to scale by on the X axis.
             * @param yScale The value to scale by on the Y axis.
             * @param zScale The value to scale by on the Z axis.
             */
            static Matrix create_scale(const float& xScale, const float& yScale, const float& zScale);

            /**
             * Creates a scaling matrix with a center point.
             *
             * @param scales The vector that contains the amount to scale on each axis.
             * @param center The center point
             */
            static Matrix create_scale(const Vector3& scales, const Vector3& center);

            /**
             * Creates a scaling matrix that is offset by a given center point.
             *
             * @param xScale The value to scale by on the X axis.
             * @param yScale The value to scale by on the Y axis.
             * @param zScale The value to scale by on the Z axis.
             * @param center The center point.
             */
            static Matrix create_scale(const float& xScale
                                     , const float& yScale
                                     , const float& zScale
                                     , const Vector3& center);

            /**
             * Creates a translation Matrix
             *
             * @param position Amounts to translate by on the x, y, and z-axis.
             */
            static Matrix create_translation(const Vector3& position);

            /**
             * Creates a translation Matrix
             *
             * @param xPosition Value to translate by on the x-axis.
             * @param yPosition Value to translate by on the y-axis.
             * @param zPosition Value to translate by on the z-axis.
             */
            static Matrix create_translation(const float& xPosition, const float& yPosition, const float& zPosition);


            /**
             * @brief Creates a matrix that reflects the coordinate system about a specified plane.
             * @param plane The plane
             * @return A new matrix expressing the reflection.
             */
            static Matrix create_reflection(const Plane& plane);

            /**
             * Creates a matrix that flattens geometry into a specified plane as if casting a shadow from a specified light source.
             * @param lightDirection The direction from which the light that will cast the shadow is coming.
             * @param plane The plane onto which the new matrix should flatten geometry so as to cast a shadow.
             * @return A new matrix that can be used to flatten geometry onto the specified plane from the specified direction.
             */
            static Matrix create_shadow(const Vector3& lightDirection, const Plane& plane);

            /**
             * Creates a World Matrix
             *
             * @param position Position of the object. This value is used in translation operations.
             * @param forward Forward direction of the object.
             * @param up Upward direction of the object; usually [0, 1, 0].
             */
            static Matrix create_world(const Vector3& position, const Vector3& forward, const Vector3& up);

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
            static bool decompose(const Matrix& data, Vector3& scale, Quaternion& rotation, Vector3& translation);

            /**
             * Inverts the given Matrix structure.
             * @param matrix the matrix to invert.
             */
            static Matrix invert(const Matrix& data);

            /**
            * Negates the given Matrix structure.
            * @param matrix the matrix to negate.
            */
            static Matrix negate(const Matrix& data);

            /**
             * Transforms a Matrix by applying a Quaternion rotation.
             *
             * @param value the matrix to transform
             * @param rotation the quaternion rotation
             * @returns thr transformed matrix
             */
            static Matrix transform(const Matrix& value, const Quaternion& rotation);

            /**
             * Returns the tranpose of the given matrix.
             * @param source the source matrix.
             * @returns Transposed matrix.
             */
            static Matrix transpose(const Matrix& source);

        public:
            /**
             * Initializes a new instance of the Matrix class.
             */
            Matrix();

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
            Matrix(const float& m11, const float& m12, const float& m13, const float& m14
                 , const float& m21, const float& m22, const float& m23, const float& m24
                 , const float& m31, const float& m32, const float& m33, const float& m34
                 , const float& m41, const float& m42, const float& m43, const float& m44);

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
            Vector3 translation() const;

            /**
             * Sets the translation component of this matrix.
             * @param translation the translation component for this matrix.
            */
            void translation(const Vector3& translation);

        public:
            /**
             * Retrieves the determinant of this Matrix.
             * @return the determinant of this Matrix.
             */
            float determinant() const;

            /**
             * Gets a value that indicates whether this Matrix is invertible.
             * @return a value that indicates whether this Matrix is invertible.
             */
            bool has_inverse() const;

            /**
             * Determines whether this Matrix structure is an identity Matrix.
             * @return a value indicating wheter the current matix is an identity matrix.
             */
            bool is_identity() const;

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
            Matrix sub_matrix(const std::uint32_t& row, const std::uint32_t& column) const;

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
    }
}

#endif  // FRAMEWORK_MATRIX_HPP
