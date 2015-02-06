// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <System/Core.hpp>

namespace SceneR
{
    namespace Framework
    {
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
            static const Matrix& Identity;

        public:
            /**
             * Creates a new Matrix that rotates around an arbitrary axis.
             *
             * @param axis Vector3 that specifies the axis around which to rotate.
             * @param angle Value that specifies the angle of rotation, in radians.
             */
            static Matrix CreateFromAxisAngle(const Vector3& axis, const System::Single& angle);

            /**
             * Creates a rotation Matrix from a Quaternion.
             *
             * @param quaternion Quaternion to create the Matrix from.
             */
            static Matrix CreateFromQuaternion(const Quaternion& quaternion);

            /**
             * Creates a new matrix with a specified yaw, pitch, and roll.
             * The order of transformations is yaw first, then pitch, then roll
             *
             * @param yaw Yaw around the y-axis, in radians.
             * @param pitch Pitch around the z-axis, in radians.
             * @param roll Roll around the x-axis, in radians.
             */
            static Matrix CreateFromYawPitchRoll(const System::Single& yaw
                                               , const System::Single& pitch
                                               , const System::Single& roll);

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
            static Matrix CreateFrustum(const System::Single& left  , const System::Single& right
                                      , const System::Single& bottom, const System::Single& top
                                      , const System::Single& zNear , const System::Single& zFar);

            /**
             * Creates a view matrix
             *
             * @param cameraPosition The position of the camera.
             * @param cameraTarget The target towards which the camera is pointing.
             * @param cameraUpVector The direction that is "up" from the camera's point of view.
             */
            static Matrix CreateLookAt(const Vector3& cameraPosition
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
            static Matrix CreateOrthographic(const System::Single& width
                                           , const System::Single& height
                                           , const System::Single& zNear
                                           , const System::Single& zFar);

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
            static Matrix CreateOrthographicOffCenter(const System::Single& left
                                                    , const System::Single& right
                                                    , const System::Single& bottom
                                                    , const System::Single& top
                                                    , const System::Single& zNear
                                                    , const System::Single& zFar);

            /**
             * Builds a perspective projection matrix.
             *
             * @param width Width of the view volume at the near view plane.
             * @param height Height of the view volume at the near view plane.
             * @param zNear Distance to the near view plane.
             * @param zFar Distance to the far view plane.
             */
            static Matrix CreatePerspective(const System::Single& width
                                          , const System::Single& height
                                          , const System::Single& zNear
                                          , const System::Single& zFar);

            /**
             * Builds a perspective projection matrix based on a field of view and returns by value.
             *
             * @param fieldOfView Field of view in the y direction, in radians.
             * @param aspectRatio Aspect ratio, defined as view space width divided by height.
             * @param zNear Distance to the near view plane.
             * @param zFar Distance to the far view plane.
             */
            static Matrix CreatePerspectiveFieldOfView(const System::Single& fieldOfView
                                                     , const System::Single& aspectRatio
                                                     , const System::Single& zNear
                                                     , const System::Single& zFar);

            /**
             * Returns a matrix that can be used to rotate a set of vertices around the x-axis.
             *
             * @param angle Value that specifies the angle of rotation, in radians.
             */
            static Matrix CreateRotationX(const System::Single& angle);

            /**
             * Returns a matrix that can be used to rotate a set of vertices around the y-axis.
             *
             * @param angle Value that specifies the angle of rotation, in radians.
             */
            static Matrix CreateRotationY(const System::Single& angle);

            /**
             * Returns a matrix that can be used to rotate a set of vertices around the z-axis.
             *
             * @param angle Value that specifies the angle of rotation, in radians.
             */
            static Matrix CreateRotationZ(const System::Single& angle);

            /**
             * Creates a scaling Matrix.
             *
             * @param scale Amount to scale by.
             */
            static Matrix CreateScale(const System::Single& scale);

            /**
             * Creates a scaling Matrix
             *
             * @param scales Amounts to scale by on the x, y, and z axes.
             */
            static Matrix CreateScale(const Vector3& scales);

            /**
             * Creates a scaling Matrix
             *
             * @param xScale Value to scale by on the x-axis
             * @param yScale Value to scale by on the y-axis
             * @param zScale Value to scale by on the z-axis
             */
            static Matrix CreateScale(const System::Single& xScale
                                    , const System::Single& yScale
                                    , const System::Single& zScale);

            /**
             * Creates a translation Matrix
             *
             * @param position Amounts to translate by on the x, y, and z-axis.
             */
            static Matrix CreateTranslation(const Vector3& position);

            /**
             * Creates a translation Matrix
             *
             * @param xPosition Value to translate by on the x-axis.
             * @param yPosition Value to translate by on the y-axis.
             * @param zPosition Value to translate by on the z-axis.
             */
            static Matrix CreateTranslation(const System::Single& xPosition
                                          , const System::Single& yPosition
                                          , const System::Single& zPosition);

            /**
             * Creates a World Matrix
             *
             * @param position Position of the object. This value is used in translation operations.
             * @param forward Forward direction of the object.
             * @param up Upward direction of the object; usually [0, 1, 0].
             */
            static Matrix CreateWorld(const Vector3& position, const Vector3& forward, const Vector3& up);

            /**
             * Inverts the given Matrix structure.
             * @param matrix the matrix to invert.
             */
            static Matrix Invert(const Matrix& matrix);

            /**
             * Transforms a Matrix by applying a Quaternion rotation.
             *
             * @param value the matrix to transform
             * @param rotation the quaternion rotation
             * @returns thr transformed matrix
             */
            static Matrix Transform(const Matrix& value, const Quaternion& rotation);

            /**
             * Returns the tranpose of the given matrix.
             * @param matrix the source matrix.
             * @returns Transposed matrix.
             */
            static Matrix Transpose(const Matrix& source);

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
            Matrix(const System::Single& m11, const System::Single& m12, const System::Single& m13, const System::Single& m14
                 , const System::Single& m21, const System::Single& m22, const System::Single& m23, const System::Single& m24
                 , const System::Single& m31, const System::Single& m32, const System::Single& m33, const System::Single& m34
                 , const System::Single& m41, const System::Single& m42, const System::Single& m43, const System::Single& m44);

            /**
             * Initializes a new instance of the Vector3 class (Copy constructor)
             *
             * @param matrix The Matrix to be copied.
             */
            Matrix(const Matrix& matrix);

            /**
             * Default destructor
             */
            ~Matrix() = default;

        public:
            /**
             * Gets the value of the first row and first column of this Matrix.
             * @return the value of the first row and first column of this Matrix.
             */
            const System::Single& M11() const;

            /**
             * Gets the value of the first row and second column of this Matrix.
             * @return the value of the first row and second column of this Matrix.
             */
            const System::Single& M12() const;

            /**
             * Gets the value of the first row and third column of this Matrix.
             * @return the value of the first row and third column of this Matrix.
             */
            const System::Single& M13() const;

            /**
             * Gets the value of the first row and fourth column of this Matrix
             * @return the value of the first row and fourth column of this Matrix
             */
            const System::Single& M14() const;

            /**
             * Gets the value of the second row and first column of this Matrix
             * @return the value of the second row and first column of this Matrix
             */
            const System::Single& M21() const;

            /**
             * Gets the value of the second row and second column of this Matrix
             * @return the value of the second row and second column of this Matrix
             */
            const System::Single& M22() const;

            /**
             * Gets the value of the second row and third column of this Matrix
             * @return the value of the second row and third column of this Matrix
             */
            const System::Single& M23() const;

            /**
             * Gets the value of the second row and fourth column of this Matrix
             * @return the value of the second row and fourth column of this Matrix
             */
            const System::Single& M24() const;

            /**
             * Gets the value of the third row and first column of this Matrix
             * @return the value of the third row and first column of this Matrix
             */
            const System::Single& M31() const;

            /**
             * Gets the value of the third row and second column of this Matrix
             * @return the value of the third row and second column of this Matrix
             */
            const System::Single& M32() const;

            /**
             * Gets the value of the third row and third column of this Matrix
             * @return the value of the third row and third column of this Matrix
             */
            const System::Single& M33() const;

            /**
             * Gets the value of the third row and fourth column of this Matrix
             * @return the value of the third row and fourth column of this Matrix
             */
            const System::Single& M34() const;

            /**
             * Gets the value of the fourth row and first column of this Matrix
             * @return the value of the fourth row and first column of this Matrix
             */
            const System::Single& M41() const;

            /**
             * Gets the value of the fourth row and second column of this Matrix
             * @return the value of the fourth row and second column of this Matrix
             */
            const System::Single& M42() const;

            /**
             * Gets the value of the fourth row and third column of this Matrix
             * @return the value of the fourth row and third column of this Matrix
             */
            const System::Single& M43() const;

            /**
             * Gets the value of the fourth row and fourth column of this Matrix
             * @return the value of the fourth row and fourth column of this Matrix
             */
            const System::Single& M44() const;

        public:
            /**
             * Sets the value of the first row and first column of this Matrix.
             */
            void M11(const System::Single& value);

            /**
             * Sets the value of the first row and second column of this Matrix.
             */
            void M12(const System::Single& value);

            /**
             * Sets the value of the first row and third column of this Matrix.
             */
            void M13(const System::Single& value);

            /**
             * Sets the value of the first row and fourth column of this Matrix
             */
            void M14(const System::Single& value);

            /**
             * Sets the value of the second row and first column of this Matrix
             */
            void M21(const System::Single& value);

            /**
             * Sets the value of the second row and second column of this Matrix
             */
            void M22(const System::Single& value);

            /**
             * Gets the value of the second row and third column of this Matrix
             */
            void M23(const System::Single& value);

            /**
             * Sets the value of the second row and fourth column of this Matrix
             */
            void M24(const System::Single& value);

            /**
             * Sets the value of the third row and first column of this Matrix
             */
            void M31(const System::Single& value);

            /**
             * Sets the value of the third row and second column of this Matrix
             */
            void M32(const System::Single& value);

            /**
            * Gets the value of the third row and third column of this Matrix
            * @return the value of the third row and third column of this Matrix
            */
            void M33(const System::Single& value);

            /**
             * Gets the value of the third row and fourth column of this Matrix
             * @return the value of the third row and fourth column of this Matrix
             */
            void M34(const System::Single& value);

            /**
             * Sets the value of the fourth row and first column of this Matrix
             */
            void M41(const System::Single& value);

            /**
             * Sets the value of the fourth row and second column of this Matrix
             */
            void M42(const System::Single& value);

            /**
             * Sets the value of the fourth row and third column of this Matrix
             */
            void M43(const System::Single& value);

            /**
             * Sets the value of the fourth row and fourth column of this Matrix
             */
            void M44(const System::Single& value);

        public:
            /**
             * Extracts the scalar, translation, and rotation components from a 3D scale/rotate/translate (SRT) Matrix.
             *
             * @param scale The scalar component of the transform matrix, expressed as a Vector3.
             * @param rotation The rotation component of the transform matrix, expressed as a Quaternion.
             * @param translation The translation component of the transform matrix, expressed as a Vector3.
             *
             * @returns true if the Matrix can be decomposed; false otherwise.
             */
            bool Decompose(Vector3& scale, Quaternion& rotation, Vector3& translation);

            /**
             * Retrieves the determinant of this Matrix.
             * @return the determinant of this Matrix.
             */
            System::Single Determinant() const;

            /**
             * Gets a value that indicates whether this Matrix is invertible.
             * @return a value that indicates whether this Matrix is invertible.
             */
            bool HasInverse() const;

            /**
             * Inverts this Matrix structure.
             */
            void Invert();

            /**
             * Determines whether this Matrix structure is an identity Matrix.
             * @return a value indicating wheter the current matix is an identity matrix.
             */
            bool IsIdentity() const;

            /**
             * Transposes this Matrix structure.
             */
            void Transpose();

        public:
            System::Single& operator[](const System::Size& index);
            const System::Single& operator[](const System::Size& index) const;
            bool operator==(const Matrix& matrix) const;
            bool operator!=(const Matrix& matrix) const;
            Matrix& operator*=(const Matrix& matrix);
            const Matrix operator*(const Matrix& matrix) const;

        private:
            System::Single SubMatrixDeterminant();
            Matrix SubMatrix(const System::UInt32& row, const System::UInt32& column) const;

        private:
            union
            {
                System::Single matrix[16];
                struct
                {
                    System::Single m11;
                    System::Single m12;
                    System::Single m13;
                    System::Single m14;
                    System::Single m21;
                    System::Single m22;
                    System::Single m23;
                    System::Single m24;
                    System::Single m31;
                    System::Single m32;
                    System::Single m33;
                    System::Single m34;
                    System::Single m41;
                    System::Single m42;
                    System::Single m43;
                    System::Single m44;
                };
            };
        };
    }
}

#endif  /* MATRIX_HPP */
