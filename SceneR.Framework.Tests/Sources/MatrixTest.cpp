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
#include <MatrixTest.hpp>

using namespace SceneR::Framework;


TEST_F(MatrixTest, DefaultConstructor)
{
    Matrix matrix;

    ASSERT_EQ(0.0f, matrix.M11());
    ASSERT_EQ(0.0f, matrix.M12());
    ASSERT_EQ(0.0f, matrix.M13());
    ASSERT_EQ(0.0f, matrix.M14());
    ASSERT_EQ(0.0f, matrix.M21());
    ASSERT_EQ(0.0f, matrix.M22());
    ASSERT_EQ(0.0f, matrix.M23());
    ASSERT_EQ(0.0f, matrix.M24());
    ASSERT_EQ(0.0f, matrix.M31());
    ASSERT_EQ(0.0f, matrix.M32());
    ASSERT_EQ(0.0f, matrix.M33());
    ASSERT_EQ(0.0f, matrix.M34());
    ASSERT_EQ(0.0f, matrix.M41());
    ASSERT_EQ(0.0f, matrix.M42());
    ASSERT_EQ(0.0f, matrix.M43());
    ASSERT_EQ(0.0f, matrix.M44());
}

TEST_F(MatrixTest, MatrixConstructor)
{
    Matrix matrix(10.0f, 10.0f, 10.0f, 0.0f,
                  20.0f, 20.0f, 20.0f, 0.0f,
                  30.0f, 30.0f, 30.0f, 0.0f,
                  5.0f , 10.0f, 15.0f, 1.0f);

    ASSERT_EQ(10.0f, matrix.M11());
    ASSERT_EQ(10.0f, matrix.M12());
    ASSERT_EQ(10.0f, matrix.M13());
    ASSERT_EQ(0.0f , matrix.M14());
    ASSERT_EQ(20.0f, matrix.M21());
    ASSERT_EQ(20.0f, matrix.M22());
    ASSERT_EQ(20.0f, matrix.M23());
    ASSERT_EQ(0.0f , matrix.M24());
    ASSERT_EQ(30.0f, matrix.M31());
    ASSERT_EQ(30.0f, matrix.M32());
    ASSERT_EQ(30.0f, matrix.M33());
    ASSERT_EQ(0.0f , matrix.M34());
    ASSERT_EQ(5.0f , matrix.M41());
    ASSERT_EQ(10.0f, matrix.M42());
    ASSERT_EQ(15.0f, matrix.M43());
    ASSERT_EQ(1.0f , matrix.M44());
}

TEST_F(MatrixTest, CopyConstuctor)
{
    Matrix matrix(10.0f, 10.0f, 10.0f, 0.0f,
                   20.0f, 20.0f, 20.0f, 0.0f,
                   30.0f, 30.0f, 30.0f, 0.0f,
                   5.0f , 10.0f, 15.0f, 1.0f);

    Matrix matrix1(matrix);

    ASSERT_EQ(matrix.M11(), matrix1.M11());
    ASSERT_EQ(matrix.M12(), matrix1.M12());
    ASSERT_EQ(matrix.M13(), matrix1.M13());
    ASSERT_EQ(matrix.M14(), matrix1.M14());
    ASSERT_EQ(matrix.M21(), matrix1.M21());
    ASSERT_EQ(matrix.M22(), matrix1.M22());
    ASSERT_EQ(matrix.M23(), matrix1.M23());
    ASSERT_EQ(matrix.M24(), matrix1.M24());
    ASSERT_EQ(matrix.M31(), matrix1.M31());
    ASSERT_EQ(matrix.M32(), matrix1.M32());
    ASSERT_EQ(matrix.M33(), matrix1.M33());
    ASSERT_EQ(matrix.M34(), matrix1.M34());
    ASSERT_EQ(matrix.M41(), matrix1.M41());
    ASSERT_EQ(matrix.M42(), matrix1.M42());
    ASSERT_EQ(matrix.M43(), matrix1.M43());
    ASSERT_EQ(matrix.M44(), matrix1.M44());
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

    ASSERT_EQ(34.0f , matrixResult.M11());
    ASSERT_EQ(44.0f , matrixResult.M12());
    ASSERT_EQ(54.0f , matrixResult.M13());
    ASSERT_EQ(64.0f , matrixResult.M14());
    ASSERT_EQ(82.0f , matrixResult.M21());
    ASSERT_EQ(108.0f, matrixResult.M22());
    ASSERT_EQ(134.0f, matrixResult.M23());
    ASSERT_EQ(160.0f, matrixResult.M24());
    ASSERT_EQ(34.0f , matrixResult.M31());
    ASSERT_EQ(44.0f , matrixResult.M32());
    ASSERT_EQ(54.0f , matrixResult.M33());
    ASSERT_EQ(64.0f , matrixResult.M34());
    ASSERT_EQ(82.0f , matrixResult.M41());
    ASSERT_EQ(108.0f, matrixResult.M42());
    ASSERT_EQ(134.0f, matrixResult.M43());
    ASSERT_EQ(160.0f, matrixResult.M44());
}

TEST_F(MatrixTest, MatrixTranspose)
{
    Matrix matrix(1.0f, 0.0f, 0.0f, 10.0f, 0.0f, 1.0f, 0.0f, 10.0f, 0.0f, 0.0f, 1.0f, 10.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    matrix.Transpose();
}

/*
void AxisAngleRotateTransform3DTest::testTransformAxisX()
{
    Vector3D vector(0, 0, 10);
    Vector3D axis(1, 0, 0);
    AxisAngleRotateTransform3D axisAngleRotateTransform3D(axis, 90);

    Vector3D vectorResult = axisAngleRotateTransform3D.Transform(vector);

    ASSERT_EQ(0.0f  , vectorResult.X());
    ASSERT_EQ(-10.0f, vectorResult.Y());
    ASSERT_EQ(0.0f  , vectorResult.Z());
}

void AxisAngleRotateTransform3DTest::testTransformAxisY()
{
    Vector3D vector(0, 10, 0);
    Vector3D axis(0, 1, 0);
    AxisAngleRotateTransform3D axisAngleRotateTransform3D(axis, 90);

    Vector3D vectorResult = axisAngleRotateTransform3D.Transform(vector);

    ASSERT_EQ(0.0f , vectorResult.X());
    ASSERT_EQ(10.0f, vectorResult.Y());
    ASSERT_EQ(0.0f , vectorResult.Z());
}

void AxisAngleRotateTransform3DTest::testTransformAxisZ()
{
    Vector3D vector(0, 0, 10);
    Vector3D axis(0, 0, 1);
    AxisAngleRotateTransform3D axisAngleRotateTransform3D(axis, 90);

    Vector3D vectorResult = axisAngleRotateTransform3D.Transform(vector);

    ASSERT_EQ(0.0f , vectorResult.X());
    ASSERT_EQ(0.0f , vectorResult.Y());
    ASSERT_EQ(10.0f, vectorResult.Z());
}

void AxisAngleRotateTransform3DTest::testValue()
{
}

void Transform3DGroupTest::testAddTransform()
{
    // Apply multiple transformations to the object. In this sample, a rotation and scale
    // transform is applied.

    // Create and apply a transformation that rotates the object.
    AxisAngleRotateTransform3D rotateTransform3D(Vector3D(0, 3, 0), 40);

    // Add the rotation transform to a Transform3DGroup
    Transform3DGroup transform3DGroup;

    transform3DGroup.AddTransform(rotateTransform3D);

    // Create and apply a scale transformation that stretches the object along the local x-axis
    // by 200 percent and shrinks it along the local y-axis by 50 percent.
    ScaleTransform3D scaleTransform3D(2, 0.5, 1);

    // Add the scale transform to the Transform3DGroup.
    transform3DGroup.AddTransform(scaleTransform3D);

    // Set the Transform property of the GeometryModel to the Transform3DGroup which includes
    // both transformations. The 3D object now has two Transformations applied to it.
    // myGeometryModel.Transform = myTransform3DGroup;
}

void Transform3DGroupTest::testTransform()
{
    // Apply multiple transformations to the object. In this sample, a rotation and scale
    // transform is applied.

    // Create and apply a transformation that rotates the object.
    AxisAngleRotateTransform3D rotateTransform3D(Vector3D(0, 3, 0), 40);

    // Add the rotation transform to a Transform3DGroup
    Transform3DGroup transform3DGroup;

    transform3DGroup.AddTransform(rotateTransform3D);

    // Create and apply a scale transformation that stretches the object along the local x-axis
    // by 200 percent and shrinks it along the local y-axis by 50 percent.
    ScaleTransform3D scaleTransform3D(2, 0.5, 1);

    // Add the scale transform to the Transform3DGroup.
    transform3DGroup.AddTransform(scaleTransform3D);

    transform3DGroup.Transform(Vector3D(10, 20, 40));
}

void Transform3DGroupTest::testValue()
{
}

void Transform3DGroupTest::testGetCount()
{
    // Create and apply a transformation that rotates the object.
    AxisAngleRotateTransform3D rotateTransform3D(Vector3D(0, 3, 0), 40);

    // Add the rotation transform to a Transform3DGroup
    Transform3DGroup transform3DGroup;

    transform3DGroup.AddTransform(rotateTransform3D);

    ASSERT_EQ((size_t)1, transform3DGroup.GetCount());

    // Create and apply a scale transformation that stretches the object along the local x-axis
    // by 200 percent and shrinks it along the local y-axis by 50 percent.
    ScaleTransform3D scaleTransform3D(2, 0.5, 1);

    // Add the scale transform to the Transform3DGroup.
    transform3DGroup.AddTransform(scaleTransform3D);

    ASSERT_EQ((size_t)2, transform3DGroup.GetCount());
}

void Transform3DGroupTest::testClear()
{
    // Create and apply a transformation that rotates the object.
    AxisAngleRotateTransform3D rotateTransform3D(Vector3D(0, 3, 0), 40);

    // Add the rotation transform to a Transform3DGroup
    Transform3DGroup transform3DGroup;

    transform3DGroup.AddTransform(rotateTransform3D);

    // Create and apply a scale transformation that stretches the object along the local x-axis
    // by 200 percent and shrinks it along the local y-axis by 50 percent.
    ScaleTransform3D scaleTransform3D(2, 0.5, 1);

    // Add the scale transform to the Transform3DGroup.
    transform3DGroup.AddTransform(scaleTransform3D);

    ASSERT_EQ((size_t)2, transform3DGroup.GetCount());

    transform3DGroup.Clear();

    ASSERT_EQ((size_t)0, transform3DGroup.GetCount());
}

void Transform3DGroupTest::testTransformChain()
{
    Point4D                    originalVector(10, 10, 10, 1);
    Vector3D                   rotationAxis(1, 0, 0);
    Point4D                    transformedVector;
    Transform3DGroup           transformGroup;
    TranslateTransform3D       translateTransform(10, 0, 0);
    AxisAngleRotateTransform3D rotateTransform(rotationAxis, 90);
    ScaleTransform3D           scaleTransform(2, 2, 2);

    transformGroup.AddTransform(translateTransform);

	ASSERT_EQ(01.0f, transformGroup.Value().M11());
	ASSERT_EQ(00.0f, transformGroup.Value().M12());
	ASSERT_EQ(00.0f, transformGroup.Value().M13());
	ASSERT_EQ(00.0f, transformGroup.Value().M14());
	ASSERT_EQ(00.0f, transformGroup.Value().M21());
	ASSERT_EQ(01.0f, transformGroup.Value().M22());
	ASSERT_EQ(00.0f, transformGroup.Value().M23());
	ASSERT_EQ(00.0f, transformGroup.Value().M24());
	ASSERT_EQ(00.0f, transformGroup.Value().M31());
	ASSERT_EQ(00.0f, transformGroup.Value().M32());
	ASSERT_EQ(01.0f, transformGroup.Value().M33());
	ASSERT_EQ(00.0f, transformGroup.Value().M34());
	ASSERT_EQ(10.0f, transformGroup.Value().M41());
	ASSERT_EQ(00.0f, transformGroup.Value().M42());
	ASSERT_EQ(00.0f, transformGroup.Value().M43());
	ASSERT_EQ(01.0f, transformGroup.Value().M44());

    transformedVector = transformGroup.Transform(originalVector);

	ASSERT_EQ(20.0f, transformedVector.X());
	ASSERT_EQ(10.0f, transformedVector.Y());
	ASSERT_EQ(10.0f, transformedVector.Z());
	ASSERT_EQ(01.0f, transformedVector.W());

    transformGroup.AddTransform(rotateTransform);

	ASSERT_EQ(01.0f, transformGroup.Value().M11());
	ASSERT_EQ(00.0f, transformGroup.Value().M12());
	ASSERT_EQ(00.0f, transformGroup.Value().M13());
	ASSERT_EQ(00.0f, transformGroup.Value().M14());
	ASSERT_EQ(00.0f, transformGroup.Value().M21());
	ASSERT_EQ(00.0f, transformGroup.Value().M22());
	ASSERT_EQ(1.0f, transformGroup.Value().M23());
	ASSERT_EQ(00.0f, transformGroup.Value().M24());
	ASSERT_EQ(00.0f, transformGroup.Value().M31());
	ASSERT_EQ(-1.0f, transformGroup.Value().M32());
	ASSERT_EQ(00.0f, transformGroup.Value().M33());
	ASSERT_EQ(00.0f, transformGroup.Value().M34());
	ASSERT_EQ(10.0f, transformGroup.Value().M41());
	ASSERT_EQ(00.0f, transformGroup.Value().M42());
	ASSERT_EQ(00.0f, transformGroup.Value().M43());
	ASSERT_EQ(01.0f, transformGroup.Value().M44());

	transformedVector = transformGroup.Transform(originalVector);

	ASSERT_EQ(20.0f, transformedVector.X());
	ASSERT_EQ(-10.0f, transformedVector.Y());
	ASSERT_EQ(10.0f, transformedVector.Z());
	ASSERT_EQ(01.0f, transformedVector.W());

    transformGroup.AddTransform(scaleTransform);

	ASSERT_EQ(02.0f, transformGroup.Value().M11());
	ASSERT_EQ(00.0f, transformGroup.Value().M12());
	ASSERT_EQ(00.0f, transformGroup.Value().M13());
	ASSERT_EQ(00.0f, transformGroup.Value().M14());

	ASSERT_EQ(00.0f, transformGroup.Value().M21());
	ASSERT_EQ(00.0f, transformGroup.Value().M22());
	ASSERT_EQ(2.0f, transformGroup.Value().M23());
	ASSERT_EQ(00.0f, transformGroup.Value().M24());

	ASSERT_EQ(00.0f, transformGroup.Value().M31());
	ASSERT_EQ(-2.0f, transformGroup.Value().M32());
	ASSERT_EQ(0.0f, transformGroup.Value().M33());
	ASSERT_EQ(00.0f, transformGroup.Value().M34());

	ASSERT_EQ(20.0f, transformGroup.Value().M41());
	ASSERT_EQ(00.0f, transformGroup.Value().M42());
	ASSERT_EQ(00.0f, transformGroup.Value().M43());
	ASSERT_EQ(01.0f, transformGroup.Value().M44());

    transformedVector = transformGroup.Transform(originalVector);

	ASSERT_EQ(40.0f, transformedVector.X());
	ASSERT_EQ(-20.0f, transformedVector.Y());
	ASSERT_EQ(20.0f, transformedVector.Z());
	ASSERT_EQ(01.0f, transformedVector.W());
}

*/
