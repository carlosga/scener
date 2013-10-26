#include <cppunit/SourceLine.h>
#include <cppunit/TestAssert.h>
#include <Framework/Matrix.hpp>
#include <MatrixTest.hpp>

using namespace SceneR::Framework;

CPPUNIT_TEST_SUITE_REGISTRATION(MatrixTest);

MatrixTest::MatrixTest()
{
}

MatrixTest::~MatrixTest()
{
}

void MatrixTest::setUp()
{
}

void MatrixTest::tearDown()
{
}

void MatrixTest::testMatrix3()
{
    Matrix matrix3;
}

void MatrixTest::testMatrix32()
{
    Matrix matrix1(10.0f, 10.0f, 10.0f, 0.0f,
                   20.0f, 20.0f, 20.0f, 0.0f,
                   30.0f, 30.0f, 30.0f, 0.0f,
                   5.0f , 10.0f, 15.0f, 1.0f);
}

void MatrixTest::testMatrix33()
{
    // Copy Constuctor
}

void MatrixTest::testMatrixMultiply()
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

    CPPUNIT_ASSERT_EQUAL(34.0f , matrixResult.M11());
    CPPUNIT_ASSERT_EQUAL(44.0f , matrixResult.M12());
    CPPUNIT_ASSERT_EQUAL(54.0f , matrixResult.M13());
    CPPUNIT_ASSERT_EQUAL(64.0f , matrixResult.M14());
    CPPUNIT_ASSERT_EQUAL(82.0f , matrixResult.M21());
    CPPUNIT_ASSERT_EQUAL(108.0f, matrixResult.M22());
    CPPUNIT_ASSERT_EQUAL(134.0f, matrixResult.M23());
    CPPUNIT_ASSERT_EQUAL(160.0f, matrixResult.M24());
    CPPUNIT_ASSERT_EQUAL(34.0f , matrixResult.M31());
    CPPUNIT_ASSERT_EQUAL(44.0f , matrixResult.M32());
    CPPUNIT_ASSERT_EQUAL(54.0f , matrixResult.M33());
    CPPUNIT_ASSERT_EQUAL(64.0f , matrixResult.M34());
    CPPUNIT_ASSERT_EQUAL(82.0f , matrixResult.M41());
    CPPUNIT_ASSERT_EQUAL(108.0f, matrixResult.M42());
    CPPUNIT_ASSERT_EQUAL(134.0f, matrixResult.M43());
    CPPUNIT_ASSERT_EQUAL(160.0f, matrixResult.M44());
}

void MatrixTest::testTranspose()
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

    CPPUNIT_ASSERT_EQUAL(0.0f  , vectorResult.X());
    CPPUNIT_ASSERT_EQUAL(-10.0f, vectorResult.Y());
    CPPUNIT_ASSERT_EQUAL(0.0f  , vectorResult.Z());
}

void AxisAngleRotateTransform3DTest::testTransformAxisY()
{
    Vector3D vector(0, 10, 0);
    Vector3D axis(0, 1, 0);
    AxisAngleRotateTransform3D axisAngleRotateTransform3D(axis, 90);

    Vector3D vectorResult = axisAngleRotateTransform3D.Transform(vector);

    CPPUNIT_ASSERT_EQUAL(0.0f , vectorResult.X());
    CPPUNIT_ASSERT_EQUAL(10.0f, vectorResult.Y());
    CPPUNIT_ASSERT_EQUAL(0.0f , vectorResult.Z());
}

void AxisAngleRotateTransform3DTest::testTransformAxisZ()
{
    Vector3D vector(0, 0, 10);
    Vector3D axis(0, 0, 1);
    AxisAngleRotateTransform3D axisAngleRotateTransform3D(axis, 90);

    Vector3D vectorResult = axisAngleRotateTransform3D.Transform(vector);

    CPPUNIT_ASSERT_EQUAL(0.0f , vectorResult.X());
    CPPUNIT_ASSERT_EQUAL(0.0f , vectorResult.Y());
    CPPUNIT_ASSERT_EQUAL(10.0f, vectorResult.Z());
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

    CPPUNIT_ASSERT_EQUAL((size_t)1, transform3DGroup.GetCount());

    // Create and apply a scale transformation that stretches the object along the local x-axis
    // by 200 percent and shrinks it along the local y-axis by 50 percent.
    ScaleTransform3D scaleTransform3D(2, 0.5, 1);

    // Add the scale transform to the Transform3DGroup.
    transform3DGroup.AddTransform(scaleTransform3D);

    CPPUNIT_ASSERT_EQUAL((size_t)2, transform3DGroup.GetCount());
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

    CPPUNIT_ASSERT_EQUAL((size_t)2, transform3DGroup.GetCount());

    transform3DGroup.Clear();

    CPPUNIT_ASSERT_EQUAL((size_t)0, transform3DGroup.GetCount());
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

	CPPUNIT_ASSERT_EQUAL(01.0f, transformGroup.Value().M11());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M12());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M13());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M14());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M21());
	CPPUNIT_ASSERT_EQUAL(01.0f, transformGroup.Value().M22());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M23());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M24());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M31());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M32());
	CPPUNIT_ASSERT_EQUAL(01.0f, transformGroup.Value().M33());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M34());
	CPPUNIT_ASSERT_EQUAL(10.0f, transformGroup.Value().M41());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M42());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M43());
	CPPUNIT_ASSERT_EQUAL(01.0f, transformGroup.Value().M44());

    transformedVector = transformGroup.Transform(originalVector);

	CPPUNIT_ASSERT_EQUAL(20.0f, transformedVector.X());
	CPPUNIT_ASSERT_EQUAL(10.0f, transformedVector.Y());
	CPPUNIT_ASSERT_EQUAL(10.0f, transformedVector.Z());
	CPPUNIT_ASSERT_EQUAL(01.0f, transformedVector.W());

    transformGroup.AddTransform(rotateTransform);

	CPPUNIT_ASSERT_EQUAL(01.0f, transformGroup.Value().M11());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M12());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M13());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M14());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M21());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M22());
	CPPUNIT_ASSERT_EQUAL(1.0f, transformGroup.Value().M23());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M24());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M31());
	CPPUNIT_ASSERT_EQUAL(-1.0f, transformGroup.Value().M32());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M33());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M34());
	CPPUNIT_ASSERT_EQUAL(10.0f, transformGroup.Value().M41());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M42());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M43());
	CPPUNIT_ASSERT_EQUAL(01.0f, transformGroup.Value().M44());

	transformedVector = transformGroup.Transform(originalVector);

	CPPUNIT_ASSERT_EQUAL(20.0f, transformedVector.X());
	CPPUNIT_ASSERT_EQUAL(-10.0f, transformedVector.Y());
	CPPUNIT_ASSERT_EQUAL(10.0f, transformedVector.Z());
	CPPUNIT_ASSERT_EQUAL(01.0f, transformedVector.W());

    transformGroup.AddTransform(scaleTransform);

	CPPUNIT_ASSERT_EQUAL(02.0f, transformGroup.Value().M11());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M12());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M13());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M14());

	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M21());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M22());
	CPPUNIT_ASSERT_EQUAL(2.0f, transformGroup.Value().M23());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M24());

	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M31());
	CPPUNIT_ASSERT_EQUAL(-2.0f, transformGroup.Value().M32());
	CPPUNIT_ASSERT_EQUAL(0.0f, transformGroup.Value().M33());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M34());

	CPPUNIT_ASSERT_EQUAL(20.0f, transformGroup.Value().M41());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M42());
	CPPUNIT_ASSERT_EQUAL(00.0f, transformGroup.Value().M43());
	CPPUNIT_ASSERT_EQUAL(01.0f, transformGroup.Value().M44());

    transformedVector = transformGroup.Transform(originalVector);

	CPPUNIT_ASSERT_EQUAL(40.0f, transformedVector.X());
	CPPUNIT_ASSERT_EQUAL(-20.0f, transformedVector.Y());
	CPPUNIT_ASSERT_EQUAL(20.0f, transformedVector.Z());
	CPPUNIT_ASSERT_EQUAL(01.0f, transformedVector.W());
}

*/
