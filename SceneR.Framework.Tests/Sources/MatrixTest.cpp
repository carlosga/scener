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

#include <MatrixTest.hpp>

#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Framework/MathHelper.hpp>

using namespace System;
using namespace SceneR::Framework;

TEST_F(MatrixTest, DefaultConstructor)
{
    auto matrix = Matrix { };

    EXPECT_TRUE(0.0f == matrix.M11());
    EXPECT_TRUE(0.0f == matrix.M12());
    EXPECT_TRUE(0.0f == matrix.M13());
    EXPECT_TRUE(0.0f == matrix.M14());
    EXPECT_TRUE(0.0f == matrix.M21());
    EXPECT_TRUE(0.0f == matrix.M22());
    EXPECT_TRUE(0.0f == matrix.M23());
    EXPECT_TRUE(0.0f == matrix.M24());
    EXPECT_TRUE(0.0f == matrix.M31());
    EXPECT_TRUE(0.0f == matrix.M32());
    EXPECT_TRUE(0.0f == matrix.M33());
    EXPECT_TRUE(0.0f == matrix.M34());
    EXPECT_TRUE(0.0f == matrix.M41());
    EXPECT_TRUE(0.0f == matrix.M42());
    EXPECT_TRUE(0.0f == matrix.M43());
    EXPECT_TRUE(0.0f == matrix.M44());
}

TEST_F(MatrixTest, MatrixConstructor)
{
    auto matrix = Matrix { 10.0f, 10.0f, 10.0f, 0.0f
                         , 20.0f, 20.0f, 20.0f, 0.0f
                         , 30.0f, 30.0f, 30.0f, 0.0f
                         , 5.0f , 10.0f, 15.0f, 1.0f };

    EXPECT_TRUE(10.0f == matrix.M11());
    EXPECT_TRUE(10.0f == matrix.M12());
    EXPECT_TRUE(10.0f == matrix.M13());
    EXPECT_TRUE(0.0f  == matrix.M14());
    EXPECT_TRUE(20.0f == matrix.M21());
    EXPECT_TRUE(20.0f == matrix.M22());
    EXPECT_TRUE(20.0f == matrix.M23());
    EXPECT_TRUE(0.0f  == matrix.M24());
    EXPECT_TRUE(30.0f == matrix.M31());
    EXPECT_TRUE(30.0f == matrix.M32());
    EXPECT_TRUE(30.0f == matrix.M33());
    EXPECT_TRUE(0.0f  == matrix.M34());
    EXPECT_TRUE(5.0f  == matrix.M41());
    EXPECT_TRUE(10.0f == matrix.M42());
    EXPECT_TRUE(15.0f == matrix.M43());
    EXPECT_TRUE(1.0f  == matrix.M44());
}

TEST_F(MatrixTest, CopyConstuctor)
{
    auto matrix = Matrix { 10.0f, 10.0f, 10.0f, 0.0f
                         , 20.0f, 20.0f, 20.0f, 0.0f
                         , 30.0f, 30.0f, 30.0f, 0.0f
                         , 5.0f , 10.0f, 15.0f, 1.0f };

    auto matrix1 = Matrix { matrix };

    EXPECT_TRUE(matrix.M11() == matrix1.M11());
    EXPECT_TRUE(matrix.M12() == matrix1.M12());
    EXPECT_TRUE(matrix.M13() == matrix1.M13());
    EXPECT_TRUE(matrix.M14() == matrix1.M14());
    EXPECT_TRUE(matrix.M21() == matrix1.M21());
    EXPECT_TRUE(matrix.M22() == matrix1.M22());
    EXPECT_TRUE(matrix.M23() == matrix1.M23());
    EXPECT_TRUE(matrix.M24() == matrix1.M24());
    EXPECT_TRUE(matrix.M31() == matrix1.M31());
    EXPECT_TRUE(matrix.M32() == matrix1.M32());
    EXPECT_TRUE(matrix.M33() == matrix1.M33());
    EXPECT_TRUE(matrix.M34() == matrix1.M34());
    EXPECT_TRUE(matrix.M41() == matrix1.M41());
    EXPECT_TRUE(matrix.M42() == matrix1.M42());
    EXPECT_TRUE(matrix.M43() == matrix1.M43());
    EXPECT_TRUE(matrix.M44() == matrix1.M44());
}

TEST_F(MatrixTest, MatrixMultiplication)
{
    auto matrix1 = Matrix { 1.0f, 2.0f, 3.0f, 4.0f
                          , 5.0f, 6.0f, 7.0f, 8.0f
                          , 1.0f, 2.0f, 3.0f, 4.0f
                          , 5.0f, 6.0f, 7.0f, 8.0f };
    auto matrix2 = Matrix { 1.0f, 2.0f, 3.0f, 4.0f
                          , 5.0f, 6.0f, 7.0f, 8.0f
                          , 1.0f, 2.0f, 3.0f, 4.0f
                          , 5.0f, 6.0f, 7.0f, 8.0f };

    auto result = matrix1 * matrix2;

	// 34  44  54  64
	// 82 108 134 160
	// 34  44  54  64
	// 82 108 134 160

    EXPECT_TRUE(34.0f  == result.M11());
    EXPECT_TRUE(44.0f  == result.M12());
    EXPECT_TRUE(54.0f  == result.M13());
    EXPECT_TRUE(64.0f  == result.M14());
    EXPECT_TRUE(82.0f  == result.M21());
    EXPECT_TRUE(108.0f == result.M22());
    EXPECT_TRUE(134.0f == result.M23());
    EXPECT_TRUE(160.0f == result.M24());
    EXPECT_TRUE(34.0f  == result.M31());
    EXPECT_TRUE(44.0f  == result.M32());
    EXPECT_TRUE(54.0f  == result.M33());
    EXPECT_TRUE(64.0f  == result.M34());
    EXPECT_TRUE(82.0f  == result.M41());
    EXPECT_TRUE(108.0f == result.M42());
    EXPECT_TRUE(134.0f == result.M43());
    EXPECT_TRUE(160.0f == result.M44());
}

TEST_F(MatrixTest, MatrixTranspose)
{
    auto matrix = Matrix { 1.0f, 0.0f, 0.0f, 10.0f
                         , 0.0f, 1.0f, 0.0f, 10.0f
                         , 0.0f, 0.0f, 1.0f, 10.0f
                         , 0.0f, 0.0f, 0.0f, 1.0f };

    matrix.Transpose();

    EXPECT_TRUE(1.0f  == matrix.M11());
    EXPECT_TRUE(0.0f  == matrix.M12());
    EXPECT_TRUE(0.0f  == matrix.M13());
    EXPECT_TRUE(0.0f  == matrix.M14());
    EXPECT_TRUE(0.0f  == matrix.M21());
    EXPECT_TRUE(1.0f  == matrix.M22());
    EXPECT_TRUE(0.0f  == matrix.M23());
    EXPECT_TRUE(0.0f  == matrix.M24());
    EXPECT_TRUE(0.0f  == matrix.M31());
    EXPECT_TRUE(0.0f  == matrix.M32());
    EXPECT_TRUE(1.0f  == matrix.M33());
    EXPECT_TRUE(0.0f  == matrix.M34());
    EXPECT_TRUE(10.0f == matrix.M41());
    EXPECT_TRUE(10.0f == matrix.M42());
    EXPECT_TRUE(10.0f == matrix.M43());
    EXPECT_TRUE(1.0f  == matrix.M44());
}

TEST_F(MatrixTest, Determinant)
{
    auto matrix = Matrix { 2.0f, 3.0f, 4.0f , 0.0f
                         , 1.0f, 2.0f, -3.0f, 0.0f
                         , 1.0f, 1.0f, 5.0f , 0.0f
                         , 0.0f, 0.0f, 0.0f , 1.0f };

    EXPECT_TRUE(-2.0f == matrix.Determinant());
}

TEST_F(MatrixTest, Inverse)
{
    auto matrix = Matrix { 2.0f, 3.0f, 4.0f , 0.0f
                         , 1.0f, 2.0f, -3.0f, 0.0f
                         , 1.0f, 1.0f, 5.0f , 0.0f
                         , 0.0f, 0.0f, 0.0f , 1.0f };

    matrix.Invert();

    EXPECT_TRUE(-6.5f == matrix.M11());
    EXPECT_TRUE(05.5f == matrix.M12());
    EXPECT_TRUE(08.5f == matrix.M13());
    EXPECT_TRUE(00.0f == matrix.M14());
    EXPECT_TRUE(04.0f == matrix.M21());
    EXPECT_TRUE(-3.0f == matrix.M22());
    EXPECT_TRUE(-5.0f == matrix.M23());
    EXPECT_TRUE(00.0f == matrix.M24());
    EXPECT_TRUE(00.5f == matrix.M31());
    EXPECT_TRUE(-0.5f == matrix.M32());
    EXPECT_TRUE(-0.5f == matrix.M33());
    EXPECT_TRUE(00.0f == matrix.M34());
    EXPECT_TRUE(00.0f == matrix.M41());
    EXPECT_TRUE(00.0f == matrix.M42());
    EXPECT_TRUE(00.0f == matrix.M43());
    EXPECT_TRUE(01.0f == matrix.M44());
}

TEST_F(MatrixTest, CreateFromYawPitchRoll)
{
    Single yaw   = 0.0f;
    Single pitch = 0.0f;
    Single roll  = MathHelper::PiOver2;

    auto matrix = Matrix::CreateFromYawPitchRoll(yaw, pitch, roll);

    EXPECT_TRUE(1.0f  == matrix.M11());
    EXPECT_TRUE(0.0f  == matrix.M12());
    EXPECT_TRUE(0.0f  == matrix.M13());
    EXPECT_TRUE(0.0f  == matrix.M14());
    EXPECT_TRUE(0.0f  == matrix.M21());
    EXPECT_TRUE(0.0f  == matrix.M22());
    EXPECT_TRUE(-1.0f == matrix.M23());
    EXPECT_TRUE(0.0f  == matrix.M24());
    EXPECT_TRUE(0.0f  == matrix.M31());
    EXPECT_TRUE(1.0f  == matrix.M32());
    EXPECT_TRUE(0.0f  == matrix.M33());
    EXPECT_TRUE(0.0f  == matrix.M34());
    EXPECT_TRUE(0.0f  == matrix.M41());
    EXPECT_TRUE(0.0f  == matrix.M42());
    EXPECT_TRUE(0.0f  == matrix.M43());
    EXPECT_TRUE(1.0f  == matrix.M44());
}

TEST_F(MatrixTest, CreateFromQuaternion)
{
    auto q      = Quaternion { 0.7071f, 0.0f, 0.0f, 0.7071f };
    auto matrix = Matrix::CreateFromQuaternion(q);

    EXPECT_TRUE(1.0f            == matrix.M11());
    EXPECT_TRUE(0.0f            == matrix.M12());
    EXPECT_TRUE(0.0f            == matrix.M13());
    EXPECT_TRUE(0.0f            == matrix.M14());

    EXPECT_TRUE(0.0f            == matrix.M21());
    EXPECT_TRUE(1.92523003e-05f == matrix.M22());
    EXPECT_TRUE(-0.999980748f   == matrix.M23());
    EXPECT_TRUE(0.0f            == matrix.M24());

    EXPECT_TRUE(0.0f            == matrix.M31());
    EXPECT_TRUE(0.999980748f    == matrix.M32());
    EXPECT_TRUE(1.92523003e-05f == matrix.M33());
    EXPECT_TRUE(0.0f            == matrix.M34());
}

TEST_F(MatrixTest, CreatePerspectiveFieldOfView)
{
    Single fieldOfView = MathHelper::PiOver4;
    Single aspectRatio = 768.0f / 480.0f;
    auto   perspective = Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, 0.1f, 100.0f);

    EXPECT_TRUE(1.50888336f == perspective.M11());
    EXPECT_TRUE(00.0f       == perspective.M12());
    EXPECT_TRUE(00.0f       == perspective.M13());
    EXPECT_TRUE(00.0f       == perspective.M14());
    EXPECT_TRUE(00.0f       == perspective.M21());
    EXPECT_TRUE(2.41421342f == perspective.M22());
    EXPECT_TRUE(00.0f       == perspective.M23());
    EXPECT_TRUE(00.0f       == perspective.M24());
    EXPECT_TRUE(00.0f       == perspective.M31());
    EXPECT_TRUE(00.0f       == perspective.M32());
    EXPECT_TRUE(-1.001001f  == perspective.M33());
    EXPECT_TRUE(-1.0f       == perspective.M34());
    EXPECT_TRUE(00.0f       == perspective.M41());
    EXPECT_TRUE(00.0f       == perspective.M42());
    EXPECT_TRUE(-0.1001001f == perspective.M43());
    EXPECT_TRUE(00.0f       == perspective.M44());
}

TEST_F(MatrixTest, CreateLookAt)
{
    auto lookAt = Matrix::CreateLookAt({ 0.0f, 1.0f, -5.0f }, Vector3::UnitY, Vector3::Up);

    EXPECT_TRUE(-1.0f == lookAt.M11());
    EXPECT_TRUE(00.0f == lookAt.M12());
    EXPECT_TRUE(00.0f == lookAt.M13());
    EXPECT_TRUE(00.0f == lookAt.M14());
    EXPECT_TRUE(00.0f == lookAt.M21());
    EXPECT_TRUE(01.0f == lookAt.M22());
    EXPECT_TRUE(00.0f == lookAt.M23());
    EXPECT_TRUE(00.0f == lookAt.M24());
    EXPECT_TRUE(00.0f == lookAt.M31());
    EXPECT_TRUE(00.0f == lookAt.M32());
    EXPECT_TRUE(-1.0f == lookAt.M33());
    EXPECT_TRUE(00.0f == lookAt.M34());
    EXPECT_TRUE(00.0f == lookAt.M41());
    EXPECT_TRUE(-1.0f == lookAt.M42());
    EXPECT_TRUE(-5.0f == lookAt.M43());
    EXPECT_TRUE(01.0f == lookAt.M44());
}

TEST_F(MatrixTest, TransformChain)
{
    auto originalVector      = Vector4 { 10.0f, 10.0f, 10.0f, 1.0f };
    auto rotationAxis        = Vector3 { 1.0f, 0.0f, 0.0f };
    auto transformedVector   = Vector4 { };
    auto matrix              = Matrix::Identity;
    auto translateTransform  = Matrix::CreateTranslation(10.0f, 0.0f, 0.0f);
    auto rotateTransform     = Matrix::CreateFromAxisAngle(rotationAxis, MathHelper::PiOver2);
    auto scaleTransform      = Matrix::CreateScale(2);

    matrix *= translateTransform;

    EXPECT_TRUE(01.0f == matrix.M11());
    EXPECT_TRUE(00.0f == matrix.M12());
    EXPECT_TRUE(00.0f == matrix.M13());
    EXPECT_TRUE(00.0f == matrix.M14());
    EXPECT_TRUE(00.0f == matrix.M21());
    EXPECT_TRUE(01.0f == matrix.M22());
    EXPECT_TRUE(00.0f == matrix.M23());
    EXPECT_TRUE(00.0f == matrix.M24());
    EXPECT_TRUE(00.0f == matrix.M31());
    EXPECT_TRUE(00.0f == matrix.M32());
    EXPECT_TRUE(01.0f == matrix.M33());
    EXPECT_TRUE(00.0f == matrix.M34());
    EXPECT_TRUE(10.0f == matrix.M41());
    EXPECT_TRUE(00.0f == matrix.M42());
    EXPECT_TRUE(00.0f == matrix.M43());
    EXPECT_TRUE(01.0f == matrix.M44());

    transformedVector = originalVector * matrix;

    EXPECT_TRUE(20.0f == transformedVector.X());
    EXPECT_TRUE(10.0f == transformedVector.Y());
    EXPECT_TRUE(10.0f == transformedVector.Z());
    EXPECT_TRUE(01.0f == transformedVector.W());

    matrix *= rotateTransform;

    EXPECT_TRUE(01.0f == matrix.M11());
    EXPECT_TRUE(00.0f == matrix.M12());
    EXPECT_TRUE(00.0f == matrix.M13());
    EXPECT_TRUE(00.0f == matrix.M14());
    EXPECT_TRUE(00.0f == matrix.M21());
    EXPECT_TRUE(00.0f == matrix.M22());
    EXPECT_TRUE(-1.0f == matrix.M23());
    EXPECT_TRUE(00.0f == matrix.M24());
    EXPECT_TRUE(00.0f == matrix.M31());
    EXPECT_TRUE(01.0f == matrix.M32());
    EXPECT_TRUE(00.0f == matrix.M33());
    EXPECT_TRUE(00.0f == matrix.M34());
    EXPECT_TRUE(10.0f == matrix.M41());
    EXPECT_TRUE(00.0f == matrix.M42());
    EXPECT_TRUE(00.0f == matrix.M43());
    EXPECT_TRUE(01.0f == matrix.M44());

    transformedVector = originalVector * matrix;

    EXPECT_TRUE(20.0f  == transformedVector.X());
    EXPECT_TRUE(10.0f  == transformedVector.Y());
    EXPECT_TRUE(-10.0f == transformedVector.Z());
    EXPECT_TRUE(01.0f  == transformedVector.W());

    matrix *= scaleTransform;

    EXPECT_TRUE(02.0f == matrix.M11());
    EXPECT_TRUE(00.0f == matrix.M12());
    EXPECT_TRUE(00.0f == matrix.M13());
    EXPECT_TRUE(00.0f == matrix.M14());

    EXPECT_TRUE(00.0f == matrix.M21());
    EXPECT_TRUE(00.0f == matrix.M22());
    EXPECT_TRUE(-2.0f == matrix.M23());
    EXPECT_TRUE(00.0f == matrix.M24());

    EXPECT_TRUE(00.0f == matrix.M31());
    EXPECT_TRUE(02.0f == matrix.M32());
    EXPECT_TRUE(0.0f  == matrix.M33());
    EXPECT_TRUE(00.0f == matrix.M34());

    EXPECT_TRUE(20.0f == matrix.M41());
    EXPECT_TRUE(00.0f == matrix.M42());
    EXPECT_TRUE(00.0f == matrix.M43());
    EXPECT_TRUE(01.0f == matrix.M44());

    transformedVector = originalVector * matrix;

    EXPECT_TRUE(40.0f  == transformedVector.X());
    EXPECT_TRUE(20.0f  == transformedVector.Y());
    EXPECT_TRUE(-20.0f == transformedVector.Z());
    EXPECT_TRUE(01.0f  == transformedVector.W());
}

TEST_F(MatrixTest, TransformFromAxisAngleX)
{
    auto vector = Vector3 { 10.0f, 0.0f, 0.0f };
    auto axis   = Vector3 { 1.0f, 0.0f, 0.0f };
    auto matrix = Matrix::CreateFromAxisAngle(axis, MathHelper::PiOver2);
    auto result = vector * matrix;

    EXPECT_TRUE(10.0f == result.X());
    EXPECT_TRUE(0.0f  == result.Y());
    EXPECT_TRUE(0.0f  == result.Z());
}

TEST_F(MatrixTest, TransformFromAxisAngleY)
{
    auto vector = Vector3 { 0.0f, 10.0f, 0.0f };
    auto axis   = Vector3 { 0.0f, 1.0f, 0.0f };
    auto matrix = Matrix::CreateFromAxisAngle(axis, MathHelper::PiOver2);
    auto result = vector * matrix;

    EXPECT_TRUE(0.0f  == result.X());
    EXPECT_TRUE(10.0f == result.Y());
    EXPECT_TRUE(0.0f  == result.Z());
}

TEST_F(MatrixTest, TransformFromAxisAngleZ)
{
    auto vector = Vector3 { 0.0f, 0.0f, 10.0f };
    auto axis   = Vector3 { 0.0f, 0.0f, 1.0f };
    auto matrix = Matrix::CreateFromAxisAngle(axis, MathHelper::PiOver2);
    auto result = vector * matrix;

    EXPECT_TRUE(0.0f  == result.X());
    EXPECT_TRUE(0.0f  == result.Y());
    EXPECT_TRUE(10.0f == result.Z());
}
