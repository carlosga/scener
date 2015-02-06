// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Vector2Test.hpp>

#include <cmath>
#include <limits>

#include <Framework/Vector2.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/MathHelper.hpp>

using namespace System;
using namespace SceneR::Framework;

TEST_F(Vector2Test, IndividualCoordinatesConstructor)
{
    float x = 20.0f;
    float y = 30.0f;

    auto vector = Vector2 { x, y };

    // vector2 is equal to (20.0, 30.0)
    EXPECT_TRUE(x == vector.X());
    EXPECT_TRUE(y == vector.Y());
}

TEST_F(Vector2Test, Magnitude)
{
    auto vector = Vector2 { 20.0f, 30.0f };

    EXPECT_TRUE(36.05551275463989f == vector.Length());
}

TEST_F(Vector2Test, Length)
{
    auto vector1 = Vector2 { 1.0f, 1.0f };
    auto vector2 = Vector2 { 3.0f, 3.0f };

    EXPECT_TRUE(2.82842708f == Vector2::Distance(vector1, vector2));
}

TEST_F(Vector2Test, Lerp)
{
    auto vector1 = Vector2 { 5.0f, 10.0f };
    auto vector2 = Vector2 { 0.0f, -20.0f };
    auto result  = Vector2::Lerp(vector1, vector2, 0.4f);

    EXPECT_TRUE(3.0f  == result.X());
    EXPECT_TRUE(-2.0f == result.Y());
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Distance)
{
    auto a = Vector2 { 1.0f, 2.0f };
    auto b = Vector2 { 3.0f, 4.0f };

    Single expected = (Single)std::sqrt(8);
    Single actual   = Vector2::Distance(a, b);

    EXPECT_TRUE(expected == actual);
}

// A test for Distance (Vector2f, Vector2f)
// Distance from the same point
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Distance2)
{
    auto a = Vector2 { 1.051f, 2.05f };
    auto b = Vector2 { 1.051f, 2.05f };

    Single actual = Vector2::Distance(a, b);

    EXPECT_TRUE(0.0f == actual);
}

// A test for DistanceSquared (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, DistanceSquared)
{
    auto a = Vector2 { 1.0f, 2.0f };
    auto b = Vector2 { 3.0f, 4.0f };

    Single expected = 8.0f;
    Single actual   = Vector2::DistanceSquared(a, b);

    EXPECT_TRUE(expected == actual);
}

// A test for Dot (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Dot)
{
    auto a = Vector2 { 1.0f, 2.0f };
    auto b = Vector2 { 3.0f, 4.0f };

    Single expected = 11.0f;
    Single actual   = Vector2::DotProduct(a, b);

    EXPECT_TRUE(expected == actual);
}

// A test for Dot (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, DotWithPerpendicularVector)
{
    auto a = Vector2 { 1.55f, 1.55f };
    auto b = Vector2 { -1.55f, 1.55f };

    Single expected = 0.0f;
    Single actual   = Vector2::DotProduct(a, b);

    EXPECT_TRUE(expected == actual);
}

// A test for Dot (Vector2f, Vector2f)
// Dot test with special float values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, DotWithSpecialFloatValues)
{
    auto a = Vector2 { std::numeric_limits<Single>::min(), std::numeric_limits<Single>::min() };
    auto b = Vector2 { std::numeric_limits<Single>::max(), std::numeric_limits<Single>::max() };

    Single actual = Vector2::DotProduct(a, b);

    EXPECT_TRUE(MathHelper::IsNegativeInfinity(actual));
};

// A test for Length ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Length2)
{
    auto a      = Vector2 { 2.0f, 4.0f };
    auto target = a;

    Single expected = (Single)std::sqrt(20);
    Single actual   = target.Length();

    EXPECT_TRUE(expected == actual);
};

// A test for Length ()
// Length test where length is zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, ZeroLength)
{
    auto target = Vector2 { 0.0f, 0.0f };

    Single expected = 0.0f;
    Single actual   = target.Length();

    EXPECT_TRUE(expected == actual);
}

// A test for LengthSquared ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, LengthSquared1)
{
    auto a      = Vector2 { 2.0f, 4.0f };
    auto target = a;

    Single expected = 20.0f;
    Single actual   = target.LengthSquared();

    EXPECT_TRUE(expected == actual);
}

// A test for LengthSquared ()
// LengthSquared test where the result is zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, ZeroLengthSquared)
{
    auto a = Vector2 { 0.0f, 0.0f };

    Single expected = 0.0f;
    Single actual   = a.LengthSquared();

    EXPECT_TRUE(expected == actual);
}

// A test for Min (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Min)
{
    auto a = Vector2 { -1.0f, 4.0f };
    auto b = Vector2 { 2.0f, 1.0f };

    auto expected = Vector2 { -1.0f, 1.0f };
    auto actual   = Vector2::Min(a, b);

    EXPECT_TRUE(expected == actual);
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, MinMaxCodeCoverage)
{
    auto min = Vector2 { 0.0f, 0.0f };
    auto max = Vector2 { 1.0f, 1.0f };

    // Min.
    auto actual = Vector2::Min(min, max);
    EXPECT_TRUE(actual == min);

    actual = Vector2::Min(max, min);
    EXPECT_TRUE(actual == min);

    // Max.
    actual = Vector2::Max(min, max);
    EXPECT_TRUE(actual == max);

    actual = Vector2::Max(max, min);
    EXPECT_TRUE(actual == max);
}

// A test for Max (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Max)
{
    auto a = Vector2 { -1.0f, 4.0f };
    auto b = Vector2 { 2.0f, 1.0f };

    auto expected = Vector2 { 2.0f, 4.0f };
    auto actual   = Vector2::Max(a, b);

    EXPECT_TRUE(expected == actual);
}

// A test for Clamp (Vector2f, Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Clamp)
{
    auto a   = Vector2 { 0.5f, 0.3f };
    auto min = Vector2 { 0.0f, 0.1f };
    auto max = Vector2 { 1.0f, 1.1f };

    // Normal case.
    // Case N1: specified value is in the range.
    auto expected = Vector2(0.5f, 0.3f);
    auto actual   = Vector2::Clamp(a, min, max);

    EXPECT_TRUE(expected == actual);

    // Normal case.
    // Case N2: specified value is bigger than max value.
    a        = Vector2 { 2.0f, 3.0f };
    expected = max;
    actual   = Vector2::Clamp(a, min, max);

    EXPECT_TRUE(expected == actual);

    // Case N3: specified value is smaller than max value.
    a        = Vector2 { -1.0f, -2.0f };
    expected = min;
    actual   = Vector2::Clamp(a, min, max);

    EXPECT_TRUE(expected == actual);

    // Case N4: combination case.
    a        = Vector2(-2.0f, 4.0f);
    expected = Vector2(min.X(), max.Y());
    actual   = Vector2::Clamp(a, min, max);

    EXPECT_TRUE(expected == actual);

    // User specified min value is bigger than max value.
    max = Vector2 { 0.0f, 0.1f };
    min = Vector2 { 1.0f, 1.1f };

    // Case W1: specified value is in the range.
    a        = Vector2 { 0.5f, 0.3f };
    expected = min;
    actual   = Vector2::Clamp(a, min, max);

    EXPECT_TRUE(expected == actual);

    // Normal case.
    // Case W2: specified value is bigger than max and min value.
    a        = Vector2 { 2.0f, 3.0f };
    expected = min;
    actual   = Vector2::Clamp(a, min, max);

    EXPECT_TRUE(expected == actual);

    // Case W3: specified value is smaller than min and max value.
    a        = Vector2 { -1.0f, -2.0f };
    expected = min;
    actual   = Vector2::Clamp(a, min, max);

    EXPECT_TRUE(expected == actual);
}

// A test for Lerp (Vector2f, Vector2f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Lerp2)
{
    auto a = Vector2 { 1.0f, 2.0f };
    auto b = Vector2 { 3.0f, 4.0f };

    Single t = 0.5f;

    auto expected = Vector2 { 2.0f, 3.0f };
    auto actual   = Vector2::Lerp(a, b, t);

    EXPECT_TRUE(expected == actual);
}

// A test for Lerp (Vector2f, Vector2f, float)
// Lerp test with factor zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, LerpWithFactorZero)
{
    auto a = Vector2 { 0.0f, 0.0f };
    auto b = Vector2 { 3.18f, 4.25f };

    Single t = 0.0f;

    auto expected = Vector2::Zero;
    auto actual   = Vector2::Lerp(a, b, t);

    EXPECT_TRUE(expected == actual);
}

// A test for Lerp (Vector2f, Vector2f, float)
// Lerp test with factor one
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, LerpWithFactorOne)
{
    auto a = Vector2 { 0.0f, 0.0f };
    auto b = Vector2 { 3.18f, 4.25f };

    Single t = 1.0f;

    auto expected = Vector2(3.18f, 4.25f);
    auto actual = Vector2::Lerp(a, b, t);

    EXPECT_TRUE(expected == actual);
}

// A test for Lerp (Vector2f, Vector2f, float)
// Lerp test with factor > 1
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, LerpWithFactorGreaterThanOne)
{
    auto a = Vector2 { 0.0f, 0.0f };
    auto b = Vector2 { 3.18f, 4.25f };

    Single  t = 2.0f;

    auto expected = b * 2.0f;
    auto actual   = Vector2::Lerp(a, b, t);

    EXPECT_TRUE(expected == actual);
}

// A test for Lerp (Vector2f, Vector2f, float)
// Lerp test with factor < 0
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, LerpWithFactorLessThanZero)
{
    auto a = Vector2 { 0.0f, 0.0f };
    auto b = Vector2 { 3.18f, 4.25f };

    Single t = -2.0f;

    auto expected = Vector2::Negate(b * 2.0f);
    auto actual   = Vector2::Lerp(a, b, t);

    EXPECT_TRUE(expected == actual);
}

// A test for Lerp (Vector2f, Vector2f, float)
// Lerp test with special float value
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, LerpWithSpecialFloatValue)
{
    auto a = Vector2 { 45.67f, 90.0f };
    auto b = Vector2 { MathHelper::PositiveInfinity, MathHelper::NegativeInfinity };

    Single t = 0.408f;

    auto actual = Vector2::Lerp(a, b, t);

    EXPECT_TRUE(MathHelper::IsPositiveInfinity(actual.X()));
    EXPECT_TRUE(MathHelper::IsNegativeInfinity(actual.Y()));
}

// A test for Lerp (Vector2f, Vector2f, float)
// Lerp test from the same point
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, LerpFromSamePoint)
{
    auto a = Vector2 { 1.0f, 2.0f };
    auto b = Vector2 { 1.0f, 2.0f };

    float t = 0.5f;

    auto expected = Vector2 { 1.0f, 2.0f };
    auto actual   = Vector2::Lerp(a, b, t);

    EXPECT_TRUE(expected == actual);
}

// A test for Transform(Vector2f, Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Transform)
{
    auto v = Vector2 { 1.0f, 2.0f };
    auto m = Matrix::CreateRotationX(MathHelper::ToRadians(30.0f))
           * Matrix::CreateRotationY(MathHelper::ToRadians(30.0f))
           * Matrix::CreateRotationZ(MathHelper::ToRadians(30.0f));

    m.M41(10.0f);
    m.M42(20.0f);
    m.M43(30.0f);

    auto expected = Vector2 { 10.316987f, 22.183012f };
    auto actual   = Vector2::Transform(v, m);

    EXPECT_TRUE(expected == actual);
}

// A test for TransformNormal (Vector2f, Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, TransformNormal)
{
    auto v = Vector2 { 1.0f, 2.0f };
    auto m = Matrix::CreateRotationX(MathHelper::ToRadians(30.0f))
           * Matrix::CreateRotationY(MathHelper::ToRadians(30.0f))
           * Matrix::CreateRotationZ(MathHelper::ToRadians(30.0f));

    m.M41(10.0f);
    m.M42(20.0f);
    m.M43(30.0f);

    auto expected = Vector2 { 0.3169873f, 2.18301272f };
    auto actual   = Vector2::TransformNormal(v, m);

    EXPECT_TRUE(expected == actual);
}

/*
// A test for Transform (Vector2f, Quaternion)
[Fact]
public void Vector2TransformByQuaternionTest()
{
    Vector2 v = new Vector2(1.0f, 2.0f);

    Matrix4x4 m =
                  Matrix4x4.CreateRotationX(MathHelper.ToRadians(30.0f)) *
                      Matrix4x4.CreateRotationY(MathHelper.ToRadians(30.0f)) *
                      Matrix4x4.CreateRotationZ(MathHelper.ToRadians(30.0f));
    Quaternion q = Quaternion.CreateFromRotationMatrix(m);

    Vector2 expected = Vector2.Transform(v, m);
    Vector2 actual = Vector2.Transform(v, q);
    Assert.True(MathHelper.Equal(expected, actual), "Vector2f.Transform did not return the expected value.");
}

// A test for Transform (Vector2f, Quaternion)
// Transform Vector2f with zero quaternion
[Fact]
public void Vector2TransformByQuaternionTest1()
{
    Vector2 v = new Vector2(1.0f, 2.0f);
    Quaternion q = new Quaternion();
    Vector2 expected = v;

    Vector2 actual = Vector2.Transform(v, q);
    Assert.True(MathHelper.Equal(expected, actual), "Vector2f.Transform did not return the expected value.");
}

// A test for Transform (Vector2f, Quaternion)
// Transform Vector2f with identity quaternion
[Fact]
public void Vector2TransformByQuaternionTest2()
{
    Vector2 v = new Vector2(1.0f, 2.0f);
    Quaternion q = Quaternion.Identity;
    Vector2 expected = v;

    Vector2 actual = Vector2.Transform(v, q);
    Assert.True(MathHelper.Equal(expected, actual), "Vector2f.Transform did not return the expected value.");
}

// A test for Normalize (Vector2f)
[Fact]
public void Vector2NormalizeTest()
{
    Vector2 a = new Vector2(2.0f, 3.0f);
    Vector2 expected = new Vector2(0.554700196225229122018341733457f, 0.8320502943378436830275126001855f);
    Vector2 actual;

    actual = Vector2.Normalize(a);
    Assert.True(MathHelper.Equal(expected, actual), "Vector2f.Normalize did not return the expected value.");
}

// A test for Normalize (Vector2f)
// Normalize zero length vector
[Fact]
public void Vector2NormalizeTest1()
{
    Vector2 a = new Vector2(); // no parameter, default to 0.0f
    Vector2 actual = Vector2.Normalize(a);
    Assert.True(float.IsNaN(actual.X) && float.IsNaN(actual.Y), "Vector2f.Normalize did not return the expected value.");
}

// A test for Normalize (Vector2f)
// Normalize infinite length vector
[Fact]
public void Vector2NormalizeTest2()
{
    Vector2 a = new Vector2(float.MaxValue, float.MaxValue);
    Vector2 actual = Vector2.Normalize(a);
    Vector2 expected = new Vector2(0, 0);
    Assert.Equal(expected, actual);
}

// A test for operator - (Vector2f)
[Fact]
public void Vector2UnaryNegationTest()
{
    Vector2 a = new Vector2(1.0f, 2.0f);

    Vector2 expected = new Vector2(-1.0f, -2.0f);
    Vector2 actual;

    actual = -a;

    Assert.True(MathHelper.Equal(expected, actual), "Vector2f.operator - did not return the expected value.");
}



// A test for operator - (Vector2f)
// Negate test with special float value
[Fact]
public void Vector2UnaryNegationTest1()
{
    Vector2 a = new Vector2(float.PositiveInfinity, float.NegativeInfinity);

    Vector2 actual = -a;

    Assert.True(float.IsNegativeInfinity(actual.X), "Vector2f.operator - did not return the expected value.");
    Assert.True(float.IsPositiveInfinity(actual.Y), "Vector2f.operator - did not return the expected value.");
}

// A test for operator - (Vector2f)
// Negate test with special float value
[Fact]
public void Vector2UnaryNegationTest2()
{
    Vector2 a = new Vector2(float.NaN, 0.0f);
    Vector2 actual = -a;

    Assert.True(float.IsNaN(actual.X), "Vector2f.operator - did not return the expected value.");
    Assert.True(float.Equals(0.0f, actual.Y), "Vector2f.operator - did not return the expected value.");
}

// A test for operator - (Vector2f, Vector2f)
[Fact]
public void Vector2SubtractionTest()
{
    Vector2 a = new Vector2(1.0f, 3.0f);
    Vector2 b = new Vector2(2.0f, 1.5f);

    Vector2 expected = new Vector2(-1.0f, 1.5f);
    Vector2 actual;

    actual = a - b;

    Assert.True(MathHelper.Equal(expected, actual), "Vector2f.operator - did not return the expected value.");
}

// A test for operator * (Vector2f, float)
[Fact]
public void Vector2MultiplyTest()
{
    Vector2 a = new Vector2(2.0f, 3.0f);
    float factor = 2.0f;

    Vector2 expected = new Vector2(4.0f, 6.0f);
    Vector2 actual;

    actual = a * factor;
    Assert.True(MathHelper.Equal(expected, actual), "Vector2f.operator * did not return the expected value.");
}

// A test for operator * (float, Vector2f)
[Fact]
public void Vector2MultiplyTest4()
{
    Vector2 a = new Vector2(2.0f, 3.0f);
    float factor = 2.0f;

    Vector2 expected = new Vector2(4.0f, 6.0f);
    Vector2 actual;

    actual = factor * a;
    Assert.True(MathHelper.Equal(expected, actual), "Vector2f.operator * did not return the expected value.");
}

// A test for operator * (Vector2f, Vector2f)
[Fact]
public void Vector2MultiplyTest1()
{
    Vector2 a = new Vector2(2.0f, 3.0f);
    Vector2 b = new Vector2(4.0f, 5.0f);

    Vector2 expected = new Vector2(8.0f, 15.0f);
    Vector2 actual;

    actual = a * b;

    Assert.True(MathHelper.Equal(expected, actual), "Vector2f.operator * did not return the expected value.");
}

// A test for operator / (Vector2f, float)
[Fact]
public void Vector2DivisionTest()
{
    Vector2 a = new Vector2(2.0f, 3.0f);

    float div = 2.0f;

    Vector2 expected = new Vector2(1.0f, 1.5f);
    Vector2 actual;

    actual = a / div;

    Assert.True(MathHelper.Equal(expected, actual), "Vector2f.operator / did not return the expected value.");
}

// A test for operator / (Vector2f, Vector2f)
[Fact]
public void Vector2DivisionTest1()
{
    Vector2 a = new Vector2(2.0f, 3.0f);
    Vector2 b = new Vector2(4.0f, 5.0f);

    Vector2 expected = new Vector2(2.0f / 4.0f, 3.0f / 5.0f);
    Vector2 actual;

    actual = a / b;

    Assert.True(MathHelper.Equal(expected, actual), "Vector2f.operator / did not return the expected value.");
}

// A test for operator / (Vector2f, float)
// Divide by zero
[Fact]
public void Vector2DivisionTest2()
{
    Vector2 a = new Vector2(-2.0f, 3.0f);

    float div = 0.0f;

    Vector2 actual = a / div;

    Assert.True(float.IsNegativeInfinity(actual.X), "Vector2f.operator / did not return the expected value.");
    Assert.True(float.IsPositiveInfinity(actual.Y), "Vector2f.operator / did not return the expected value.");
}

// A test for operator / (Vector2f, Vector2f)
// Divide by zero
[Fact]
public void Vector2DivisionTest3()
{
    Vector2 a = new Vector2(0.047f, -3.0f);
    Vector2 b = new Vector2();

    Vector2 actual = a / b;

    Assert.True(float.IsInfinity(actual.X), "Vector2f.operator / did not return the expected value.");
    Assert.True(float.IsInfinity(actual.Y), "Vector2f.operator / did not return the expected value.");
}

// A test for operator + (Vector2f, Vector2f)
[Fact]
public void Vector2AdditionTest()
{
    Vector2 a = new Vector2(1.0f, 2.0f);
    Vector2 b = new Vector2(3.0f, 4.0f);

    Vector2 expected = new Vector2(4.0f, 6.0f);
    Vector2 actual;

    actual = a + b;

    Assert.True(MathHelper.Equal(expected, actual), "Vector2f.operator + did not return the expected value.");
}

// A test for Vector2f (float, float)
[Fact]
public void Vector2ConstructorTest()
{
    float x = 1.0f;
    float y = 2.0f;

    Vector2 target = new Vector2(x, y);
    Assert.True(MathHelper.Equal(target.X, x) && MathHelper.Equal(target.Y, y), "Vector2f(x,y) constructor did not return the expected value.");
}

// A test for Vector2f ()
// Constructor with no parameter
[Fact]
public void Vector2ConstructorTest2()
{
    Vector2 target = new Vector2();
    Assert.Equal(target.X, 0.0f);
    Assert.Equal(target.Y, 0.0f);
}

// A test for Vector2f (float, float)
// Constructor with special floating values
[Fact]
public void Vector2ConstructorTest3()
{
    Vector2 target = new Vector2(float.NaN, float.MaxValue);
    Assert.Equal(target.X, float.NaN);
    Assert.Equal(target.Y, float.MaxValue);
}

// A test for Vector2f (float)
[Fact]
public void Vector2ConstructorTest4()
{
    float value = 1.0f;
    Vector2 target = new Vector2(value);

    Vector2 expected = new Vector2(value, value);
    Assert.Equal(expected, target);

    value = 2.0f;
    target = new Vector2(value);
    expected = new Vector2(value, value);
    Assert.Equal(expected, target);
}

// A test for Add (Vector2f, Vector2f)
[Fact]
public void Vector2AddTest()
{
    Vector2 a = new Vector2(1.0f, 2.0f);
    Vector2 b = new Vector2(5.0f, 6.0f);

    Vector2 expected = new Vector2(6.0f, 8.0f);
    Vector2 actual;

    actual = Vector2.Add(a, b);
    Assert.Equal(expected, actual);
}

// A test for Divide (Vector2f, float)
[Fact]
public void Vector2DivideTest()
{
    Vector2 a = new Vector2(1.0f, 2.0f);
    float div = 2.0f;
    Vector2 expected = new Vector2(0.5f, 1.0f);
    Vector2 actual;
    actual = Vector2.Divide(a, div);
    Assert.Equal(expected, actual);
}

// A test for Divide (Vector2f, Vector2f)
[Fact]
public void Vector2DivideTest1()
{
    Vector2 a = new Vector2(1.0f, 6.0f);
    Vector2 b = new Vector2(5.0f, 2.0f);

    Vector2 expected = new Vector2(1.0f / 5.0f, 6.0f / 2.0f);
    Vector2 actual;

    actual = Vector2.Divide(a, b);
    Assert.Equal(expected, actual);
}

// A test for Equals (object)
[Fact]
public void Vector2EqualsTest()
{
    Vector2 a = new Vector2(1.0f, 2.0f);
    Vector2 b = new Vector2(1.0f, 2.0f);

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

// A test for Multiply (Vector2f, float)
[Fact]
public void Vector2MultiplyTest2()
{
    Vector2 a = new Vector2(1.0f, 2.0f);
    float factor = 2.0f;
    Vector2 expected = new Vector2(2.0f, 4.0f);
    Vector2 actual = Vector2.Multiply(a, factor);
    Assert.Equal(expected, actual);
}

// A test for Negate (Vector2f)
[Fact]
public void Vector2NegateTest()
{
    Vector2 a = new Vector2(1.0f, 2.0f);

    Vector2 expected = new Vector2(-1.0f, -2.0f);
    Vector2 actual;

    actual = Vector2.Negate(a);
    Assert.Equal(expected, actual);
}

// A test for operator != (Vector2f, Vector2f)
[Fact]
public void Vector2InequalityTest()
{
    Vector2 a = new Vector2(1.0f, 2.0f);
    Vector2 b = new Vector2(1.0f, 2.0f);

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

// A test for operator == (Vector2f, Vector2f)
[Fact]
public void Vector2EqualityTest()
{
    Vector2 a = new Vector2(1.0f, 2.0f);
    Vector2 b = new Vector2(1.0f, 2.0f);

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

// A test for Subtract (Vector2f, Vector2f)
[Fact]
public void Vector2SubtractTest()
{
    Vector2 a = new Vector2(1.0f, 6.0f);
    Vector2 b = new Vector2(5.0f, 2.0f);

    Vector2 expected = new Vector2(-4.0f, 4.0f);
    Vector2 actual;

    actual = Vector2.Subtract(a, b);
    Assert.Equal(expected, actual);
}

// A test for UnitX
[Fact]
public void Vector2UnitXTest()
{
    Vector2 val = new Vector2(1.0f, 0.0f);
    Assert.Equal(val, Vector2.UnitX);
}

// A test for UnitY
[Fact]
public void Vector2UnitYTest()
{
    Vector2 val = new Vector2(0.0f, 1.0f);
    Assert.Equal(val, Vector2.UnitY);
}

// A test for One
[Fact]
public void Vector2OneTest()
{
    Vector2 val = new Vector2(1.0f, 1.0f);
    Assert.Equal(val, Vector2.One);
}

// A test for Zero
[Fact]
public void Vector2ZeroTest()
{
    Vector2 val = new Vector2(0.0f, 0.0f);
    Assert.Equal(val, Vector2.Zero);
}

// A test for Equals (Vector2f)
[Fact]
public void Vector2EqualsTest1()
{
    Vector2 a = new Vector2(1.0f, 2.0f);
    Vector2 b = new Vector2(1.0f, 2.0f);

    // case 1: compare between same values
    bool expected = true;
    bool actual = a.Equals(b);
    Assert.Equal(expected, actual);

    // case 2: compare between different values
    b.X = 10.0f;
    expected = false;
    actual = a.Equals(b);
    Assert.Equal(expected, actual);
}

// A test for Vector2f comparison involving NaN values
[Fact]
public void Vector2EqualsNanTest()
{
    Vector2 a = new Vector2(float.NaN, 0);
    Vector2 b = new Vector2(0, float.NaN);

    Assert.False(a == Vector2.Zero);
    Assert.False(b == Vector2.Zero);

    Assert.True(a != Vector2.Zero);
    Assert.True(b != Vector2.Zero);

    Assert.False(a.Equals(Vector2.Zero));
    Assert.False(b.Equals(Vector2.Zero));

    // Counterintuitive result - IEEE rules for NaN comparison are weird!
    Assert.False(a.Equals(a));
    Assert.False(b.Equals(b));
}

// A test for Reflect (Vector2f, Vector2f)
[Fact]
public void Vector2ReflectTest()
{
    Vector2 a = Vector2.Normalize(new Vector2(1.0f, 1.0f));

    // Reflect on XZ plane.
    Vector2 n = new Vector2(0.0f, 1.0f);
    Vector2 expected = new Vector2(a.X, -a.Y);
    Vector2 actual = Vector2.Reflect(a, n);
    Assert.True(MathHelper.Equal(expected, actual), "Vector2f.Reflect did not return the expected value.");

    // Reflect on XY plane.
    n = new Vector2(0.0f, 0.0f);
    expected = new Vector2(a.X, a.Y);
    actual = Vector2.Reflect(a, n);
    Assert.True(MathHelper.Equal(expected, actual), "Vector2f.Reflect did not return the expected value.");

    // Reflect on YZ plane.
    n = new Vector2(1.0f, 0.0f);
    expected = new Vector2(-a.X, a.Y);
    actual = Vector2.Reflect(a, n);
    Assert.True(MathHelper.Equal(expected, actual), "Vector2f.Reflect did not return the expected value.");
}

// A test for Reflect (Vector2f, Vector2f)
// Reflection when normal and source are the same
[Fact]
public void Vector2ReflectTest1()
{
    Vector2 n = new Vector2(0.45f, 1.28f);
    n = Vector2.Normalize(n);
    Vector2 a = n;

    Vector2 expected = -n;
    Vector2 actual = Vector2.Reflect(a, n);
    Assert.True(MathHelper.Equal(expected, actual), "Vector2f.Reflect did not return the expected value.");
}

// A test for Reflect (Vector2f, Vector2f)
// Reflection when normal and source are negation
[Fact]
public void Vector2ReflectTest2()
{
    Vector2 n = new Vector2(0.45f, 1.28f);
    n = Vector2.Normalize(n);
    Vector2 a = -n;

    Vector2 expected = n;
    Vector2 actual = Vector2.Reflect(a, n);
    Assert.True(MathHelper.Equal(expected, actual), "Vector2f.Reflect did not return the expected value.");
}

[Fact]
public void Vector2AbsTest()
{
    Vector2 v1 = new Vector2(-2.5f, 2.0f);
    Vector2 v3 = Vector2.Abs(new Vector2(0.0f, Single.NegativeInfinity));
    Vector2 v = Vector2.Abs(v1);
    Assert.Equal(2.5f, v.X);
    Assert.Equal(2.0f, v.Y);
    Assert.Equal(0.0f, v3.X);
    Assert.Equal(Single.PositiveInfinity, v3.Y);
}

[Fact]
public void Vector2SqrtTest()
{
    Vector2 v1 = new Vector2(-2.5f, 2.0f);
    Vector2 v2 = new Vector2(5.5f, 4.5f);
    Assert.Equal(2, (int)Vector2.SquareRoot(v2).X);
    Assert.Equal(2, (int)Vector2.SquareRoot(v2).Y);
    Assert.Equal(Single.NaN, Vector2.SquareRoot(v1).X);
}

// A test to make sure these types are blittable directly into GPU buffer memory layouts
[Fact]
public unsafe void Vector2SizeofTest()
{
    Assert.Equal(8, sizeof(Vector2));
    Assert.Equal(16, sizeof(Vector2_2x));
    Assert.Equal(12, sizeof(Vector2PlusFloat));
    Assert.Equal(24, sizeof(Vector2PlusFloat_2x));
}

[StructLayout(LayoutKind.Sequential)]
struct Vector2_2x
{
private Vector2 _a;
private Vector2 _b;
}

[StructLayout(LayoutKind.Sequential)]
struct Vector2PlusFloat
{
private Vector2 _v;
private float _f;
}

[StructLayout(LayoutKind.Sequential)]
struct Vector2PlusFloat_2x
{
private Vector2PlusFloat _a;
private Vector2PlusFloat _b;
}

[Fact]
public void SetFieldsTest()
{
    Vector2 v3 = new Vector2(4f, 5f);
    v3.X = 1.0f;
    v3.Y = 2.0f;
    Assert.Equal(1.0f, v3.X);
    Assert.Equal(2.0f, v3.Y);
    Vector2 v4 = v3;
    v4.Y = 0.5f;
    Assert.Equal(1.0f, v4.X);
    Assert.Equal(0.5f, v4.Y);
    Assert.Equal(2.0f, v3.Y);
}

[Fact]
public void EmbeddedVectorSetFields()
{
    EmbeddedVectorObject evo = new EmbeddedVectorObject();
    evo.FieldVector.X = 5.0f;
    evo.FieldVector.Y = 5.0f;
    Assert.Equal(5.0f, evo.FieldVector.X);
    Assert.Equal(5.0f, evo.FieldVector.Y);
}

private class EmbeddedVectorObject
{
public Vector2 FieldVector;
}
*/