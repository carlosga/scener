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

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <System/Core.hpp>

namespace SceneR
{
    namespace Framework
    {
        class Vector3;
        class Quaternion;

        /**
         * Represents a 4 x 4 matrix.
         */
        class Matrix
        {
        public:
            /**
             * Returns the identity matrix.
             */
            static const Matrix Identity;

        public:
            /**
             * Creates a new Matrix that rotates around an arbitrary axis.
             *
             * @param axis Vector3 that specifies the axis around which to rotate.
             * @param angle Value that specifies the angle of rotation, in degrees.
             */
            static Matrix CreateFromAxisAngle(const Vector3& axis, const Single& angle);

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
             * @param yaw Yaw around the y-axis, in degrees.
             * @param pitch Pitch around the z-axis, in degrees.
             * @param roll Roll around the x-axis, in degrees.
             */
            static Matrix CreateFromYawPitchRoll(const Single& yaw, const Single& pitch, const Single& roll);

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
            static Matrix CreateFrustum(const Single& left  , const Single& right,
                                        const Single& bottom, const Single& top,
                                        const Single& zNear , const Single& zFar);

            /**
             * Creates a view matrix
             *
             * @param cameraPosition The position of the camera.
             * @param cameraTarget The target towards which the camera is pointing.
             * @param cameraUpVector The direction that is "up" from the camera's point of view.
             */
            static Matrix CreateLookAt(const Vector3& cameraPosition,
                                       const Vector3& cameraTarget,
                                       const Vector3& cameraUpVector);

            /**
             * Creates an orthogonal matrix
             *
             * @param width Width of the view volume.
             * @param height Height of the view volume.
             * @param zNear Minimum z-value of the view volume.
             * @param zFar Maximun z-value of the view volume.
             */
            static Matrix CreateOrthographic(const Single& width,
                                             const Single& height,
                                             const Single& zNear,
                                             const Single& zFar);

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
            static Matrix CreateOrthographicOffCenter(const Single& left,
                                                      const Single& right,
                                                      const Single& bottom,
                                                      const Single& top,
                                                      const Single& zNear,
                                                      const Single& zFar);

            /**
             * Builds a perspective projection matrix.
             *
             * @param width Width of the view volume at the near view plane.
             * @param height Height of the view volume at the near view plane.
             * @param zNear Distance to the near view plane.
             * @param zFar Distance to the far view plane.
             */
            static Matrix CreatePerspective(const Single& width,
                                            const Single& height,
                                            const Single& zNear,
                                            const Single& zFar);

            /**
             * Builds a perspective projection matrix based on a field of view and returns by value.
             *
             * @param fieldOfView Field of view in the y direction, in degrees.
             * @param aspectRatio Aspect ratio, defined as view space width divided by height.
             * @param zNear Distance to the near view plane.
             * @param zFar Distance to the far view plane.
             */
            static Matrix CreatePerspectiveFieldOfView(const Single& fieldOfView,
                                                       const Single& aspectRatio,
                                                       const Single& zNear,
                                                       const Single& zFar);

            /**
             * Returns a matrix that can be used to rotate a set of vertices around the x-axis.
             *
             * @param angle Value that specifies the angle of rotation, in degrees.
             */
            static Matrix CreateRotationX(const Single& angle);

            /**
             * Returns a matrix that can be used to rotate a set of vertices around the y-axis.
             *
             * @param angle Value that specifies the angle of rotation, in degrees.
             */
            static Matrix CreateRotationY(const Single& angle);

            /**
             * Returns a matrix that can be used to rotate a set of vertices around the z-axis.
             *
             * @param angle Value that specifies the angle of rotation, in degrees.
             */
            static Matrix CreateRotationZ(const Single& angle);

            /**
             * Creates a scaling Matrix.
             *
             * @param scale Amount to scale by.
             */
            static Matrix CreateScale(const Single& scale);

            /**
             * Creates a scaling Matrix
             *
             * @param xScale Value to scale by on the x-axis
             * @param yScale Value to scale by on the y-axis
             * @param zScale Value to scale by on the z-axis
             */
            static Matrix CreateScale(const Single& xScale,
                                      const Single& yScale,
                                      const Single& zScale);

            /**
             * Creates a scaling Matrix
             *
             * @param scales Amounts to scale by on the x, y, and z axes.
             */
            static Matrix CreateScale(const Vector3& scales);

            /**
             * Creates a translation Matrix
             *
             * @param xPosition Value to translate by on the x-axis.
             * @param yPosition Value to translate by on the y-axis.
             * @param zPosition Value to translate by on the z-axis.
             */
            static Matrix CreateTranslation(const Single& xPosition,
                                            const Single& yPosition,
                                            const Single& zPosition);

            /**
             * Creates a translation Matrix
             *
             * @param position Amounts to translate by on the x, y, and z-axis.
             */
            static Matrix CreateTranslation(const Vector3& position);

            /**
             * Creates a World Matrix
             *
             * @param position Position of the object. This value is used in translation operations.
             * @param forward Forward direction of the object.
             * @param up Upward direction of the object; usually [0, 1, 0].
             */
            static Matrix CreateWorld(const Vector3& position,
                                      const Vector3& forward,
                                      const Vector3& up);

            /**
             * Transforms a Matrix by applying a Quaternion rotation.
             *
             * @param value the matrix to transform
             * @param rotation the quaternion rotation
             * @returns thr transformed matrix
             */
            static Matrix Transform(const Matrix& value,
                                    const Quaternion& rotation);

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
            Matrix(const Single& m11, const Single& m12, const Single& m13, const Single& m14,
                   const Single& m21, const Single& m22, const Single& m23, const Single& m24,
                   const Single& m31, const Single& m32, const Single& m33, const Single& m34,
                   const Single& m41, const Single& m42, const Single& m43, const Single& m44);

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
            const Single& M11() const;

            /**
             * Gets the value of the first row and second column of this Matrix.
             * @return the value of the first row and second column of this Matrix.
             */
            const Single& M12() const;

            /**
             * Gets the value of the first row and third column of this Matrix.
             * @return the value of the first row and third column of this Matrix.
             */
            const Single& M13() const;

            /**
             * Gets the value of the first row and fourth column of this Matrix
             * @return the value of the first row and fourth column of this Matrix
             */
            const Single& M14() const;

            /**
             * Gets the value of the second row and first column of this Matrix
             * @return the value of the second row and first column of this Matrix
             */
            const Single& M21() const;

            /**
             * Gets the value of the second row and second column of this Matrix
             * @return the value of the second row and second column of this Matrix
             */
            const Single& M22() const;

            /**
             * Gets the value of the second row and third column of this Matrix
             * @return the value of the second row and third column of this Matrix
             */
            const Single& M23() const;

            /**
             * Gets the value of the second row and fourth column of this Matrix
             * @return the value of the second row and fourth column of this Matrix
             */
            const Single& M24() const;

            /**
             * Gets the value of the third row and first column of this Matrix
             * @return the value of the third row and first column of this Matrix
             */
            const Single& M31() const;

            /**
             * Gets the value of the third row and second column of this Matrix
             * @return the value of the third row and second column of this Matrix
             */
            const Single& M32() const;

            /**
             * Gets the value of the third row and third column of this Matrix
             * @return the value of the third row and third column of this Matrix
             */
            const Single& M33() const;

            /**
             * Gets the value of the third row and fourth column of this Matrix
             * @return the value of the third row and fourth column of this Matrix
             */
            const Single& M34() const;

            /**
             * Gets the value of the fourth row and first column of this Matrix
             * @return the value of the fourth row and first column of this Matrix
             */
            const Single& M41() const;

            /**
             * Gets the value of the fourth row and second column of this Matrix
             * @return the value of the fourth row and second column of this Matrix
             */
            const Single& M42() const;

            /**
             * Gets the value of the fourth row and third column of this Matrix
             * @return the value of the fourth row and third column of this Matrix
             */
            const Single& M43() const;

            /**
             * Gets the value of the fourth row and fourth column of this Matrix
             * @return the value of the fourth row and fourth column of this Matrix
             */
            const Single& M44() const;

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
            const Single Determinant() const;

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
            Single& operator[](const UInt32& index);
            const Single& operator[](const UInt32& index) const;
            bool operator==(const Matrix &matrix) const;
            bool operator!=(const Matrix &matrix) const;
            Matrix& operator*=(const Matrix &matrix);
            const Matrix operator*(const Matrix &matrix) const;

        private:
            Single SubMatrixDeterminant();
            Matrix SubMatrix(const UInt32& row, const UInt32& column) const;

        private:
            union
            {
                Single matrix[16];
                struct
                {
                    Single m11;
                    Single m12;
                    Single m13;
                    Single m14;
                    Single m21;
                    Single m22;
                    Single m23;
                    Single m24;
                    Single m31;
                    Single m32;
                    Single m33;
                    Single m34;
                    Single m41;
                    Single m42;
                    Single m43;
                    Single m44;
                };
            };
        };
    }
}

#endif  /* MATRIX_HPP */
