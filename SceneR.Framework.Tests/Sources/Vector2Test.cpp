// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Vector2Test.hpp>

#include <System/Math.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Matrix.hpp>

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

    auto expected = Math::sqrt(8.0f);
    auto actual   = Vector2::Distance(a, b);

    EXPECT_TRUE(expected == actual);
}

// A test for Distance (Vector2f, Vector2f)
// Distance from the same point
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Distance2)
{
    auto a = Vector2 { 1.051f, 2.05f };
    auto b = Vector2 { 1.051f, 2.05f };

    auto actual = Vector2::Distance(a, b);

    EXPECT_TRUE(0.0f == actual);
}

// A test for DistanceSquared (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, DistanceSquared)
{
    auto a = Vector2 { 1.0f, 2.0f };
    auto b = Vector2 { 3.0f, 4.0f };

    auto expected = 8.0f;
    auto actual   = Vector2::DistanceSquared(a, b);

    EXPECT_TRUE(expected == actual);
}

// A test for Dot (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Dot)
{
    auto a = Vector2 { 1.0f, 2.0f };
    auto b = Vector2 { 3.0f, 4.0f };

    auto expected = 11.0f;
    auto actual   = Vector2::DotProduct(a, b);

    EXPECT_TRUE(expected == actual);
}

// A test for Dot (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, DotWithPerpendicularVector)
{
    auto a = Vector2 { 1.55f, 1.55f };
    auto b = Vector2 { -1.55f, 1.55f };

    auto expected = 0.0f;
    auto actual   = Vector2::DotProduct(a, b);

    EXPECT_TRUE(expected == actual);
}

// A test for Dot (Vector2f, Vector2f)
// Dot test with special float values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, DotWithSpecialFloatValues)
{
    auto a = Vector2 { Math::min_value, Math::min_value};
    auto b = Vector2 { Math::max_value, Math::max_value};

    auto actual = Vector2::DotProduct(a, b);

    EXPECT_TRUE(Math::is_negative_infinity(actual));
}

// A test for Length ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Length2)
{
    auto a      = Vector2 { 2.0f, 4.0f };
    auto target = a;

    auto expected = Math::sqrt(20.0f);
    auto actual   = target.Length();

    EXPECT_TRUE(expected == actual);
}

// A test for Length ()
// Length test where length is zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, ZeroLength)
{
    auto target = Vector2 { 0.0f, 0.0f };

    auto expected = 0.0f;
    auto actual   = target.Length();

    EXPECT_TRUE(expected == actual);
}

// A test for LengthSquared ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, LengthSquared1)
{
    auto a      = Vector2 { 2.0f, 4.0f };
    auto target = a;

    auto expected = 20.0f;
    auto actual   = target.LengthSquared();

    EXPECT_TRUE(expected == actual);
}

// A test for LengthSquared ()
// LengthSquared test where the result is zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, ZeroLengthSquared)
{
    auto a = Vector2 { 0.0f, 0.0f };

    auto expected = 0.0f;
    auto actual   = a.LengthSquared();

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

// A test for clamp (Vector2f, Vector2f, Vector2f)
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
    auto t = 0.5f;

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
    auto t = 0.0f;

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
    auto t = 1.0f;

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
    auto t = 2.0f;

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
    auto t = -2.0f;

    auto expected = -(b * 2.0f);
    auto actual   = Vector2::Lerp(a, b, t);

    EXPECT_TRUE(expected == actual);
}

// A test for Lerp (Vector2f, Vector2f, float)
// Lerp test with special float value
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, LerpWithSpecialFloatValue)
{
    auto a = Vector2 { 45.67f, 90.0f };
    auto b = Vector2 { Math::positive_infinity, Math::negative_infinity};
    auto t = 0.408f;

    auto actual = Vector2::Lerp(a, b, t);

    EXPECT_TRUE(Math::is_positive_infinity(actual.X()));
    EXPECT_TRUE(Math::is_negative_infinity(actual.Y()));
}

// A test for Lerp (Vector2f, Vector2f, float)
// Lerp test from the same point
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, LerpFromSamePoint)
{
    auto a = Vector2 { 1.0f, 2.0f };
    auto b = Vector2 { 1.0f, 2.0f };
    auto t = 0.5f;

    auto expected = Vector2 { 1.0f, 2.0f };
    auto actual   = Vector2::Lerp(a, b, t);

    EXPECT_TRUE(expected == actual);
}

// A test for Transform(Vector2f, Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Transform)
{
    auto v = Vector2 { 1.0f, 2.0f };
    auto m = Matrix::CreateRotationX(Math::to_radians(30.0f))
           * Matrix::CreateRotationY(Math::to_radians(30.0f))
           * Matrix::CreateRotationZ(Math::to_radians(30.0f));

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
    auto m = Matrix::CreateRotationX(Math::to_radians(30.0f))
           * Matrix::CreateRotationY(Math::to_radians(30.0f))
           * Matrix::CreateRotationZ(Math::to_radians(30.0f));

    m.M41(10.0f);
    m.M42(20.0f);
    m.M43(30.0f);

    auto expected = Vector2 { 0.3169873f, 2.18301272f };
    auto actual   = Vector2::TransformNormal(v, m);

    EXPECT_TRUE(expected == actual);
}

// A test for Normalize (Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Normalize)
{
    auto a        = Vector2 { 2.0f, 3.0f };
    auto expected = Vector2 { 0.554700196225229122018341733457f, 0.8320502943378436830275126001855f };
    auto actual   = Vector2::Normalize(a);

    EXPECT_TRUE(expected == actual);
};

// A test for Normalize (Vector2f)
// Normalize zero length vector
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, NormalizeZeroLengthVector)
{
    Vector2 a; // no parameter, default to 0.0f
    Vector2 actual = Vector2::Normalize(a);

    EXPECT_TRUE(Math::is_nan(actual.X()) && Math::is_nan(actual.Y()));
}

// A test for Normalize (Vector2f)
// Normalize infinite length vector
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, NormalizeInfiniteLengthVector)
{
    auto a        = Vector2 { Math::max_value, Math::max_value};
    auto actual   = Vector2::Normalize(a);
    auto expected = Vector2 { 0, 0 };

    EXPECT_TRUE(expected == actual);
}

// A test for operator - (Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, UnaryNegation)
{
    auto a        = Vector2 { 1.0f, 2.0f };
    auto expected = Vector2 { -1.0f, -2.0f };
    auto actual   = -a;

    EXPECT_TRUE(expected == actual);
}

// A test for operator - (Vector2f)
// negate test with special float value
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, UnaryNegationWithInfinityValues)
{
    auto a      = Vector2 { Math::positive_infinity, Math::negative_infinity};
    auto actual = -a;

    EXPECT_TRUE(Math::is_negative_infinity(actual.X()));
    EXPECT_TRUE(Math::is_positive_infinity(actual.Y()));
}

// A test for operator - (Vector2f)
// negate test with special float value
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, UnaryNegationWithNanValue)
{
    auto a      = Vector2 { Math::nan, 0.0f };
    auto actual = -a;

    EXPECT_TRUE(Math::is_nan(actual.X()));
    EXPECT_TRUE(0.0f == actual.Y());
}

// A test for operator - (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Subtraction)
{
    auto a        = Vector2 { 1.0f, 3.0f };
    auto b        = Vector2 { 2.0f, 1.5f };
    auto expected = Vector2 { -1.0f, 1.5f };
    auto actual   = a - b;

    EXPECT_TRUE(expected == actual);
}

// A test for operator * (Vector2f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Multiply)
{
    auto a        = Vector2 { 2.0f, 3.0f };
    auto factor   = 2.0f;
    auto expected = Vector2 { 4.0f, 6.0f };
    auto actual   = a * factor;

    EXPECT_TRUE(expected == actual);
}

// A test for operator * (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Multiply1)
{
    auto a        = Vector2 { 2.0f, 3.0f };
    auto b        = Vector2 { 4.0f, 5.0f };
    auto expected = Vector2 { 8.0f, 15.0f };
    auto actual   = a * b;

    EXPECT_TRUE(expected == actual);
}

// A test for operator / (Vector2f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Division)
{
    auto a        = Vector2 { 2.0f, 3.0f };
    auto div      = 2.0f;
    auto expected = Vector2 { 1.0f, 1.5f };
    auto actual   = a / div;

    EXPECT_TRUE(expected == actual);
}

// A test for operator / (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Division1)
{
    auto a        = Vector2 { 2.0f, 3.0f };
    auto b        = Vector2 { 4.0f, 5.0f };
    auto expected = Vector2 { 2.0f / 4.0f, 3.0f / 5.0f };
    auto actual   = a / b;

    EXPECT_TRUE(expected == actual);
}

// A test for operator / (Vector2f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Division2)
{
    auto a      = Vector2 { -2.0f, 3.0f };
    auto div    = 0.0f;
    auto actual = a / div;

    EXPECT_TRUE(Math::is_negative_infinity(actual.X()));
    EXPECT_TRUE(Math::is_positive_infinity(actual.Y()));
}

// A test for operator / (Vector2f, Vector2f)
// Divide by zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, DivisionByZero)
{
    auto a      = Vector2 { 0.047f, -3.0f };
    auto b      = Vector2 { };
    auto actual = a / b;

    EXPECT_TRUE(Math::is_positive_infinity(actual.X()));
    EXPECT_TRUE(Math::is_negative_infinity(actual.Y()));
}

// A test for operator + (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Addition)
{
    auto a        = Vector2 { 1.0f, 2.0f };
    auto b        = Vector2 { 3.0f, 4.0f };
    auto expected = Vector2 { 4.0f, 6.0f };
    auto actual   = a + b;

    EXPECT_TRUE(expected == actual);
}

// A test for Vector2f (float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Constructor)
{
    auto x      = 1.0f;
    auto y      = 2.0f;
    auto target = Vector2 { x, y };

    EXPECT_TRUE(x == target.X());
    EXPECT_TRUE(y == target.Y());
}

// A test for Vector2f ()
// Constructor with no parameter
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, DefaultConstructor)
{
    auto target = Vector2 { };

    EXPECT_TRUE(0.0f == target.X());
    EXPECT_TRUE(0.0f == target.Y());
}

// A test for Vector2f (float, float)
// Constructor with special floating values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, ConstructorWithSpecialValues)
{
    auto target = Vector2 { Math::nan, Math::max_value};

    EXPECT_TRUE(Math::is_nan(target.X()));
    EXPECT_TRUE(Math::max_value == target.Y());
}

// A test for Vector2f (float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Constructor4)
{
    auto value    = 1.0f;
    auto target   = Vector2 { value };
    auto expected = Vector2 { value, value };

    EXPECT_TRUE(expected == target);

    value    = 2.0f;
    target   = Vector2 { value };
    expected = Vector2 { value, value };

    EXPECT_TRUE(expected == target);
}

// A test for negate (Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Negate)
{
    auto a        = Vector2 { 1.0f, 2.0f };
    auto expected = Vector2 { -1.0f, -2.0f };
    auto actual   = Vector2::Negate(a);

    EXPECT_TRUE(expected == actual);
}

// A test for operator != (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Inequality)
{
    auto a = Vector2 { 1.0f, 2.0f };
    auto b = Vector2 { 1.0f, 2.0f };

    // case 1: compare between same values
    bool expected = false;
    bool actual   = a != b;

    EXPECT_TRUE(expected == actual);

    // case 2: compare between different values
    b        = Vector2 { 10.0f, 2.0f };
    expected = true;
    actual   = a != b;

    EXPECT_TRUE(expected == actual);
}

// A test for operator == (Vector2f, Vector2f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Equality)
{
    auto a = Vector2 { 1.0f, 2.0f };
    auto b = Vector2 { 1.0f, 2.0f };

    // case 1: compare between same values
    bool expected = true;
    bool actual   = a == b;

    EXPECT_TRUE(expected == actual);

    // case 2: compare between different values
    b        = Vector2 { 10.0f, 2.0f };
    expected = false;
    actual   = a == b;

    EXPECT_TRUE(expected == actual);
}

// A test for UnitX
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, UnitX)
{
    auto actual = Vector2 { 1.0f, 0.0f };

    EXPECT_TRUE(Vector2::UnitX == actual);
}

// A test for UnitY
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, UnitY)
{
    auto actual = Vector2 { 0.0f, 1.0f };

    EXPECT_TRUE(Vector2::UnitY == actual);
}

// A test for One
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, One)
{
    auto actual = Vector2 { 1.0f, 1.0f };

    EXPECT_TRUE(Vector2::One == actual);
}

// A test for Zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Zero)
{
    auto actual = Vector2 { 0.0f, 0.0f };

    EXPECT_TRUE(Vector2::Zero == actual);
}

// A test for Vector2f comparison involving NaN values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Equals)
{
    auto a = Vector2 { Math::nan, 0.0f };
    auto b = Vector2 { 0, Math::nan};

    EXPECT_FALSE(a == Vector2::Zero);
    EXPECT_FALSE(b == Vector2::Zero);

    EXPECT_TRUE(a != Vector2::Zero);
    EXPECT_TRUE(b != Vector2::Zero);
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Abs)
{
    auto v1 = Vector2 { -2.5f, 2.0f };
    auto v3 = Vector2::Abs(Vector2 { 0.0f, Math::negative_infinity});
    auto v  = Vector2::Abs(v1);

    EXPECT_TRUE(2.5f == v.X());
    EXPECT_TRUE(2.0f == v.Y());
    EXPECT_TRUE(0.0f == v3.X());
    EXPECT_TRUE(Math::positive_infinity == v3.Y());
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, Sqrt)
{
    auto v1 = Vector2 { -2.5f, 2.0f };
    auto v2 = Vector2 { 5.5f, 4.5f };

    EXPECT_TRUE(2 == (std::int32_t)Vector2::SquareRoot(v2).X());
    EXPECT_TRUE(2 == (std::int32_t)Vector2::SquareRoot(v2).Y());
    EXPECT_TRUE(Math::is_nan(Vector2::SquareRoot(v1).X()));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector2Test, SetFields)
{
//    Vector2 v3 = new Vector2(4f, 5f);
//    v3.X = 1.0f;
//    v3.Y = 2.0f;
//    Assert.equal(1.0f, v3.X);
//    Assert.equal(2.0f, v3.Y);
//    Vector2 v4 = v3;
//    v4.Y = 0.5f;
//    Assert.equal(1.0f, v4.X);
//    Assert.equal(0.5f, v4.Y);
//    Assert.equal(2.0f, v3.Y);
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

// A test for Reflect (Vector2f, Vector2f)
[Fact]
public void Vector2ReflectTest()
{
    Vector2 a = Vector2.Normalize(new Vector2(1.0f, 1.0f));

    // Reflect on XZ plane.
    Vector2 n = new Vector2(0.0f, 1.0f);
    Vector2 expected = new Vector2(a.X, -a.Y);
    Vector2 actual = Vector2.Reflect(a, n);
    Assert.True(MathHelper.equal(expected, actual), "Vector2f.Reflect did not return the expected value.");

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
*/
