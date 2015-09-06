// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Vector4Test.hpp>

#include <EqualityHelper.hpp>

#include <System/Math.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Vector4.hpp>

using namespace System;
using namespace SceneR::Framework;

TEST_F(Vector4Test, VectorMatrixMultiplication)
{
    auto point  = Vector4 { 10.0f, 5.0f, 1.0f, 4.0f };
    auto matrix = Matrix  { 10.0f, 10.0f, 10.0f, 0.0f
                          , 20.0f, 20.0f, 20.0f, 0.0f
                          , 30.0f, 30.0f, 30.0f, 0.0f
                          , 5.0f , 10.0f, 15.0f, 1.0f };
    auto result = point * matrix;

    // pointResult is equal to (250, 270, 290, 4)
    EXPECT_TRUE(result.x == 250.0f);
    EXPECT_TRUE(result.y == 270.0f);
    EXPECT_TRUE(result.z == 290.0f);
    EXPECT_TRUE(result.w == 4.0f);
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Sizeof)
{
    EXPECT_TRUE(16 == sizeof(Vector4));
}

// A test for DistanceSquared (Vector4f, Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, DistanceSquared)
{
    auto a = Vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = Vector4 { 5.0f, 6.0f, 7.0f, 8.0f };

    auto expected = 64.0f;
    auto actual   = Vector4::distance_squared(a, b);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Distance (Vector4f, Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Distance)
{
    auto a = Vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = Vector4 { 5.0f, 6.0f, 7.0f, 8.0f };

    auto expected = 8.0f;
    auto actual   = Vector4::distance(a, b);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Distance (Vector4f, Vector4f)
// Distance from the same point
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, DistanceFromTheSamePoint)
{
    auto a = Vector4({ 1.051f, 2.05f }, 3.478f, 1.0f);  // With Vector2
    auto b = Vector4({ 1.051f, 2.05f, 3.478f }, 0.0f); // With Vector3

    b.w = 1.0f;

    auto actual = Vector4::distance(a, b);

    EXPECT_TRUE(0.0f == actual);
}

// A test for Dot (Vector4f, Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Dot)
{
    auto a = Vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = Vector4 { 5.0f, 6.0f, 7.0f, 8.0f };

    auto expected = 70.0f;
    auto actual   = Vector4::dot(a, b);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Dot (Vector4f, Vector4f)
// Dot test for perpendicular vector
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, DotForPerpendicularVector)
{
    auto a = Vector3 { 1.55f, 1.55f, 1 };
    auto b = Vector3 { 2.5f, 3, 1.5f };
    auto c = Vector3::cross(a, b);

    auto d = Vector4 { a, 0 };
    auto e = Vector4 { c, 0 };

    auto actual = Vector4::dot(d, e);

    EXPECT_TRUE(EqualityHelper::Equal(0.0f, actual));
}

// A test for Length ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Length)
{
    auto a      = Vector3 { 1.0f, 2.0f, 3.0f };
    auto w      = 4.0f;
    auto target = Vector4 { a, w };

    auto expected = Math::sqrt(30.0f);
    auto actual   = target.length();

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Length ()
// Length test where length is zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, LengthWhereLengthIsZero)
{
    Vector4 target;
    auto    expected = 0.0f;
    auto    actual   = target.length();

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for LengthSquared ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, LengthSquared)
{
    auto a = Vector3 { 1.0f, 2.0f, 3.0f };
    auto w = 4.0f;

    auto target = Vector4 { a, w };

    auto expected = 30;
    auto actual   = target.length_squared();

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Min (Vector4f, Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Min)
{
    auto a = Vector4 { -1.0f, 4.0f, -3.0f, 1000.0f };
    auto b = Vector4 { 2.0f, 1.0f, -1.0f, 0.0f };

    auto expected = Vector4 { -1.0f, 1.0f, -3.0f, 0.0f };
    auto actual   = Vector4::min(a, b);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Max (Vector4f, Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Max)
{
    auto a = Vector4 { -1.0f, 4.0f, -3.0f, 1000.0f };
    auto b = Vector4 { 2.0f, 1.0f, -1.0f, 0.0f };

    auto expected = Vector4(2.0f, 4.0f, -1.0f, 1000.0f);
    auto actual   = Vector4::max(a, b);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, MinMaxCodeCoverage)
{
    auto    min = Vector4::zero;
    auto    max = Vector4::one;
    Vector4 actual;

    // Min.
    actual = Vector4::min(min, max);

    EXPECT_TRUE(actual == min);

    actual = Vector4::min(max, min);

    EXPECT_TRUE(actual == min);

    // Max.
    actual = Vector4::max(min, max);

    EXPECT_TRUE(actual == max);

    actual = Vector4::max(max, min);

    EXPECT_TRUE(actual == max);
}

// A test for clamp (Vector4f, Vector4f, Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Clamp)
{
    auto a   = Vector4 { 0.5f, 0.3f, 0.33f, 0.44f };
    auto min = Vector4 { 0.0f, 0.1f, 0.13f, 0.14f };
    auto max = Vector4 { 1.0f, 1.1f, 1.13f, 1.14f };

    // Normal case.
    // Case N1: specfied value is in the range.
    auto expected = Vector4 { 0.5f, 0.3f, 0.33f, 0.44f };
    auto actual   = Vector4::clamp(a, min, max);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Normal case.
    // Case N2: specfied value is bigger than max value.
    a        = Vector4 { 2.0f, 3.0f, 4.0f, 5.0f };
    expected = max;
    actual   = Vector4::clamp(a, min, max);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Case N3: specfied value is smaller than max value.
    a        = Vector4 { -2.0f, -3.0f, -4.0f, -5.0f };
    expected = min;
    actual   = Vector4::clamp(a, min, max);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Case N4: combination case.
    a        = Vector4 { -2.0f, 0.5f, 4.0f, -5.0f };
    expected = Vector4 { min.x, a.y, max.z, min.w };
    actual   = Vector4::clamp(a, min, max);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // User specfied min value is bigger than max value.
    max = Vector4 { 0.0f, 0.1f, 0.13f, 0.14f };
    min = Vector4 { 1.0f, 1.1f, 1.13f, 1.14f };

    // Case W1: specfied value is in the range.
    a        = Vector4 { 0.5f, 0.3f, 0.33f, 0.44f };
    expected = min;
    actual   = Vector4::clamp(a, min, max);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Normal case.
    // Case W2: specfied value is bigger than max and min value.
    a        = Vector4 { 2.0f, 3.0f, 4.0f, 5.0f };
    expected = min;
    actual   = Vector4::clamp(a, min, max);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Case W3: specfied value is smaller than min and max value.
    a        = Vector4 { -2.0f, -3.0f, -4.0f, -5.0f };
    expected = min;
    actual   = Vector4::clamp(a, min, max);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Vector4f, Vector4f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Lerp)
{
    auto a = Vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = Vector4 { 5.0f, 6.0f, 7.0f, 8.0f };
    auto t = 0.5f;

    auto expected = Vector4 { 3.0f, 4.0f, 5.0f, 6.0f };
    auto actual   = Vector4::lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Vector4f, Vector4f, float)
// Lerp test with factor zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, LerpWithFactorZero)
{
    auto a = Vector4 { { 1.0f, 2.0f, 3.0f }, 4.0f };
    auto b = Vector4 { 4.0f, 5.0f, 6.0f, 7.0f };
    auto t = 0.0f;

    auto expected = Vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto actual   = Vector4::lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Vector4f, Vector4f, float)
// Lerp test with factor one
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, LerpWithFactorOne)
{
    auto a = Vector4 { { 1.0f, 2.0f, 3.0f }, 4.0f };
    auto b = Vector4 { 4.0f, 5.0f, 6.0f, 7.0f };
    auto t = 1.0f;

    auto expected = Vector4 { 4.0f, 5.0f, 6.0f, 7.0f };
    auto actual   = Vector4::lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Vector4f, Vector4f, float)
// Lerp test with factor > 1
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, LerpWithFactorGreaterThanOne)
{
    auto a = Vector4 { { 0.0f, 0.0f, 0.0f }, 0.0f };
    auto b = Vector4 { 4.0f, 5.0f, 6.0f, 7.0f };
    auto t = 2.0f;

    auto expected = Vector4 { 8.0f, 10.0f, 12.0f, 14.0f };
    auto actual   = Vector4::lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Vector4f, Vector4f, float)
// Lerp test with factor < 0
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, LerpWithFactorLessThanZero)
{
    auto a = Vector4 { { 0.0f, 0.0f, 0.0f }, 0.0f };
    auto b = Vector4 { 4.0f, 5.0f, 6.0f, 7.0f };
    auto t = -2.0f;

    auto expected = -(b * 2);
    auto actual   = Vector4::lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Vector4f, Vector4f, float)
// Lerp test from the same point
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, LerpFromTheSamePoint)
{
    Vector4 a = Vector4 { 4.0f, 5.0f, 6.0f, 7.0f };
    Vector4 b = Vector4 { 4.0f, 5.0f, 6.0f, 7.0f };
    auto    t = 0.85f;

    auto expected = a;
    auto actual   = Vector4::lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector2f, Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformVector2)
{
    auto v = Vector2 { 1.0f, 2.0f };
    auto m = Matrix::create_rotation_x(Math::to_radians(30.0f))
           * Matrix::create_rotation_y(Math::to_radians(30.0f))
           * Matrix::create_rotation_z(Math::to_radians(30.0f));

    m.m41 = 10.0f;
    m.m42 = 20.0f;
    m.m43 = 30.0f;

    auto expected = Vector4 { 10.316987f, 22.183012f, 30.3660259f, 1.0f };
    auto actual   = Vector4::transform(v, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector3f, Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformVector3)
{
    auto v = Vector3 { 1.0f, 2.0f, 3.0f };
    auto m = Matrix::create_rotation_x(Math::to_radians(30.0f))
           * Matrix::create_rotation_y(Math::to_radians(30.0f))
           * Matrix::create_rotation_z(Math::to_radians(30.0f));

    m.m41 = 10.0f;
    m.m42 = 20.0f;
    m.m43 = 30.0f;

    auto expected = Vector4(12.19198728f, 21.53349376f, 32.61602545f, 1.0f);
    auto actual   = Vector4::transform(v, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector4f, Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Transform)
{
    auto v = Vector4 { 1.0f, 2.0f, 3.0f, 0.0f };
    auto m = Matrix::create_rotation_x(Math::to_radians(30.0f))
           * Matrix::create_rotation_y(Math::to_radians(30.0f))
           * Matrix::create_rotation_z(Math::to_radians(30.0f));

    m.m41 = 10.0f;
    m.m42 = 20.0f;
    m.m43 = 30.0f;

    auto expected = Vector4(2.19198728f, 1.53349376f, 2.61602545f, 0.0f);
    auto actual   = Vector4::transform(v, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    //
    v.w = 1.0f;

    expected = Vector4 { 12.19198728f, 21.53349376f, 32.61602545f, 1.0f };
    actual   = Vector4::transform(v, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector4f, Matrix4x4)
// Transform vector4 with zero matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformWithZeroMatrix)
{
    auto v        = Vector4 { 1.0f, 2.0f, 3.0f, 0.0f };
    auto m        = Matrix { };
    auto expected = Vector4 { 0, 0, 0, 0 };
    auto actual   = Vector4::transform(v, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector4f, Matrix4x4)
// Transform vector4 with identity matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformWithIdentityMatrix)
{
    auto v        = Vector4 { 1.0f, 2.0f, 3.0f, 0.0f };
    auto m        = Matrix::Identity;
    auto expected = Vector4 { 1.0f, 2.0f, 3.0f, 0.0f };
    auto actual   = Vector4::transform(v, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector3f, Matrix4x4)
// Transform Vector3f test
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformVector32)
{
    auto v = Vector3 { 1.0f, 2.0f, 3.0f };
    auto m = Matrix::create_rotation_x(Math::to_radians(30.0f))
           * Matrix::create_rotation_y(Math::to_radians(30.0f))
           * Matrix::create_rotation_z(Math::to_radians(30.0f));

    m.m41 = 10.0f;
    m.m42 = 20.0f;
    m.m43 = 30.0f;

    auto expected = Vector4::transform({ v, 1.0f }, m);
    auto actual   = Vector4::transform(v, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector3f, Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformVector3WithZeroMatrix)
{
    auto v        = Vector3 { 1.0f, 2.0f, 3.0f };
    auto m        = Matrix { };
    auto expected = Vector4 { 0, 0, 0, 0 };
    auto actual   = Vector4::transform(v, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector3f, Matrix4x4)
// Transform vector3 with identity matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformVector3WithIdentityMatrix)
{
    auto v        = Vector3 { 1.0f, 2.0f, 3.0f };
    auto m        = Matrix::Identity;
    auto expected = Vector4 { 1.0f, 2.0f, 3.0f, 1.0f };
    auto actual   = Vector4::transform(v, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector2f, Matrix4x4)
// Transform Vector2f test
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformVector22)
{
    auto v = Vector2 { 1.0f, 2.0f };
    auto m = Matrix::create_rotation_x(Math::to_radians(30.0f))
           * Matrix::create_rotation_y(Math::to_radians(30.0f))
           * Matrix::create_rotation_z(Math::to_radians(30.0f));

    m.m41 = 10.0f;
    m.m42 = 20.0f;
    m.m43 = 30.0f;

    auto expected = Vector4::transform({ v, 0.0f, 1.0f }, m);
    auto actual   = Vector4::transform(v, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector2f, Matrix4x4)
// Transform Vector2f with zero matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformVector2WithZeroMatrix)
{
    auto v        = Vector2 { 1.0f, 2.0f };
    auto m        = Matrix { };
    auto expected = Vector4(0, 0, 0, 0);
    auto actual   = Vector4::transform(v, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector2f, Matrix4x4)
// Transform vector2 with identity matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformVector2WithIdentityMatrix)
{
    auto v        = Vector2 { 1.0f, 2.0f };
    auto m        = Matrix::Identity;
    auto expected = Vector4 { 1.0f, 2.0f, 0, 1.0f };
    auto actual   = Vector4::transform(v, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector2f, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformVector2Quaternion)
{
    auto v = Vector2 { 1.0f, 2.0f };
    auto m = Matrix::create_rotation_x(Math::to_radians(30.0f))
           * Matrix::create_rotation_y(Math::to_radians(30.0f))
           * Matrix::create_rotation_z(Math::to_radians(30.0f));

    auto q        = Quaternion::create_from_rotation_matrix(m);
    auto expected = Vector4::transform(v, m);
    auto actual   = Vector4::transform(v, q);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector3f, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformVector3Quaternion)
{
    auto v = Vector3 { 1.0f, 2.0f, 3.0f };
    auto m = Matrix::create_rotation_x(Math::to_radians(30.0f))
           * Matrix::create_rotation_y(Math::to_radians(30.0f))
           * Matrix::create_rotation_z(Math::to_radians(30.0f));

    auto q        = Quaternion::create_from_rotation_matrix(m);
    auto expected = Vector4::transform(v, m);
    auto actual   = Vector4::transform(v, q);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector4f, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformQuaternion)
{
    auto v = Vector4 { 1.0f, 2.0f, 3.0f, 0.0f };
    auto m = Matrix::create_rotation_x(Math::to_radians(30.0f))
           * Matrix::create_rotation_y(Math::to_radians(30.0f))
           * Matrix::create_rotation_z(Math::to_radians(30.0f));

    auto q        = Quaternion::create_from_rotation_matrix(m);
    auto expected = Vector4::transform(v, m);
    auto actual   = Vector4::transform(v, q);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    //
    v.w        = 1.0f;
    expected.w = 1.0f;

    actual = Vector4::transform(v, q);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector4f, Quaternion)
// Transform vector4 with zero quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformWithZeroQuaternion)
{
    auto v        = Vector4 { 1.0f, 2.0f, 3.0f, 0.0f };
    auto q        = Quaternion { };
    auto expected = v;
    auto actual   = Vector4::transform(v, q);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector4f, Quaternion)
// Transform vector4 with identity quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformWithIdentityQuaternion)
{
    auto v        = Vector4 { 1.0f, 2.0f, 3.0f, 0.0f };
    auto q        = Quaternion::Identity;
    auto expected = Vector4 { 1.0f, 2.0f, 3.0f, 0.0f };
    auto actual   = Vector4::transform(v, q);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector3f, Quaternion)
// Transform vector3 with zero quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformVector3WithZeroQuaternion)
{
    auto v        = Vector3 { 1.0f, 2.0f, 3.0f };
    auto q        = Quaternion { };
    auto expected = Vector4 { v, 1.0f };
    auto actual   = Vector4::transform(v, q);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector3f, Quaternion)
// Transform vector3 with identity quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformVector3WithIdentityQuaternion)
{
    auto v        = Vector3 { 1.0f, 2.0f, 3.0f };
    auto q        = Quaternion::Identity;
    auto expected = Vector4 { 1.0f, 2.0f, 3.0f, 1.0f };
    auto actual   = Vector4::transform(v, q);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector2f, Quaternion)
// Transform Vector2f with zero quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformVector2WithZeroQuaternion)
{
    auto v        = Vector2 { 1.0f, 2.0f };
    auto q        = Quaternion { };
    auto expected = Vector4 { 1.0f, 2.0f, 0, 1.0f };
    auto actual   = Vector4::transform(v, q);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector2f, Matrix4x4)
// Transform vector2 with identity Quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformVector2WithIdentityQuaternion)
{
    auto v        = Vector2 { 1.0f, 2.0f };
    auto q        = Quaternion::Identity;
    auto expected = Vector4 { 1.0f, 2.0f, 0, 1.0f };
    auto actual   = Vector4::transform(v, q);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Normalize (Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Normalize)
{
    auto a        = Vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto expected = Vector4 { 0.1825741858350553711523232609336f
                            , 0.3651483716701107423046465218672f
                            , 0.5477225575051661134569697828008f
                            , 0.7302967433402214846092930437344f };

    auto actual = Vector4::normalize(a);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Normalize (Vector4f)
// Normalize vector of length one
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, NormalizeVectorOfLengthZero)
{
    auto a        = Vector4 { 1.0f, 0.0f, 0.0f, 0.0f };
    auto expected = Vector4 { 1.0f, 0.0f, 0.0f, 0.0f };
    auto actual   = Vector4::normalize(a);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Normalize (Vector4f)
// Normalize vector of length zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, NormalizeVectorOfLengthZero2)
{
    auto a      = Vector4 { 0.0f, 0.0f, 0.0f, 0.0f };
    auto actual = Vector4::normalize(a);

    EXPECT_TRUE(Math::is_nan(actual.x)
             && Math::is_nan(actual.y)
             && Math::is_nan(actual.z)
             && Math::is_nan(actual.w));
}

// A test for operator - (Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, UnaryNegation)
{
    auto a        = Vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto expected = Vector4 { -1.0f, -2.0f, -3.0f, -4.0f };
    auto actual   = -a;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator - (Vector4f, Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Subtraction)
{
    auto a        = Vector4 { 1.0f, 6.0f, 3.0f, 4.0f };
    auto b        = Vector4 { 5.0f, 2.0f, 3.0f, 9.0f };
    auto expected = Vector4 { -4.0f, 4.0f, 0.0f, -5.0f };
    auto actual   = a - b;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator * (Vector4f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, MultiplyVectorByScalar)
{
    auto a      = Vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto factor = 2.0f;

    auto expected = Vector4 { 2.0f, 4.0f, 6.0f, 8.0f };
    auto actual   = a * factor;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator * (float, Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, MultiplyScalarByVector)
{
    auto a      = Vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto factor = 2.0f;

    auto expected = Vector4 { 2.0f, 4.0f, 6.0f, 8.0f };
    auto actual   = factor * a;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator * (Vector4f, Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Multiply)
{
    auto a        = Vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b        = Vector4 { 5.0f, 6.0f, 7.0f, 8.0f };
    auto expected = Vector4 { 5.0f, 12.0f, 21.0f, 32.0f };
    auto actual   = a * b;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator / (Vector4f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Division)
{
    auto a   = Vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto div = 2.0f;

    auto expected = Vector4 { 0.5f, 1.0f, 1.5f, 2.0f };
    auto actual   = a / div;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator / (Vector4f, Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Division1)
{
    auto a = Vector4 { 1.0f, 6.0f, 7.0f, 4.0f };
    auto b = Vector4 { 5.0f, 2.0f, 3.0f, 8.0f };

    auto expected = Vector4 { 1.0f / 5.0f, 6.0f / 2.0f, 7.0f / 3.0f, 4.0f / 8.0f };
    auto actual   = a / b;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator / (Vector4f, Vector4f)
// Divide by zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, ScalarDivisionByZero)
{
    auto a   = Vector4 { -2.0f, 3.0f, Math::max_value, Math::nan};
    auto div = 0.0f;

    auto actual = a / div;

    EXPECT_TRUE(Math::is_negative_infinity(actual.x));
    EXPECT_TRUE(Math::is_positive_infinity(actual.y));
    EXPECT_TRUE(Math::is_positive_infinity(actual.z));
    EXPECT_TRUE(Math::is_nan(actual.w));
}

// A test for operator / (Vector4f, Vector4f)
// Divide by zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, DivisionByZero)
{
    auto a = Vector4 { 0.047f, -3.0f, Math::negative_infinity, Math::min_value};
    auto b = Vector4 { };

    Vector4 actual = a / b;

    EXPECT_TRUE(Math::is_positive_infinity(actual.x));
    EXPECT_TRUE(Math::is_negative_infinity(actual.y));
    EXPECT_TRUE(Math::is_negative_infinity(actual.z));
    EXPECT_TRUE(Math::is_negative_infinity(actual.w));
}

// A test for operator + (Vector4f, Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Addition)
{
    auto a = Vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = Vector4 { 5.0f, 6.0f, 7.0f, 8.0f };

    auto expected = Vector4 { 6.0f, 8.0f, 10.0f, 12.0f };
    auto actual   = a + b;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Add)
{
    auto v1 = Vector4 { 2.5f, 2.0f, 3.0f, 3.3f };
    auto v2 = Vector4 { 5.5f, 4.5f, 6.5f, 7.5f };

    auto v3 = v1 + v2;
    auto v5 = Vector4 { -1.0f, 0.0f, 0.0f, Math::nan};
    auto v4 = v1 + v5;

    EXPECT_TRUE( 8.0f == v3.x);
    EXPECT_TRUE( 6.5f == v3.y);
    EXPECT_TRUE( 9.5f == v3.z);
    EXPECT_TRUE(10.8f == v3.w);
    EXPECT_TRUE( 1.5f == v4.x);
    EXPECT_TRUE( 2.0f == v4.y);
    EXPECT_TRUE( 3.0f == v4.z);
    EXPECT_TRUE(Math::is_nan(v4.w));
}

// A test for Vector4f (float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Constructor)
{
    auto x = 1.0f;
    auto y = 2.0f;
    auto z = 3.0f;
    auto w = 4.0f;

    auto target = Vector4 { x, y, z, w };

    EXPECT_TRUE(EqualityHelper::Equal(target.x, x)
             && EqualityHelper::Equal(target.y, y)
             && EqualityHelper::Equal(target.z, z)
             && EqualityHelper::Equal(target.w, w));
}

// A test for Vector4f (Vector2f, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, ConstructorWithVector2)
{
    auto a = Vector2 { 1.0f, 2.0f };
    auto z = 3.0f;
    auto w = 4.0f;

    auto target = Vector4 { a, z, w };

    EXPECT_TRUE(EqualityHelper::Equal(target.x, a.x)
             && EqualityHelper::Equal(target.y, a.y)
             && EqualityHelper::Equal(target.z, z)
             && EqualityHelper::Equal(target.w, w));
}

// A test for Vector4f (Vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, ConstructorWithVector3)
{
    auto a = Vector3 { 1.0f, 2.0f, 3.0f };
    auto w = 4.0f;

    auto target = Vector4 { a, w };

    EXPECT_TRUE(EqualityHelper::Equal(target.x, a.x)
             && EqualityHelper::Equal(target.y, a.y)
             && EqualityHelper::Equal(target.z, a.z)
             && EqualityHelper::Equal(target.w, w));
}

// A test for Vector4f ()
// Constructor with no parameter
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, DefaultConstructor)
{
    Vector4 a;

    EXPECT_TRUE(a.x == 0.0f);
    EXPECT_TRUE(a.y == 0.0f);
    EXPECT_TRUE(a.z == 0.0f);
    EXPECT_TRUE(a.w == 0.0f);
}

// A test for Vector4f ()
// Constructor with special floating values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, ConstructorWithSpecialFloatingValues)
{
    auto target = Vector4 { Math::nan, Math::max_value, Math::positive_infinity, Math::epsilon};

    EXPECT_TRUE(Math::is_nan(target.x));
    EXPECT_TRUE(EqualityHelper::Equal(Math::max_value, target.y));
    EXPECT_TRUE(Math::is_positive_infinity(target.z));
    EXPECT_TRUE(EqualityHelper::Equal(Math::epsilon, target.w));
}

// A test for negate (Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Negate)
{
    auto a        = Vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto expected = Vector4 { -1.0f, -2.0f, -3.0f, -4.0f };
    auto actual   = Vector4::negate(a);

    EXPECT_TRUE(expected == actual);
}

// A test for operator != (Vector4f, Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Inequality)
{
    auto a = Vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = Vector4 { 1.0f, 2.0f, 3.0f, 4.0f };

    // case 1: compare between same values
    bool expected = false;
    bool actual   = a != b;

    EXPECT_TRUE(expected == actual);

    // case 2: compare between different values
    b.x = 10.0f;

    expected = true;
    actual   = a != b;

    EXPECT_TRUE(expected == actual);
}

// A test for operator == (Vector4f, Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Equality)
{
    auto a = Vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = Vector4 { 1.0f, 2.0f, 3.0f, 4.0f };

    // case 1: compare between same values
    bool expected = true;
    bool actual   = a == b;

    EXPECT_TRUE(expected == actual);

    // case 2: compare between different values
    b.x = 10.0f;

    expected = false;
    actual   = a == b;

    EXPECT_TRUE(expected == actual);
}

// A test for UnitW
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, UnitW)
{
    Vector4 val { 0.0f, 0.0f, 0.0f, 1.0f };

    EXPECT_TRUE(val == Vector4::unit_w);
}

// A test for UnitX
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, UnitX)
{
    Vector4 val { 1.0f, 0.0f, 0.0f, 0.0f };

    EXPECT_TRUE(val == Vector4::unit_x);
}

// A test for UnitY
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, UnitY)
{
    Vector4 val { 0.0f, 1.0f, 0.0f, 0.0f };

    EXPECT_TRUE(val == Vector4::unit_y);
}

// A test for UnitZ
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, UnitZ)
{
    Vector4 val { 0.0f, 0.0f, 1.0f, 0.0f };

    EXPECT_TRUE(val == Vector4::unit_z);
}

// A test for One
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, One)
{
    Vector4 val { 1.0f, 1.0f, 1.0f, 1.0f };

    EXPECT_TRUE(val == Vector4::one);
}

// A test for Zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Zero)
{
    Vector4 val { 0.0f, 0.0f, 0.0f, 0.0f };

    EXPECT_TRUE(val == Vector4::zero);
}

// A test for Vector4f (float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, ConstructorWithScalarValue)
{
    auto    value = 1.0f;
    Vector4 target { value };

    Vector4 expected { value, value, value, value };

    EXPECT_TRUE(expected == target);

    value    = 2.0f;
    target   = Vector4 { value };
    expected = Vector4 { value, value, value, value };

    EXPECT_TRUE(expected == target);
}

// A test for Vector4f comparison involving NaN values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, EqualsNaN)
{
    Vector4 a { Math::nan, 0, 0, 0 };
    Vector4 b { 0, Math::nan, 0, 0 };
    Vector4 c { 0, 0, Math::nan, 0 };
    Vector4 d { 0, 0, 0, Math::nan};

    EXPECT_FALSE(a == Vector4::zero);
    EXPECT_FALSE(b == Vector4::zero);
    EXPECT_FALSE(c == Vector4::zero);
    EXPECT_FALSE(d == Vector4::zero);

    EXPECT_TRUE(a != Vector4::zero);
    EXPECT_TRUE(b != Vector4::zero);
    EXPECT_TRUE(c != Vector4::zero);
    EXPECT_TRUE(d != Vector4::zero);
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Abs)
{
    Vector4 v1 { -2.5f, 2.0f, 3.0f, 3.3f };
    Vector4 v3 = Vector4::abs(Vector4 { Math::positive_infinity, 0.0f, Math::negative_infinity, Math::nan});
    Vector4 v  = Vector4::abs(v1);

    EXPECT_TRUE(2.5f == v.x);
    EXPECT_TRUE(2.0f == v.y);
    EXPECT_TRUE(3.0f == v.z);
    EXPECT_TRUE(3.3f == v.w);
    EXPECT_TRUE(Math::positive_infinity == v3.x);
    EXPECT_TRUE(0.0f == v3.y);
    EXPECT_TRUE(Math::positive_infinity == v3.z);
    EXPECT_TRUE(Math::is_nan(v3.w));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, SquareRoot)
{
    Vector4 v1 { -2.5f, 2.0f, 3.0f, 3.3f };
    Vector4 v2 { 5.5f, 4.5f, 6.5f, 7.5f };

    EXPECT_TRUE(2 == (std::int32_t)Vector4::square_root(v2).x);
    EXPECT_TRUE(2 == (std::int32_t)Vector4::square_root(v2).y);
    EXPECT_TRUE(2 == (std::int32_t)Vector4::square_root(v2).z);
    EXPECT_TRUE(2 == (std::int32_t)Vector4::square_root(v2).w);
    EXPECT_TRUE(Math::is_nan(Vector4::square_root(v1).x));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, SetFields)
{
    Vector4 v3 { 4.0f, 5.0f, 6.0f, 7 };

    v3.x = 1.0f;
    v3.y = 2.0f;
    v3.z = 3.0f;
    v3.w = 4.0f;

    EXPECT_TRUE(1.0f == v3.x);
    EXPECT_TRUE(2.0f == v3.y);
    EXPECT_TRUE(3.0f == v3.z);
    EXPECT_TRUE(4.0f == v3.w);

    auto v4 = v3;

    v4.y = 0.5f;
    v4.z = 2.2f;
    v4.w = 3.5f;

    EXPECT_TRUE(1.0f == v4.x);
    EXPECT_TRUE(0.5f == v4.y);
    EXPECT_TRUE(2.2f == v4.z);
    EXPECT_TRUE(3.5f == v4.w);
    EXPECT_TRUE(2.0f == v3.y);
}
