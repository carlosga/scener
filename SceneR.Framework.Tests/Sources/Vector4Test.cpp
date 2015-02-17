// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Vector4Test.hpp>

#include <EqualityHelper.hpp>

#include <System/Math.hpp>
#include <Framework/MathHelper.hpp>
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
    EXPECT_TRUE(result.X() == 250.0f);
    EXPECT_TRUE(result.Y() == 270.0f);
    EXPECT_TRUE(result.Z() == 290.0f);
    EXPECT_TRUE(result.W() == 4.0f);
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

    Single expected = 64.0f;
    Single actual   = Vector4::DistanceSquared(a, b);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Distance (Vector4f, Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Distance)
{
    auto a = Vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = Vector4 { 5.0f, 6.0f, 7.0f, 8.0f };

    Single expected = 8.0f;
    Single actual   = Vector4::Distance(a, b);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Distance (Vector4f, Vector4f)
// Distance from the same point
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, DistanceFromTheSamePoint)
{
    auto a = Vector4({ 1.051f, 2.05f }, 3.478f, 1.0f);  // With Vector2
    auto b = Vector4({ 1.051f, 2.05f, 3.478f }, 0.0f); // With Vector3

    b.W(1.0f);

    Single actual = Vector4::Distance(a, b);

    EXPECT_TRUE(0.0f == actual);
}

// A test for Dot (Vector4f, Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Dot)
{
    auto a = Vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = Vector4 { 5.0f, 6.0f, 7.0f, 8.0f };

    Single expected = 70.0f;
    Single actual = Vector4::Dot(a, b);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Dot (Vector4f, Vector4f)
// Dot test for perpendicular vector
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, DotForPerpendicularVector)
{
    auto a = Vector3 { 1.55f, 1.55f, 1 };
    auto b = Vector3 { 2.5f, 3, 1.5f };
    auto c = Vector3::Cross(a, b);

    auto d = Vector4 { a, 0 };
    auto e = Vector4 { c, 0 };

    Single actual = Vector4::Dot(d, e);

    EXPECT_TRUE(EqualityHelper::Equal(0.0f, actual));
}

// A test for Length ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Length)
{
    auto   a      = Vector3 { 1.0f, 2.0f, 3.0f };
    Single w      = 4.0f;
    auto   target = Vector4 { a, w };

    Single expected = Math::Sqrt(30.0f);
    Single actual   = target.Length();

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Length ()
// Length test where length is zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, LengthWhereLengthIsZero)
{
    Vector4 target;
    Single  expected = 0.0f;
    Single  actual   = target.Length();

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for LengthSquared ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, LengthSquared)
{
    auto   a = Vector3 { 1.0f, 2.0f, 3.0f };
    Single w = 4.0f;

    auto target = Vector4 { a, w };

    Single expected = 30;
    Single actual   = target.LengthSquared();

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Min (Vector4f, Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Min)
{
    auto a = Vector4 { -1.0f, 4.0f, -3.0f, 1000.0f };
    auto b = Vector4 { 2.0f, 1.0f, -1.0f, 0.0f };

    auto expected = Vector4 { -1.0f, 1.0f, -3.0f, 0.0f };
    auto actual   = Vector4::Min(a, b);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Max (Vector4f, Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Max)
{
    auto a = Vector4 { -1.0f, 4.0f, -3.0f, 1000.0f };
    auto b = Vector4 { 2.0f, 1.0f, -1.0f, 0.0f };

    auto expected = Vector4(2.0f, 4.0f, -1.0f, 1000.0f);
    auto actual   = Vector4::Max(a, b);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, MinMaxCodeCoverage)
{
    auto    min = Vector4::Zero;
    auto    max = Vector4::One;
    Vector4 actual;

    // Min.
    actual = Vector4::Min(min, max);

    EXPECT_TRUE(actual == min);

    actual = Vector4::Min(max, min);

    EXPECT_TRUE(actual == min);

    // Max.
    actual = Vector4::Max(min, max);

    EXPECT_TRUE(actual == max);

    actual = Vector4::Max(max, min);

    EXPECT_TRUE(actual == max);
}

// A test for Clamp (Vector4f, Vector4f, Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Clamp)
{
    auto a   = Vector4 { 0.5f, 0.3f, 0.33f, 0.44f };
    auto min = Vector4 { 0.0f, 0.1f, 0.13f, 0.14f };
    auto max = Vector4 { 1.0f, 1.1f, 1.13f, 1.14f };

    // Normal case.
    // Case N1: specfied value is in the range.
    auto expected = Vector4 { 0.5f, 0.3f, 0.33f, 0.44f };
    auto actual   = Vector4::Clamp(a, min, max);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Normal case.
    // Case N2: specfied value is bigger than max value.
    a        = Vector4 { 2.0f, 3.0f, 4.0f, 5.0f };
    expected = max;
    actual   = Vector4::Clamp(a, min, max);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Case N3: specfied value is smaller than max value.
    a        = Vector4 { -2.0f, -3.0f, -4.0f, -5.0f };
    expected = min;
    actual   = Vector4::Clamp(a, min, max);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Case N4: combination case.
    a        = Vector4 { -2.0f, 0.5f, 4.0f, -5.0f };
    expected = Vector4 { min.X(), a.Y(), max.Z(), min.W() };
    actual   = Vector4::Clamp(a, min, max);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // User specfied min value is bigger than max value.
    max = Vector4 { 0.0f, 0.1f, 0.13f, 0.14f };
    min = Vector4 { 1.0f, 1.1f, 1.13f, 1.14f };

    // Case W1: specfied value is in the range.
    a        = Vector4 { 0.5f, 0.3f, 0.33f, 0.44f };
    expected = min;
    actual   = Vector4::Clamp(a, min, max);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Normal case.
    // Case W2: specfied value is bigger than max and min value.
    a        = Vector4 { 2.0f, 3.0f, 4.0f, 5.0f };
    expected = min;
    actual   = Vector4::Clamp(a, min, max);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Case W3: specfied value is smaller than min and max value.
    a        = Vector4 { -2.0f, -3.0f, -4.0f, -5.0f };
    expected = min;
    actual   = Vector4::Clamp(a, min, max);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Vector4f, Vector4f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Lerp)
{
    auto a = Vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = Vector4 { 5.0f, 6.0f, 7.0f, 8.0f };

    Single t = 0.5f;

    auto expected = Vector4 { 3.0f, 4.0f, 5.0f, 6.0f };
    auto actual   = Vector4::Lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Vector4f, Vector4f, float)
// Lerp test with factor zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, LerpWithFactorZero)
{
    auto a = Vector4 { { 1.0f, 2.0f, 3.0f }, 4.0f };
    auto b = Vector4 { 4.0f, 5.0f, 6.0f, 7.0f };

    Single t = 0.0f;

    auto expected = Vector4 { 1.0f, 2.0f, 3.0f, 4.0f };
    auto actual   = Vector4::Lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Vector4f, Vector4f, float)
// Lerp test with factor one
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, LerpWithFactorOne)
{
    auto a = Vector4 { { 1.0f, 2.0f, 3.0f }, 4.0f };
    auto b = Vector4 { 4.0f, 5.0f, 6.0f, 7.0f };

    Single t = 1.0f;

    auto expected = Vector4 { 4.0f, 5.0f, 6.0f, 7.0f };
    auto actual   = Vector4::Lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Vector4f, Vector4f, float)
// Lerp test with factor > 1
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, LerpWithFactorGreaterThanOne)
{
    auto a = Vector4 { { 0.0f, 0.0f, 0.0f }, 0.0f };
    auto b = Vector4 { 4.0f, 5.0f, 6.0f, 7.0f };

    Single t = 2.0f;

    auto expected = Vector4 { 8.0f, 10.0f, 12.0f, 14.0f };
    auto actual   = Vector4::Lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Vector4f, Vector4f, float)
// Lerp test with factor < 0
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, LerpWithFactorLessThanZero)
{
    auto a = Vector4 { { 0.0f, 0.0f, 0.0f }, 0.0f };
    auto b = Vector4 { 4.0f, 5.0f, 6.0f, 7.0f };

    Single t = -2.0f;

    auto expected = -(b * 2);
    auto actual   = Vector4::Lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Vector4f, Vector4f, float)
// Lerp test from the same point
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, LerpFromTheSamePoint)
{
    Vector4 a = Vector4 { 4.0f, 5.0f, 6.0f, 7.0f };
    Vector4 b = Vector4 { 4.0f, 5.0f, 6.0f, 7.0f };

    float t = 0.85f;

    auto expected = a;
    auto actual   = Vector4::Lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector2f, Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformVector2)
{
    auto v = Vector2 { 1.0f, 2.0f };
    auto m = Matrix::CreateRotationX(MathHelper::ToRadians(30.0f))
           * Matrix::CreateRotationY(MathHelper::ToRadians(30.0f))
           * Matrix::CreateRotationZ(MathHelper::ToRadians(30.0f));

    m.M41(10.0f);
    m.M42(20.0f);
    m.M43(30.0f);

    auto expected = Vector4 { 10.316987f, 22.183012f, 30.3660259f, 1.0f };
    auto actual   = Vector4::Transform(v, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector3f, Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformVector3)
{
    auto v = Vector3 { 1.0f, 2.0f, 3.0f };
    auto m = Matrix::CreateRotationX(MathHelper::ToRadians(30.0f))
           * Matrix::CreateRotationY(MathHelper::ToRadians(30.0f))
           * Matrix::CreateRotationZ(MathHelper::ToRadians(30.0f));

    m.M41(10.0f);
    m.M42(20.0f);
    m.M43(30.0f);

    auto expected = Vector4(12.19198728f, 21.53349376f, 32.61602545f, 1.0f);
    auto actual   = Vector4::Transform(v, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector4f, Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, Transform)
{
    auto v = Vector4 { 1.0f, 2.0f, 3.0f, 0.0f };
    auto m = Matrix::CreateRotationX(MathHelper::ToRadians(30.0f))
           * Matrix::CreateRotationY(MathHelper::ToRadians(30.0f))
           * Matrix::CreateRotationZ(MathHelper::ToRadians(30.0f));

    m.M41(10.0f);
    m.M42(20.0f);
    m.M43(30.0f);

    auto expected = Vector4(2.19198728f, 1.53349376f, 2.61602545f, 0.0f);
    auto actual   = Vector4::Transform(v, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    //
    v.W(1.0f);

    expected = Vector4 { 12.19198728f, 21.53349376f, 32.61602545f, 1.0f };
    actual   = Vector4::Transform(v, m);

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
    auto actual   = Vector4::Transform(v, m);

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
    auto actual   = Vector4::Transform(v, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector3f, Matrix4x4)
// Transform Vector3f test
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformVector32)
{
    auto v = Vector3 { 1.0f, 2.0f, 3.0f };
    auto m = Matrix::CreateRotationX(MathHelper::ToRadians(30.0f))
           * Matrix::CreateRotationY(MathHelper::ToRadians(30.0f))
           * Matrix::CreateRotationZ(MathHelper::ToRadians(30.0f));

    m.M41(10.0f);
    m.M42(20.0f);
    m.M43(30.0f);

    auto expected = Vector4::Transform({ v, 1.0f }, m);
    auto actual   = Vector4::Transform(v, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector3f, Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformVector3WithZeroMatrix)
{
    auto v        = Vector3 { 1.0f, 2.0f, 3.0f };
    auto m        = Matrix { };
    auto expected = Vector4 { 0, 0, 0, 0 };
    auto actual   = Vector4::Transform(v, m);

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
    auto actual   = Vector4::Transform(v, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector2f, Matrix4x4)
// Transform Vector2f test
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformVector22)
{
    auto v = Vector2 { 1.0f, 2.0f };
    auto m = Matrix::CreateRotationX(MathHelper::ToRadians(30.0f))
           * Matrix::CreateRotationY(MathHelper::ToRadians(30.0f))
           * Matrix::CreateRotationZ(MathHelper::ToRadians(30.0f));

    m.M41(10.0f);
    m.M42(20.0f);
    m.M43(30.0f);

    auto expected = Vector4::Transform({ v, 0.0f, 1.0f }, m);
    auto actual   = Vector4::Transform(v, m);

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
    auto actual   = Vector4::Transform(v, m);

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
    auto actual   = Vector4::Transform(v, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector2f, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformVector2Quaternion)
{
    auto v = Vector2 { 1.0f, 2.0f };
    auto m = Matrix::CreateRotationX(MathHelper::ToRadians(30.0f))
           * Matrix::CreateRotationY(MathHelper::ToRadians(30.0f))
           * Matrix::CreateRotationZ(MathHelper::ToRadians(30.0f));

    auto q        = Quaternion::CreateFromRotationMatrix(m);
    auto expected = Vector4::Transform(v, m);
    auto actual   = Vector4::Transform(v, q);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector3f, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector4Test, TransformVector3Quaternion)
{
    auto v = Vector3 { 1.0f, 2.0f, 3.0f };
    auto m = Matrix::CreateRotationX(MathHelper::ToRadians(30.0f))
           * Matrix::CreateRotationY(MathHelper::ToRadians(30.0f))
           * Matrix::CreateRotationZ(MathHelper::ToRadians(30.0f));

    auto q        = Quaternion::CreateFromRotationMatrix(m);
    auto expected = Vector4::Transform(v, m);
    auto actual   = Vector4::Transform(v, q);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

/*
// A test for Transform (Vector4f, Quaternion)
[Fact]
public void Vector4TransformVector4QuaternionTest()
{
    Vector4 v = Vector4(1.0f, 2.0f, 3.0f, 0.0f);

    Matrix4x4 m =
        Matrix4x4.CreateRotationX(MathHelper.ToRadians(30.0f)) *
        Matrix4x4.CreateRotationY(MathHelper.ToRadians(30.0f)) *
        Matrix4x4.CreateRotationZ(MathHelper.ToRadians(30.0f));
    Quaternion q = Quaternion.CreateFromRotationMatrix(m);

    Vector4 expected = Vector4.Transform(v, m);
    Vector4 actual;

    actual = Vector4.Transform(v, q);
    Assert.True(MathHelper.Equal(expected, actual), "Vector4f.Transform did not return the expected value.");

    //
    v.W = 1.0f;
    expected.W = 1.0f;
    actual = Vector4.Transform(v, q);
    Assert.True(MathHelper.Equal(expected, actual), "Vector4f.Transform did not return the expected value.");
}

// A test for Transform (Vector4f, Quaternion)
// Transform vector4 with zero quaternion
[Fact]
public void Vector4TransformVector4QuaternionTest1()
{
    Vector4 v = Vector4(1.0f, 2.0f, 3.0f, 0.0f);
    Quaternion q = new Quaternion();
    Vector4 expected = v;

    Vector4 actual = Vector4.Transform(v, q);
    Assert.True(MathHelper.Equal(expected, actual), "Vector4f.Transform did not return the expected value.");
}

// A test for Transform (Vector4f, Quaternion)
// Transform vector4 with identity matrix
[Fact]
public void Vector4TransformVector4QuaternionTest2()
{
    Vector4 v = Vector4(1.0f, 2.0f, 3.0f, 0.0f);
    Quaternion q = Quaternion.Identity;
    Vector4 expected = Vector4(1.0f, 2.0f, 3.0f, 0.0f);

    Vector4 actual = Vector4.Transform(v, q);
    Assert.True(MathHelper.Equal(expected, actual), "Vector4f.Transform did not return the expected value.");
}

// A test for Transform (Vector3f, Quaternion)
// Transform Vector3f test
[Fact]
public void Vector4TransformVector3QuaternionTest()
{
    Vector3 v = new Vector3(1.0f, 2.0f, 3.0f);

    Matrix4x4 m =
        Matrix4x4.CreateRotationX(MathHelper.ToRadians(30.0f)) *
        Matrix4x4.CreateRotationY(MathHelper.ToRadians(30.0f)) *
        Matrix4x4.CreateRotationZ(MathHelper.ToRadians(30.0f));
    Quaternion q = Quaternion.CreateFromRotationMatrix(m);

    Vector4 expected = Vector4.Transform(v, m);
    Vector4 actual = Vector4.Transform(v, q);
    Assert.True(MathHelper.Equal(expected, actual), "Vector4f.Transform did not return the expected value.");
}

// A test for Transform (Vector3f, Quaternion)
// Transform vector3 with zero quaternion
[Fact]
public void Vector4TransformVector3QuaternionTest1()
{
    Vector3 v = new Vector3(1.0f, 2.0f, 3.0f);
    Quaternion q = new Quaternion();
    Vector4 expected = Vector4(v, 1.0f);

    Vector4 actual = Vector4.Transform(v, q);
    Assert.True(MathHelper.Equal(expected, actual), "Vector4f.Transform did not return the expected value.");
}

// A test for Transform (Vector3f, Quaternion)
// Transform vector3 with identity quaternion
[Fact]
public void Vector4TransformVector3QuaternionTest2()
{
    Vector3 v = new Vector3(1.0f, 2.0f, 3.0f);
    Quaternion q = Quaternion.Identity;
    Vector4 expected = Vector4(1.0f, 2.0f, 3.0f, 1.0f);

    Vector4 actual = Vector4.Transform(v, q);
    Assert.True(MathHelper.Equal(expected, actual), "Vector4f.Transform did not return the expected value.");
}

// A test for Transform (Vector2f, Quaternion)
// Transform Vector2f by quaternion test
[Fact]
public void Vector4TransformVector2QuaternionTest()
{
    Vector2 v = new Vector2(1.0f, 2.0f);

    Matrix4x4 m =
        Matrix4x4.CreateRotationX(MathHelper.ToRadians(30.0f)) *
        Matrix4x4.CreateRotationY(MathHelper.ToRadians(30.0f)) *
        Matrix4x4.CreateRotationZ(MathHelper.ToRadians(30.0f));
    Quaternion q = Quaternion.CreateFromRotationMatrix(m);

    Vector4 expected = Vector4.Transform(v, m);
    Vector4 actual = Vector4.Transform(v, q);
    Assert.True(MathHelper.Equal(expected, actual), "Vector4f.Transform did not return the expected value.");
}

// A test for Transform (Vector2f, Quaternion)
// Transform Vector2f with zero quaternion
[Fact]
public void Vector4TransformVector2QuaternionTest1()
{
    Vector2 v = new Vector2(1.0f, 2.0f);
    Quaternion q = new Quaternion();
    Vector4 expected = Vector4(1.0f, 2.0f, 0, 1.0f);

    Vector4 actual = Vector4.Transform(v, q);
    Assert.True(MathHelper.Equal(expected, actual), "Vector4f.Transform did not return the expected value.");
}

// A test for Transform (Vector2f, Matrix4x4)
// Transform vector2 with identity Quaternion
[Fact]
public void Vector4TransformVector2QuaternionTest2()
{
    Vector2 v = new Vector2(1.0f, 2.0f);
    Quaternion q = Quaternion.Identity;
    Vector4 expected = Vector4(1.0f, 2.0f, 0, 1.0f);

    Vector4 actual = Vector4.Transform(v, q);
    Assert.True(MathHelper.Equal(expected, actual), "Vector4f.Transform did not return the expected value.");
}

// A test for Normalize (Vector4f)
[Fact]
public void Vector4NormalizeTest()
{
    Vector4 a = Vector4(1.0f, 2.0f, 3.0f, 4.0f);

    Vector4 expected = Vector4(
        0.1825741858350553711523232609336f,
        0.3651483716701107423046465218672f,
        0.5477225575051661134569697828008f,
        0.7302967433402214846092930437344f);
    Vector4 actual;

    actual = Vector4.Normalize(a);
    Assert.True(MathHelper.Equal(expected, actual), "Vector4f.Normalize did not return the expected value.");
}

// A test for Normalize (Vector4f)
// Normalize vector of length one
[Fact]
public void Vector4NormalizeTest1()
{
    Vector4 a = Vector4(1.0f, 0.0f, 0.0f, 0.0f);

    Vector4 expected = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
    Vector4 actual = Vector4.Normalize(a);
    Assert.True(MathHelper.Equal(expected, actual), "Vector4f.Normalize did not return the expected value.");
}

// A test for Normalize (Vector4f)
// Normalize vector of length zero
[Fact]
public void Vector4NormalizeTest2()
{
    Vector4 a = Vector4(0.0f, 0.0f, 0.0f, 0.0f);

    Vector4 expected = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
    Vector4 actual = Vector4.Normalize(a);
    Assert.True(float.IsNaN(actual.X) && float.IsNaN(actual.Y) && float.IsNaN(actual.Z) && float.IsNaN(actual.W), "Vector4f.Normalize did not return the expected value.");
}

// A test for operator - (Vector4f)
[Fact]
public void Vector4UnaryNegationTest()
{
    Vector4 a = Vector4(1.0f, 2.0f, 3.0f, 4.0f);

    Vector4 expected = Vector4(-1.0f, -2.0f, -3.0f, -4.0f);
    Vector4 actual;

    actual = -a;

    Assert.True(MathHelper.Equal(expected, actual), "Vector4f.operator - did not return the expected value.");
}

// A test for operator - (Vector4f, Vector4f)
[Fact]
public void Vector4SubtractionTest()
{
    Vector4 a = Vector4(1.0f, 6.0f, 3.0f, 4.0f);
    Vector4 b = Vector4(5.0f, 2.0f, 3.0f, 9.0f);

    Vector4 expected = Vector4(-4.0f, 4.0f, 0.0f, -5.0f);
    Vector4 actual;

    actual = a - b;

    Assert.True(MathHelper.Equal(expected, actual), "Vector4f.operator - did not return the expected value.");
}

// A test for operator * (Vector4f, float)
[Fact]
public void Vector4MultiplyTest()
{
    Vector4 a = Vector4(1.0f, 2.0f, 3.0f, 4.0f);

    float factor = 2.0f;

    Vector4 expected = Vector4(2.0f, 4.0f, 6.0f, 8.0f);
    Vector4 actual;

    actual = a * factor;
    Assert.True(MathHelper.Equal(expected, actual), "Vector4f.operator * did not return the expected value.");
}

// A test for operator * (float, Vector4f)
[Fact]
public void Vector4MultiplyTest4()
{
    Vector4 a = Vector4(1.0f, 2.0f, 3.0f, 4.0f);

    float factor = 2.0f;
    Vector4 expected = Vector4(2.0f, 4.0f, 6.0f, 8.0f);
    Vector4 actual;

    actual = factor * a;
    Assert.True(MathHelper.Equal(expected, actual), "Vector4f.operator * did not return the expected value.");
}

// A test for operator * (Vector4f, Vector4f)
[Fact]
public void Vector4MultiplyTest1()
{
    Vector4 a = Vector4(1.0f, 2.0f, 3.0f, 4.0f);
    Vector4 b = Vector4(5.0f, 6.0f, 7.0f, 8.0f);

    Vector4 expected = Vector4(5.0f, 12.0f, 21.0f, 32.0f);
    Vector4 actual;

    actual = a * b;

    Assert.True(MathHelper.Equal(expected, actual), "Vector4f.operator * did not return the expected value.");
}

// A test for operator / (Vector4f, float)
[Fact]
public void Vector4DivisionTest()
{
    Vector4 a = Vector4(1.0f, 2.0f, 3.0f, 4.0f);

    float div = 2.0f;

    Vector4 expected = Vector4(0.5f, 1.0f, 1.5f, 2.0f);
    Vector4 actual;

    actual = a / div;

    Assert.True(MathHelper.Equal(expected, actual), "Vector4f.operator / did not return the expected value.");
}

// A test for operator / (Vector4f, Vector4f)
[Fact]
public void Vector4DivisionTest1()
{
    Vector4 a = Vector4(1.0f, 6.0f, 7.0f, 4.0f);
    Vector4 b = Vector4(5.0f, 2.0f, 3.0f, 8.0f);

    Vector4 expected = Vector4(1.0f / 5.0f, 6.0f / 2.0f, 7.0f / 3.0f, 4.0f / 8.0f);
    Vector4 actual;

    actual = a / b;

    Assert.True(MathHelper.Equal(expected, actual), "Vector4f.operator / did not return the expected value.");
}

// A test for operator / (Vector4f, Vector4f)
// Divide by zero
[Fact]
public void Vector4DivisionTest2()
{
    Vector4 a = Vector4(-2.0f, 3.0f, float.MaxValue, float.NaN);

    float div = 0.0f;

    Vector4 actual = a / div;

    Assert.True(float.IsNegativeInfinity(actual.X), "Vector4f.operator / did not return the expected value.");
    Assert.True(float.IsPositiveInfinity(actual.Y), "Vector4f.operator / did not return the expected value.");
    Assert.True(float.IsPositiveInfinity(actual.Z), "Vector4f.operator / did not return the expected value.");
    Assert.True(float.IsNaN(actual.W), "Vector4f.operator / did not return the expected value.");
}

// A test for operator / (Vector4f, Vector4f)
// Divide by zero
[Fact]
public void Vector4DivisionTest3()
{
    Vector4 a = Vector4(0.047f, -3.0f, float.NegativeInfinity, float.MinValue);
    Vector4 b = Vector4();

    Vector4 actual = a / b;

    Assert.True(float.IsPositiveInfinity(actual.X), "Vector4f.operator / did not return the expected value.");
    Assert.True(float.IsNegativeInfinity(actual.Y), "Vector4f.operator / did not return the expected value.");
    Assert.True(float.IsNegativeInfinity(actual.Z), "Vector4f.operator / did not return the expected value.");
    Assert.True(float.IsNegativeInfinity(actual.W), "Vector4f.operator / did not return the expected value.");
}

// A test for operator + (Vector4f, Vector4f)
[Fact]
public void Vector4AdditionTest()
{
    Vector4 a = Vector4(1.0f, 2.0f, 3.0f, 4.0f);
    Vector4 b = Vector4(5.0f, 6.0f, 7.0f, 8.0f);

    Vector4 expected = Vector4(6.0f, 8.0f, 10.0f, 12.0f);
    Vector4 actual;

    actual = a + b;

    Assert.True(MathHelper.Equal(expected, actual), "Vector4f.operator + did not return the expected value.");
}

[Fact]
public void OperatorAddTest()
{
    Vector4 v1 = Vector4(2.5f, 2.0f, 3.0f, 3.3f);
    Vector4 v2 = Vector4(5.5f, 4.5f, 6.5f, 7.5f);

    Vector4 v3 = v1 + v2;
    Vector4 v5 = Vector4(-1.0f, 0.0f, 0.0f, Single.NaN);
    Vector4 v4 = v1 + v5;
    Assert.Equal(8.0f, v3.X);
    Assert.Equal(6.5f, v3.Y);
    Assert.Equal(9.5f, v3.Z);
    Assert.Equal(10.8f, v3.W);
    Assert.Equal(1.5f, v4.X);
    Assert.Equal(2.0f, v4.Y);
    Assert.Equal(3.0f, v4.Z);
    Assert.Equal(Single.NaN, v4.W);
}

// A test for Vector4f (float, float, float, float)
[Fact]
public void Vector4ConstructorTest()
{
    float x = 1.0f;
    float y = 2.0f;
    float z = 3.0f;
    float w = 4.0f;

    Vector4 target = Vector4(x, y, z, w);

    Assert.True(MathHelper.Equal(target.X, x) && MathHelper.Equal(target.Y, y) && MathHelper.Equal(target.Z, z) && MathHelper.Equal(target.W, w),
        "Vector4f constructor(x,y,z,w) did not return the expected value.");
}

// A test for Vector4f (Vector2f, float, float)
[Fact]
public void Vector4ConstructorTest1()
{
    Vector2 a = new Vector2(1.0f, 2.0f);
    float z = 3.0f;
    float w = 4.0f;

    Vector4 target = Vector4(a, z, w);
    Assert.True(MathHelper.Equal(target.X, a.X) && MathHelper.Equal(target.Y, a.Y) && MathHelper.Equal(target.Z, z) && MathHelper.Equal(target.W, w),
        "Vector4f constructor(Vector2f,z,w) did not return the expected value.");
}

// A test for Vector4f (Vector3f, float)
[Fact]
public void Vector4ConstructorTest2()
{
    Vector3 a = new Vector3(1.0f, 2.0f, 3.0f);
    float w = 4.0f;

    Vector4 target = Vector4(a, w);

    Assert.True(MathHelper.Equal(target.X, a.X) && MathHelper.Equal(target.Y, a.Y) && MathHelper.Equal(target.Z, a.Z) && MathHelper.Equal(target.W, w),
        "Vector4f constructor(Vector3f,w) did not return the expected value.");
}

// A test for Vector4f ()
// Constructor with no parameter
[Fact]
public void Vector4ConstructorTest4()
{
    Vector4 a = Vector4();

    Assert.Equal(a.X, 0.0f);
    Assert.Equal(a.Y, 0.0f);
    Assert.Equal(a.Z, 0.0f);
    Assert.Equal(a.W, 0.0f);
}

// A test for Vector4f ()
// Constructor with special floating values
[Fact]
public void Vector4ConstructorTest5()
{
    Vector4 target = Vector4(float.NaN, float.MaxValue, float.PositiveInfinity, float.Epsilon);

    Assert.True(float.IsNaN(target.X), "Vector4f.constructor (float, float, float, float) did not return the expected value.");
    Assert.True(float.Equals(float.MaxValue, target.Y), "Vector4f.constructor (float, float, float, float) did not return the expected value.");
    Assert.True(float.IsPositiveInfinity(target.Z), "Vector4f.constructor (float, float, float, float) did not return the expected value.");
    Assert.True(float.Equals(float.Epsilon, target.W), "Vector4f.constructor (float, float, float, float) did not return the expected value.");
}

// A test for Add (Vector4f, Vector4f)
[Fact]
public void Vector4AddTest()
{
    Vector4 a = Vector4(1.0f, 2.0f, 3.0f, 4.0f);
    Vector4 b = Vector4(5.0f, 6.0f, 7.0f, 8.0f);

    Vector4 expected = Vector4(6.0f, 8.0f, 10.0f, 12.0f);
    Vector4 actual;

    actual = Vector4.Add(a, b);
    Assert.Equal(expected, actual);
}

// A test for Divide (Vector4f, float)
[Fact]
public void Vector4DivideTest()
{
    Vector4 a = Vector4(1.0f, 2.0f, 3.0f, 4.0f);
    float div = 2.0f;
    Vector4 expected = Vector4(0.5f, 1.0f, 1.5f, 2.0f);
    Vector4 actual;
    actual = Vector4.Divide(a, div);
    Assert.Equal(expected, actual);
}

// A test for Divide (Vector4f, Vector4f)
[Fact]
public void Vector4DivideTest1()
{
    Vector4 a = Vector4(1.0f, 6.0f, 7.0f, 4.0f);
    Vector4 b = Vector4(5.0f, 2.0f, 3.0f, 8.0f);

    Vector4 expected = Vector4(1.0f / 5.0f, 6.0f / 2.0f, 7.0f / 3.0f, 4.0f / 8.0f);
    Vector4 actual;

    actual = Vector4.Divide(a, b);
    Assert.Equal(expected, actual);
}

// A test for Equals (object)
[Fact]
public void Vector4EqualsTest()
{
    Vector4 a = Vector4(1.0f, 2.0f, 3.0f, 4.0f);
    Vector4 b = Vector4(1.0f, 2.0f, 3.0f, 4.0f);

    // case 1: compare between same values
    object obj = b;

    bool expected = true;
    bool actual = a.Equals(obj);
    Assert.Equal(expected, actual);

    // case 2: compare between different values
    b.X = 10.0f;
    obj = b;
    expected = false;
    actual = a.Equals(obj);
    Assert.Equal(expected, actual);

    // case 3: compare between different types.
    obj = new Quaternion();
    expected = false;
    actual = a.Equals(obj);
    Assert.Equal(expected, actual);

    // case 3: compare against null.
    obj = null;
    expected = false;
    actual = a.Equals(obj);
    Assert.Equal(expected, actual);
}

// A test for Multiply (Vector4f, float)
[Fact]
public void Vector4MultiplyTest2()
{
    Vector4 a = Vector4(1.0f, 2.0f, 3.0f, 4.0f);
    float factor = 2.0f;
    Vector4 expected = Vector4(2.0f, 4.0f, 6.0f, 8.0f);
    Vector4 actual = Vector4.Multiply(a, factor);
    Assert.Equal(expected, actual);
}

// A test for Multiply (Vector4f, Vector4f)
[Fact]
public void Vector4MultiplyTest3()
{
    Vector4 a = Vector4(1.0f, 2.0f, 3.0f, 4.0f);
    Vector4 b = Vector4(5.0f, 6.0f, 7.0f, 8.0f);

    Vector4 expected = Vector4(5.0f, 12.0f, 21.0f, 32.0f);
    Vector4 actual;

    actual = Vector4.Multiply(a, b);
    Assert.Equal(expected, actual);
}

// A test for Negate (Vector4f)
[Fact]
public void Vector4NegateTest()
{
    Vector4 a = Vector4(1.0f, 2.0f, 3.0f, 4.0f);

    Vector4 expected = Vector4(-1.0f, -2.0f, -3.0f, -4.0f);
    Vector4 actual;

    actual = Vector4.Negate(a);
    Assert.Equal(expected, actual);
}

// A test for operator != (Vector4f, Vector4f)
[Fact]
public void Vector4InequalityTest()
{
    Vector4 a = Vector4(1.0f, 2.0f, 3.0f, 4.0f);
    Vector4 b = Vector4(1.0f, 2.0f, 3.0f, 4.0f);

    // case 1: compare between same values
    bool expected = false;
    bool actual = a != b;
    Assert.Equal(expected, actual);

    // case 2: compare between different values
    b.X = 10.0f;
    expected = true;
    actual = a != b;
    Assert.Equal(expected, actual);
}

// A test for operator == (Vector4f, Vector4f)
[Fact]
public void Vector4EqualityTest()
{
    Vector4 a = Vector4(1.0f, 2.0f, 3.0f, 4.0f);
    Vector4 b = Vector4(1.0f, 2.0f, 3.0f, 4.0f);

    // case 1: compare between same values
    bool expected = true;
    bool actual = a == b;
    Assert.Equal(expected, actual);

    // case 2: compare between different values
    b.X = 10.0f;
    expected = false;
    actual = a == b;
    Assert.Equal(expected, actual);
}

// A test for Subtract (Vector4f, Vector4f)
[Fact]
public void Vector4SubtractTest()
{
    Vector4 a = Vector4(1.0f, 6.0f, 3.0f, 4.0f);
    Vector4 b = Vector4(5.0f, 2.0f, 3.0f, 9.0f);

    Vector4 expected = Vector4(-4.0f, 4.0f, 0.0f, -5.0f);
    Vector4 actual;

    actual = Vector4.Subtract(a, b);

    Assert.Equal(expected, actual);
}

// A test for UnitW
[Fact]
public void Vector4UnitWTest()
{
    Vector4 val = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
    Assert.Equal(val, Vector4.UnitW);
}

// A test for UnitX
[Fact]
public void Vector4UnitXTest()
{
    Vector4 val = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
    Assert.Equal(val, Vector4.UnitX);
}

// A test for UnitY
[Fact]
public void Vector4UnitYTest()
{
    Vector4 val = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
    Assert.Equal(val, Vector4.UnitY);
}

// A test for UnitZ
[Fact]
public void Vector4UnitZTest()
{
    Vector4 val = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
    Assert.Equal(val, Vector4.UnitZ);
}

// A test for One
[Fact]
public void Vector4OneTest()
{
    Vector4 val = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    Assert.Equal(val, Vector4.One);
}

// A test for Zero
[Fact]
public void Vector4ZeroTest()
{
    Vector4 val = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
    Assert.Equal(val, Vector4.Zero);
}

// A test for Equals (Vector4f)
[Fact]
public void Vector4EqualsTest1()
{
    Vector4 a = Vector4(1.0f, 2.0f, 3.0f, 4.0f);
    Vector4 b = Vector4(1.0f, 2.0f, 3.0f, 4.0f);

    // case 1: compare between same values
    Assert.True(a.Equals(b));

    // case 2: compare between different values
    b.X = 10.0f;
    Assert.False(a.Equals(b));
}

// A test for Vector4f (float)
[Fact]
public void Vector4ConstructorTest6()
{
    float value = 1.0f;
    Vector4 target = Vector4(value);

    Vector4 expected = Vector4(value, value, value, value);
    Assert.Equal(expected, target);

    value = 2.0f;
    target = Vector4(value);
    expected = Vector4(value, value, value, value);
    Assert.Equal(expected, target);
}

// A test for Vector4f comparison involving NaN values
[Fact]
public void Vector4EqualsNanTest()
{
    Vector4 a = Vector4(float.NaN, 0, 0, 0);
    Vector4 b = Vector4(0, float.NaN, 0, 0);
    Vector4 c = Vector4(0, 0, float.NaN, 0);
    Vector4 d = Vector4(0, 0, 0, float.NaN);

    Assert.False(a == Vector4.Zero);
    Assert.False(b == Vector4.Zero);
    Assert.False(c == Vector4.Zero);
    Assert.False(d == Vector4.Zero);

    Assert.True(a != Vector4.Zero);
    Assert.True(b != Vector4.Zero);
    Assert.True(c != Vector4.Zero);
    Assert.True(d != Vector4.Zero);

    Assert.False(a.Equals(Vector4.Zero));
    Assert.False(b.Equals(Vector4.Zero));
    Assert.False(c.Equals(Vector4.Zero));
    Assert.False(d.Equals(Vector4.Zero));

    // Counterintuitive result - IEEE rules for NaN comparison are weird!
    Assert.False(a.Equals(a));
    Assert.False(b.Equals(b));
    Assert.False(c.Equals(c));
    Assert.False(d.Equals(d));
}

[Fact]
public void Vector4AbsTest()
{
    Vector4 v1 = Vector4(-2.5f, 2.0f, 3.0f, 3.3f);
    Vector4 v3 = Vector4.Abs(Vector4(Single.PositiveInfinity, 0.0f, Single.NegativeInfinity, Single.NaN));
    Vector4 v = Vector4.Abs(v1);
    Assert.Equal(2.5f, v.X);
    Assert.Equal(2.0f, v.Y);
    Assert.Equal(3.0f, v.Z);
    Assert.Equal(3.3f, v.W);
    Assert.Equal(Single.PositiveInfinity, v3.X);
    Assert.Equal(0.0f, v3.Y);
    Assert.Equal(Single.PositiveInfinity, v3.Z);
    Assert.Equal(Single.NaN, v3.W);
}

[Fact]
public void Vector4SqrtTest()
{
    Vector4 v1 = Vector4(-2.5f, 2.0f, 3.0f, 3.3f);
    Vector4 v2 = Vector4(5.5f, 4.5f, 6.5f, 7.5f);
    Assert.Equal(2, (int)Vector4.SquareRoot(v2).X);
    Assert.Equal(2, (int)Vector4.SquareRoot(v2).Y);
    Assert.Equal(2, (int)Vector4.SquareRoot(v2).Z);
    Assert.Equal(2, (int)Vector4.SquareRoot(v2).W);
    Assert.Equal(Single.NaN, Vector4.SquareRoot(v1).X);
}

// A test to make sure these types are blittable directly into GPU buffer memory layouts
[Fact]
public unsafe void Vector4SizeofTest()
{
    Assert.Equal(16, sizeof(Vector4));
    Assert.Equal(32, sizeof(Vector4_2x));
    Assert.Equal(20, sizeof(Vector4PlusFloat));
    Assert.Equal(40, sizeof(Vector4PlusFloat_2x));
}

[StructLayout(LayoutKind.Sequential)]
struct Vector4_2x
{
    private Vector4 _a;
    private Vector4 _b;
}

[StructLayout(LayoutKind.Sequential)]
struct Vector4PlusFloat
{
    private Vector4 _v;
    private float _f;
}

[StructLayout(LayoutKind.Sequential)]
struct Vector4PlusFloat_2x
{
    private Vector4PlusFloat _a;
    private Vector4PlusFloat _b;
}

[Fact]
public void SetFieldsTest()
{
    Vector4 v3 = Vector4(4f, 5f, 6f, 7f);
    v3.X = 1.0f;
    v3.Y = 2.0f;
    v3.Z = 3.0f;
    v3.W = 4.0f;
    Assert.Equal(1.0f, v3.X);
    Assert.Equal(2.0f, v3.Y);
    Assert.Equal(3.0f, v3.Z);
    Assert.Equal(4.0f, v3.W);
    Vector4 v4 = v3;
    v4.Y = 0.5f;
    v4.Z = 2.2f;
    v4.W = 3.5f;
    Assert.Equal(1.0f, v4.X);
    Assert.Equal(0.5f, v4.Y);
    Assert.Equal(2.2f, v4.Z);
    Assert.Equal(3.5f, v4.W);
    Assert.Equal(2.0f, v3.Y);
}

[Fact]
public void EmbeddedVectorSetFields()
{
    EmbeddedVectorObject evo = new EmbeddedVectorObject();
    evo.FieldVector.X = 5.0f;
    evo.FieldVector.Y = 5.0f;
    evo.FieldVector.Z = 5.0f;
    evo.FieldVector.W = 5.0f;
    Assert.Equal(5.0f, evo.FieldVector.X);
    Assert.Equal(5.0f, evo.FieldVector.Y);
    Assert.Equal(5.0f, evo.FieldVector.Z);
    Assert.Equal(5.0f, evo.FieldVector.W);
}

[Fact]
public void DeeplyEmbeddedObjectTest()
{
    DeeplyEmbeddedClass obj = new DeeplyEmbeddedClass();
    obj.L0.L1.L2.L3.L4.L5.L6.L7.EmbeddedVector.X = 5f;
    Assert.Equal(5f, obj.RootEmbeddedObject.X);
    Assert.Equal(5f, obj.RootEmbeddedObject.Y);
    Assert.Equal(1f, obj.RootEmbeddedObject.Z);
    Assert.Equal(-5f, obj.RootEmbeddedObject.W);
    obj.L0.L1.L2.L3.L4.L5.L6.L7.EmbeddedVector = Vector4(1, 2, 3, 4);
    Assert.Equal(1f, obj.RootEmbeddedObject.X);
    Assert.Equal(2f, obj.RootEmbeddedObject.Y);
    Assert.Equal(3f, obj.RootEmbeddedObject.Z);
    Assert.Equal(4f, obj.RootEmbeddedObject.W);
}

[Fact]
public void DeeplyEmbeddedStructTest()
{
    DeeplyEmbeddedStruct obj = DeeplyEmbeddedStruct.Create();
    obj.L0.L1.L2.L3.L4.L5.L6.L7.EmbeddedVector.X = 5f;
    Assert.Equal(5f, obj.RootEmbeddedObject.X);
    Assert.Equal(5f, obj.RootEmbeddedObject.Y);
    Assert.Equal(1f, obj.RootEmbeddedObject.Z);
    Assert.Equal(-5f, obj.RootEmbeddedObject.W);
    obj.L0.L1.L2.L3.L4.L5.L6.L7.EmbeddedVector = Vector4(1, 2, 3, 4);
    Assert.Equal(1f, obj.RootEmbeddedObject.X);
    Assert.Equal(2f, obj.RootEmbeddedObject.Y);
    Assert.Equal(3f, obj.RootEmbeddedObject.Z);
    Assert.Equal(4f, obj.RootEmbeddedObject.W);
}

private class EmbeddedVectorObject
{
    public Vector4 FieldVector;
}

private class DeeplyEmbeddedClass
{
    public readonly Level0 L0 = new Level0();
    public Vector4 RootEmbeddedObject { get { return L0.L1.L2.L3.L4.L5.L6.L7.EmbeddedVector; } }
    public class Level0
    {
        public readonly Level1 L1 = new Level1();
        public class Level1
        {
            public readonly Level2 L2 = new Level2();
            public class Level2
            {
                public readonly Level3 L3 = new Level3();
                public class Level3
                {
                    public readonly Level4 L4 = new Level4();
                    public class Level4
                    {
                        public readonly Level5 L5 = new Level5();
                        public class Level5
                        {
                            public readonly Level6 L6 = new Level6();
                            public class Level6
                            {
                                public readonly Level7 L7 = new Level7();
                                public class Level7
                                {
                                    public Vector4 EmbeddedVector = Vector4(1, 5, 1, -5);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// Contrived test for strangely-sized and shaped embedded structures, with unused buffer fields.
#pragma warning disable 0169
private struct DeeplyEmbeddedStruct
{
    public static DeeplyEmbeddedStruct Create()
    {
        var obj = new DeeplyEmbeddedStruct();
        obj.L0 = new Level0();
        obj.L0.L1 = new Level0.Level1();
        obj.L0.L1.L2 = new Level0.Level1.Level2();
        obj.L0.L1.L2.L3 = new Level0.Level1.Level2.Level3();
        obj.L0.L1.L2.L3.L4 = new Level0.Level1.Level2.Level3.Level4();
        obj.L0.L1.L2.L3.L4.L5 = new Level0.Level1.Level2.Level3.Level4.Level5();
        obj.L0.L1.L2.L3.L4.L5.L6 = new Level0.Level1.Level2.Level3.Level4.Level5.Level6();
        obj.L0.L1.L2.L3.L4.L5.L6.L7 = new Level0.Level1.Level2.Level3.Level4.Level5.Level6.Level7();
        obj.L0.L1.L2.L3.L4.L5.L6.L7.EmbeddedVector = Vector4(1, 5, 1, -5);

        return obj;
    }

    public Level0 L0;
    public Vector4 RootEmbeddedObject { get { return L0.L1.L2.L3.L4.L5.L6.L7.EmbeddedVector; } }
    public struct Level0
    {
        private float _buffer0, _buffer1;
        public Level1 L1;
        private float _buffer2;
        public struct Level1
        {
            private float _buffer0, _buffer1;
            public Level2 L2;
            private byte _buffer2;
            public struct Level2
            {
                public Level3 L3;
                private float _buffer0;
                private byte _buffer1;
                public struct Level3
                {
                    public Level4 L4;
                    public struct Level4
                    {
                        private float _buffer0;
                        public Level5 L5;
                        private long _buffer1;
                        private byte _buffer2;
                        private double _buffer3;
                        public struct Level5
                        {
                            private byte _buffer0;
                            public Level6 L6;
                            public struct Level6
                            {
                                private byte _buffer0;
                                public Level7 L7;
                                private byte _buffer1, _buffer2;
                                public struct Level7
                                {
                                    public Vector4 EmbeddedVector;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
#pragma warning restore 0169
}
*/
