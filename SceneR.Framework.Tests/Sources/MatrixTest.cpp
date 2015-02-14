// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <MatrixTest.hpp>

#include <cmath>

#include <EqualityHelper.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Framework/MathHelper.hpp>

using namespace System;
using namespace SceneR::Framework;

Matrix MatrixTest::GenerateMatrixNumberFrom1To16()
{
    Matrix a;

    a.M11(1.0f);
    a.M12(2.0f);
    a.M13(3.0f);
    a.M14(4.0f);
    a.M21(5.0f);
    a.M22(6.0f);
    a.M23(7.0f);
    a.M24(8.0f);
    a.M31(9.0f);
    a.M32(10.0f);
    a.M33(11.0f);
    a.M34(12.0f);
    a.M41(13.0f);
    a.M42(14.0f);
    a.M43(15.0f);
    a.M44(16.0f);

    return a;
}

Matrix MatrixTest::GenerateTestMatrix()
{
    auto m = Matrix::CreateRotationX(MathHelper::ToRadians(30.0f))
           * Matrix::CreateRotationY(MathHelper::ToRadians(30.0f))
           * Matrix::CreateRotationZ(MathHelper::ToRadians(30.0f));

    // m.Translation({ 111.0f, 222.0f, 333.0f });

    return m;
}

void MatrixTest::Decompose(const Single& yaw
                         , const Single& pitch
                         , const Single& roll
                         , const Vector3& expectedTranslation
                         , const Vector3& expectedScales)
{
    auto expectedRotation = Quaternion::CreateFromYawPitchRoll(MathHelper::ToRadians(yaw)
                                                             , MathHelper::ToRadians(pitch)
                                                             , MathHelper::ToRadians(roll));

    auto m = Matrix::CreateScale(expectedScales)
           * Matrix::CreateFromQuaternion(expectedRotation)
           * Matrix::CreateTranslation(expectedTranslation);

    Vector3    scales;
    Quaternion rotation;
    Vector3    translation;

    bool actualResult = Matrix::Decompose(m, scales, rotation, translation);

    EXPECT_TRUE(actualResult);

    bool scaleIsZeroOrNegative = expectedScales.X() <= 0
                              || expectedScales.Y() <= 0
                              || expectedScales.Z() <= 0;

    if (scaleIsZeroOrNegative)
    {
        EXPECT_TRUE(EqualityHelper::Equal(std::abs(expectedScales.X()), std::abs(scales.X())));
        EXPECT_TRUE(EqualityHelper::Equal(std::abs(expectedScales.Y()), std::abs(scales.Y())));
        EXPECT_TRUE(EqualityHelper::Equal(std::abs(expectedScales.Z()), std::abs(scales.Z())));
    }
    else
    {
        EXPECT_TRUE(EqualityHelper::Equal(expectedScales, scales));
        EXPECT_TRUE(EqualityHelper::EqualRotation(expectedRotation, rotation));
    }

    EXPECT_TRUE(EqualityHelper::Equal(expectedTranslation, translation));
}

void MatrixTest::DecomposeScale(const Single& sx, const Single& sy, const Single& sz)
{
    auto m              = Matrix::CreateScale(sx, sy, sz);
    auto expectedScales = Vector3 { sx, sy, sz };

    Vector3    scales;
    Quaternion rotation;
    Vector3    translation;

    bool actualResult = Matrix::Decompose(m, scales, rotation, translation);

    EXPECT_TRUE(actualResult);
    EXPECT_TRUE(EqualityHelper::Equal(expectedScales, scales));
    EXPECT_TRUE(EqualityHelper::EqualRotation(Quaternion::Identity, rotation));
    EXPECT_TRUE(EqualityHelper::Equal(Vector3::Zero, translation));
}

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

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, Identity)
{
    Matrix val;

    val.M11(1.0f);
    val.M22(1.0f);
    val.M33(1.0f);
    val.M44(1.0f);

    EXPECT_TRUE(EqualityHelper::Equal(val, Matrix::Identity));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, Determinant1)
{
    auto target = Matrix::CreateRotationX(MathHelper::ToRadians(30.0f))
                * Matrix::CreateRotationY(MathHelper::ToRadians(30.0f))
                * Matrix::CreateRotationZ(MathHelper::ToRadians(30.0f));

    Single val = 1.0f;
    Single det = target.Determinant();

    EXPECT_TRUE(val == det);
}

// Determinant test |A| = 1 / |A'|
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, Determinant2)
{
    Matrix a;

    a.M11(5.0f);
    a.M12(2.0f);
    a.M13(8.25f);
    a.M14(1.0f);
    a.M21(12.0f);
    a.M22(6.8f);
    a.M23(2.14f);
    a.M24(9.6f);
    a.M31(6.5f);
    a.M32(1.0f);
    a.M33(3.14f);
    a.M34(2.22f);
    a.M41(0.0f);
    a.M42(0.86f);
    a.M43(4.0f);
    a.M44(1.0f);

    auto   i    = Matrix::Invert(a);
    Single detA = a.Determinant();
    Single detI = i.Determinant();
    Single t    = 1.0f / detI;

    // only accurate to 3 precision
    EXPECT_TRUE(std::abs(detA - t) < 1e-3);
}

// A test for Invert (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, Invert)
{
    auto mtx = Matrix::CreateRotationX(MathHelper::ToRadians(30.0f))
             * Matrix::CreateRotationY(MathHelper::ToRadians(30.0f))
             * Matrix::CreateRotationZ(MathHelper::ToRadians(30.0f));

    auto expected = Matrix { 0.74999994f , -0.216506317f, 0.62499994f  , 0.0f
                           , 0.433012635f, 0.87499994f  , -0.216506317f, 0.0f
                           , -0.49999997f, 0.433012635f , 0.74999994f  , 0.0f
                           , 0.0f        , 0.0f         , 0.0f         , 0.99999994f };

    auto actual = Matrix::Invert(mtx);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Make sure M*M is identity matrix
    auto i = mtx * actual;

    EXPECT_TRUE(EqualityHelper::Equal(Matrix::Identity, i));
}

// A test for Invert (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, InvertIdentityMatrix)
{
    auto mtx    = Matrix::Identity;
    auto actual = Matrix::Invert(mtx);

    EXPECT_TRUE(EqualityHelper::Equal(actual, Matrix::Identity));
}

// A test for Invert (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, InvertTranslationMatrix)
{
    auto mtx    = Matrix::CreateTranslation(23, 42, 666);
    auto actual = Matrix::Invert(mtx);
    auto i      = mtx * actual;

    EXPECT_TRUE(EqualityHelper::Equal(i, Matrix::Identity));
}

// A test for Invert (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, InvertRotationMatrix)
{
    auto mtx    = Matrix::CreateFromYawPitchRoll(3, 4, 5);
    auto actual = Matrix::Invert(mtx);
    auto i      = mtx * actual;

    EXPECT_TRUE(EqualityHelper::Equal(i, Matrix::Identity));
}

// A test for Invert (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, InvertScaleMatrix)
{
    auto mtx    = Matrix::CreateScale(23, 42, -666);
    auto actual = Matrix::Invert(mtx);
    auto i      = mtx * actual;

    EXPECT_TRUE(EqualityHelper::Equal(i, Matrix::Identity));
}

// A test for Invert (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, InvertProjectionMatrix)
{
    auto mtx    = Matrix::CreatePerspectiveFieldOfView(1, 1.333f, 0.1f, 666);
    auto actual = Matrix::Invert(mtx);
    auto i      = mtx * actual;

    EXPECT_TRUE(EqualityHelper::Equal(i, Matrix::Identity));
}

// A test for Invert (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, InvertAffineMatrix)
{
    auto mtx = Matrix::CreateFromYawPitchRoll(3, 4, 5)
             * Matrix::CreateScale(23, 42, -666)
             * Matrix::CreateTranslation(17, 53, 89);

    auto actual = Matrix::Invert(mtx);
    auto i      = mtx * actual;

    EXPECT_TRUE(EqualityHelper::Equal(i, Matrix::Identity));
}

// Various rotation decompose test.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, Decompose)
{
    MatrixTest::Decompose(10.0f, 20.0f, 30.0f, { 10, 20, 30 }, { 2, 3, 4 });

    const Single step = 35.0f;

    for (Single yawAngle = -720.0f; yawAngle <= 720.0f; yawAngle += step)
    {
        for (Single pitchAngle = -720.0f; pitchAngle <= 720.0f; pitchAngle += step)
        {
            for (Single rollAngle = -720.0f; rollAngle <= 720.0f; rollAngle += step)
            {
                MatrixTest::Decompose(yawAngle, pitchAngle, rollAngle, { 10, 20, 30 }, { 2, 3, 4 });
            }
        }
    }
}

// Various scaled matrix decompose test.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, VariousScaledMatrixDecomposition)
{
    MatrixTest::Decompose(10.0f, 20.0f, 30.0f, { 10, 20, 30 }, { 2, 3, 4 });

    // Various scales.
    MatrixTest::Decompose(0, 0, 0, Vector3::Zero, { 1, 2, 3 });
    MatrixTest::Decompose(0, 0, 0, Vector3::Zero, { 1, 3, 2 });
    MatrixTest::Decompose(0, 0, 0, Vector3::Zero, { 2, 1, 3 });
    MatrixTest::Decompose(0, 0, 0, Vector3::Zero, { 2, 3, 1 });
    MatrixTest::Decompose(0, 0, 0, Vector3::Zero, { 3, 1, 2 });
    MatrixTest::Decompose(0, 0, 0, Vector3::Zero, { 3, 2, 1 });

    MatrixTest::Decompose(0, 0, 0, Vector3::Zero, { -2, 1, 1 });

    // Small scales.
    MatrixTest::Decompose(0, 0, 0, Vector3::Zero, { 1e-4f, 2e-4f, 3e-4f });
    MatrixTest::Decompose(0, 0, 0, Vector3::Zero, { 1e-4f, 3e-4f, 2e-4f });
    MatrixTest::Decompose(0, 0, 0, Vector3::Zero, { 2e-4f, 1e-4f, 3e-4f });
    MatrixTest::Decompose(0, 0, 0, Vector3::Zero, { 2e-4f, 3e-4f, 1e-4f });
    MatrixTest::Decompose(0, 0, 0, Vector3::Zero, { 3e-4f, 1e-4f, 2e-4f });
    MatrixTest::Decompose(0, 0, 0, Vector3::Zero, { 3e-4f, 2e-4f, 1e-4f });

    // Zero scales.
    MatrixTest::Decompose(0, 0, 0, { 10, 20, 30 }, { 0, 0, 0 });
    MatrixTest::Decompose(0, 0, 0, { 10, 20, 30 }, { 1, 0, 0 });
    MatrixTest::Decompose(0, 0, 0, { 10, 20, 30 }, { 0, 1, 0 });
    MatrixTest::Decompose(0, 0, 0, { 10, 20, 30 }, { 0, 0, 1 });
    MatrixTest::Decompose(0, 0, 0, { 10, 20, 30 }, { 0, 1, 1 });
    MatrixTest::Decompose(0, 0, 0, { 10, 20, 30 }, { 1, 0, 1 });
    MatrixTest::Decompose(0, 0, 0, { 10, 20, 30 }, { 1, 1, 0 });

    // Negative scales.
    MatrixTest::Decompose(0, 0, 0, { 10, 20, 30 }, { -1, -1, -1 });
    MatrixTest::Decompose(0, 0, 0, { 10, 20, 30 }, { 1, -1, -1 });
    MatrixTest::Decompose(0, 0, 0, { 10, 20, 30 }, { -1, 1, -1 });
    MatrixTest::Decompose(0, 0, 0, { 10, 20, 30 }, { -1, -1, 1 });
    MatrixTest::Decompose(0, 0, 0, { 10, 20, 30 }, { -1, 1, 1 });
    MatrixTest::Decompose(0, 0, 0, { 10, 20, 30 }, { 1, -1, 1 });
    MatrixTest::Decompose(0, 0, 0, { 10, 20, 30 }, { 1, 1, -1 });
}

// Tiny scale decompose test.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, ScaleDecompose)
{
    MatrixTest::DecomposeScale(1, 2e-4f, 3e-4f);
    MatrixTest::DecomposeScale(1, 3e-4f, 2e-4f);
    MatrixTest::DecomposeScale(2e-4f, 1, 3e-4f);
    MatrixTest::DecomposeScale(2e-4f, 3e-4f, 1);
    MatrixTest::DecomposeScale(3e-4f, 1, 2e-4f);
    MatrixTest::DecomposeScale(3e-4f, 2e-4f, 1);
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, ScaleDecompose1)
{
    Vector3    scales;
    Quaternion rotation;
    Vector3    translation;

    EXPECT_FALSE(Matrix::Decompose(MatrixTest::GenerateMatrixNumberFrom1To16(), scales, rotation, translation));
    //EXPECT_FALSE(Matrix::Decompose(new Matrix4x4(Matrix3x2.CreateSkew(1, 2)), out scales, out rotation, out translation));
}

// Transform by quaternion test
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, TransformByQuaternion)
{
    auto target = MatrixTest::GenerateMatrixNumberFrom1To16();
    auto m      = Matrix::CreateRotationX(MathHelper::ToRadians(30.0f))
                * Matrix::CreateRotationY(MathHelper::ToRadians(30.0f))
                * Matrix::CreateRotationZ(MathHelper::ToRadians(30.0f));

    auto q        = Quaternion::CreateFromRotationMatrix(m);
    auto expected = target * m;
    auto actual   = Matrix::Transform(target, q);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreateRotationX (float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateRotationX)
{
    Single radians = MathHelper::ToRadians(30.0f);
    Matrix expected;

    expected.M11(1.0f);
    expected.M22(0.8660254f);
    expected.M23(0.5f);
    expected.M32(-0.5f);
    expected.M33(0.8660254f);
    expected.M44(1.0f);

    auto actual = Matrix::CreateRotationX(radians);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreateRotationX (float)
// CreateRotationX of zero degree
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateRotationXOfZeroDegree)
{
    Single radians = 0;

    auto expected = Matrix::Identity;
    auto actual   = Matrix::CreateRotationX(radians);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreateRotationX (float, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateRotationXCenter)
{
//    Single radians = MathHelper::ToRadians(30.0f);
//    auto   center  = Vector3 { 23, 42, 66 };
//
//    auto rotateAroundZero         = Matrix::CreateRotationX(radians, Vector3::Zero);
//    auto rotateAroundZeroExpected = Matrix::CreateRotationX(radians);
//
//    EXPECT_TRUE(EqualityHelper::Equal(rotateAroundZero, rotateAroundZeroExpected));
//
//    auto rotateAroundCenter         = Matrix::CreateRotationX(radians, center);
//    auto rotateAroundCenterExpected = Matrix::CreateTranslation(-center)
//                                    * Matrix::CreateRotationX(radians)
//                                    * Matrix::CreateTranslation(center);
//
//    EXPECT_TRUE(EqualityHelper::Equal(rotateAroundCenter, rotateAroundCenterExpected));
}

// A test for CreateRotationY (float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateRotationY)
{
    Single radians = MathHelper::ToRadians(60.0f);
    Matrix expected;

    expected.M11(0.49999997f);
    expected.M13(-0.866025448f);
    expected.M22(1.0f);
    expected.M31(0.866025448f);
    expected.M33(0.49999997f);
    expected.M44(1.0f);

    auto actual = Matrix::CreateRotationY(radians);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for RotationY (float)
// CreateRotationY test for negative angle
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateRotationYForNegativeAngle)
{
    Single radians = MathHelper::ToRadians(-300.0f);
    Matrix expected;

    expected.M11(0.49999997f);
    expected.M13(-0.866025448f);
    expected.M22(1.0f);
    expected.M31(0.866025448f);
    expected.M33(0.49999997f);
    expected.M44(1.0f);

    auto actual = Matrix::CreateRotationY(radians);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreateRotationY (float, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateRotationYCenter)
{
//    Single radians = MathHelper::ToRadians(30.0f);
//    auto   center  = Vector3 { 23, 42, 66 };
//
//    auto rotateAroundZero         = Matrix::CreateRotationY(radians, Vector3::Zero);
//    auto rotateAroundZeroExpected = Matrix::CreateRotationY(radians);
//
//    EXPECT_TRUE(EqualityHelper::Equal(rotateAroundZero, rotateAroundZeroExpected));
//
//    auto rotateAroundCenter         = Matrix::CreateRotationY(radians, center);
//    auto rotateAroundCenterExpected = Matrix::CreateTranslation(-center)
//                                    * Matrix::CreateRotationY(radians)
//                                    * Matrix::CreateTranslation(center);
//
//    EXPECT_TRUE(EqualityHelper::Equal(rotateAroundCenter, rotateAroundCenterExpected));
}

// A test for CreateFromAxisAngle(Vector3f,float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateFromAxisAngle)
{
    Single radians  = MathHelper::ToRadians(-30.0f);
    auto   expected = Matrix::CreateRotationX(radians);
    auto   actual   = Matrix::CreateFromAxisAngle(Vector3::UnitX, radians);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    expected = Matrix::CreateRotationY(radians);
    actual   = Matrix::CreateFromAxisAngle(Vector3::UnitY, radians);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    expected = Matrix::CreateRotationZ(radians);
    actual   = Matrix::CreateFromAxisAngle(Vector3::UnitZ, radians);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    expected = Matrix::CreateFromQuaternion(Quaternion::CreateFromAxisAngle(Vector3::Normalize(Vector3::One), radians));
    actual   = Matrix::CreateFromAxisAngle(Vector3::Normalize(Vector3::One), radians);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    const UInt32 rotCount = 16;

    for (UInt32 i = 0; i < rotCount; ++i)
    {
        Single latitude = (2.0f * MathHelper::Pi) * ((Single)i / (Single)rotCount);

        for (UInt32 j = 0; j < rotCount; ++j)
        {
            Single longitude = -MathHelper::PiOver2 + MathHelper::Pi * ((Single)j / (float)rotCount);

            auto m    = Matrix::CreateRotationZ(longitude) * Matrix::CreateRotationY(latitude);
            auto axis = Vector3 { m.M11(), m.M12(), m.M13() };

            for (UInt32 k = 0; k < rotCount; ++k)
            {
                Single rot = (2.0f * MathHelper::Pi) * ((Single)k / (Single)rotCount);

                expected = Matrix::CreateFromQuaternion(Quaternion::CreateFromAxisAngle(axis, rot));
                actual   = Matrix::CreateFromAxisAngle(axis, rot);

                EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
            }
        }
    }
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateFromYawPitchRoll)
{
    Single yawAngle   = MathHelper::ToRadians(30.0f);
    Single pitchAngle = MathHelper::ToRadians(40.0f);
    Single rollAngle  = MathHelper::ToRadians(50.0f);

    auto yaw      = Matrix::CreateFromAxisAngle(Vector3::UnitY, yawAngle);
    auto pitch    = Matrix::CreateFromAxisAngle(Vector3::UnitX, pitchAngle);
    auto roll     = Matrix::CreateFromAxisAngle(Vector3::UnitZ, rollAngle);
    auto expected = roll * pitch * yaw;
    auto actual   = Matrix::CreateFromYawPitchRoll(yawAngle, pitchAngle, rollAngle);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// Covers more numeric rigions
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateFromYawPitchRoll2)
{
    const Single step = 35.0f;

    for (Single yawAngle = -720.0f; yawAngle <= 720.0f; yawAngle += step)
    {
        for (Single pitchAngle = -720.0f; pitchAngle <= 720.0f; pitchAngle += step)
        {
            for (Single rollAngle = -720.0f; rollAngle <= 720.0f; rollAngle += step)
            {
                Single yawRad   = MathHelper::ToRadians(yawAngle);
                Single pitchRad = MathHelper::ToRadians(pitchAngle);
                Single rollRad  = MathHelper::ToRadians(rollAngle);

                auto yaw   = Matrix::CreateFromAxisAngle(Vector3::UnitY, yawRad);
                auto pitch = Matrix::CreateFromAxisAngle(Vector3::UnitX, pitchRad);
                auto roll  = Matrix::CreateFromAxisAngle(Vector3::UnitZ, rollRad);

                auto expected = roll * pitch * yaw;
                auto actual   = Matrix::CreateFromYawPitchRoll(yawRad, pitchRad, rollRad);

                EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
            }
        }
    }
}

// A test for CreateRotationZ (float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateRotationZ)
{
    Single radians = MathHelper::ToRadians(50.0f);

    Matrix expected;

    expected.M11(0.642787635f);
    expected.M12(0.766044438f);
    expected.M21(-0.766044438f);
    expected.M22(0.642787635f);
    expected.M33(1.0f);
    expected.M44(1.0f);

    auto actual = Matrix::CreateRotationZ(radians);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreateRotationZ (float, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateRotationZCenter)
{
//    float radians = MathHelper.ToRadians(30.0f);
//    Vector3 center = new Vector3(23, 42, 66);
//
//    Matrix4x4 rotateAroundZero = Matrix4x4.CreateRotationZ(radians, Vector3.Zero);
//    Matrix4x4 rotateAroundZeroExpected = Matrix4x4.CreateRotationZ(radians);
//    Assert.True(MathHelper.Equal(rotateAroundZero, rotateAroundZeroExpected));
//
//    Matrix4x4 rotateAroundCenter = Matrix4x4.CreateRotationZ(radians, center);
//    Matrix4x4 rotateAroundCenterExpected = Matrix4x4.CreateTranslation(-center) * Matrix4x4.CreateRotationZ(radians) * Matrix4x4.CreateTranslation(center);
//    Assert.True(MathHelper.Equal(rotateAroundCenter, rotateAroundCenterExpected));
}

// A test for CrateLookAt (Vector3f, Vector3f, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateLookAt2)
{
    auto cameraPosition = Vector3 { 10.0f, 20.0f, 30.0f };
    auto cameraTarget   = Vector3 { 3.0f, 2.0f, -4.0f };
    auto cameraUpVector = Vector3 { 0.0f, 1.0f, 0.0f };

    Matrix expected;

    expected.M11(0.979457f);
    expected.M12(-0.0928267762f);
    expected.M13(0.179017f);

    expected.M21(0.0f);
    expected.M22(0.8877481f);
    expected.M23(0.460329473f);

    expected.M31(-0.201652914f);
    expected.M32(-0.450872928f);
    expected.M33(0.8695112f);

    expected.M41(-3.74498272f);
    expected.M42(-3.30050683f);
    expected.M43(-37.0820961f);
    expected.M44(1.0f);

    auto actual = Matrix::CreateLookAt(cameraPosition, cameraTarget, cameraUpVector);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreateWorld (Vector3f, Vector3f, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateWorld)
{
    auto objectPosition         = Vector3 { 10.0f, 20.0f, 30.0f };
    auto objectForwardDirection = Vector3 { 3.0f, 2.0f, -4.0f };
    auto objectUpVector         = Vector3 { 0.0f, 1.0f, 0.0f };

    Matrix expected;

    expected.M11(0.799999952f);
    expected.M12(0);
    expected.M13(0.599999964f);
    expected.M14(0);

    expected.M21(-0.2228344f);
    expected.M22(0.928476632f);
    expected.M23(0.297112525f);
    expected.M24(0);

    expected.M31(-0.557086f);
    expected.M32(-0.371390671f);
    expected.M33(0.742781341f);
    expected.M34(0);

    expected.M41(10);
    expected.M42(20);
    expected.M43(30);
    expected.M44(1.0f);

    auto actual = Matrix::CreateWorld(objectPosition, objectForwardDirection, objectUpVector);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    //EXPECT_TRUE(objectPosition, actual.Translation);
    EXPECT_TRUE(Vector3::DotProduct(Vector3::Normalize(objectUpVector), Vector3(actual.M21(), actual.M22(), actual.M23())) > 0);
    EXPECT_TRUE(Vector3::DotProduct(Vector3::Normalize(objectForwardDirection), Vector3(-actual.M31(), -actual.M32(), -actual.M33())) > 0.999f);
}

// A test for CreateOrtho (float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateOrtho)
{
    Single width      = 100.0f;
    Single height     = 200.0f;
    Single zNearPlane = 1.5f;
    Single zFarPlane  = 1000.0f;

    Matrix expected;

    expected.M11(0.02f);
    expected.M22(0.01f);
    expected.M33(-0.00100150227f);
    expected.M43(-0.00150225335f);
    expected.M44(1.0f);

    auto actual = Matrix::CreateOrthographic(width, height, zNearPlane, zFarPlane);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreateOrthoOffCenter (float, float, float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateOrthoOffCenter)
{
    Single left       = 10.0f;
    Single right      = 90.0f;
    Single bottom     = 20.0f;
    Single top        = 180.0f;
    Single zNearPlane = 1.5f;
    Single zFarPlane  = 1000.0f;

    Matrix expected;

    expected.M11(0.025f);
    expected.M22(0.0125f);
    expected.M33(-0.00100150227f);
    expected.M41(-1.25f);
    expected.M42(-1.25f);
    expected.M43(-0.00150225335f);
    expected.M44(1.0f);

    auto actual = Matrix::CreateOrthographicOffCenter(left, right, bottom, top, zNearPlane, zFarPlane);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreatePerspective (float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspective)
{
    Single width      = 100.0f;
    Single height     = 200.0f;
    Single zNearPlane = 1.5f;
    Single zFarPlane  = 1000.0f;

    Matrix expected;

    expected.M11(0.03f);
    expected.M22(0.015f);
    expected.M33(-1.00150228f);
    expected.M34(-1.0f);
    expected.M43(-1.50225341f);

    auto actual = Matrix::CreatePerspective(width, height, zNearPlane, zFarPlane);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreatePerspective (float, float, float, float)
// CreatePerspective test where znear = zfar
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveWhereZnearEqualsZfar)
{
    Single width      = 100.0f;
    Single height     = 200.0f;
    Single zNearPlane = 0.0f;
    Single zFarPlane  = 0.0f;

    ASSERT_THROW(Matrix::CreatePerspective(width, height, zNearPlane, zFarPlane), std::out_of_range);
}

// A test for CreatePerspective (float, float, float, float)
// CreatePerspective test where near plane is negative value
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveWhereNearPlaneIsNegative)
{
    ASSERT_THROW(Matrix::CreatePerspective(10, 10, -10, 10), std::out_of_range);
}

// A test for CreatePerspective (float, float, float, float)
// CreatePerspective test where far plane is negative value
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveWhereFarPlaneIsNegative)
{
    ASSERT_THROW(Matrix::CreatePerspective(10, 10, 10, -10), std::out_of_range);
}

// A test for CreatePerspective (float, float, float, float)
// CreatePerspective test where near plane is beyond far plane
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveWhereNearPlaneIsBeyondFarPlane)
{
    ASSERT_THROW(Matrix::CreatePerspective(10, 10, 10, 1), std::out_of_range);
}

// A test for CreatePerspectiveFieldOfView (float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveFieldOfView1)
{
    Single fieldOfView = MathHelper::ToRadians(30.0f);
    Single aspectRatio = 1280.0f / 720.0f;
    Single zNearPlane  = 1.5f;
    Single zFarPlane   = 1000.0f;

    Matrix expected;

    expected.M11(2.09927845f);
    expected.M22(3.73205066f);
    expected.M33(-1.00150228f);
    expected.M34(-1.0f);
    expected.M43(-1.50225341f);

    auto actual = Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, zNearPlane, zFarPlane);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreatePerspectiveFieldOfView (float, float, float, float)
// CreatePerspectiveFieldOfView test where filedOfView is negative value.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveFieldOfViewWhereFieldOfViewIsNegative)
{
    EXPECT_THROW(Matrix::CreatePerspectiveFieldOfView(-1, 1, 1, 10), std::out_of_range);
}

// A test for CreatePerspectiveFieldOfView (float, float, float, float)
// CreatePerspectiveFieldOfView test where filedOfView is more than pi.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveFieldOfViewWhereFieldOfViewIsGreatherThanPi)
{
    EXPECT_THROW(Matrix::CreatePerspectiveFieldOfView(MathHelper::Pi + 0.01f, 1, 1, 10), std::out_of_range);
}

// A test for CreatePerspectiveFieldOfView (float, float, float, float)
// CreatePerspectiveFieldOfView test where nearPlaneDistance is negative value.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveFieldOfViewWhereNearPlaneIsNegative)
{
    EXPECT_THROW(Matrix::CreatePerspectiveFieldOfView(MathHelper::PiOver4, 1, -1, 10), std::out_of_range);
}

// A test for CreatePerspectiveFieldOfView (float, float, float, float)
// CreatePerspectiveFieldOfView test where farPlaneDistance is negative value.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveFieldOfViewWhereFarPlaneIsNegative)
{
    EXPECT_THROW(Matrix::CreatePerspectiveFieldOfView(MathHelper::PiOver4, 1, 1, -10), std::out_of_range);
}

// A test for CreatePerspectiveFieldOfView (float, float, float, float)
// CreatePerspectiveFieldOfView test where nearPlaneDistance is larger than farPlaneDistance.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveFieldOfViewWhereNearPlaneIsLargerThanFarPlane)
{
    EXPECT_THROW(Matrix::CreatePerspectiveFieldOfView(MathHelper::PiOver4, 1, 10, 1), std::out_of_range);
}

// A test for CreatePerspectiveOffCenter (float, float, float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveOffCenter)
{
    Single left       = 10.0f;
    Single right      = 90.0f;
    Single bottom     = 20.0f;
    Single top        = 180.0f;
    Single zNearPlane = 1.5f;
    Single zFarPlane  = 1000.0f;

    Matrix expected;

    expected.M11(0.0375f);
    expected.M22(0.01875f);
    expected.M31(1.25f);
    expected.M32(1.25f);
    expected.M33(-1.00150228f);
    expected.M34(-1.0f);
    expected.M43(-1.50225341f);

    auto actual = Matrix::CreatePerspectiveOffCenter(left, right, bottom, top, zNearPlane, zFarPlane);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreatePerspectiveOffCenter (float, float, float, float, float, float)
// CreatePerspectiveOffCenter test where nearPlaneDistance is negative.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveOffCenterWhereNearPlaneIsNegative)
{
    EXPECT_THROW(Matrix::CreatePerspectiveOffCenter(10.0f, 90.0f, 20.0f, 180.0f, -1, 10), std::out_of_range);
}

// A test for CreatePerspectiveOffCenter (float, float, float, float, float, float)
// CreatePerspectiveOffCenter test where farPlaneDistance is negative.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveOffCenterWhereFarPlaneIsNegative)
{
    EXPECT_THROW(Matrix::CreatePerspectiveOffCenter(10.0f, 90.0f, 20.0f, 180.0f, 1, -10), std::out_of_range);
}

// A test for CreatePerspectiveOffCenter (float, float, float, float, float, float)
// CreatePerspectiveOffCenter test where test where nearPlaneDistance is larger than farPlaneDistance.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveOffCenterWhereNearPlaneIsLargerThanFarPlane)
{
    EXPECT_THROW(Matrix::CreatePerspectiveOffCenter(10.0f, 90.0f, 20.0f, 180.0f, 10, 1), std::out_of_range);
}

// A test for Invert (Matrix4x4)
// Non invertible matrix - determinant is zero - singular matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, InvertNonInvertibleMatrix)
{
    Matrix a = { 1.0f , 2.0f , 3.0f , 4.0f
               , 5.0f , 6.0f , 7.0f , 8.0f
               , 9.0f , 10.0f, 11.0f, 12.0f
               , 13.0f, 14.0f, 15.0f, 16.0f };

    Single detA = a.Determinant();

    EXPECT_TRUE(EqualityHelper::Equal(detA, 0.0f));

    auto actual = Matrix::Invert(a);

    // all the elements in Actual is NaN
    EXPECT_TRUE(MathHelper::IsNaN(actual.M11())
             && MathHelper::IsNaN(actual.M12())
             && MathHelper::IsNaN(actual.M13())
             && MathHelper::IsNaN(actual.M14())
             && MathHelper::IsNaN(actual.M21())
             && MathHelper::IsNaN(actual.M22())
             && MathHelper::IsNaN(actual.M23())
             && MathHelper::IsNaN(actual.M24())
             && MathHelper::IsNaN(actual.M31())
             && MathHelper::IsNaN(actual.M32())
             && MathHelper::IsNaN(actual.M33())
             && MathHelper::IsNaN(actual.M34())
             && MathHelper::IsNaN(actual.M41())
             && MathHelper::IsNaN(actual.M42())
             && MathHelper::IsNaN(actual.M43())
             && MathHelper::IsNaN(actual.M44()));
}

// A test for operator - (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, UnaryNegation)
{
    auto a = MatrixTest::GenerateMatrixNumberFrom1To16();

    Matrix expected;

    expected.M11(-1.0f);
    expected.M12(-2.0f);
    expected.M13(-3.0f);
    expected.M14(-4.0f);
    expected.M21(-5.0f);
    expected.M22(-6.0f);
    expected.M23(-7.0f);
    expected.M24(-8.0f);
    expected.M31(-9.0f);
    expected.M32(-10.0f);
    expected.M33(-11.0f);
    expected.M34(-12.0f);
    expected.M41(-13.0f);
    expected.M42(-14.0f);
    expected.M43(-15.0f);
    expected.M44(-16.0f);

    auto actual = -a;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator - (Matrix4x4, Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, Subtraction)
{
    auto a = MatrixTest::GenerateMatrixNumberFrom1To16();
    auto b = MatrixTest::GenerateMatrixNumberFrom1To16();

    Matrix expected;

    auto actual = a - b;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator * (Matrix4x4, Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, MultiplyTest1)
{
    auto a = MatrixTest::GenerateMatrixNumberFrom1To16();
    auto b = MatrixTest::GenerateMatrixNumberFrom1To16();

    Matrix expected;

    expected.M11(a.M11() * b.M11() + a.M12() * b.M21() + a.M13() * b.M31() + a.M14() * b.M41());
    expected.M12(a.M11() * b.M12() + a.M12() * b.M22() + a.M13() * b.M32() + a.M14() * b.M42());
    expected.M13(a.M11() * b.M13() + a.M12() * b.M23() + a.M13() * b.M33() + a.M14() * b.M43());
    expected.M14(a.M11() * b.M14() + a.M12() * b.M24() + a.M13() * b.M34() + a.M14() * b.M44());

    expected.M21(a.M21() * b.M11() + a.M22() * b.M21() + a.M23() * b.M31() + a.M24() * b.M41());
    expected.M22(a.M21() * b.M12() + a.M22() * b.M22() + a.M23() * b.M32() + a.M24() * b.M42());
    expected.M23(a.M21() * b.M13() + a.M22() * b.M23() + a.M23() * b.M33() + a.M24() * b.M43());
    expected.M24(a.M21() * b.M14() + a.M22() * b.M24() + a.M23() * b.M34() + a.M24() * b.M44());

    expected.M31(a.M31() * b.M11() + a.M32() * b.M21() + a.M33() * b.M31() + a.M34() * b.M41());
    expected.M32(a.M31() * b.M12() + a.M32() * b.M22() + a.M33() * b.M32() + a.M34() * b.M42());
    expected.M33(a.M31() * b.M13() + a.M32() * b.M23() + a.M33() * b.M33() + a.M34() * b.M43());
    expected.M34(a.M31() * b.M14() + a.M32() * b.M24() + a.M33() * b.M34() + a.M34() * b.M44());

    expected.M41(a.M41() * b.M11() + a.M42() * b.M21() + a.M43() * b.M31() + a.M44() * b.M41());
    expected.M42(a.M41() * b.M12() + a.M42() * b.M22() + a.M43() * b.M32() + a.M44() * b.M42());
    expected.M43(a.M41() * b.M13() + a.M42() * b.M23() + a.M43() * b.M33() + a.M44() * b.M43());
    expected.M44(a.M41() * b.M14() + a.M42() * b.M24() + a.M43() * b.M34() + a.M44() * b.M44());

    auto actual = a * b;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator * (Matrix4x4, Matrix4x4)
// Multiply with identity matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, MultiplyTest2)
{
    Matrix a = { 1.0f , 2.0f  , 3.0f , 4.0f
               , 5.0f , -6.0f , 7.0f , -8.0f
               , 9.0f , 10.0f , 11.0f, 12.0f
               , 13.0f, -14.0f, 15.0f, -16.0f };

    auto b = Matrix::Identity;

    auto expected = a;
    auto actual   = a * b;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator + (Matrix4x4, Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, Addition)
{
    auto a = MatrixTest::GenerateMatrixNumberFrom1To16();
    auto b = MatrixTest::GenerateMatrixNumberFrom1To16();

    Matrix expected = { a.M11() + b.M11(), a.M12() + b.M12(), a.M13() + b.M13(), a.M14() + b.M14()
                      , a.M21() + b.M21(), a.M22() + b.M22(), a.M23() + b.M23(), a.M24() + b.M24()
                      , a.M31() + b.M31(), a.M32() + b.M32(), a.M33() + b.M33(), a.M34() + b.M34()
                      , a.M41() + b.M41(), a.M42() + b.M42(), a.M43() + b.M43(), a.M44() + b.M44() };

    auto actual = a + b;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transpose (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, Transpose)
{
    auto a = MatrixTest::GenerateMatrixNumberFrom1To16();

    Matrix expected = { a.M11(), a.M21(), a.M31(), a.M41()
                      , a.M12(), a.M22(), a.M32(), a.M42()
                      , a.M13(), a.M23(), a.M33(), a.M43()
                      , a.M14(), a.M24(), a.M34(), a.M44() };

    auto actual = Matrix::Transpose(a);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transpose (Matrix4x4)
// Transpose Identity matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, TransposeIdentityMatrix)
{
    auto a        = Matrix::Identity;
    auto expected = Matrix::Identity;
    auto actual   = Matrix::Transpose(a);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Matrix4x4 (Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateFromQuaternion)
{
    auto axis = Vector3::Normalize({ 1.0f, 2.0f, 3.0f });
    auto q    = Quaternion::CreateFromAxisAngle(axis, MathHelper::ToRadians(30.0f));

    Matrix expected = { 0.875595033f, 0.420031041f, -0.2385524f , 0.0f
                      , -0.38175258f, 0.904303849f, 0.1910483f  , 0.0f
                      , 0.295970082f, -0.07621294f, 0.952151954f, 0.0f
                      , 0.0f        , 0.0f        , 0.0f        , 1.0f };

    auto target = Matrix::CreateFromQuaternion(q);

    EXPECT_TRUE(EqualityHelper::Equal(expected, target));
}

// A test for FromQuaternion (Matrix4x4)
// Convert X axis rotation matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateFromQuaternionConvertXAxisRotationMatrix)
{
    for (Single angle = 0.0f; angle < 720.0f; angle += 10.0f)
    {
        auto quat     = Quaternion::CreateFromAxisAngle(Vector3::UnitX, angle);
        auto expected = Matrix::CreateRotationX(angle);
        auto actual   = Matrix::CreateFromQuaternion(quat);

        EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

        // make sure convert back to quaternion is same as we passed quaternion.
        auto q2 = Quaternion::CreateFromRotationMatrix(actual);

        EXPECT_TRUE(EqualityHelper::EqualRotation(quat, q2));
    }
}

/*
// A test for FromQuaternion (Matrix4x4)
// Convert Y axis rotation matrix
[Fact]
public void Matrix4x4FromQuaternionTest3()
{
    for (float angle = 0.0f; angle < 720.0f; angle += 10.0f)
    {
        Quaternion quat = Quaternion.CreateFromAxisAngle(Vector3.UnitY, angle);

        Matrix4x4 expected = Matrix4x4.CreateRotationY(angle);
        Matrix4x4 actual = Matrix4x4.CreateFromQuaternion(quat);
        Assert.True(MathHelper.Equal(expected, actual),
                    string.Format("Quaternion.FromQuaternion did not return the expected value. angle:{0}",
                                  angle.ToString()));

        // make sure convert back to quaternion is same as we passed quaternion.
        Quaternion q2 = Quaternion.CreateFromRotationMatrix(actual);
        Assert.True(MathHelper.EqualRotation(quat, q2),
                    string.Format("Quaternion.FromQuaternion did not return the expected value. angle:{0}",
                                  angle.ToString()));
    }
}

// A test for FromQuaternion (Matrix4x4)
// Convert Z axis rotation matrix
[Fact]
public void Matrix4x4FromQuaternionTest4()
{
    for (float angle = 0.0f; angle < 720.0f; angle += 10.0f)
    {
        Quaternion quat = Quaternion.CreateFromAxisAngle(Vector3.UnitZ, angle);

        Matrix4x4 expected = Matrix4x4.CreateRotationZ(angle);
        Matrix4x4 actual = Matrix4x4.CreateFromQuaternion(quat);
        Assert.True(MathHelper.Equal(expected, actual),
                    string.Format("Quaternion.FromQuaternion did not return the expected value. angle:{0}",
                                  angle.ToString()));

        // make sure convert back to quaternion is same as we passed quaternion.
        Quaternion q2 = Quaternion.CreateFromRotationMatrix(actual);
        Assert.True(MathHelper.EqualRotation(quat, q2),
                    string.Format("Quaternion.FromQuaternion did not return the expected value. angle:{0}",
                                  angle.ToString()));
    }
}

// A test for FromQuaternion (Matrix4x4)
// Convert XYZ axis rotation matrix
[Fact]
public void Matrix4x4FromQuaternionTest5()
{
    for (float angle = 0.0f; angle < 720.0f; angle += 10.0f)
    {
        Quaternion quat =
                       Quaternion.CreateFromAxisAngle(Vector3.UnitZ, angle) *
                           Quaternion.CreateFromAxisAngle(Vector3.UnitY, angle) *
                           Quaternion.CreateFromAxisAngle(Vector3.UnitX, angle);

        Matrix4x4 expected =
                      Matrix4x4.CreateRotationX(angle) *
                          Matrix4x4.CreateRotationY(angle) *
                          Matrix4x4.CreateRotationZ(angle);
        Matrix4x4 actual = Matrix4x4.CreateFromQuaternion(quat);
        Assert.True(MathHelper.Equal(expected, actual),
                    string.Format("Quaternion.FromQuaternion did not return the expected value. angle:{0}",
                                  angle.ToString()));

        // make sure convert back to quaternion is same as we passed quaternion.
        Quaternion q2 = Quaternion.CreateFromRotationMatrix(actual);
        Assert.True(MathHelper.EqualRotation(quat, q2),
                    string.Format("Quaternion.FromQuaternion did not return the expected value. angle:{0}",
                                  angle.ToString()));
    }
}

// A test for ToString ()
[Fact]
public void Matrix4x4ToStringTest()
{
    Matrix4x4 a = new Matrix4x4();
    a.M11 = 11.0f;
    a.M12 = -12.0f;
    a.M13 = -13.3f;
    a.M14 = 14.4f;
    a.M21 = 21.0f;
    a.M22 = 22.0f;
    a.M23 = 23.0f;
    a.M24 = 24.0f;
    a.M31 = 31.0f;
    a.M32 = 32.0f;
    a.M33 = 33.0f;
    a.M34 = 34.0f;
    a.M41 = 41.0f;
    a.M42 = 42.0f;
    a.M43 = 43.0f;
    a.M44 = 44.0f;

    string expected = String.Format(CultureInfo.CurrentCulture,
                                    "{{ {{M11:{0} M12:{1} M13:{2} M14:{3}}} {{M21:{4} M22:{5} M23:{6} M24:{7}}} {{M31:{8} M32:{9} M33:{10} M34:{11}}} {{M41:{12} M42:{13} M43:{14} M44:{15}}} }}",
                                    11.0f, -12.0f, -13.3f, 14.4f,
                                    21.0f, 22.0f, 23.0f, 24.0f,
                                    31.0f, 32.0f, 33.0f, 34.0f,
                                    41.0f, 42.0f, 43.0f, 44.0f);

    string actual = a.ToString();
    Assert.Equal(expected, actual);
}

// A test for Add (Matrix4x4, Matrix4x4)
[Fact]
public void Matrix4x4AddTest()
{
    Matrix4x4 a = GenerateMatrixNumberFrom1To16();
    Matrix4x4 b = GenerateMatrixNumberFrom1To16();

    Matrix4x4 expected = new Matrix4x4();
    expected.M11 = a.M11 + b.M11;
    expected.M12 = a.M12 + b.M12;
    expected.M13 = a.M13 + b.M13;
    expected.M14 = a.M14 + b.M14;
    expected.M21 = a.M21 + b.M21;
    expected.M22 = a.M22 + b.M22;
    expected.M23 = a.M23 + b.M23;
    expected.M24 = a.M24 + b.M24;
    expected.M31 = a.M31 + b.M31;
    expected.M32 = a.M32 + b.M32;
    expected.M33 = a.M33 + b.M33;
    expected.M34 = a.M34 + b.M34;
    expected.M41 = a.M41 + b.M41;
    expected.M42 = a.M42 + b.M42;
    expected.M43 = a.M43 + b.M43;
    expected.M44 = a.M44 + b.M44;

    Matrix4x4 actual;

    actual = Matrix4x4.Add(a, b);
    Assert.Equal(expected, actual);
}

// A test for Equals (object)
[Fact]
public void Matrix4x4EqualsTest()
{
    Matrix4x4 a = GenerateMatrixNumberFrom1To16();
    Matrix4x4 b = GenerateMatrixNumberFrom1To16();

    // case 1: compare between same values
    object obj = b;

    bool expected = true;
    bool actual = a.Equals(obj);
    Assert.Equal(expected, actual);

    // case 2: compare between different values
    b.M11 = 11.0f;
    obj = b;
    expected = false;
    actual = a.Equals(obj);
    Assert.Equal(expected, actual);

    // case 3: compare between different types.
    obj = new Vector4();
    expected = false;
    actual = a.Equals(obj);
    Assert.Equal(expected, actual);

    // case 3: compare against null.
    obj = null;
    expected = false;
    actual = a.Equals(obj);
    Assert.Equal(expected, actual);
}

// A test for GetHashCode ()
[Fact]
public void Matrix4x4GetHashCodeTest()
{
    Matrix4x4 target = GenerateMatrixNumberFrom1To16();
    int expected = target.M11.GetHashCode() + target.M12.GetHashCode() + target.M13.GetHashCode() + target.M14.GetHashCode() +
        target.M21.GetHashCode() + target.M22.GetHashCode() + target.M23.GetHashCode() + target.M24.GetHashCode() +
        target.M31.GetHashCode() + target.M32.GetHashCode() + target.M33.GetHashCode() + target.M34.GetHashCode() +
        target.M41.GetHashCode() + target.M42.GetHashCode() + target.M43.GetHashCode() + target.M44.GetHashCode();
    int actual;

    actual = target.GetHashCode();
    Assert.Equal(expected, actual);
}

// A test for Multiply (Matrix4x4, Matrix4x4)
[Fact]
public void Matrix4x4MultiplyTest3()
{
    Matrix4x4 a = GenerateMatrixNumberFrom1To16();
    Matrix4x4 b = GenerateMatrixNumberFrom1To16();

    Matrix4x4 expected = new Matrix4x4();
    expected.M11 = a.M11 * b.M11 + a.M12 * b.M21 + a.M13 * b.M31 + a.M14 * b.M41;
    expected.M12 = a.M11 * b.M12 + a.M12 * b.M22 + a.M13 * b.M32 + a.M14 * b.M42;
    expected.M13 = a.M11 * b.M13 + a.M12 * b.M23 + a.M13 * b.M33 + a.M14 * b.M43;
    expected.M14 = a.M11 * b.M14 + a.M12 * b.M24 + a.M13 * b.M34 + a.M14 * b.M44;

    expected.M21 = a.M21 * b.M11 + a.M22 * b.M21 + a.M23 * b.M31 + a.M24 * b.M41;
    expected.M22 = a.M21 * b.M12 + a.M22 * b.M22 + a.M23 * b.M32 + a.M24 * b.M42;
    expected.M23 = a.M21 * b.M13 + a.M22 * b.M23 + a.M23 * b.M33 + a.M24 * b.M43;
    expected.M24 = a.M21 * b.M14 + a.M22 * b.M24 + a.M23 * b.M34 + a.M24 * b.M44;

    expected.M31 = a.M31 * b.M11 + a.M32 * b.M21 + a.M33 * b.M31 + a.M34 * b.M41;
    expected.M32 = a.M31 * b.M12 + a.M32 * b.M22 + a.M33 * b.M32 + a.M34 * b.M42;
    expected.M33 = a.M31 * b.M13 + a.M32 * b.M23 + a.M33 * b.M33 + a.M34 * b.M43;
    expected.M34 = a.M31 * b.M14 + a.M32 * b.M24 + a.M33 * b.M34 + a.M34 * b.M44;

    expected.M41 = a.M41 * b.M11 + a.M42 * b.M21 + a.M43 * b.M31 + a.M44 * b.M41;
    expected.M42 = a.M41 * b.M12 + a.M42 * b.M22 + a.M43 * b.M32 + a.M44 * b.M42;
    expected.M43 = a.M41 * b.M13 + a.M42 * b.M23 + a.M43 * b.M33 + a.M44 * b.M43;
    expected.M44 = a.M41 * b.M14 + a.M42 * b.M24 + a.M43 * b.M34 + a.M44 * b.M44;
    Matrix4x4 actual;
    actual = Matrix4x4.Multiply(a, b);

    Assert.Equal(expected, actual);
}

// A test for Multiply (Matrix4x4, float)
[Fact]
public void Matrix4x4MultiplyTest5()
{
    Matrix4x4 a = GenerateMatrixNumberFrom1To16();
    Matrix4x4 expected = new Matrix4x4(3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48);
    Matrix4x4 actual = Matrix4x4.Multiply(a, 3);

    Assert.Equal(expected, actual);
}

// A test for Multiply (Matrix4x4, float)
[Fact]
public void Matrix4x4MultiplyTest6()
{
    Matrix4x4 a = GenerateMatrixNumberFrom1To16();
    Matrix4x4 expected = new Matrix4x4(3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48);
    Matrix4x4 actual = a * 3;

    Assert.Equal(expected, actual);
}

// A test for Negate (Matrix4x4)
[Fact]
public void Matrix4x4NegateTest()
{
    Matrix4x4 m = GenerateMatrixNumberFrom1To16();

    Matrix4x4 expected = new Matrix4x4();
    expected.M11 = -1.0f;
    expected.M12 = -2.0f;
    expected.M13 = -3.0f;
    expected.M14 = -4.0f;
    expected.M21 = -5.0f;
    expected.M22 = -6.0f;
    expected.M23 = -7.0f;
    expected.M24 = -8.0f;
    expected.M31 = -9.0f;
    expected.M32 = -10.0f;
    expected.M33 = -11.0f;
    expected.M34 = -12.0f;
    expected.M41 = -13.0f;
    expected.M42 = -14.0f;
    expected.M43 = -15.0f;
    expected.M44 = -16.0f;
    Matrix4x4 actual;

    actual = Matrix4x4.Negate(m);
    Assert.Equal(expected, actual);
}

// A test for operator != (Matrix4x4, Matrix4x4)
[Fact]
public void Matrix4x4InequalityTest()
{
    Matrix4x4 a = GenerateMatrixNumberFrom1To16();
    Matrix4x4 b = GenerateMatrixNumberFrom1To16();

    // case 1: compare between same values
    bool expected = false;
    bool actual = a != b;
    Assert.Equal(expected, actual);

    // case 2: compare between different values
    b.M11 = 11.0f;
    expected = true;
    actual = a != b;
    Assert.Equal(expected, actual);
}

// A test for operator == (Matrix4x4, Matrix4x4)
[Fact]
public void Matrix4x4EqualityTest()
{
    Matrix4x4 a = GenerateMatrixNumberFrom1To16();
    Matrix4x4 b = GenerateMatrixNumberFrom1To16();

    // case 1: compare between same values
    bool expected = true;
    bool actual = a == b;
    Assert.Equal(expected, actual);

    // case 2: compare between different values
    b.M11 = 11.0f;
    expected = false;
    actual = a == b;
    Assert.Equal(expected, actual);
}

// A test for Subtract (Matrix4x4, Matrix4x4)
[Fact]
public void Matrix4x4SubtractTest()
{
    Matrix4x4 a = GenerateMatrixNumberFrom1To16();
    Matrix4x4 b = GenerateMatrixNumberFrom1To16();
    Matrix4x4 expected = new Matrix4x4();
    Matrix4x4 actual;

    actual = Matrix4x4.Subtract(a, b);
    Assert.Equal(expected, actual);
}

private void CreateBillboardFact(Vector3 placeDirection, Vector3 cameraUpVector, Matrix4x4 expectedRotation)
{
    Vector3 cameraPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 objectPosition = cameraPosition + placeDirection * 10.0f;
    Matrix4x4 expected = expectedRotation * Matrix4x4.CreateTranslation(objectPosition);
    Matrix4x4 actual = Matrix4x4.CreateBillboard(objectPosition, cameraPosition, cameraUpVector, new Vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix4x4.CreateBillboard did not return the expected value.");
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Forward side of camera on XZ-plane
[Fact]
public void Matrix4x4CreateBillboardTest01()
{
    // Object placed at Forward of camera. result must be same as 180 degrees rotate along y-axis.
    CreateBillboardFact(new Vector3(0, 0, -1), new Vector3(0, 1, 0), Matrix4x4.CreateRotationY(MathHelper.ToRadians(180.0f)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Backward side of camera on XZ-plane
[Fact]
public void Matrix4x4CreateBillboardTest02()
{
    // Object placed at Backward of camera. This result must be same as 0 degrees rotate along y-axis.
    CreateBillboardFact(new Vector3(0, 0, 1), new Vector3(0, 1, 0), Matrix4x4.CreateRotationY(MathHelper.ToRadians(0)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Right side of camera on XZ-plane
[Fact]
public void Matrix4x4CreateBillboardTest03()
{
    // Place object at Right side of camera. This result must be same as 90 degrees rotate along y-axis.
    CreateBillboardFact(new Vector3(1, 0, 0), new Vector3(0, 1, 0), Matrix4x4.CreateRotationY(MathHelper.ToRadians(90)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Left side of camera on XZ-plane
[Fact]
public void Matrix4x4CreateBillboardTest04()
{
    // Place object at Left side of camera. This result must be same as -90 degrees rotate along y-axis.
    CreateBillboardFact(new Vector3(-1, 0, 0), new Vector3(0, 1, 0), Matrix4x4.CreateRotationY(MathHelper.ToRadians(-90)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Up side of camera on XY-plane
[Fact]
public void Matrix4x4CreateBillboardTest05()
{
    // Place object at Up side of camera. result must be same as 180 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateBillboardFact(new Vector3(0, 1, 0), new Vector3(0, 0, 1),
                        Matrix4x4.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix4x4.CreateRotationZ(MathHelper.ToRadians(180)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Down side of camera on XY-plane
[Fact]
public void Matrix4x4CreateBillboardTest06()
{
    // Place object at Down side of camera. result must be same as 0 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateBillboardFact(new Vector3(0, -1, 0), new Vector3(0, 0, 1),
                        Matrix4x4.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix4x4.CreateRotationZ(MathHelper.ToRadians(0)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Right side of camera on XY-plane
[Fact]
public void Matrix4x4CreateBillboardTest07()
{
    // Place object at Right side of camera. result must be same as 90 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateBillboardFact(new Vector3(1, 0, 0), new Vector3(0, 0, 1),
                        Matrix4x4.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix4x4.CreateRotationZ(MathHelper.ToRadians(90.0f)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Left side of camera on XY-plane
[Fact]
public void Matrix4x4CreateBillboardTest08()
{
    // Place object at Left side of camera. result must be same as -90 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateBillboardFact(new Vector3(-1, 0, 0), new Vector3(0, 0, 1),
                        Matrix4x4.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix4x4.CreateRotationZ(MathHelper.ToRadians(-90.0f)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Up side of camera on YZ-plane
[Fact]
public void Matrix4x4CreateBillboardTest09()
{
    // Place object at Up side of camera. result must be same as -90 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateBillboardFact(new Vector3(0, 1, 0), new Vector3(-1, 0, 0),
                        Matrix4x4.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix4x4.CreateRotationX(MathHelper.ToRadians(-90.0f)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Down side of camera on YZ-plane
[Fact]
public void Matrix4x4CreateBillboardTest10()
{
    // Place object at Down side of camera. result must be same as 90 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateBillboardFact(new Vector3(0, -1, 0), new Vector3(-1, 0, 0),
                        Matrix4x4.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix4x4.CreateRotationX(MathHelper.ToRadians(90.0f)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Forward side of camera on YZ-plane
[Fact]
public void Matrix4x4CreateBillboardTest11()
{
    // Place object at Forward side of camera. result must be same as 180 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateBillboardFact(new Vector3(0, 0, -1), new Vector3(-1, 0, 0),
                        Matrix4x4.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix4x4.CreateRotationX(MathHelper.ToRadians(180.0f)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Backward side of camera on YZ-plane
[Fact]
public void Matrix4x4CreateBillboardTest12()
{
    // Place object at Backward side of camera. result must be same as 0 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateBillboardFact(new Vector3(0, 0, 1), new Vector3(-1, 0, 0),
                        Matrix4x4.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix4x4.CreateRotationX(MathHelper.ToRadians(0.0f)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Object and camera positions are too close and doesn't pass cameraFowardVector.
[Fact]
public void Matrix4x4CreateBillboardTooCloseTest1()
{
    Vector3 objectPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 cameraPosition = objectPosition;
    Vector3 cameraUpVector = new Vector3(0, 1, 0);

    // Doesn't pass camera face direction. CreateBillboard uses new Vector3f(0, 0, -1) direction. Result must be same as 180 degrees rotate along y-axis.
    Matrix4x4 expected = Matrix4x4.CreateRotationY(MathHelper.ToRadians(180.0f)) * Matrix4x4.CreateTranslation(objectPosition);
    Matrix4x4 actual = Matrix4x4.CreateBillboard(objectPosition, cameraPosition, cameraUpVector, new Vector3(0, 0, 1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix4x4.CreateBillboard did not return the expected value.");
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Object and camera positions are too close and passed cameraFowardVector.
[Fact]
public void Matrix4x4CreateBillboardTooCloseTest2()
{
    Vector3 objectPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 cameraPosition = objectPosition;
    Vector3 cameraUpVector = new Vector3(0, 1, 0);

    // Passes Vector3f.Rgiht as camera face direction. Result must be same as -90 degrees rotate along y-axis.
    Matrix4x4 expected = Matrix4x4.CreateRotationY(MathHelper.ToRadians(-90.0f)) * Matrix4x4.CreateTranslation(objectPosition);
    Matrix4x4 actual = Matrix4x4.CreateBillboard(objectPosition, cameraPosition, cameraUpVector, new Vector3(1, 0, 0));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix4x4.CreateBillboard did not return the expected value.");
}

private void CreateConstrainedBillboardFact(Vector3 placeDirection, Vector3 rotateAxis, Matrix4x4 expectedRotation)
{
    Vector3 cameraPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 objectPosition = cameraPosition + placeDirection * 10.0f;
    Matrix4x4 expected = expectedRotation * Matrix4x4.CreateTranslation(objectPosition);
    Matrix4x4 actual = Matrix4x4.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new Vector3(0, 0, -1), new Vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix4x4.CreateConstrainedBillboard did not return the expected value.");

    // When you move camera along rotateAxis, result must be same.
    cameraPosition += rotateAxis * 10.0f;
    actual = Matrix4x4.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new Vector3(0, 0, -1), new Vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix4x4.CreateConstrainedBillboard did not return the expected value.");

    cameraPosition -= rotateAxis * 30.0f;
    actual = Matrix4x4.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new Vector3(0, 0, -1), new Vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix4x4.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Forward side of camera on XZ-plane
[Fact]
public void Matrix4x4CreateConstrainedBillboardTest01()
{
    // Object placed at Forward of camera. result must be same as 180 degrees rotate along y-axis.
    CreateConstrainedBillboardFact(new Vector3(0, 0, -1), new Vector3(0, 1, 0), Matrix4x4.CreateRotationY(MathHelper.ToRadians(180.0f)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Backward side of camera on XZ-plane
[Fact]
public void Matrix4x4CreateConstrainedBillboardTest02()
{
    // Object placed at Backward of camera. This result must be same as 0 degrees rotate along y-axis.
    CreateConstrainedBillboardFact(new Vector3(0, 0, 1), new Vector3(0, 1, 0), Matrix4x4.CreateRotationY(MathHelper.ToRadians(0)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Right side of camera on XZ-plane
[Fact]
public void Matrix4x4CreateConstrainedBillboardTest03()
{
    // Place object at Right side of camera. This result must be same as 90 degrees rotate along y-axis.
    CreateConstrainedBillboardFact(new Vector3(1, 0, 0), new Vector3(0, 1, 0), Matrix4x4.CreateRotationY(MathHelper.ToRadians(90)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Left side of camera on XZ-plane
[Fact]
public void Matrix4x4CreateConstrainedBillboardTest04()
{
    // Place object at Left side of camera. This result must be same as -90 degrees rotate along y-axis.
    CreateConstrainedBillboardFact(new Vector3(-1, 0, 0), new Vector3(0, 1, 0), Matrix4x4.CreateRotationY(MathHelper.ToRadians(-90)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Up side of camera on XY-plane
[Fact]
public void Matrix4x4CreateConstrainedBillboardTest05()
{
    // Place object at Up side of camera. result must be same as 180 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateConstrainedBillboardFact(new Vector3(0, 1, 0), new Vector3(0, 0, 1),
                                   Matrix4x4.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix4x4.CreateRotationZ(MathHelper.ToRadians(180)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Down side of camera on XY-plane
[Fact]
public void Matrix4x4CreateConstrainedBillboardTest06()
{
    // Place object at Down side of camera. result must be same as 0 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateConstrainedBillboardFact(new Vector3(0, -1, 0), new Vector3(0, 0, 1),
                                   Matrix4x4.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix4x4.CreateRotationZ(MathHelper.ToRadians(0)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Right side of camera on XY-plane
[Fact]
public void Matrix4x4CreateConstrainedBillboardTest07()
{
    // Place object at Right side of camera. result must be same as 90 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateConstrainedBillboardFact(new Vector3(1, 0, 0), new Vector3(0, 0, 1),
                                   Matrix4x4.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix4x4.CreateRotationZ(MathHelper.ToRadians(90.0f)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Left side of camera on XY-plane
[Fact]
public void Matrix4x4CreateConstrainedBillboardTest08()
{
    // Place object at Left side of camera. result must be same as -90 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateConstrainedBillboardFact(new Vector3(-1, 0, 0), new Vector3(0, 0, 1),
                                   Matrix4x4.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix4x4.CreateRotationZ(MathHelper.ToRadians(-90.0f)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Up side of camera on YZ-plane
[Fact]
public void Matrix4x4CreateConstrainedBillboardTest09()
{
    // Place object at Up side of camera. result must be same as -90 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateConstrainedBillboardFact(new Vector3(0, 1, 0), new Vector3(-1, 0, 0),
                                   Matrix4x4.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix4x4.CreateRotationX(MathHelper.ToRadians(-90.0f)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Down side of camera on YZ-plane
[Fact]
public void Matrix4x4CreateConstrainedBillboardTest10()
{
    // Place object at Down side of camera. result must be same as 90 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateConstrainedBillboardFact(new Vector3(0, -1, 0), new Vector3(-1, 0, 0),
                                   Matrix4x4.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix4x4.CreateRotationX(MathHelper.ToRadians(90.0f)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Forward side of camera on YZ-plane
[Fact]
public void Matrix4x4CreateConstrainedBillboardTest11()
{
    // Place object at Forward side of camera. result must be same as 180 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateConstrainedBillboardFact(new Vector3(0, 0, -1), new Vector3(-1, 0, 0),
                                   Matrix4x4.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix4x4.CreateRotationX(MathHelper.ToRadians(180.0f)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Backward side of camera on YZ-plane
[Fact]
public void Matrix4x4CreateConstrainedBillboardTest12()
{
    // Place object at Backward side of camera. result must be same as 0 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateConstrainedBillboardFact(new Vector3(0, 0, 1), new Vector3(-1, 0, 0),
                                   Matrix4x4.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix4x4.CreateRotationX(MathHelper.ToRadians(0.0f)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Object and camera positions are too close and doesn't pass cameraForwardVector.
[Fact]
public void Matrix4x4CreateConstrainedBillboardTooCloseTest1()
{
    Vector3 objectPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 cameraPosition = objectPosition;
    Vector3 cameraUpVector = new Vector3(0, 1, 0);

    // Doesn't pass camera face direction. CreateConstrainedBillboard uses new Vector3f(0, 0, -1) direction. Result must be same as 180 degrees rotate along y-axis.
    Matrix4x4 expected = Matrix4x4.CreateRotationY(MathHelper.ToRadians(180.0f)) * Matrix4x4.CreateTranslation(objectPosition);
    Matrix4x4 actual = Matrix4x4.CreateConstrainedBillboard(objectPosition, cameraPosition, cameraUpVector, new Vector3(0, 0, 1), new Vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix4x4.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Object and camera positions are too close and passed cameraForwardVector.
[Fact]
public void Matrix4x4CreateConstrainedBillboardTooCloseTest2()
{
    Vector3 objectPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 cameraPosition = objectPosition;
    Vector3 cameraUpVector = new Vector3(0, 1, 0);

    // Passes Vector3f.Rgiht as camera face direction. Result must be same as -90 degrees rotate along y-axis.
    Matrix4x4 expected = Matrix4x4.CreateRotationY(MathHelper.ToRadians(-90.0f)) * Matrix4x4.CreateTranslation(objectPosition);
    Matrix4x4 actual = Matrix4x4.CreateConstrainedBillboard(objectPosition, cameraPosition, cameraUpVector, new Vector3(1, 0, 0), new Vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix4x4.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Angle between rotateAxis and camera to object vector is too small. And use doesn't passed objectForwardVector parameter.
[Fact]
public void Matrix4x4CreateConstrainedBillboardAlongAxisTest1()
{
    // Place camera at up side of object.
    Vector3 objectPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 rotateAxis = new Vector3(0, 1, 0);
    Vector3 cameraPosition = objectPosition + rotateAxis * 10.0f;

    // In this case, CreateConstrainedBillboard picks new Vector3f(0, 0, -1) as object forward vector.
    Matrix4x4 expected = Matrix4x4.CreateRotationY(MathHelper.ToRadians(180.0f)) * Matrix4x4.CreateTranslation(objectPosition);
    Matrix4x4 actual = Matrix4x4.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new Vector3(0, 0, -1), new Vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix4x4.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Angle between rotateAxis and camera to object vector is too small. And user doesn't passed objectForwardVector parameter.
[Fact]
public void Matrix4x4CreateConstrainedBillboardAlongAxisTest2()
{
    // Place camera at up side of object.
    Vector3 objectPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 rotateAxis = new Vector3(0, 0, -1);
    Vector3 cameraPosition = objectPosition + rotateAxis * 10.0f;

    // In this case, CreateConstrainedBillboard picks new Vector3f(1, 0, 0) as object forward vector.
    Matrix4x4 expected = Matrix4x4.CreateRotationX(MathHelper.ToRadians(-90.0f)) * Matrix4x4.CreateRotationZ(MathHelper.ToRadians(-90.0f)) * Matrix4x4.CreateTranslation(objectPosition);
    Matrix4x4 actual = Matrix4x4.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new Vector3(0, 0, -1), new Vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix4x4.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Angle between rotateAxis and camera to object vector is too small. And user passed correct objectForwardVector parameter.
[Fact]
public void Matrix4x4CreateConstrainedBillboardAlongAxisTest3()
{
    // Place camera at up side of object.
    Vector3 objectPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 rotateAxis = new Vector3(0, 1, 0);
    Vector3 cameraPosition = objectPosition + rotateAxis * 10.0f;

    // User passes correct objectForwardVector.
    Matrix4x4 expected = Matrix4x4.CreateRotationY(MathHelper.ToRadians(180.0f)) * Matrix4x4.CreateTranslation(objectPosition);
    Matrix4x4 actual = Matrix4x4.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new Vector3(0, 0, -1), new Vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix4x4.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Angle between rotateAxis and camera to object vector is too small. And user passed incorrect objectForwardVector parameter.
[Fact]
public void Matrix4x4CreateConstrainedBillboardAlongAxisTest4()
{
    // Place camera at up side of object.
    Vector3 objectPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 rotateAxis = new Vector3(0, 1, 0);
    Vector3 cameraPosition = objectPosition + rotateAxis * 10.0f;

    // User passes correct objectForwardVector.
    Matrix4x4 expected = Matrix4x4.CreateRotationY(MathHelper.ToRadians(180.0f)) * Matrix4x4.CreateTranslation(objectPosition);
    Matrix4x4 actual = Matrix4x4.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new Vector3(0, 0, -1), new Vector3(0, 1, 0));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix4x4.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Angle between rotateAxis and camera to object vector is too small. And user passed incorrect objectForwardVector parameter.
[Fact]
public void Matrix4x4CreateConstrainedBillboardAlongAxisTest5()
{
    // Place camera at up side of object.
    Vector3 objectPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 rotateAxis = new Vector3(0, 0, -1);
    Vector3 cameraPosition = objectPosition + rotateAxis * 10.0f;

    // In this case, CreateConstrainedBillboard picks Vector3f.Right as object forward vector.
    Matrix4x4 expected = Matrix4x4.CreateRotationX(MathHelper.ToRadians(-90.0f)) * Matrix4x4.CreateRotationZ(MathHelper.ToRadians(-90.0f)) * Matrix4x4.CreateTranslation(objectPosition);
    Matrix4x4 actual = Matrix4x4.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new Vector3(0, 0, -1), new Vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix4x4.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateScale (Vector3f)
[Fact]
public void Matrix4x4CreateScaleTest1()
{
    Vector3 scales = new Vector3(2.0f, 3.0f, 4.0f);
    Matrix4x4 expected = new Matrix4x4(
        2.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 3.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 4.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    Matrix4x4 actual = Matrix4x4.CreateScale(scales);
    Assert.Equal(expected, actual);
}

// A test for CreateScale (Vector3f, Vector3f)
[Fact]
public void Matrix4x4CreateScaleCenterTest1()
{
    Vector3 scale = new Vector3(3, 4, 5);
    Vector3 center = new Vector3(23, 42, 666);

    Matrix4x4 scaleAroundZero = Matrix4x4.CreateScale(scale, Vector3.Zero);
    Matrix4x4 scaleAroundZeroExpected = Matrix4x4.CreateScale(scale);
    Assert.True(MathHelper.Equal(scaleAroundZero, scaleAroundZeroExpected));

    Matrix4x4 scaleAroundCenter = Matrix4x4.CreateScale(scale, center);
    Matrix4x4 scaleAroundCenterExpected = Matrix4x4.CreateTranslation(-center) * Matrix4x4.CreateScale(scale) * Matrix4x4.CreateTranslation(center);
    Assert.True(MathHelper.Equal(scaleAroundCenter, scaleAroundCenterExpected));
}

// A test for CreateScale (float)
[Fact]
public void Matrix4x4CreateScaleTest2()
{
    float scale = 2.0f;
    Matrix4x4 expected = new Matrix4x4(
        2.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 2.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    Matrix4x4 actual = Matrix4x4.CreateScale(scale);
    Assert.Equal(expected, actual);
}

// A test for CreateScale (float, Vector3f)
[Fact]
public void Matrix4x4CreateScaleCenterTest2()
{
    float scale = 5;
    Vector3 center = new Vector3(23, 42, 666);

    Matrix4x4 scaleAroundZero = Matrix4x4.CreateScale(scale, Vector3.Zero);
    Matrix4x4 scaleAroundZeroExpected = Matrix4x4.CreateScale(scale);
    Assert.True(MathHelper.Equal(scaleAroundZero, scaleAroundZeroExpected));

    Matrix4x4 scaleAroundCenter = Matrix4x4.CreateScale(scale, center);
    Matrix4x4 scaleAroundCenterExpected = Matrix4x4.CreateTranslation(-center) * Matrix4x4.CreateScale(scale) * Matrix4x4.CreateTranslation(center);
    Assert.True(MathHelper.Equal(scaleAroundCenter, scaleAroundCenterExpected));
}

// A test for CreateScale (float, float, float)
[Fact]
public void Matrix4x4CreateScaleTest3()
{
    float xScale = 2.0f;
    float yScale = 3.0f;
    float zScale = 4.0f;
    Matrix4x4 expected = new Matrix4x4(
        2.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 3.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 4.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    Matrix4x4 actual = Matrix4x4.CreateScale(xScale, yScale, zScale);
    Assert.Equal(expected, actual);
}

// A test for CreateScale (float, float, float, Vector3f)
[Fact]
public void Matrix4x4CreateScaleCenterTest3()
{
    Vector3 scale = new Vector3(3, 4, 5);
    Vector3 center = new Vector3(23, 42, 666);

    Matrix4x4 scaleAroundZero = Matrix4x4.CreateScale(scale.X, scale.Y, scale.Z, Vector3.Zero);
    Matrix4x4 scaleAroundZeroExpected = Matrix4x4.CreateScale(scale.X, scale.Y, scale.Z);
    Assert.True(MathHelper.Equal(scaleAroundZero, scaleAroundZeroExpected));

    Matrix4x4 scaleAroundCenter = Matrix4x4.CreateScale(scale.X, scale.Y, scale.Z, center);
    Matrix4x4 scaleAroundCenterExpected = Matrix4x4.CreateTranslation(-center) * Matrix4x4.CreateScale(scale.X, scale.Y, scale.Z) * Matrix4x4.CreateTranslation(center);
    Assert.True(MathHelper.Equal(scaleAroundCenter, scaleAroundCenterExpected));
}

// A test for CreateTranslation (Vector3f)
[Fact]
public void Matrix4x4CreateTranslationTest1()
{
    Vector3 position = new Vector3(2.0f, 3.0f, 4.0f);
    Matrix4x4 expected = new Matrix4x4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        2.0f, 3.0f, 4.0f, 1.0f);

    Matrix4x4 actual = Matrix4x4.CreateTranslation(position);
    Assert.Equal(expected, actual);
}

// A test for CreateTranslation (float, float, float)
[Fact]
public void Matrix4x4CreateTranslationTest2()
{
    float xPosition = 2.0f;
    float yPosition = 3.0f;
    float zPosition = 4.0f;

    Matrix4x4 expected = new Matrix4x4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        2.0f, 3.0f, 4.0f, 1.0f);

    Matrix4x4 actual = Matrix4x4.CreateTranslation(xPosition, yPosition, zPosition);
    Assert.Equal(expected, actual);
}

// A test for Translation
[Fact]
public void Matrix4x4TranslationTest()
{
    Matrix4x4 a = GenerateTestMatrix();
    Matrix4x4 b = a;

    // Transfomed vector that has same semantics of property must be same.
    Vector3 val = new Vector3(a.M41, a.M42, a.M43);
    Assert.Equal(val, a.Translation);

    // Set value and get value must be same.
    val = new Vector3(1.0f, 2.0f, 3.0f);
    a.Translation = val;
    Assert.Equal(val, a.Translation);

    // Make sure it only modifies expected value of matrix.
    Assert.True(
        a.M11 == b.M11 && a.M12 == b.M12 && a.M13 == b.M13 && a.M14 == b.M14 &&
            a.M21 == b.M21 && a.M22 == b.M22 && a.M23 == b.M23 && a.M24 == b.M24 &&
            a.M31 == b.M31 && a.M32 == b.M32 && a.M33 == b.M33 && a.M34 == b.M34 &&
            a.M41 != b.M41 && a.M42 != b.M42 && a.M43 != b.M43 && a.M44 == b.M44);
}

// A test for Equals (Matrix4x4)
[Fact]
public void Matrix4x4EqualsTest1()
{
    Matrix4x4 a = GenerateMatrixNumberFrom1To16();
    Matrix4x4 b = GenerateMatrixNumberFrom1To16();

    // case 1: compare between same values
    bool expected = true;
    bool actual = a.Equals(b);
    Assert.Equal(expected, actual);

    // case 2: compare between different values
    b.M11 = 11.0f;
    expected = false;
    actual = a.Equals(b);
    Assert.Equal(expected, actual);
}

// A test for IsIdentity
[Fact]
public void Matrix4x4IsIdentityTest()
{
    Assert.True(Matrix4x4.Identity.IsIdentity);
    Assert.True(new Matrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).IsIdentity);
    Assert.False(new Matrix4x4(0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).IsIdentity);
    Assert.False(new Matrix4x4(1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).IsIdentity);
    Assert.False(new Matrix4x4(1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).IsIdentity);
    Assert.False(new Matrix4x4(1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).IsIdentity);
    Assert.False(new Matrix4x4(1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).IsIdentity);
    Assert.False(new Matrix4x4(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).IsIdentity);
    Assert.False(new Matrix4x4(1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1).IsIdentity);
    Assert.False(new Matrix4x4(1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1).IsIdentity);
    Assert.False(new Matrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1).IsIdentity);
    Assert.False(new Matrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1).IsIdentity);
    Assert.False(new Matrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1).IsIdentity);
    Assert.False(new Matrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1).IsIdentity);
    Assert.False(new Matrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1).IsIdentity);
    Assert.False(new Matrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1).IsIdentity);
    Assert.False(new Matrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1).IsIdentity);
    Assert.False(new Matrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0).IsIdentity);
}

// A test for Matrix4x4 (Matrix3x2)
[Fact]
public void Matrix4x4From3x2Test()
{
    Matrix3x2 source = new Matrix3x2(1, 2, 3, 4, 5, 6);
    Matrix4x4 result = new Matrix4x4(source);

    Assert.Equal(source.M11, result.M11);
    Assert.Equal(source.M12, result.M12);
    Assert.Equal(0f, result.M13);
    Assert.Equal(0f, result.M14);

    Assert.Equal(source.M21, result.M21);
    Assert.Equal(source.M22, result.M22);
    Assert.Equal(0f, result.M23);
    Assert.Equal(0f, result.M24);

    Assert.Equal(0f, result.M31);
    Assert.Equal(0f, result.M32);
    Assert.Equal(1f, result.M33);
    Assert.Equal(0f, result.M34);

    Assert.Equal(source.M31, result.M41);
    Assert.Equal(source.M32, result.M42);
    Assert.Equal(0f, result.M43);
    Assert.Equal(1f, result.M44);
}

// A test for Matrix4x4 comparison involving NaN values
[Fact]
public void Matrix4x4EqualsNanTest()
{
    Matrix4x4 a = new Matrix4x4(float.NaN, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    Matrix4x4 b = new Matrix4x4(0, float.NaN, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    Matrix4x4 c = new Matrix4x4(0, 0, float.NaN, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    Matrix4x4 d = new Matrix4x4(0, 0, 0, float.NaN, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    Matrix4x4 e = new Matrix4x4(0, 0, 0, 0, float.NaN, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    Matrix4x4 f = new Matrix4x4(0, 0, 0, 0, 0, float.NaN, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    Matrix4x4 g = new Matrix4x4(0, 0, 0, 0, 0, 0, float.NaN, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    Matrix4x4 h = new Matrix4x4(0, 0, 0, 0, 0, 0, 0, float.NaN, 0, 0, 0, 0, 0, 0, 0, 0);
    Matrix4x4 i = new Matrix4x4(0, 0, 0, 0, 0, 0, 0, 0, float.NaN, 0, 0, 0, 0, 0, 0, 0);
    Matrix4x4 j = new Matrix4x4(0, 0, 0, 0, 0, 0, 0, 0, 0, float.NaN, 0, 0, 0, 0, 0, 0);
    Matrix4x4 k = new Matrix4x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, float.NaN, 0, 0, 0, 0, 0);
    Matrix4x4 l = new Matrix4x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, float.NaN, 0, 0, 0, 0);
    Matrix4x4 m = new Matrix4x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, float.NaN, 0, 0, 0);
    Matrix4x4 n = new Matrix4x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, float.NaN, 0, 0);
    Matrix4x4 o = new Matrix4x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, float.NaN, 0);
    Matrix4x4 p = new Matrix4x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, float.NaN);

    Assert.False(a == new Matrix4x4());
    Assert.False(b == new Matrix4x4());
    Assert.False(c == new Matrix4x4());
    Assert.False(d == new Matrix4x4());
    Assert.False(e == new Matrix4x4());
    Assert.False(f == new Matrix4x4());
    Assert.False(g == new Matrix4x4());
    Assert.False(h == new Matrix4x4());
    Assert.False(i == new Matrix4x4());
    Assert.False(j == new Matrix4x4());
    Assert.False(k == new Matrix4x4());
    Assert.False(l == new Matrix4x4());
    Assert.False(m == new Matrix4x4());
    Assert.False(n == new Matrix4x4());
    Assert.False(o == new Matrix4x4());
    Assert.False(p == new Matrix4x4());

    Assert.True(a != new Matrix4x4());
    Assert.True(b != new Matrix4x4());
    Assert.True(c != new Matrix4x4());
    Assert.True(d != new Matrix4x4());
    Assert.True(e != new Matrix4x4());
    Assert.True(f != new Matrix4x4());
    Assert.True(g != new Matrix4x4());
    Assert.True(h != new Matrix4x4());
    Assert.True(i != new Matrix4x4());
    Assert.True(j != new Matrix4x4());
    Assert.True(k != new Matrix4x4());
    Assert.True(l != new Matrix4x4());
    Assert.True(m != new Matrix4x4());
    Assert.True(n != new Matrix4x4());
    Assert.True(o != new Matrix4x4());
    Assert.True(p != new Matrix4x4());

    Assert.False(a.Equals(new Matrix4x4()));
    Assert.False(b.Equals(new Matrix4x4()));
    Assert.False(c.Equals(new Matrix4x4()));
    Assert.False(d.Equals(new Matrix4x4()));
    Assert.False(e.Equals(new Matrix4x4()));
    Assert.False(f.Equals(new Matrix4x4()));
    Assert.False(g.Equals(new Matrix4x4()));
    Assert.False(h.Equals(new Matrix4x4()));
    Assert.False(i.Equals(new Matrix4x4()));
    Assert.False(j.Equals(new Matrix4x4()));
    Assert.False(k.Equals(new Matrix4x4()));
    Assert.False(l.Equals(new Matrix4x4()));
    Assert.False(m.Equals(new Matrix4x4()));
    Assert.False(n.Equals(new Matrix4x4()));
    Assert.False(o.Equals(new Matrix4x4()));
    Assert.False(p.Equals(new Matrix4x4()));

    Assert.False(a.IsIdentity);
    Assert.False(b.IsIdentity);
    Assert.False(c.IsIdentity);
    Assert.False(d.IsIdentity);
    Assert.False(e.IsIdentity);
    Assert.False(f.IsIdentity);
    Assert.False(g.IsIdentity);
    Assert.False(h.IsIdentity);
    Assert.False(i.IsIdentity);
    Assert.False(j.IsIdentity);
    Assert.False(k.IsIdentity);
    Assert.False(l.IsIdentity);
    Assert.False(m.IsIdentity);
    Assert.False(n.IsIdentity);
    Assert.False(o.IsIdentity);
    Assert.False(p.IsIdentity);

    // Counterintuitive result - IEEE rules for NaN comparison are weird!
    Assert.False(a.Equals(a));
    Assert.False(b.Equals(b));
    Assert.False(c.Equals(c));
    Assert.False(d.Equals(d));
    Assert.False(e.Equals(e));
    Assert.False(f.Equals(f));
    Assert.False(g.Equals(g));
    Assert.False(h.Equals(h));
    Assert.False(i.Equals(i));
    Assert.False(j.Equals(j));
    Assert.False(k.Equals(k));
    Assert.False(l.Equals(l));
    Assert.False(m.Equals(m));
    Assert.False(n.Equals(n));
    Assert.False(o.Equals(o));
    Assert.False(p.Equals(p));
}

// A test to make sure these types are blittable directly into GPU buffer memory layouts
[Fact]
public unsafe void Matrix4x4SizeofTest()
{
    Assert.Equal(64, sizeof(Matrix4x4));
    Assert.Equal(128, sizeof(Matrix4x4_2x));
    Assert.Equal(68, sizeof(Matrix4x4PlusFloat));
    Assert.Equal(136, sizeof(Matrix4x4PlusFloat_2x));
}

[StructLayout(LayoutKind.Sequential)]
struct Matrix4x4_2x
{
private Matrix4x4 _a;
private Matrix4x4 _b;
}

[StructLayout(LayoutKind.Sequential)]
struct Matrix4x4PlusFloat
{
private Matrix4x4 _v;
private float _f;
}

[StructLayout(LayoutKind.Sequential)]
struct Matrix4x4PlusFloat_2x
{
private Matrix4x4PlusFloat _a;
private Matrix4x4PlusFloat _b;
}

// A test to make sure the fields are laid out how we expect
[Fact]
public unsafe void Matrix4x4FieldOffsetTest()
{
    Matrix4x4* ptr = (Matrix4x4*)0;

    Assert.Equal(new IntPtr(0), new IntPtr(&ptr->M11));
    Assert.Equal(new IntPtr(4), new IntPtr(&ptr->M12));
    Assert.Equal(new IntPtr(8), new IntPtr(&ptr->M13));
    Assert.Equal(new IntPtr(12), new IntPtr(&ptr->M14));

    Assert.Equal(new IntPtr(16), new IntPtr(&ptr->M21));
    Assert.Equal(new IntPtr(20), new IntPtr(&ptr->M22));
    Assert.Equal(new IntPtr(24), new IntPtr(&ptr->M23));
    Assert.Equal(new IntPtr(28), new IntPtr(&ptr->M24));

    Assert.Equal(new IntPtr(32), new IntPtr(&ptr->M31));
    Assert.Equal(new IntPtr(36), new IntPtr(&ptr->M32));
    Assert.Equal(new IntPtr(40), new IntPtr(&ptr->M33));
    Assert.Equal(new IntPtr(44), new IntPtr(&ptr->M34));

    Assert.Equal(new IntPtr(48), new IntPtr(&ptr->M41));
    Assert.Equal(new IntPtr(52), new IntPtr(&ptr->M42));
    Assert.Equal(new IntPtr(56), new IntPtr(&ptr->M43));
    Assert.Equal(new IntPtr(60), new IntPtr(&ptr->M44));
}
// Simple shadow test.
[Fact]
public void Matrix4x4CreateShadowTest01()
{
    Vector3 lightDir = Vector3.UnitY;
    Plane plane = new Plane(Vector3.UnitY, 0);

    Matrix4x4 expected = Matrix4x4.CreateScale(1, 0, 1);

    Matrix4x4 actual = Matrix4x4.CreateShadow(lightDir, plane);
    Assert.True(MathHelper.Equal(expected, actual), "Matrix4x4.CreateShadow did not returned expected value.");
}

// Various plane projections.
[Fact]
public void Matrix4x4CreateShadowTest02()
{
    // Complex cases.
    Plane[] planes = {
        new Plane( 0, 1, 0, 0 ),
        new Plane( 1, 2, 3, 4 ),
        new Plane( 5, 6, 7, 8 ),
        new Plane(-1,-2,-3,-4 ),
        new Plane(-5,-6,-7,-8 ),
    };

    Vector3[] points = {
        new Vector3( 1, 2, 3),
        new Vector3( 5, 6, 7),
        new Vector3( 8, 9, 10),
        new Vector3(-1,-2,-3),
        new Vector3(-5,-6,-7),
        new Vector3(-8,-9,-10),
    };

    foreach (Plane p in planes)
    {
        Plane plane = Plane.Normalize(p);

        // Try various direction of light directions.
        var testDirections = new Vector3[]
            {
                new Vector3( -1.0f, 1.0f, 1.0f ),
                new Vector3(  0.0f, 1.0f, 1.0f ),
                new Vector3(  1.0f, 1.0f, 1.0f ),
                new Vector3( -1.0f, 0.0f, 1.0f ),
                new Vector3(  0.0f, 0.0f, 1.0f ),
                new Vector3(  1.0f, 0.0f, 1.0f ),
                new Vector3( -1.0f,-1.0f, 1.0f ),
                new Vector3(  0.0f,-1.0f, 1.0f ),
                new Vector3(  1.0f,-1.0f, 1.0f ),

                new Vector3( -1.0f, 1.0f, 0.0f ),
                new Vector3(  0.0f, 1.0f, 0.0f ),
                new Vector3(  1.0f, 1.0f, 0.0f ),
                new Vector3( -1.0f, 0.0f, 0.0f ),
                new Vector3(  0.0f, 0.0f, 0.0f ),
                new Vector3(  1.0f, 0.0f, 0.0f ),
                new Vector3( -1.0f,-1.0f, 0.0f ),
                new Vector3(  0.0f,-1.0f, 0.0f ),
                new Vector3(  1.0f,-1.0f, 0.0f ),

                new Vector3( -1.0f, 1.0f,-1.0f ),
                new Vector3(  0.0f, 1.0f,-1.0f ),
                new Vector3(  1.0f, 1.0f,-1.0f ),
                new Vector3( -1.0f, 0.0f,-1.0f ),
                new Vector3(  0.0f, 0.0f,-1.0f ),
                new Vector3(  1.0f, 0.0f,-1.0f ),
                new Vector3( -1.0f,-1.0f,-1.0f ),
                new Vector3(  0.0f,-1.0f,-1.0f ),
                new Vector3(  1.0f,-1.0f,-1.0f ),
            };

        foreach (Vector3 lightDirInfo in testDirections)
        {
            if (lightDirInfo.Length() < 0.1f)
                continue;
            Vector3 lightDir = Vector3.Normalize(lightDirInfo);

            if (Plane.DotNormal(plane, lightDir) < 0.1f)
                continue;

            Matrix4x4 m = Matrix4x4.CreateShadow(lightDir, plane);
            Vector3 pp = -plane.D * plane.Normal; // origin of the plane.

            //
            foreach (Vector3 point in points)
            {
                Vector4 v4 = Vector4.Transform(point, m);

                Vector3 sp = new Vector3(v4.X, v4.Y, v4.Z) / v4.W;

                // Make sure transformed position is on the plane.
                Vector3 v = sp - pp;
                float d = Vector3.Dot(v, plane.Normal);
                Assert.True(MathHelper.Equal(d, 0), "Matrix4x4.CreateShadow did not provide expected value.");

                // make sure direction between transformed position and original position are same as light direction.
                if (Vector3.Dot(point - pp, plane.Normal) > 0.0001f)
                {
                    Vector3 dir = Vector3.Normalize(point - sp);
                    Assert.True(MathHelper.Equal(dir, lightDir), "Matrix4x4.CreateShadow did not provide expected value.");
                }
            }
        }
    }
}

void CreateReflectionTest(Plane plane, Matrix4x4 expected)
{
    Matrix4x4 actual = Matrix4x4.CreateReflection(plane);
    Assert.True(MathHelper.Equal(actual, expected), "Matrix4x4.CreateReflection did not return expected value.");
}

[Fact]
public void Matrix4x4CreateReflectionTest01()
{
    // XY plane.
    CreateReflectionTest(new Plane(Vector3.UnitZ, 0), Matrix4x4.CreateScale(1, 1, -1));
    // XZ plane.
    CreateReflectionTest(new Plane(Vector3.UnitY, 0), Matrix4x4.CreateScale(1, -1, 1));
    // YZ plane.
    CreateReflectionTest(new Plane(Vector3.UnitX, 0), Matrix4x4.CreateScale(-1, 1, 1));

    // Complex cases.
    Plane[] planes = {
        new Plane( 0, 1, 0, 0 ),
        new Plane( 1, 2, 3, 4 ),
        new Plane( 5, 6, 7, 8 ),
        new Plane(-1,-2,-3,-4 ),
        new Plane(-5,-6,-7,-8 ),
    };

    Vector3[] points = {
        new Vector3( 1, 2, 3),
        new Vector3( 5, 6, 7),
        new Vector3(-1,-2,-3),
        new Vector3(-5,-6,-7),
    };

    foreach (Plane p in planes)
    {
        Plane plane = Plane.Normalize(p);
        Matrix4x4 m = Matrix4x4.CreateReflection(plane);
        Vector3 pp = -plane.D * plane.Normal; // Position on the plane.

        //
        foreach (Vector3 point in points)
        {
            Vector3 rp = Vector3.Transform(point, m);

            // Maniually compute refelction point and compare results.
            Vector3 v = point - pp;
            float d = Vector3.Dot(v, plane.Normal);
            Vector3 vp = point - 2.0f * d * plane.Normal;
            Assert.True(MathHelper.Equal(rp, vp), "Matrix4x4.Reflection did not provide expected value.");
        }
    }
}

// A test for Lerp (Matrix4x4, Matrix4x4, float)
[Fact]
public void Matrix4x4LerpTest()
{
    Matrix4x4 a = new Matrix4x4();
    a.M11 = 11.0f;
    a.M12 = 12.0f;
    a.M13 = 13.0f;
    a.M14 = 14.0f;
    a.M21 = 21.0f;
    a.M22 = 22.0f;
    a.M23 = 23.0f;
    a.M24 = 24.0f;
    a.M31 = 31.0f;
    a.M32 = 32.0f;
    a.M33 = 33.0f;
    a.M34 = 34.0f;
    a.M41 = 41.0f;
    a.M42 = 42.0f;
    a.M43 = 43.0f;
    a.M44 = 44.0f;

    Matrix4x4 b = GenerateMatrixNumberFrom1To16();

    float t = 0.5f;

    Matrix4x4 expected = new Matrix4x4();
    expected.M11 = a.M11 + (b.M11 - a.M11) * t;
    expected.M12 = a.M12 + (b.M12 - a.M12) * t;
    expected.M13 = a.M13 + (b.M13 - a.M13) * t;
    expected.M14 = a.M14 + (b.M14 - a.M14) * t;

    expected.M21 = a.M21 + (b.M21 - a.M21) * t;
    expected.M22 = a.M22 + (b.M22 - a.M22) * t;
    expected.M23 = a.M23 + (b.M23 - a.M23) * t;
    expected.M24 = a.M24 + (b.M24 - a.M24) * t;

    expected.M31 = a.M31 + (b.M31 - a.M31) * t;
    expected.M32 = a.M32 + (b.M32 - a.M32) * t;
    expected.M33 = a.M33 + (b.M33 - a.M33) * t;
    expected.M34 = a.M34 + (b.M34 - a.M34) * t;

    expected.M41 = a.M41 + (b.M41 - a.M41) * t;
    expected.M42 = a.M42 + (b.M42 - a.M42) * t;
    expected.M43 = a.M43 + (b.M43 - a.M43) * t;
    expected.M44 = a.M44 + (b.M44 - a.M44) * t;

    Matrix4x4 actual;
    actual = Matrix4x4.Lerp(a, b, t);
    Assert.True(MathHelper.Equal(expected, actual), "Matrix4x4.Lerp did not return the expected value.");
}
*/
