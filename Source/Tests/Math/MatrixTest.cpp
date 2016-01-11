// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "MatrixTest.hpp"

#include <cstdint>
#include <vector>

#include "EqualityHelper.hpp"

#include <SceneR/Math/Math.hpp>
#include <SceneR/Math/Quaternion.hpp>
#include <SceneR/Math/Vector3.hpp>
#include <SceneR/Math/Vector4.hpp>

using namespace SceneR::Math;

Matrix MatrixTest::GenerateMatrixNumberFrom1To16()
{
    Matrix a;

    a.m11 = 1.0f;
    a.m12 = 2.0f;
    a.m13 = 3.0f;
    a.m14 = 4.0f;
    a.m21 = 5.0f;
    a.m22 = 6.0f;
    a.m23 = 7.0f;
    a.m24 = 8.0f;
    a.m31 = 9.0f;
    a.m32 = 10.0f;
    a.m33 = 11.0f;
    a.m34 = 12.0f;
    a.m41 = 13.0f;
    a.m42 = 14.0f;
    a.m43 = 15.0f;
    a.m44 = 16.0f;

    return a;
}

Matrix MatrixTest::GenerateTestMatrix()
{
    auto m = Matrix::create_rotation_x(SceneR::Math::to_radians(30.0f))
           * Matrix::create_rotation_y(SceneR::Math::to_radians(30.0f))
           * Matrix::create_rotation_z(SceneR::Math::to_radians(30.0f));

    // m.Translation({ 111.0f, 222.0f, 333.0f });

    return m;
}

void MatrixTest::Decompose(const float&   yaw
                         , const float&   pitch
                         , const float&   roll
                         , const Vector3& expectedTranslation
                         , const Vector3& expectedScales)
{
    auto expectedRotation = Quaternion::create_from_yaw_pitch_roll(SceneR::Math::to_radians(yaw)
                                                                 , SceneR::Math::to_radians(pitch)
                                                                 , SceneR::Math::to_radians(roll));

    auto m = Matrix::create_scale(expectedScales)
           * Matrix::create_from_quaternion(expectedRotation)
           * Matrix::create_translation(expectedTranslation);

    Vector3    scales;
    Quaternion rotation;
    Vector3    translation;

    bool actualResult = Matrix::decompose(m, scales, rotation, translation);

    EXPECT_TRUE(actualResult);

    bool scaleIsZeroOrNegative = expectedScales.x <= 0
                              || expectedScales.y <= 0
                              || expectedScales.z <= 0;

    if (scaleIsZeroOrNegative)
    {
        EXPECT_TRUE(EqualityHelper::Equal(std::abs(expectedScales.x), std::abs(scales.x)));
        EXPECT_TRUE(EqualityHelper::Equal(std::abs(expectedScales.y), std::abs(scales.y)));
        EXPECT_TRUE(EqualityHelper::Equal(std::abs(expectedScales.z), std::abs(scales.z)));
    }
    else
    {
        EXPECT_TRUE(EqualityHelper::Equal(expectedScales, scales));
        EXPECT_TRUE(EqualityHelper::EqualRotation(expectedRotation, rotation));
    }

    EXPECT_TRUE(EqualityHelper::Equal(expectedTranslation, translation));
}

void MatrixTest::DecomposeScale(const float& sx, const float& sy, const float& sz)
{
    auto m              = Matrix::create_scale(sx, sy, sz);
    auto expectedScales = Vector3 { sx, sy, sz };

    Vector3    scales;
    Quaternion rotation;
    Vector3    translation;

    bool actualResult = Matrix::decompose(m, scales, rotation, translation);

    EXPECT_TRUE(actualResult);
    EXPECT_TRUE(EqualityHelper::Equal(expectedScales, scales));
    EXPECT_TRUE(EqualityHelper::EqualRotation(Quaternion::identity, rotation));
    EXPECT_TRUE(EqualityHelper::Equal(Vector3::zero, translation));
}

void MatrixTest::CreateReflection(const Plane& plane, const Matrix& expected)
{
    auto actual = Matrix::create_reflection(plane);

    EXPECT_TRUE(EqualityHelper::Equal(actual, expected));
}

TEST_F(MatrixTest, DefaultConstructor)
{
    auto matrix = Matrix { };

    EXPECT_TRUE(0.0f == matrix.m11);
    EXPECT_TRUE(0.0f == matrix.m12);
    EXPECT_TRUE(0.0f == matrix.m13);
    EXPECT_TRUE(0.0f == matrix.m14);
    EXPECT_TRUE(0.0f == matrix.m21);
    EXPECT_TRUE(0.0f == matrix.m22);
    EXPECT_TRUE(0.0f == matrix.m23);
    EXPECT_TRUE(0.0f == matrix.m24);
    EXPECT_TRUE(0.0f == matrix.m31);
    EXPECT_TRUE(0.0f == matrix.m32);
    EXPECT_TRUE(0.0f == matrix.m33);
    EXPECT_TRUE(0.0f == matrix.m34);
    EXPECT_TRUE(0.0f == matrix.m41);
    EXPECT_TRUE(0.0f == matrix.m42);
    EXPECT_TRUE(0.0f == matrix.m43);
    EXPECT_TRUE(0.0f == matrix.m44);
}

TEST_F(MatrixTest, MatrixConstructor)
{
    auto matrix = Matrix { 10.0f, 10.0f, 10.0f, 0.0f
                         , 20.0f, 20.0f, 20.0f, 0.0f
                         , 30.0f, 30.0f, 30.0f, 0.0f
                         , 5.0f , 10.0f, 15.0f, 1.0f };

    EXPECT_TRUE(10.0f == matrix.m11);
    EXPECT_TRUE(10.0f == matrix.m12);
    EXPECT_TRUE(10.0f == matrix.m13);
    EXPECT_TRUE(0.0f  == matrix.m14);
    EXPECT_TRUE(20.0f == matrix.m21);
    EXPECT_TRUE(20.0f == matrix.m22);
    EXPECT_TRUE(20.0f == matrix.m23);
    EXPECT_TRUE(0.0f  == matrix.m24);
    EXPECT_TRUE(30.0f == matrix.m31);
    EXPECT_TRUE(30.0f == matrix.m32);
    EXPECT_TRUE(30.0f == matrix.m33);
    EXPECT_TRUE(0.0f  == matrix.m34);
    EXPECT_TRUE(5.0f  == matrix.m41);
    EXPECT_TRUE(10.0f == matrix.m42);
    EXPECT_TRUE(15.0f == matrix.m43);
    EXPECT_TRUE(1.0f  == matrix.m44);
}

TEST_F(MatrixTest, CopyConstuctor)
{
    auto matrix = Matrix { 10.0f, 10.0f, 10.0f, 0.0f
                         , 20.0f, 20.0f, 20.0f, 0.0f
                         , 30.0f, 30.0f, 30.0f, 0.0f
                         , 5.0f , 10.0f, 15.0f, 1.0f };

    auto matrix1 = Matrix { matrix };

    EXPECT_TRUE(matrix.m11 == matrix1.m11);
    EXPECT_TRUE(matrix.m12 == matrix1.m12);
    EXPECT_TRUE(matrix.m13 == matrix1.m13);
    EXPECT_TRUE(matrix.m14 == matrix1.m14);
    EXPECT_TRUE(matrix.m21 == matrix1.m21);
    EXPECT_TRUE(matrix.m22 == matrix1.m22);
    EXPECT_TRUE(matrix.m23 == matrix1.m23);
    EXPECT_TRUE(matrix.m24 == matrix1.m24);
    EXPECT_TRUE(matrix.m31 == matrix1.m31);
    EXPECT_TRUE(matrix.m32 == matrix1.m32);
    EXPECT_TRUE(matrix.m33 == matrix1.m33);
    EXPECT_TRUE(matrix.m34 == matrix1.m34);
    EXPECT_TRUE(matrix.m41 == matrix1.m41);
    EXPECT_TRUE(matrix.m42 == matrix1.m42);
    EXPECT_TRUE(matrix.m43 == matrix1.m43);
    EXPECT_TRUE(matrix.m44 == matrix1.m44);
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

    EXPECT_TRUE(34.0f  == result.m11);
    EXPECT_TRUE(44.0f  == result.m12);
    EXPECT_TRUE(54.0f  == result.m13);
    EXPECT_TRUE(64.0f  == result.m14);
    EXPECT_TRUE(82.0f  == result.m21);
    EXPECT_TRUE(108.0f == result.m22);
    EXPECT_TRUE(134.0f == result.m23);
    EXPECT_TRUE(160.0f == result.m24);
    EXPECT_TRUE(34.0f  == result.m31);
    EXPECT_TRUE(44.0f  == result.m32);
    EXPECT_TRUE(54.0f  == result.m33);
    EXPECT_TRUE(64.0f  == result.m34);
    EXPECT_TRUE(82.0f  == result.m41);
    EXPECT_TRUE(108.0f == result.m42);
    EXPECT_TRUE(134.0f == result.m43);
    EXPECT_TRUE(160.0f == result.m44);
}

TEST_F(MatrixTest, MatrixTranspose)
{
    auto source = Matrix { 1.0f, 0.0f, 0.0f, 10.0f
                         , 0.0f, 1.0f, 0.0f, 10.0f
                         , 0.0f, 0.0f, 1.0f, 10.0f
                         , 0.0f, 0.0f, 0.0f, 1.0f };

    auto transposed = Matrix::transpose(source);

    EXPECT_TRUE(1.0f  == transposed.m11);
    EXPECT_TRUE(0.0f  == transposed.m12);
    EXPECT_TRUE(0.0f  == transposed.m13);
    EXPECT_TRUE(0.0f  == transposed.m14);
    EXPECT_TRUE(0.0f  == transposed.m21);
    EXPECT_TRUE(1.0f  == transposed.m22);
    EXPECT_TRUE(0.0f  == transposed.m23);
    EXPECT_TRUE(0.0f  == transposed.m24);
    EXPECT_TRUE(0.0f  == transposed.m31);
    EXPECT_TRUE(0.0f  == transposed.m32);
    EXPECT_TRUE(1.0f  == transposed.m33);
    EXPECT_TRUE(0.0f  == transposed.m34);
    EXPECT_TRUE(10.0f == transposed.m41);
    EXPECT_TRUE(10.0f == transposed.m42);
    EXPECT_TRUE(10.0f == transposed.m43);
    EXPECT_TRUE(1.0f  == transposed.m44);
}

TEST_F(MatrixTest, Determinant)
{
    auto matrix = Matrix { 2.0f, 3.0f, 4.0f , 0.0f
                         , 1.0f, 2.0f, -3.0f, 0.0f
                         , 1.0f, 1.0f, 5.0f , 0.0f
                         , 0.0f, 0.0f, 0.0f , 1.0f };

    EXPECT_TRUE(-2.0f == matrix.determinant());
}

TEST_F(MatrixTest, Inverse)
{
    auto matrix = Matrix { 2.0f, 3.0f, 4.0f , 0.0f
                         , 1.0f, 2.0f, -3.0f, 0.0f
                         , 1.0f, 1.0f, 5.0f , 0.0f
                         , 0.0f, 0.0f, 0.0f , 1.0f };

    auto inverse = Matrix::invert(matrix);

    EXPECT_TRUE(-6.5f == inverse.m11);
    EXPECT_TRUE(05.5f == inverse.m12);
    EXPECT_TRUE(08.5f == inverse.m13);
    EXPECT_TRUE(00.0f == inverse.m14);
    EXPECT_TRUE(04.0f == inverse.m21);
    EXPECT_TRUE(-3.0f == inverse.m22);
    EXPECT_TRUE(-5.0f == inverse.m23);
    EXPECT_TRUE(00.0f == inverse.m24);
    EXPECT_TRUE(00.5f == inverse.m31);
    EXPECT_TRUE(-0.5f == inverse.m32);
    EXPECT_TRUE(-0.5f == inverse.m33);
    EXPECT_TRUE(00.0f == inverse.m34);
    EXPECT_TRUE(00.0f == inverse.m41);
    EXPECT_TRUE(00.0f == inverse.m42);
    EXPECT_TRUE(00.0f == inverse.m43);
    EXPECT_TRUE(01.0f == inverse.m44);
}

TEST_F(MatrixTest, CreatePerspectiveFieldOfView)
{
    auto fieldOfView = SceneR::Math::pi_over_4;
    auto aspectRatio = 768.0f / 480.0f;
    auto perspective = Matrix::create_perspective_field_of_view(fieldOfView, aspectRatio, 0.1f, 100.0f);

    EXPECT_TRUE(1.50888336f == perspective.m11);
    EXPECT_TRUE(00.0f       == perspective.m12);
    EXPECT_TRUE(00.0f       == perspective.m13);
    EXPECT_TRUE(00.0f       == perspective.m14);
    EXPECT_TRUE(00.0f       == perspective.m21);
    EXPECT_TRUE(2.41421342f == perspective.m22);
    EXPECT_TRUE(00.0f       == perspective.m23);
    EXPECT_TRUE(00.0f       == perspective.m24);
    EXPECT_TRUE(00.0f       == perspective.m31);
    EXPECT_TRUE(00.0f       == perspective.m32);
    EXPECT_TRUE(-1.001001f  == perspective.m33);
    EXPECT_TRUE(-1.0f       == perspective.m34);
    EXPECT_TRUE(00.0f       == perspective.m41);
    EXPECT_TRUE(00.0f       == perspective.m42);
    EXPECT_TRUE(-0.1001001f == perspective.m43);
    EXPECT_TRUE(00.0f       == perspective.m44);
}

TEST_F(MatrixTest, CreateLookAt)
{
    auto lookAt = Matrix::create_look_at({ 0.0f, 1.0f, -5.0f }, Vector3::unit_y, Vector3::up);

    EXPECT_TRUE(-1.0f == lookAt.m11);
    EXPECT_TRUE(00.0f == lookAt.m12);
    EXPECT_TRUE(00.0f == lookAt.m13);
    EXPECT_TRUE(00.0f == lookAt.m14);
    EXPECT_TRUE(00.0f == lookAt.m21);
    EXPECT_TRUE(01.0f == lookAt.m22);
    EXPECT_TRUE(00.0f == lookAt.m23);
    EXPECT_TRUE(00.0f == lookAt.m24);
    EXPECT_TRUE(00.0f == lookAt.m31);
    EXPECT_TRUE(00.0f == lookAt.m32);
    EXPECT_TRUE(-1.0f == lookAt.m33);
    EXPECT_TRUE(00.0f == lookAt.m34);
    EXPECT_TRUE(00.0f == lookAt.m41);
    EXPECT_TRUE(-1.0f == lookAt.m42);
    EXPECT_TRUE(-5.0f == lookAt.m43);
    EXPECT_TRUE(01.0f == lookAt.m44);
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, Identity)
{
    Matrix val;

    val.m11 = 1.0f;
    val.m22 = 1.0f;
    val.m33 = 1.0f;
    val.m44 = 1.0f;

    EXPECT_TRUE(EqualityHelper::Equal(val, Matrix::identity));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, Determinant1)
{
    auto target = Matrix::create_rotation_x(SceneR::Math::to_radians(30.0f))
                * Matrix::create_rotation_y(SceneR::Math::to_radians(30.0f))
                * Matrix::create_rotation_z(SceneR::Math::to_radians(30.0f));

    float val = 1.0f;
    float det = target.determinant();

    EXPECT_TRUE(val == det);
}

// Determinant test |A| = 1 / |A'|
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, Determinant2)
{
    Matrix a;

    a.m11 = 5.0f;
    a.m12 = 2.0f;
    a.m13 = 8.25f;
    a.m14 = 1.0f;
    a.m21 = 12.0f;
    a.m22 = 6.8f;
    a.m23 = 2.14f;
    a.m24 = 9.6f;
    a.m31 = 6.5f;
    a.m32 = 1.0f;
    a.m33 = 3.14f;
    a.m34 = 2.22f;
    a.m41 = 0.0f;
    a.m42 = 0.86f;
    a.m43 = 4.0f;
    a.m44 = 1.0f;

    auto  i    = Matrix::invert(a);
    float detA = a.determinant();
    float detI = i.determinant();
    float t    = 1.0f / detI;

    // only accurate to 3 precision
    EXPECT_TRUE(std::abs(detA - t) < 1e-3);
}

// A test for Invert (Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, Invert)
{
    auto mtx = Matrix::create_rotation_x(SceneR::Math::to_radians(30.0f))
             * Matrix::create_rotation_y(SceneR::Math::to_radians(30.0f))
             * Matrix::create_rotation_z(SceneR::Math::to_radians(30.0f));

    auto expected = Matrix { 0.74999994f , -0.216506317f, 0.62499994f  , 0.0f
                           , 0.433012635f, 0.87499994f  , -0.216506317f, 0.0f
                           , -0.49999997f, 0.433012635f , 0.74999994f  , 0.0f
                           , 0.0f        , 0.0f         , 0.0f         , 0.99999994f };

    auto actual = Matrix::invert(mtx);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Make sure M*M is identity matrix
    auto i = mtx * actual;

    EXPECT_TRUE(EqualityHelper::Equal(Matrix::identity, i));
}

// A test for Invert (Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, InvertIdentityMatrix)
{
    auto mtx    = Matrix::identity;
    auto actual = Matrix::invert(mtx);

    EXPECT_TRUE(EqualityHelper::Equal(actual, Matrix::identity));
}

// A test for Invert (Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, InvertTranslationMatrix)
{
    auto mtx    = Matrix::create_translation(23, 42, 666);
    auto actual = Matrix::invert(mtx);
    auto i      = mtx * actual;

    EXPECT_TRUE(EqualityHelper::Equal(i, Matrix::identity));
}

// A test for Invert (Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, InvertRotationMatrix)
{
    auto mtx    = Matrix::create_from_yaw_pitch_roll(3, 4, 5);
    auto actual = Matrix::invert(mtx);
    auto i      = mtx * actual;

    EXPECT_TRUE(EqualityHelper::Equal(i, Matrix::identity));
}

// A test for Invert (Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, InvertScaleMatrix)
{
    auto mtx    = Matrix::create_scale(23, 42, -666);
    auto actual = Matrix::invert(mtx);
    auto i      = mtx * actual;

    EXPECT_TRUE(EqualityHelper::Equal(i, Matrix::identity));
}

// A test for Invert (Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, InvertProjectionMatrix)
{
    auto mtx    = Matrix::create_perspective_field_of_view(1, 1.333f, 0.1f, 666);
    auto actual = Matrix::invert(mtx);
    auto i      = mtx * actual;

    EXPECT_TRUE(EqualityHelper::Equal(i, Matrix::identity));
}

// A test for Invert (Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, InvertAffineMatrix)
{
    auto mtx = Matrix::create_from_yaw_pitch_roll(3, 4, 5)
             * Matrix::create_scale(23, 42, -666)
             * Matrix::create_translation(17, 53, 89);

    auto actual = Matrix::invert(mtx);
    auto i      = mtx * actual;

    EXPECT_TRUE(EqualityHelper::Equal(i, Matrix::identity));
}

// Various rotation decompose test.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, Decompose)
{
    MatrixTest::Decompose(10.0f, 20.0f, 30.0f, { 10, 20, 30 }, { 2, 3, 4 });

    const float step = 35.0f;

    for (float yawAngle = -720.0f; yawAngle <= 720.0f; yawAngle += step)
    {
        for (float pitchAngle = -720.0f; pitchAngle <= 720.0f; pitchAngle += step)
        {
            for (float rollAngle = -720.0f; rollAngle <= 720.0f; rollAngle += step)
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
    MatrixTest::Decompose(0, 0, 0, Vector3::zero, { 1, 2, 3 });
    MatrixTest::Decompose(0, 0, 0, Vector3::zero, { 1, 3, 2 });
    MatrixTest::Decompose(0, 0, 0, Vector3::zero, { 2, 1, 3 });
    MatrixTest::Decompose(0, 0, 0, Vector3::zero, { 2, 3, 1 });
    MatrixTest::Decompose(0, 0, 0, Vector3::zero, { 3, 1, 2 });
    MatrixTest::Decompose(0, 0, 0, Vector3::zero, { 3, 2, 1 });

    MatrixTest::Decompose(0, 0, 0, Vector3::zero, { -2, 1, 1 });

    // Small scales.
    MatrixTest::Decompose(0, 0, 0, Vector3::zero, { 1e-4f, 2e-4f, 3e-4f });
    MatrixTest::Decompose(0, 0, 0, Vector3::zero, { 1e-4f, 3e-4f, 2e-4f });
    MatrixTest::Decompose(0, 0, 0, Vector3::zero, { 2e-4f, 1e-4f, 3e-4f });
    MatrixTest::Decompose(0, 0, 0, Vector3::zero, { 2e-4f, 3e-4f, 1e-4f });
    MatrixTest::Decompose(0, 0, 0, Vector3::zero, { 3e-4f, 1e-4f, 2e-4f });
    MatrixTest::Decompose(0, 0, 0, Vector3::zero, { 3e-4f, 2e-4f, 1e-4f });

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

    EXPECT_FALSE(Matrix::decompose(MatrixTest::GenerateMatrixNumberFrom1To16(), scales, rotation, translation));
    //EXPECT_FALSE(Matrix::Decompose(new Matrix(Matrix3x2.CreateSkew(1, 2)), out scales, out rotation, out translation));
}

// Transform by quaternion test
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, TransformByQuaternion)
{
    auto target = MatrixTest::GenerateMatrixNumberFrom1To16();
    auto m      = Matrix::create_rotation_x(SceneR::Math::to_radians(30.0f))
                * Matrix::create_rotation_y(SceneR::Math::to_radians(30.0f))
                * Matrix::create_rotation_z(SceneR::Math::to_radians(30.0f));

    auto q        = Quaternion::create_from_rotation_matrix(m);
    auto expected = target * m;
    auto actual   = Matrix::transform(target, q);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreateRotationX (float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateRotationX)
{
    float radians = SceneR::Math::to_radians(30.0f);
    Matrix expected;

    expected.m11 = 1.0f;
    expected.m22 = 0.8660254f;
    expected.m23 = 0.5f;
    expected.m32 = -0.5f;
    expected.m33 = 0.8660254f;
    expected.m44 = 1.0f;

    auto actual = Matrix::create_rotation_x(radians);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreateRotationX (float)
// CreateRotationX of zero degree
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateRotationXOfZeroDegree)
{
    float radians = 0;

    auto expected = Matrix::identity;
    auto actual   = Matrix::create_rotation_x(radians);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreateRotationX (float, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateRotationXCenter)
{
    float radians = SceneR::Math::to_radians(30.0f);
    auto  center  = Vector3 { 23, 42, 66 };

    auto rotateAroundZero         = Matrix::create_rotation_x(radians, Vector3::zero);
    auto rotateAroundZeroExpected = Matrix::create_rotation_x(radians);

    EXPECT_TRUE(EqualityHelper::Equal(rotateAroundZero, rotateAroundZeroExpected));

    auto rotateAroundCenter         = Matrix::create_rotation_x(radians, center);
    auto rotateAroundCenterExpected = Matrix::create_translation(-center)
                                    * Matrix::create_rotation_x(radians)
                                    * Matrix::create_translation(center);

    EXPECT_TRUE(EqualityHelper::Equal(rotateAroundCenter, rotateAroundCenterExpected));
}

// A test for CreateRotationY (float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateRotationY)
{
    float radians = SceneR::Math::to_radians(60.0f);
    Matrix expected;

    expected.m11 = 0.49999997f;
    expected.m13 = -0.866025448f;
    expected.m22 = 1.0f;
    expected.m31 = 0.866025448f;
    expected.m33 = 0.49999997f;
    expected.m44 = 1.0f;

    auto actual = Matrix::create_rotation_y(radians);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for RotationY (float)
// CreateRotationY test for negative angle
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateRotationYForNegativeAngle)
{
    float radians = SceneR::Math::to_radians(-300.0f);
    Matrix expected;

    expected.m11 = 0.49999997f;
    expected.m13 = -0.866025448f;
    expected.m22 = 1.0f;
    expected.m31 = 0.866025448f;
    expected.m33 = 0.49999997f;
    expected.m44 = 1.0f;

    auto actual = Matrix::create_rotation_y(radians);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreateRotationY (float, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateRotationYCenter)
{
    float radians = SceneR::Math::to_radians(30.0f);
    auto  center  = Vector3 { 23, 42, 66 };

    auto rotateAroundZero         = Matrix::create_rotation_y(radians, Vector3::zero);
    auto rotateAroundZeroExpected = Matrix::create_rotation_y(radians);

    EXPECT_TRUE(EqualityHelper::Equal(rotateAroundZero, rotateAroundZeroExpected));

    auto rotateAroundCenter         = Matrix::create_rotation_y(radians, center);
    auto rotateAroundCenterExpected = Matrix::create_translation(-center)
                                    * Matrix::create_rotation_y(radians)
                                    * Matrix::create_translation(center);

    EXPECT_TRUE(EqualityHelper::Equal(rotateAroundCenter, rotateAroundCenterExpected));
}

// A test for CreateFromAxisAngle(Vector3f,float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateFromAxisAngle)
{
    float radians  = SceneR::Math::to_radians(-30.0f);
    auto  expected = Matrix::create_rotation_x(radians);
    auto  actual   = Matrix::create_from_axis_angle(Vector3::unit_x, radians);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    expected = Matrix::create_rotation_y(radians);
    actual   = Matrix::create_from_axis_angle(Vector3::unit_y, radians);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    expected = Matrix::create_rotation_z(radians);
    actual   = Matrix::create_from_axis_angle(Vector3::unit_z, radians);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    expected = Matrix::create_from_quaternion(Quaternion::create_from_axis_angle(Vector3::normalize(Vector3::one), radians));
    actual   = Matrix::create_from_axis_angle(Vector3::normalize(Vector3::one), radians);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    const std::uint32_t rotCount = 16;

    for (std::uint32_t i = 0; i < rotCount; ++i)
    {
        float latitude = (2.0f * SceneR::Math::pi) * ((float)i / (float)rotCount);

        for (std::uint32_t j = 0; j < rotCount; ++j)
        {
            float longitude = -SceneR::Math::pi_over_2 + SceneR::Math::pi * ((float)j / (float)rotCount);

            auto m    = Matrix::create_rotation_z(longitude) * Matrix::create_rotation_y(latitude);
            auto axis = Vector3 { m.m11, m.m12, m.m13 };

            for (std::uint32_t k = 0; k < rotCount; ++k)
            {
                float rot = (2.0f * SceneR::Math::pi) * ((float)k / (float)rotCount);

                expected = Matrix::create_from_quaternion(Quaternion::create_from_axis_angle(axis, rot));
                actual   = Matrix::create_from_axis_angle(axis, rot);

                EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
            }
        }
    }
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateFromYawPitchRoll)
{
    float yawAngle   = SceneR::Math::to_radians(30.0f);
    float pitchAngle = SceneR::Math::to_radians(40.0f);
    float rollAngle  = SceneR::Math::to_radians(50.0f);

    auto yaw      = Matrix::create_from_axis_angle(Vector3::unit_y, yawAngle);
    auto pitch    = Matrix::create_from_axis_angle(Vector3::unit_x, pitchAngle);
    auto roll     = Matrix::create_from_axis_angle(Vector3::unit_z, rollAngle);
    auto expected = roll * pitch * yaw;
    auto actual   = Matrix::create_from_yaw_pitch_roll(yawAngle, pitchAngle, rollAngle);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// Covers more numeric rigions
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateFromYawPitchRoll2)
{
    const float step = 35.0f;

    for (float yawAngle = -720.0f; yawAngle <= 720.0f; yawAngle += step)
    {
        for (float pitchAngle = -720.0f; pitchAngle <= 720.0f; pitchAngle += step)
        {
            for (float rollAngle = -720.0f; rollAngle <= 720.0f; rollAngle += step)
            {
                float yawRad   = SceneR::Math::to_radians(yawAngle);
                float pitchRad = SceneR::Math::to_radians(pitchAngle);
                float rollRad  = SceneR::Math::to_radians(rollAngle);

                auto yaw   = Matrix::create_from_axis_angle(Vector3::unit_y, yawRad);
                auto pitch = Matrix::create_from_axis_angle(Vector3::unit_x, pitchRad);
                auto roll  = Matrix::create_from_axis_angle(Vector3::unit_z, rollRad);

                auto expected = roll * pitch * yaw;
                auto actual   = Matrix::create_from_yaw_pitch_roll(yawRad, pitchRad, rollRad);

                EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
            }
        }
    }
}

// Simple shadow test.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateShadow)
{
    auto lightDir = Vector3::unit_y;
    auto plane    = Plane { Vector3::unit_y, 0 };
    auto expected = Matrix::create_scale(1, 0, 1);
    auto actual   = Matrix::create_shadow(lightDir, plane);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// Various plane projections.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateShadowVariousPlaneProjections)
{
    // Complex cases.
    auto planes = std::vector<Plane>();

    planes.push_back({ 0, 1, 0, 0 });
    planes.push_back({ 1, 2, 3, 4 });
    planes.push_back({ 5, 6, 7, 8 });
    planes.push_back({-1,-2,-3,-4 });
    planes.push_back({-5,-6,-7,-8 });

    auto points = std::vector<Vector3>();

    points.push_back({ 1, 2,  3 });
    points.push_back({ 5, 6,  7 });
    points.push_back({ 8, 9, 10 });
    points.push_back({-1,-2, -3 });
    points.push_back({-5,-6, -7 });
    points.push_back({-8,-9,-10 });

    for (auto& p : planes)
    {
        auto plane = Plane::normalize(p);

        // Try various direction of light directions.
        auto testDirections = std::vector<Vector3>();

        points.push_back({ -1.0f, 1.0f, 1.0f });
        points.push_back({  0.0f, 1.0f, 1.0f });
        points.push_back({  1.0f, 1.0f, 1.0f });
        points.push_back({ -1.0f, 0.0f, 1.0f });
        points.push_back({  0.0f, 0.0f, 1.0f });
        points.push_back({  1.0f, 0.0f, 1.0f });
        points.push_back({ -1.0f,-1.0f, 1.0f });
        points.push_back({  0.0f,-1.0f, 1.0f });
        points.push_back({  1.0f,-1.0f, 1.0f });

        points.push_back({ -1.0f, 1.0f, 0.0f });
        points.push_back({  0.0f, 1.0f, 0.0f });
        points.push_back({  1.0f, 1.0f, 0.0f });
        points.push_back({ -1.0f, 0.0f, 0.0f });
        points.push_back({  0.0f, 0.0f, 0.0f });
        points.push_back({  1.0f, 0.0f, 0.0f });
        points.push_back({ -1.0f,-1.0f, 0.0f });
        points.push_back({  0.0f,-1.0f, 0.0f });
        points.push_back({  1.0f,-1.0f, 0.0f });

        points.push_back({ -1.0f, 1.0f,-1.0f });
        points.push_back({  0.0f, 1.0f,-1.0f });
        points.push_back({  1.0f, 1.0f,-1.0f });
        points.push_back({ -1.0f, 0.0f,-1.0f });
        points.push_back({  0.0f, 0.0f,-1.0f });
        points.push_back({  1.0f, 0.0f,-1.0f });
        points.push_back({ -1.0f,-1.0f,-1.0f });
        points.push_back({  0.0f,-1.0f,-1.0f });
        points.push_back({  1.0f,-1.0f,-1.0f });

        for (auto& lightDirInfo : testDirections)
        {
            if (lightDirInfo.length() < 0.1f)
            {
                continue;
            }

            auto lightDir = Vector3::normalize(lightDirInfo);

            if (Plane::dot_normal(plane, lightDir) < 0.1f)
            {
                continue;
            }

            auto m  = Matrix::create_shadow(lightDir, plane);
            auto pp = -plane.d * plane.normal; // origin of the plane.

            for (auto& point : points)
            {
                auto v4 = Vector4::transform(point, m);
                auto sp = Vector3 { v4.x, v4.y, v4.z } / v4.w;

                // Make sure transformed position is on the plane.
                auto   v = sp - pp;
                float d = Vector3::dot(v, plane.normal);

                EXPECT_TRUE(EqualityHelper::Equal(d, 0));

                // make sure direction between transformed position and original position are same as light direction.
                if (Vector3::dot(point - pp, plane.normal) > 0.0001f)
                {
                    auto dir = Vector3::normalize(point - sp);

                    EXPECT_TRUE(EqualityHelper::Equal(dir, lightDir));
                }
            };
        }
    }
}

// A test for CreateRotationZ (float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateRotationZ)
{
    float radians = SceneR::Math::to_radians(50.0f);

    Matrix expected;

    expected.m11 = 0.642787635f;
    expected.m12 = 0.766044438f;
    expected.m21 = -0.766044438f;
    expected.m22 = 0.642787635f;
    expected.m33 = 1.0f;
    expected.m44 = 1.0f;

    auto actual = Matrix::create_rotation_z(radians);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreateRotationZ (float, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateRotationZCenter)
{
    float radians = SceneR::Math::to_radians(30.0f);
    auto  center  = Vector3 { 23, 42, 66 };

    auto rotateAroundZero         = Matrix::create_rotation_z(radians, Vector3::zero);
    auto rotateAroundZeroExpected = Matrix::create_rotation_z(radians);

    EXPECT_TRUE(EqualityHelper::Equal(rotateAroundZero, rotateAroundZeroExpected));

    auto rotateAroundCenter         = Matrix::create_rotation_z(radians, center);
    auto rotateAroundCenterExpected = Matrix::create_translation(-center)
                                    * Matrix::create_rotation_z(radians)
                                    * Matrix::create_translation(center);

    EXPECT_TRUE(EqualityHelper::Equal(rotateAroundCenter, rotateAroundCenterExpected));
}

// A test for CrateLookAt (Vector3f, Vector3f, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateLookAt2)
{
    auto cameraPosition = Vector3 { 10.0f, 20.0f, 30.0f };
    auto cameraTarget   = Vector3 { 3.0f, 2.0f, -4.0f };
    auto cameraUpVector = Vector3 { 0.0f, 1.0f, 0.0f };

    Matrix expected;

    expected.m11 = 0.979457f;
    expected.m12 = -0.0928267762f;
    expected.m13 = 0.179017f;

    expected.m21 = 0.0f;
    expected.m22 = 0.8877481f;
    expected.m23 = 0.460329473f;

    expected.m31 = -0.201652914f;
    expected.m32 = -0.450872928f;
    expected.m33 = 0.8695112f;

    expected.m41 = -3.74498272f;
    expected.m42 = -3.30050683f;
    expected.m43 = -37.0820961f;
    expected.m44 = 1.0f;

    auto actual = Matrix::create_look_at(cameraPosition, cameraTarget, cameraUpVector);

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

    expected.m11 = 0.799999952f;
    expected.m12 = 0;
    expected.m13 = 0.599999964f;
    expected.m14 = 0;

    expected.m21 = -0.2228344f;
    expected.m22 = 0.928476632f;
    expected.m23 = 0.297112525f;
    expected.m24 = 0;

    expected.m31 = -0.557086f;
    expected.m32 = -0.371390671f;
    expected.m33 = 0.742781341f;
    expected.m34 = 0;

    expected.m41 = 10;
    expected.m42 = 20;
    expected.m43 = 30;
    expected.m44 = 1.0f;

    auto actual = Matrix::create_world(objectPosition, objectForwardDirection, objectUpVector);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    EXPECT_TRUE(objectPosition == actual.translation());
    EXPECT_TRUE(Vector3::dot(Vector3::normalize(objectUpVector), { actual.m21, actual.m22, actual.m23 }) > 0);
    EXPECT_TRUE(
        Vector3::dot(Vector3::normalize(objectForwardDirection), { -actual.m31, -actual.m32, -actual.m33 }) > 0.999f);
}

// A test for CreateOrtho (float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateOrtho)
{
    float width      = 100.0f;
    float height     = 200.0f;
    float zNearPlane = 1.5f;
    float zFarPlane  = 1000.0f;

    Matrix expected;

    expected.m11 = 0.02f;
    expected.m22 = 0.01f;
    expected.m33 = -0.00100150227f;
    expected.m43 = -0.00150225335f;
    expected.m44 = 1.0f;

    auto actual = Matrix::create_orthographic(width, height, zNearPlane, zFarPlane);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreateOrthoOffCenter (float, float, float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateOrthoOffCenter)
{
    float left       = 10.0f;
    float right      = 90.0f;
    float bottom     = 20.0f;
    float top        = 180.0f;
    float zNearPlane = 1.5f;
    float zFarPlane  = 1000.0f;

    Matrix expected;

    expected.m11 = 0.025f;
    expected.m22 = 0.0125f;
    expected.m33 = -0.00100150227f;
    expected.m41 = -1.25f;
    expected.m42 = -1.25f;
    expected.m43 = -0.00150225335f;
    expected.m44 = 1.0f;

    auto actual = Matrix::create_orthographic_off_center(left, right, bottom, top, zNearPlane, zFarPlane);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreatePerspective (float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspective)
{
    float width      = 100.0f;
    float height     = 200.0f;
    float zNearPlane = 1.5f;
    float zFarPlane  = 1000.0f;

    Matrix expected;

    expected.m11 = 0.03f;
    expected.m22 = 0.015f;
    expected.m33 = -1.00150228f;
    expected.m34 = -1.0f;
    expected.m43 = -1.50225341f;

    auto actual = Matrix::create_perspective(width, height, zNearPlane, zFarPlane);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreatePerspective (float, float, float, float)
// CreatePerspective test where znear = zfar
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveWhereZnearEqualsZfar)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    float width      = 100.0f;
    float height     = 200.0f;
    float zNearPlane = 0.0f;
    float zFarPlane  = 0.0f;

    EXPECT_DEATH(Matrix::create_perspective(width, height, zNearPlane, zFarPlane), "");
}

// A test for CreatePerspective (float, float, float, float)
// CreatePerspective test where near plane is negative value
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveWhereNearPlaneIsNegative)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(Matrix::create_perspective(10, 10, -10, 10), "");
}

// A test for CreatePerspective (float, float, float, float)
// CreatePerspective test where far plane is negative value
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveWhereFarPlaneIsNegative)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(Matrix::create_perspective(10, 10, 10, -10), "");
}

// A test for CreatePerspective (float, float, float, float)
// CreatePerspective test where near plane is beyond far plane
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveWhereNearPlaneIsBeyondFarPlane)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(Matrix::create_perspective(10, 10, 10, 1), "");
}

// A test for CreatePerspectiveFieldOfView (float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveFieldOfView1)
{
    float fieldOfView = SceneR::Math::to_radians(30.0f);
    float aspectRatio = 1280.0f / 720.0f;
    float zNearPlane  = 1.5f;
    float zFarPlane   = 1000.0f;

    Matrix expected;

    expected.m11 = 2.09927845f;
    expected.m22 = 3.73205066f;
    expected.m33 = -1.00150228f;
    expected.m34 = -1.0f;
    expected.m43 = -1.50225341f;

    auto actual = Matrix::create_perspective_field_of_view(fieldOfView, aspectRatio, zNearPlane, zFarPlane);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreatePerspectiveFieldOfView (float, float, float, float)
// CreatePerspectiveFieldOfView test where filedOfView is negative value.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveFieldOfViewWhereFieldOfViewIsNegative)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(Matrix::create_perspective_field_of_view(-1, 1, 1, 10), "");
}

// A test for CreatePerspectiveFieldOfView (float, float, float, float)
// CreatePerspectiveFieldOfView test where filedOfView is more than pi.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveFieldOfViewWhereFieldOfViewIsGreatherThanPi)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(Matrix::create_perspective_field_of_view(SceneR::Math::pi + 0.01f, 1, 1, 10), "");
}

// A test for CreatePerspectiveFieldOfView (float, float, float, float)
// CreatePerspectiveFieldOfView test where nearPlaneDistance is negative value.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveFieldOfViewWhereNearPlaneIsNegative)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(Matrix::create_perspective_field_of_view(SceneR::Math::pi_over_4, 1, -1, 10), "");
}

// A test for CreatePerspectiveFieldOfView (float, float, float, float)
// CreatePerspectiveFieldOfView test where farPlaneDistance is negative value.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveFieldOfViewWhereFarPlaneIsNegative)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(Matrix::create_perspective_field_of_view(SceneR::Math::pi_over_4, 1, 1, -10), "");
}

// A test for CreatePerspectiveFieldOfView (float, float, float, float)
// CreatePerspectiveFieldOfView test where nearPlaneDistance is larger than farPlaneDistance.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveFieldOfViewWhereNearPlaneIsLargerThanFarPlane)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(Matrix::create_perspective_field_of_view(SceneR::Math::pi_over_4, 1, 10, 1), "");
}

// A test for CreatePerspectiveOffCenter (float, float, float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveOffCenter)
{
    float left       = 10.0f;
    float right      = 90.0f;
    float bottom     = 20.0f;
    float top        = 180.0f;
    float zNearPlane = 1.5f;
    float zFarPlane  = 1000.0f;

    Matrix expected;

    expected.m11 = 0.0375f;
    expected.m22 = 0.01875f;
    expected.m31 = 1.25f;
    expected.m32 = 1.25f;
    expected.m33 = -1.00150228f;
    expected.m34 = -1.0f;
    expected.m43 = -1.50225341f;

    auto actual = Matrix::create_perspective_off_center(left, right, bottom, top, zNearPlane, zFarPlane);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreatePerspectiveOffCenter (float, float, float, float, float, float)
// CreatePerspectiveOffCenter test where nearPlaneDistance is negative.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveOffCenterWhereNearPlaneIsNegative)
{
    EXPECT_DEATH(Matrix::create_perspective_off_center(10.0f, 90.0f, 20.0f, 180.0f, -1, 10), "");
}

// A test for CreatePerspectiveOffCenter (float, float, float, float, float, float)
// CreatePerspectiveOffCenter test where farPlaneDistance is negative.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveOffCenterWhereFarPlaneIsNegative)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(Matrix::create_perspective_off_center(10.0f, 90.0f, 20.0f, 180.0f, 1, -10), "");
}

// A test for CreatePerspectiveOffCenter (float, float, float, float, float, float)
// CreatePerspectiveOffCenter test where test where nearPlaneDistance is larger than farPlaneDistance.
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreatePerspectiveOffCenterWhereNearPlaneIsLargerThanFarPlane)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    EXPECT_DEATH(Matrix::create_perspective_off_center(10.0f, 90.0f, 20.0f, 180.0f, 10, 1), "");
}

// A test for Invert (Matrix)
// Non invertible matrix - determinant is zero - singular matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, InvertNonInvertibleMatrix)
{
    Matrix a = { 1.0f , 2.0f , 3.0f , 4.0f
               , 5.0f , 6.0f , 7.0f , 8.0f
               , 9.0f , 10.0f, 11.0f, 12.0f
               , 13.0f, 14.0f, 15.0f, 16.0f };

    float detA = a.determinant();

    EXPECT_TRUE(EqualityHelper::Equal(detA, 0.0f));

    auto actual = Matrix::invert(a);

    // all the elements in Actual is NaN
    EXPECT_TRUE(SceneR::Math::is_nan(actual.m11)
             && SceneR::Math::is_nan(actual.m12)
             && SceneR::Math::is_nan(actual.m13)
             && SceneR::Math::is_nan(actual.m14)
             && SceneR::Math::is_nan(actual.m21)
             && SceneR::Math::is_nan(actual.m22)
             && SceneR::Math::is_nan(actual.m23)
             && SceneR::Math::is_nan(actual.m24)
             && SceneR::Math::is_nan(actual.m31)
             && SceneR::Math::is_nan(actual.m32)
             && SceneR::Math::is_nan(actual.m33)
             && SceneR::Math::is_nan(actual.m34)
             && SceneR::Math::is_nan(actual.m41)
             && SceneR::Math::is_nan(actual.m42)
             && SceneR::Math::is_nan(actual.m43)
             && SceneR::Math::is_nan(actual.m44));
}

// A test for operator - (Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, UnaryNegation)
{
    auto a = MatrixTest::GenerateMatrixNumberFrom1To16();

    Matrix expected;

    expected.m11 = -1.0f;
    expected.m12 = -2.0f;
    expected.m13 = -3.0f;
    expected.m14 = -4.0f;
    expected.m21 = -5.0f;
    expected.m22 = -6.0f;
    expected.m23 = -7.0f;
    expected.m24 = -8.0f;
    expected.m31 = -9.0f;
    expected.m32 = -10.0f;
    expected.m33 = -11.0f;
    expected.m34 = -12.0f;
    expected.m41 = -13.0f;
    expected.m42 = -14.0f;
    expected.m43 = -15.0f;
    expected.m44 = -16.0f;

    auto actual = -a;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator - (Matrix, Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, Subtraction)
{
    auto a = MatrixTest::GenerateMatrixNumberFrom1To16();
    auto b = MatrixTest::GenerateMatrixNumberFrom1To16();

    Matrix expected;

    auto actual = a - b;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator * (Matrix, Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, MultiplyTest1)
{
    auto a = MatrixTest::GenerateMatrixNumberFrom1To16();
    auto b = MatrixTest::GenerateMatrixNumberFrom1To16();

    Matrix expected;

    expected.m11 = (a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31 + a.m14 * b.m41);
    expected.m12 = (a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32 + a.m14 * b.m42);
    expected.m13 = (a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33 + a.m14 * b.m43);
    expected.m14 = (a.m11 * b.m14 + a.m12 * b.m24 + a.m13 * b.m34 + a.m14 * b.m44);

    expected.m21 = (a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31 + a.m24 * b.m41);
    expected.m22 = (a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32 + a.m24 * b.m42);
    expected.m23 = (a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33 + a.m24 * b.m43);
    expected.m24 = (a.m21 * b.m14 + a.m22 * b.m24 + a.m23 * b.m34 + a.m24 * b.m44);

    expected.m31 = (a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31 + a.m34 * b.m41);
    expected.m32 = (a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32 + a.m34 * b.m42);
    expected.m33 = (a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33 + a.m34 * b.m43);
    expected.m34 = (a.m31 * b.m14 + a.m32 * b.m24 + a.m33 * b.m34 + a.m34 * b.m44);

    expected.m41 = (a.m41 * b.m11 + a.m42 * b.m21 + a.m43 * b.m31 + a.m44 * b.m41);
    expected.m42 = (a.m41 * b.m12 + a.m42 * b.m22 + a.m43 * b.m32 + a.m44 * b.m42);
    expected.m43 = (a.m41 * b.m13 + a.m42 * b.m23 + a.m43 * b.m33 + a.m44 * b.m43);
    expected.m44 = (a.m41 * b.m14 + a.m42 * b.m24 + a.m43 * b.m34 + a.m44 * b.m44);

    auto actual = a * b;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator * (Matrix, Matrix)
// Multiply with identity matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, MultiplyTest2)
{
    Matrix a = { 1.0f , 2.0f  , 3.0f , 4.0f
               , 5.0f , -6.0f , 7.0f , -8.0f
               , 9.0f , 10.0f , 11.0f, 12.0f
               , 13.0f, -14.0f, 15.0f, -16.0f };

    auto b = Matrix::identity;

    auto expected = a;
    auto actual   = a * b;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator + (Matrix, Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, Addition)
{
    auto a = MatrixTest::GenerateMatrixNumberFrom1To16();
    auto b = MatrixTest::GenerateMatrixNumberFrom1To16();

    Matrix expected = { a.m11 + b.m11, a.m12 + b.m12, a.m13 + b.m13, a.m14 + b.m14
                      , a.m21 + b.m21, a.m22 + b.m22, a.m23 + b.m23, a.m24 + b.m24
                      , a.m31 + b.m31, a.m32 + b.m32, a.m33 + b.m33, a.m34 + b.m34
                      , a.m41 + b.m41, a.m42 + b.m42, a.m43 + b.m43, a.m44 + b.m44 };

    auto actual = a + b;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transpose (Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, Transpose)
{
    auto a = MatrixTest::GenerateMatrixNumberFrom1To16();

    Matrix expected = { a.m11, a.m21, a.m31, a.m41
                      , a.m12, a.m22, a.m32, a.m42
                      , a.m13, a.m23, a.m33, a.m43
                      , a.m14, a.m24, a.m34, a.m44 };

    auto actual = Matrix::transpose(a);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transpose (Matrix)
// Transpose Identity matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, TransposeIdentityMatrix)
{
    auto a        = Matrix::identity;
    auto expected = Matrix::identity;
    auto actual   = Matrix::transpose(a);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Matrix (Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateFromQuaternion)
{
    auto axis = Vector3::normalize({ 1.0f, 2.0f, 3.0f });
    auto q    = Quaternion::create_from_axis_angle(axis, SceneR::Math::to_radians(30.0f));

    Matrix expected = { 0.875595033f, 0.420031041f, -0.2385524f , 0.0f
                      , -0.38175258f, 0.904303849f, 0.1910483f  , 0.0f
                      , 0.295970082f, -0.07621294f, 0.952151954f, 0.0f
                      , 0.0f        , 0.0f        , 0.0f        , 1.0f };

    auto target = Matrix::create_from_quaternion(q);

    EXPECT_TRUE(EqualityHelper::Equal(expected, target));
}

// A test for FromQuaternion (Matrix)
// Convert X axis rotation matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateFromQuaternionConvertXAxisRotationMatrix)
{
    for (float angle = 0.0f; angle < 720.0f; angle += 10.0f)
    {
        auto quat     = Quaternion::create_from_axis_angle(Vector3::unit_x, angle);
        auto expected = Matrix::create_rotation_x(angle);
        auto actual   = Matrix::create_from_quaternion(quat);

        EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

        // make sure convert back to quaternion is same as we passed quaternion.
        auto q2 = Quaternion::create_from_rotation_matrix(actual);

        EXPECT_TRUE(EqualityHelper::EqualRotation(quat, q2));
    }
}

// A test for FromQuaternion (Matrix)
// Convert Y axis rotation matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateFromQuaternionConvertYAxisRotationMatrix)
{
    for (float angle = 0.0f; angle < 720.0f; angle += 10.0f)
    {
        auto quat     = Quaternion::create_from_axis_angle(Vector3::unit_y, angle);
        auto expected = Matrix::create_rotation_y(angle);
        auto actual   = Matrix::create_from_quaternion(quat);

        EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

        // make sure convert back to quaternion is same as we passed quaternion.
        auto q2 = Quaternion::create_from_rotation_matrix(actual);

        EXPECT_TRUE(EqualityHelper::EqualRotation(quat, q2));
    }
}

// A test for FromQuaternion (Matrix)
// Convert Z axis rotation matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateFromQuaternionConvertZAxisRotationMatrix)
{
    for (float angle = 0.0f; angle < 720.0f; angle += 10.0f)
    {
        auto quat     = Quaternion::create_from_axis_angle(Vector3::unit_z, angle);
        auto expected = Matrix::create_rotation_z(angle);
        auto actual   = Matrix::create_from_quaternion(quat);

        EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

        // make sure convert back to quaternion is same as we passed quaternion.
        auto q2 = Quaternion::create_from_rotation_matrix(actual);

        EXPECT_TRUE(EqualityHelper::EqualRotation(quat, q2));
    }
}

// A test for FromQuaternion (Matrix)
// Convert XYZ axis rotation matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateFromQuaternionConvertXYZAxisRotationMatrix)
{
    for (float angle = 0.0f; angle < 720.0f; angle += 10.0f)
    {
        auto quat = Quaternion::create_from_axis_angle(Vector3::unit_z, angle)
                  * Quaternion::create_from_axis_angle(Vector3::unit_y, angle)
                  * Quaternion::create_from_axis_angle(Vector3::unit_x, angle);

        auto expected = Matrix::create_rotation_x(angle)
                      * Matrix::create_rotation_y(angle)
                      * Matrix::create_rotation_z(angle);

        auto actual = Matrix::create_from_quaternion(quat);

        EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

        // make sure convert back to quaternion is same as we passed quaternion.
        auto q2 = Quaternion::create_from_rotation_matrix(actual);

        EXPECT_TRUE(EqualityHelper::EqualRotation(quat, q2));
    }
}

// A test for Multiply (Matrix, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, Multiply)
{
    auto a        = MatrixTest::GenerateMatrixNumberFrom1To16();
    auto expected = Matrix { 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48 };
    auto actual   = a * 3;

    EXPECT_TRUE(expected == actual);
}

// A test for negate (Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, Negate)
{
    auto m        = MatrixTest::GenerateMatrixNumberFrom1To16();
    auto expected = Matrix { -1.0f , -2.0f , -3.0f , -4.0f
                           , -5.0f , -6.0f , -7.0f , -8.0f
                           , -9.0f , -10.0f, -11.0f, -12.0f
                           , -13.0f, -14.0f, -15.0f, -16.0f };

    auto actual = Matrix::negate(m);

    EXPECT_TRUE(expected == actual);
}

// A test for operator != (Matrix, Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, Inequality)
{
    auto a = MatrixTest::GenerateMatrixNumberFrom1To16();
    auto b = MatrixTest::GenerateMatrixNumberFrom1To16();

    // case 1: compare between same values
    bool expected = false;
    bool actual   = a != b;

    EXPECT_TRUE(expected == actual);

    // case 2: compare between different values
    b.m11 = 11.0f;

    expected = true;
    actual   = a != b;

    EXPECT_TRUE(expected == actual);
}

// A test for operator == (Matrix, Matrix)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, Equality)
{
    auto a = MatrixTest::GenerateMatrixNumberFrom1To16();
    auto b = MatrixTest::GenerateMatrixNumberFrom1To16();

    // case 1: compare between same values
    bool expected = true;
    bool actual   = a == b;

    EXPECT_TRUE(expected == actual);

    // case 2: compare between different values
    b.m11 = 11.0f;

    expected = false;
    actual   = a == b;

    EXPECT_TRUE(expected == actual);
}

// A test for CreateScale (Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateScale)
{
    auto scales   = Vector3 { 2.0f, 3.0f, 4.0f };
    auto expected = Matrix { 2.0f, 0.0f, 0.0f, 0.0f
                           , 0.0f, 3.0f, 0.0f, 0.0f
                           , 0.0f, 0.0f, 4.0f, 0.0f
                           , 0.0f, 0.0f, 0.0f, 1.0f  };

    auto actual = Matrix::create_scale(scales);

    EXPECT_TRUE(expected == actual);
}

// A test for CreateScale (Vector3f, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateScaleCenter)
{
    auto scale  = Vector3 { 3, 4, 5 };
    auto center = Vector3 { 23, 42, 666 };

    auto scaleAroundZero         = Matrix::create_scale(scale, Vector3::zero);
    auto scaleAroundZeroExpected = Matrix::create_scale(scale);

    EXPECT_TRUE(EqualityHelper::Equal(scaleAroundZero, scaleAroundZeroExpected));

    auto scaleAroundCenter         = Matrix::create_scale(scale, center);
    auto scaleAroundCenterExpected = Matrix::create_translation(-center)
                                   * Matrix::create_scale(scale)
                                   * Matrix::create_translation(center);

    EXPECT_TRUE(EqualityHelper::Equal(scaleAroundCenter, scaleAroundCenterExpected));
}

// A test for CreateScale (float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateScale2)
{
    float scale    = 2.0f;
    Matrix expected = { 2.0f, 0.0f, 0.0f, 0.0f
                      , 0.0f, 2.0f, 0.0f, 0.0f
                      , 0.0f, 0.0f, 2.0f, 0.0f
                      , 0.0f, 0.0f, 0.0f, 1.0f };

    auto actual = Matrix::create_scale(scale);

    EXPECT_TRUE(expected == actual);
}

// A test for CreateScale (float, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateScale3)
{
    float scale  = 5;
    auto   center = Vector3 { 23, 42, 666 };

    auto scaleAroundZero         = Matrix::create_scale(scale, Vector3::zero);
    auto scaleAroundZeroExpected = Matrix::create_scale(scale);

    EXPECT_TRUE(EqualityHelper::Equal(scaleAroundZero, scaleAroundZeroExpected));

    auto scaleAroundCenter         = Matrix::create_scale(scale, center);
    auto scaleAroundCenterExpected = Matrix::create_translation(-center)
                                   * Matrix::create_scale(scale)
                                   * Matrix::create_translation(center);

    EXPECT_TRUE(EqualityHelper::Equal(scaleAroundCenter, scaleAroundCenterExpected));
}

// A test for CreateScale (float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateScale4)
{
    float xScale   = 2.0f;
    float yScale   = 3.0f;
    float zScale   = 4.0f;
    Matrix expected = { 2.0f, 0.0f, 0.0f, 0.0f
                      , 0.0f, 3.0f, 0.0f, 0.0f
                      , 0.0f, 0.0f, 4.0f, 0.0f
                      , 0.0f, 0.0f, 0.0f, 1.0f };

    auto actual = Matrix::create_scale(xScale, yScale, zScale);

    EXPECT_TRUE(expected == actual);
}

// A test for CreateScale (float, float, float, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateScale5)
{
    auto scale  = Vector3 { 3, 4, 5 };
    auto center = Vector3 { 23, 42, 666 };

    auto scaleAroundZero         = Matrix::create_scale(scale.x, scale.y, scale.z, Vector3::zero);
    auto scaleAroundZeroExpected = Matrix::create_scale(scale.x, scale.y, scale.z);

    EXPECT_TRUE(EqualityHelper::Equal(scaleAroundZero, scaleAroundZeroExpected));

    auto scaleAroundCenter         = Matrix::create_scale(scale.x, scale.y, scale.z, center);
    auto scaleAroundCenterExpected = Matrix::create_translation(-center)
                                   * Matrix::create_scale(scale.x, scale.y, scale.z)
                                   * Matrix::create_translation(center);

    EXPECT_TRUE(EqualityHelper::Equal(scaleAroundCenter, scaleAroundCenterExpected));
}

// A test for CreateTranslation (Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateTranslation)
{
    Vector3 position = { 2.0f, 3.0f, 4.0f };
    Matrix  expected = { 1.0f, 0.0f, 0.0f, 0.0f
                       , 0.0f, 1.0f, 0.0f, 0.0f
                       , 0.0f, 0.0f, 1.0f, 0.0f
                       , 2.0f, 3.0f, 4.0f, 1.0f };

    auto actual = Matrix::create_translation(position);

    EXPECT_TRUE(expected == actual);
}

// A test for CreateTranslation (float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateTranslation1)
{
    float xPosition = 2.0f;
    float yPosition = 3.0f;
    float zPosition = 4.0f;
    Matrix expected  = { 1.0f, 0.0f, 0.0f, 0.0f
                       , 0.0f, 1.0f, 0.0f, 0.0f
                       , 0.0f, 0.0f, 1.0f, 0.0f
                       , 2.0f, 3.0f, 4.0f, 1.0f };

    auto actual = Matrix::create_translation(xPosition, yPosition, zPosition);

    EXPECT_TRUE(expected == actual);
}

// A test for Translation
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateTranslation2)
{
    auto a = MatrixTest::GenerateTestMatrix();
    auto b = a;

    // Transfomed vector that has same semantics of property must be same.
    auto val = Vector3 { a.m41, a.m42, a.m43 };

    EXPECT_TRUE(val == a.translation());

    // Set value and get value must be same.
    val = Vector3 { 1.0f, 2.0f, 3.0f };

    a.translation(val);

    EXPECT_TRUE(val == a.translation());

    // Make sure it only modifies expected value of matrix.
    EXPECT_TRUE(a.m11 == b.m11 && a.m12 == b.m12 && a.m13 == b.m13 && a.m14 == b.m14
             && a.m21 == b.m21 && a.m22 == b.m22 && a.m23 == b.m23 && a.m24 == b.m24
             && a.m31 == b.m31 && a.m32 == b.m32 && a.m33 == b.m33 && a.m34 == b.m34
             && a.m41 != b.m41 && a.m42 != b.m42 && a.m43 != b.m43 && a.m44 == b.m44);
}

// A test for IsIdentity
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, IsIdentity)
{
    EXPECT_TRUE( Matrix::identity.is_identity());
    EXPECT_TRUE( Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).is_identity());
    EXPECT_FALSE(Matrix(0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).is_identity());
    EXPECT_FALSE(Matrix(1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).is_identity());
    EXPECT_FALSE(Matrix(1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).is_identity());
    EXPECT_FALSE(Matrix(1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).is_identity());
    EXPECT_FALSE(Matrix(1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).is_identity());
    EXPECT_FALSE(Matrix(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).is_identity());
    EXPECT_FALSE(Matrix(1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1).is_identity());
    EXPECT_FALSE(Matrix(1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1).is_identity());
    EXPECT_FALSE(Matrix(1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1).is_identity());
    EXPECT_FALSE(Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1).is_identity());
    EXPECT_FALSE(Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1).is_identity());
    EXPECT_FALSE(Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1).is_identity());
    EXPECT_FALSE(Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1).is_identity());
    EXPECT_FALSE(Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1).is_identity());
    EXPECT_FALSE(Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1).is_identity());
    EXPECT_FALSE(Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0).is_identity());
}

// A test for Matrix comparison involving NaN values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, EqualsNan)
{
    Matrix a = { SceneR::Math::nan, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Matrix b = { 0, SceneR::Math::nan, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Matrix c = { 0, 0, SceneR::Math::nan, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Matrix d = { 0, 0, 0, SceneR::Math::nan, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Matrix e = { 0, 0, 0, 0, SceneR::Math::nan, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Matrix f = { 0, 0, 0, 0, 0, SceneR::Math::nan, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Matrix g = { 0, 0, 0, 0, 0, 0, SceneR::Math::nan, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Matrix h = { 0, 0, 0, 0, 0, 0, 0, SceneR::Math::nan, 0, 0, 0, 0, 0, 0, 0, 0 };
    Matrix i = { 0, 0, 0, 0, 0, 0, 0, 0, SceneR::Math::nan, 0, 0, 0, 0, 0, 0, 0 };
    Matrix j = { 0, 0, 0, 0, 0, 0, 0, 0, 0, SceneR::Math::nan, 0, 0, 0, 0, 0, 0 };
    Matrix k = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SceneR::Math::nan, 0, 0, 0, 0, 0 };
    Matrix l = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SceneR::Math::nan, 0, 0, 0, 0 };
    Matrix m = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SceneR::Math::nan, 0, 0, 0 };
    Matrix n = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SceneR::Math::nan, 0, 0 };
    Matrix o = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SceneR::Math::nan, 0 };
    Matrix p = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SceneR::Math::nan};

    EXPECT_FALSE(a == Matrix {});
    EXPECT_FALSE(b == Matrix {});
    EXPECT_FALSE(c == Matrix {});
    EXPECT_FALSE(d == Matrix {});
    EXPECT_FALSE(e == Matrix {});
    EXPECT_FALSE(f == Matrix {});
    EXPECT_FALSE(g == Matrix {});
    EXPECT_FALSE(h == Matrix {});
    EXPECT_FALSE(i == Matrix {});
    EXPECT_FALSE(j == Matrix {});
    EXPECT_FALSE(k == Matrix {});
    EXPECT_FALSE(l == Matrix {});
    EXPECT_FALSE(m == Matrix {});
    EXPECT_FALSE(n == Matrix {});
    EXPECT_FALSE(o == Matrix {});
    EXPECT_FALSE(p == Matrix {});

    EXPECT_TRUE(a != Matrix {});
    EXPECT_TRUE(b != Matrix {});
    EXPECT_TRUE(c != Matrix {});
    EXPECT_TRUE(d != Matrix {});
    EXPECT_TRUE(e != Matrix {});
    EXPECT_TRUE(f != Matrix {});
    EXPECT_TRUE(g != Matrix {});
    EXPECT_TRUE(h != Matrix {});
    EXPECT_TRUE(i != Matrix {});
    EXPECT_TRUE(j != Matrix {});
    EXPECT_TRUE(k != Matrix {});
    EXPECT_TRUE(l != Matrix {});
    EXPECT_TRUE(m != Matrix {});
    EXPECT_TRUE(n != Matrix {});
    EXPECT_TRUE(o != Matrix {});
    EXPECT_TRUE(p != Matrix {});

    EXPECT_FALSE(a.is_identity());
    EXPECT_FALSE(b.is_identity());
    EXPECT_FALSE(c.is_identity());
    EXPECT_FALSE(d.is_identity());
    EXPECT_FALSE(e.is_identity());
    EXPECT_FALSE(f.is_identity());
    EXPECT_FALSE(g.is_identity());
    EXPECT_FALSE(h.is_identity());
    EXPECT_FALSE(i.is_identity());
    EXPECT_FALSE(j.is_identity());
    EXPECT_FALSE(k.is_identity());
    EXPECT_FALSE(l.is_identity());
    EXPECT_FALSE(m.is_identity());
    EXPECT_FALSE(n.is_identity());
    EXPECT_FALSE(o.is_identity());
    EXPECT_FALSE(p.is_identity());
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(MatrixTest, CreateReflection)
{
    // XY plane.
    MatrixTest::CreateReflection({ Vector3::unit_z, 0 }, Matrix::create_scale(1, 1, -1));
    // XZ plane.
    MatrixTest::CreateReflection({ Vector3::unit_y, 0 }, Matrix::create_scale(1, -1, 1));
    // YZ plane.
    MatrixTest::CreateReflection({ Vector3::unit_x, 0 }, Matrix::create_scale(-1, 1, 1));

    // Complex cases.
    auto planes = std::vector<Plane>();

    planes.push_back({ 0, 1, 0, 0 });
    planes.push_back({ 1, 2, 3, 4 });
    planes.push_back({ 5, 6, 7, 8 });
    planes.push_back({-1,-2,-3,-4 });
    planes.push_back({-5,-6,-7,-8 });

    auto points = std::vector<Vector3>();

    points.push_back({  1, 2, 3 });
    points.push_back({  5, 6, 7 });
    points.push_back({ -1,-2,-3 });
    points.push_back({ -5,-6,-7 });

    for (auto& p : planes)
    {
        auto plane = Plane::normalize(p);
        auto m     = Matrix::create_reflection(plane);
        auto pp    = -plane.d * plane.normal; // Position on the plane.

        for (auto& point : points)
        {
            auto rp = Vector3::transform(point, m);

            // Manually compute reflection point and compare results.
            auto   v  = point - pp;
            float d  = Vector3::dot(v, plane.normal);
            auto   vp = point - 2.0f * d * plane.normal;

            EXPECT_TRUE(EqualityHelper::Equal(rp, vp));
        }
    }
}

/*
// A test for Lerp (Matrix, Matrix, float)
[Fact]
public void MatrixLerpTest()
{
    Matrix a = new Matrix();
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

    Matrix b = GenerateMatrixNumberFrom1To16();

    float t = 0.5f;

    Matrix expected = new Matrix();
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

    Matrix actual;
    actual = Matrix.Lerp(a, b, t);
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.Lerp did not return the expected value.");
}

private void CreateBillboardFact(Vector3 placeDirection, Vector3 cameraUpVector, Matrix expectedRotation)
{
    Vector3 cameraPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 objectPosition = cameraPosition + placeDirection * 10.0f;
    Matrix expected = expectedRotation * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateBillboard(objectPosition, cameraPosition, cameraUpVector, new Vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateBillboard did not return the expected value.");
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Forward side of camera on XZ-plane
[Fact]
public void MatrixCreateBillboardTest01()
{
    // Object placed at Forward of camera. result must be same as 180 degrees rotate along y-axis.
    CreateBillboardFact(new Vector3(0, 0, -1), new Vector3(0, 1, 0), Matrix.CreateRotationY(MathHelper.ToRadians(180.0f)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Backward side of camera on XZ-plane
[Fact]
public void MatrixCreateBillboardTest02()
{
    // Object placed at Backward of camera. This result must be same as 0 degrees rotate along y-axis.
    CreateBillboardFact(new Vector3(0, 0, 1), new Vector3(0, 1, 0), Matrix.CreateRotationY(MathHelper.ToRadians(0)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Right side of camera on XZ-plane
[Fact]
public void MatrixCreateBillboardTest03()
{
    // Place object at Right side of camera. This result must be same as 90 degrees rotate along y-axis.
    CreateBillboardFact(new Vector3(1, 0, 0), new Vector3(0, 1, 0), Matrix.CreateRotationY(MathHelper.ToRadians(90)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Left side of camera on XZ-plane
[Fact]
public void MatrixCreateBillboardTest04()
{
    // Place object at Left side of camera. This result must be same as -90 degrees rotate along y-axis.
    CreateBillboardFact(new Vector3(-1, 0, 0), new Vector3(0, 1, 0), Matrix.CreateRotationY(MathHelper.ToRadians(-90)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Up side of camera on XY-plane
[Fact]
public void MatrixCreateBillboardTest05()
{
    // Place object at Up side of camera. result must be same as 180 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateBillboardFact(new Vector3(0, 1, 0), new Vector3(0, 0, 1),
                        Matrix.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationZ(MathHelper.ToRadians(180)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Down side of camera on XY-plane
[Fact]
public void MatrixCreateBillboardTest06()
{
    // Place object at Down side of camera. result must be same as 0 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateBillboardFact(new Vector3(0, -1, 0), new Vector3(0, 0, 1),
                        Matrix.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationZ(MathHelper.ToRadians(0)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Right side of camera on XY-plane
[Fact]
public void MatrixCreateBillboardTest07()
{
    // Place object at Right side of camera. result must be same as 90 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateBillboardFact(new Vector3(1, 0, 0), new Vector3(0, 0, 1),
                        Matrix.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationZ(MathHelper.ToRadians(90.0f)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Left side of camera on XY-plane
[Fact]
public void MatrixCreateBillboardTest08()
{
    // Place object at Left side of camera. result must be same as -90 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateBillboardFact(new Vector3(-1, 0, 0), new Vector3(0, 0, 1),
                        Matrix.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationZ(MathHelper.ToRadians(-90.0f)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Up side of camera on YZ-plane
[Fact]
public void MatrixCreateBillboardTest09()
{
    // Place object at Up side of camera. result must be same as -90 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateBillboardFact(new Vector3(0, 1, 0), new Vector3(-1, 0, 0),
                        Matrix.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationX(MathHelper.ToRadians(-90.0f)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Down side of camera on YZ-plane
[Fact]
public void MatrixCreateBillboardTest10()
{
    // Place object at Down side of camera. result must be same as 90 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateBillboardFact(new Vector3(0, -1, 0), new Vector3(-1, 0, 0),
                        Matrix.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationX(MathHelper.ToRadians(90.0f)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Forward side of camera on YZ-plane
[Fact]
public void MatrixCreateBillboardTest11()
{
    // Place object at Forward side of camera. result must be same as 180 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateBillboardFact(new Vector3(0, 0, -1), new Vector3(-1, 0, 0),
                        Matrix.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationX(MathHelper.ToRadians(180.0f)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Backward side of camera on YZ-plane
[Fact]
public void MatrixCreateBillboardTest12()
{
    // Place object at Backward side of camera. result must be same as 0 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateBillboardFact(new Vector3(0, 0, 1), new Vector3(-1, 0, 0),
                        Matrix.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationX(MathHelper.ToRadians(0.0f)));
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Object and camera positions are too close and doesn't pass cameraFowardVector.
[Fact]
public void MatrixCreateBillboardTooCloseTest1()
{
    Vector3 objectPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 cameraPosition = objectPosition;
    Vector3 cameraUpVector = new Vector3(0, 1, 0);

    // Doesn't pass camera face direction. CreateBillboard uses new Vector3f(0, 0, -1) direction. Result must be same as 180 degrees rotate along y-axis.
    Matrix expected = Matrix.CreateRotationY(MathHelper.ToRadians(180.0f)) * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateBillboard(objectPosition, cameraPosition, cameraUpVector, new Vector3(0, 0, 1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateBillboard did not return the expected value.");
}

// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Object and camera positions are too close and passed cameraFowardVector.
[Fact]
public void MatrixCreateBillboardTooCloseTest2()
{
    Vector3 objectPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 cameraPosition = objectPosition;
    Vector3 cameraUpVector = new Vector3(0, 1, 0);

    // Passes Vector3f.Rgiht as camera face direction. Result must be same as -90 degrees rotate along y-axis.
    Matrix expected = Matrix.CreateRotationY(MathHelper.ToRadians(-90.0f)) * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateBillboard(objectPosition, cameraPosition, cameraUpVector, new Vector3(1, 0, 0));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateBillboard did not return the expected value.");
}

private void CreateConstrainedBillboardFact(Vector3 placeDirection, Vector3 rotateAxis, Matrix expectedRotation)
{
    Vector3 cameraPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 objectPosition = cameraPosition + placeDirection * 10.0f;
    Matrix expected = expectedRotation * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new Vector3(0, 0, -1), new Vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateConstrainedBillboard did not return the expected value.");

    // When you move camera along rotateAxis, result must be same.
    cameraPosition += rotateAxis * 10.0f;
    actual = Matrix.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new Vector3(0, 0, -1), new Vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateConstrainedBillboard did not return the expected value.");

    cameraPosition -= rotateAxis * 30.0f;
    actual = Matrix.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new Vector3(0, 0, -1), new Vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Forward side of camera on XZ-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest01()
{
    // Object placed at Forward of camera. result must be same as 180 degrees rotate along y-axis.
    CreateConstrainedBillboardFact(new Vector3(0, 0, -1), new Vector3(0, 1, 0), Matrix.CreateRotationY(MathHelper.ToRadians(180.0f)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Backward side of camera on XZ-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest02()
{
    // Object placed at Backward of camera. This result must be same as 0 degrees rotate along y-axis.
    CreateConstrainedBillboardFact(new Vector3(0, 0, 1), new Vector3(0, 1, 0), Matrix.CreateRotationY(MathHelper.ToRadians(0)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Right side of camera on XZ-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest03()
{
    // Place object at Right side of camera. This result must be same as 90 degrees rotate along y-axis.
    CreateConstrainedBillboardFact(new Vector3(1, 0, 0), new Vector3(0, 1, 0), Matrix.CreateRotationY(MathHelper.ToRadians(90)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Left side of camera on XZ-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest04()
{
    // Place object at Left side of camera. This result must be same as -90 degrees rotate along y-axis.
    CreateConstrainedBillboardFact(new Vector3(-1, 0, 0), new Vector3(0, 1, 0), Matrix.CreateRotationY(MathHelper.ToRadians(-90)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Up side of camera on XY-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest05()
{
    // Place object at Up side of camera. result must be same as 180 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateConstrainedBillboardFact(new Vector3(0, 1, 0), new Vector3(0, 0, 1),
                                   Matrix.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationZ(MathHelper.ToRadians(180)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Down side of camera on XY-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest06()
{
    // Place object at Down side of camera. result must be same as 0 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateConstrainedBillboardFact(new Vector3(0, -1, 0), new Vector3(0, 0, 1),
                                   Matrix.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationZ(MathHelper.ToRadians(0)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Right side of camera on XY-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest07()
{
    // Place object at Right side of camera. result must be same as 90 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateConstrainedBillboardFact(new Vector3(1, 0, 0), new Vector3(0, 0, 1),
                                   Matrix.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationZ(MathHelper.ToRadians(90.0f)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Left side of camera on XY-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest08()
{
    // Place object at Left side of camera. result must be same as -90 degrees rotate along z-axis after 90 degrees rotate along x-axis.
    CreateConstrainedBillboardFact(new Vector3(-1, 0, 0), new Vector3(0, 0, 1),
                                   Matrix.CreateRotationX(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationZ(MathHelper.ToRadians(-90.0f)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Up side of camera on YZ-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest09()
{
    // Place object at Up side of camera. result must be same as -90 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateConstrainedBillboardFact(new Vector3(0, 1, 0), new Vector3(-1, 0, 0),
                                   Matrix.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationX(MathHelper.ToRadians(-90.0f)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Down side of camera on YZ-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest10()
{
    // Place object at Down side of camera. result must be same as 90 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateConstrainedBillboardFact(new Vector3(0, -1, 0), new Vector3(-1, 0, 0),
                                   Matrix.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationX(MathHelper.ToRadians(90.0f)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Forward side of camera on YZ-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest11()
{
    // Place object at Forward side of camera. result must be same as 180 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateConstrainedBillboardFact(new Vector3(0, 0, -1), new Vector3(-1, 0, 0),
                                   Matrix.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationX(MathHelper.ToRadians(180.0f)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Place object at Backward side of camera on YZ-plane
[Fact]
public void MatrixCreateConstrainedBillboardTest12()
{
    // Place object at Backward side of camera. result must be same as 0 degrees rotate along x-axis after 90 degrees rotate along z-axis.
    CreateConstrainedBillboardFact(new Vector3(0, 0, 1), new Vector3(-1, 0, 0),
                                   Matrix.CreateRotationZ(MathHelper.ToRadians(90.0f)) * Matrix.CreateRotationX(MathHelper.ToRadians(0.0f)));
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Object and camera positions are too close and doesn't pass cameraForwardVector.
[Fact]
public void MatrixCreateConstrainedBillboardTooCloseTest1()
{
    Vector3 objectPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 cameraPosition = objectPosition;
    Vector3 cameraUpVector = new Vector3(0, 1, 0);

    // Doesn't pass camera face direction. CreateConstrainedBillboard uses new Vector3f(0, 0, -1) direction. Result must be same as 180 degrees rotate along y-axis.
    Matrix expected = Matrix.CreateRotationY(MathHelper.ToRadians(180.0f)) * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateConstrainedBillboard(objectPosition, cameraPosition, cameraUpVector, new Vector3(0, 0, 1), new Vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Object and camera positions are too close and passed cameraForwardVector.
[Fact]
public void MatrixCreateConstrainedBillboardTooCloseTest2()
{
    Vector3 objectPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 cameraPosition = objectPosition;
    Vector3 cameraUpVector = new Vector3(0, 1, 0);

    // Passes Vector3f.Rgiht as camera face direction. Result must be same as -90 degrees rotate along y-axis.
    Matrix expected = Matrix.CreateRotationY(MathHelper.ToRadians(-90.0f)) * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateConstrainedBillboard(objectPosition, cameraPosition, cameraUpVector, new Vector3(1, 0, 0), new Vector3(0, 0, -1));
    Assert.True(MathHelper.equal(expected, actual), "Matrix.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Angle between rotateAxis and camera to object vector is too small. And use doesn't passed objectForwardVector parameter.
[Fact]
public void MatrixCreateConstrainedBillboardAlongAxisTest1()
{
    // Place camera at up side of object.
    Vector3 objectPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 rotateAxis = new Vector3(0, 1, 0);
    Vector3 cameraPosition = objectPosition + rotateAxis * 10.0f;

    // In this case, CreateConstrainedBillboard picks new Vector3f(0, 0, -1) as object forward vector.
    Matrix expected = Matrix.CreateRotationY(MathHelper.ToRadians(180.0f)) * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new Vector3(0, 0, -1), new Vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Angle between rotateAxis and camera to object vector is too small. And user doesn't passed objectForwardVector parameter.
[Fact]
public void MatrixCreateConstrainedBillboardAlongAxisTest2()
{
    // Place camera at up side of object.
    Vector3 objectPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 rotateAxis = new Vector3(0, 0, -1);
    Vector3 cameraPosition = objectPosition + rotateAxis * 10.0f;

    // In this case, CreateConstrainedBillboard picks new Vector3f(1, 0, 0) as object forward vector.
    Matrix expected = Matrix.CreateRotationX(MathHelper.ToRadians(-90.0f)) * Matrix.CreateRotationZ(MathHelper.ToRadians(-90.0f)) * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new Vector3(0, 0, -1), new Vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Angle between rotateAxis and camera to object vector is too small. And user passed correct objectForwardVector parameter.
[Fact]
public void MatrixCreateConstrainedBillboardAlongAxisTest3()
{
    // Place camera at up side of object.
    Vector3 objectPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 rotateAxis = new Vector3(0, 1, 0);
    Vector3 cameraPosition = objectPosition + rotateAxis * 10.0f;

    // User passes correct objectForwardVector.
    Matrix expected = Matrix.CreateRotationY(MathHelper.ToRadians(180.0f)) * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new Vector3(0, 0, -1), new Vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Angle between rotateAxis and camera to object vector is too small. And user passed incorrect objectForwardVector parameter.
[Fact]
public void MatrixCreateConstrainedBillboardAlongAxisTest4()
{
    // Place camera at up side of object.
    Vector3 objectPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 rotateAxis = new Vector3(0, 1, 0);
    Vector3 cameraPosition = objectPosition + rotateAxis * 10.0f;

    // User passes correct objectForwardVector.
    Matrix expected = Matrix.CreateRotationY(MathHelper.ToRadians(180.0f)) * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new Vector3(0, 0, -1), new Vector3(0, 1, 0));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateConstrainedBillboard did not return the expected value.");
}

// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
// Angle between rotateAxis and camera to object vector is too small. And user passed incorrect objectForwardVector parameter.
[Fact]
public void MatrixCreateConstrainedBillboardAlongAxisTest5()
{
    // Place camera at up side of object.
    Vector3 objectPosition = new Vector3(3.0f, 4.0f, 5.0f);
    Vector3 rotateAxis = new Vector3(0, 0, -1);
    Vector3 cameraPosition = objectPosition + rotateAxis * 10.0f;

    // In this case, CreateConstrainedBillboard picks Vector3f.Right as object forward vector.
    Matrix expected = Matrix.CreateRotationX(MathHelper.ToRadians(-90.0f)) * Matrix.CreateRotationZ(MathHelper.ToRadians(-90.0f)) * Matrix.CreateTranslation(objectPosition);
    Matrix actual = Matrix.CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, new Vector3(0, 0, -1), new Vector3(0, 0, -1));
    Assert.True(MathHelper.Equal(expected, actual), "Matrix.CreateConstrainedBillboard did not return the expected value.");
}
*/
