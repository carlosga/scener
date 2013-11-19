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

#include <Framework/Matrix.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <MatrixTest.hpp>

using namespace SceneR::Framework;

TEST_F(MatrixTest, DefaultConstructor)
{
    Matrix matrix;

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
    Matrix matrix(10.0f, 10.0f, 10.0f, 0.0f,
                  20.0f, 20.0f, 20.0f, 0.0f,
                  30.0f, 30.0f, 30.0f, 0.0f,
                  5.0f , 10.0f, 15.0f, 1.0f);

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
    Matrix matrix(10.0f, 10.0f, 10.0f, 0.0f,
                   20.0f, 20.0f, 20.0f, 0.0f,
                   30.0f, 30.0f, 30.0f, 0.0f,
                   5.0f , 10.0f, 15.0f, 1.0f);

    Matrix matrix1(matrix);

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
    Matrix matrix1(1.0f, 2.0f, 3.0f, 4.0f,
                   5.0f, 6.0f, 7.0f, 8.0f,
                   1.0f, 2.0f, 3.0f, 4.0f,
                   5.0f, 6.0f, 7.0f, 8.0f);
    Matrix matrix2(1.0f, 2.0f, 3.0f, 4.0f,
                   5.0f, 6.0f, 7.0f, 8.0f,
                   1.0f, 2.0f, 3.0f, 4.0f,
                   5.0f, 6.0f, 7.0f, 8.0f);

    Matrix matrixResult = (matrix1 * matrix2);

	// 34  44  54  64
	// 82 108 134 160
	// 34  44  54  64
	// 82 108 134 160

    EXPECT_TRUE(34.0f  == matrixResult.M11());
    EXPECT_TRUE(44.0f  == matrixResult.M12());
    EXPECT_TRUE(54.0f  == matrixResult.M13());
    EXPECT_TRUE(64.0f  == matrixResult.M14());
    EXPECT_TRUE(82.0f  == matrixResult.M21());
    EXPECT_TRUE(108.0f == matrixResult.M22());
    EXPECT_TRUE(134.0f == matrixResult.M23());
    EXPECT_TRUE(160.0f == matrixResult.M24());
    EXPECT_TRUE(34.0f  == matrixResult.M31());
    EXPECT_TRUE(44.0f  == matrixResult.M32());
    EXPECT_TRUE(54.0f  == matrixResult.M33());
    EXPECT_TRUE(64.0f  == matrixResult.M34());
    EXPECT_TRUE(82.0f  == matrixResult.M41());
    EXPECT_TRUE(108.0f == matrixResult.M42());
    EXPECT_TRUE(134.0f == matrixResult.M43());
    EXPECT_TRUE(160.0f == matrixResult.M44());
}

TEST_F(MatrixTest, MatrixTranspose)
{
    Matrix matrix(1.0f, 0.0f, 0.0f, 10.0f,
                  0.0f, 1.0f, 0.0f, 10.0f,
                  0.0f, 0.0f, 1.0f, 10.0f,
                  0.0f, 0.0f, 0.0f, 1.0f);

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

TEST_F(MatrixTest, TransformChain)
{
    Vector4 originalVector(10, 10, 10, 1);
    Vector3 rotationAxis(1, 0, 0);
    Vector4 transformedVector;
    Matrix  matrix              = Matrix::Identity;
    Matrix  translateTransform  = Matrix::CreateTranslation(10, 0, 0);
    Matrix  rotateTransform     = Matrix::CreateFromAxisAngle(rotationAxis, 90);
    Matrix  scaleTransform      = Matrix::CreateScale(2);

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
    EXPECT_TRUE(1.0f  == matrix.M23());
    EXPECT_TRUE(00.0f == matrix.M24());
    EXPECT_TRUE(00.0f == matrix.M31());
    EXPECT_TRUE(-1.0f == matrix.M32());
    EXPECT_TRUE(00.0f == matrix.M33());
    EXPECT_TRUE(00.0f == matrix.M34());
    EXPECT_TRUE(10.0f == matrix.M41());
    EXPECT_TRUE(00.0f == matrix.M42());
    EXPECT_TRUE(00.0f == matrix.M43());
    EXPECT_TRUE(01.0f == matrix.M44());

    transformedVector = originalVector * matrix;

    EXPECT_TRUE(20.0f  == transformedVector.X());
    EXPECT_TRUE(-10.0f == transformedVector.Y());
    EXPECT_TRUE(10.0f  == transformedVector.Z());
    EXPECT_TRUE(01.0f  == transformedVector.W());

    matrix *= scaleTransform;

    EXPECT_TRUE(02.0f == matrix.M11());
    EXPECT_TRUE(00.0f == matrix.M12());
    EXPECT_TRUE(00.0f == matrix.M13());
    EXPECT_TRUE(00.0f == matrix.M14());

    EXPECT_TRUE(00.0f == matrix.M21());
    EXPECT_TRUE(00.0f == matrix.M22());
    EXPECT_TRUE(2.0f  == matrix.M23());
    EXPECT_TRUE(00.0f == matrix.M24());

    EXPECT_TRUE(00.0f == matrix.M31());
    EXPECT_TRUE(-2.0f == matrix.M32());
    EXPECT_TRUE(0.0f  == matrix.M33());
    EXPECT_TRUE(00.0f == matrix.M34());

    EXPECT_TRUE(20.0f == matrix.M41());
    EXPECT_TRUE(00.0f == matrix.M42());
    EXPECT_TRUE(00.0f == matrix.M43());
    EXPECT_TRUE(01.0f == matrix.M44());

    transformedVector = originalVector * matrix;

    EXPECT_TRUE(40.0f  == transformedVector.X());
    EXPECT_TRUE(-20.0f == transformedVector.Y());
    EXPECT_TRUE(20.0f  == transformedVector.Z());
    EXPECT_TRUE(01.0f  == transformedVector.W());
}

TEST_F(MatrixTest, TransformFromAxisAngleX)
{
    Vector3 vector(10, 0, 0);
    Vector3 axis(1, 0, 0);
    Matrix  matrix = Matrix::CreateFromAxisAngle(axis, 90);

    Vector3 vectorResult = vector * matrix;

    EXPECT_TRUE(10.0f == vectorResult.X());
    EXPECT_TRUE(0.0f  == vectorResult.Y());
    EXPECT_TRUE(0.0f  == vectorResult.Z());
}

TEST_F(MatrixTest, TransformFromAxisAngleY)
{
    Vector3 vector(0, 10, 0);
    Vector3 axis(0, 1, 0);
    Matrix  matrix = Matrix::CreateFromAxisAngle(axis, 90);

    Vector3 vectorResult = vector * matrix;

    EXPECT_TRUE(0.0f  == vectorResult.X());
    EXPECT_TRUE(10.0f == vectorResult.Y());
    EXPECT_TRUE(0.0f  == vectorResult.Z());
}

TEST_F(MatrixTest, TransformFromAxisAngleZ)
{
    Vector3 vector(0, 0, 10);
    Vector3 axis(0, 0, 1);
    Matrix  matrix = Matrix::CreateFromAxisAngle(axis, 90);

    Vector3 vectorResult = vector * matrix;

    EXPECT_TRUE(0.0f  == vectorResult.X());
    EXPECT_TRUE(0.0f  == vectorResult.Y());
    EXPECT_TRUE(10.0f == vectorResult.Z());
}
