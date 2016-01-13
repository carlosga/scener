// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "Vector3Test.hpp"

#include "EqualityHelper.hpp"

#include <SceneR/Math/Math.hpp>
#include <SceneR/Math/Matrix.hpp>
#include <SceneR/Math/Vector2.hpp>
#include <SceneR/Math/Vector3.hpp>

using namespace SceneR::Math;

TEST_F(Vector3Test, DefaultConstructor)
{
    auto vector = Vector3 { };

    // vector3 is equal to (0.0, 0.0, 0.0)
    EXPECT_TRUE(0.0f == vector.x);
    EXPECT_TRUE(0.0f == vector.y);
    EXPECT_TRUE(0.0f == vector.z);
}

TEST_F(Vector3Test, IndividualCoordinatesConstructor)
{
    float x = 20.0f;
    float y = 30.0f;
    float z = 40.0f;

    auto vector3 = Vector3 { x, y, z };

    // vector3 is equal to (20.0, 30.0, 40.0)
    EXPECT_TRUE(x == vector3.x);
    EXPECT_TRUE(y == vector3.y);
    EXPECT_TRUE(z == vector3.z);
}

TEST_F(Vector3Test, CopyConstructor)
{
    float x = 20.0f;
    float y = 30.0f;
    float z = 40.0f;

    auto vector  = Vector3 { x, y, z };
    auto vector3 = Vector3 { vector };

    // vector3 is equal to (20.0, 30.0, 40.0)
    EXPECT_TRUE(x == vector3.x);
    EXPECT_TRUE(y == vector3.y);
    EXPECT_TRUE(z == vector3.z);
}

TEST_F(Vector3Test, Indexer)
{
    float x = 20.0f;
    float y = 30.0f;
    float z = 40.0f;

    auto vector = Vector3 { x, y, z };

    // vector3 is equal to (20.0, 30.0, 40.0)
    EXPECT_TRUE(x == vector[0]);
    EXPECT_TRUE(y == vector[1]);
    EXPECT_TRUE(z == vector[2]);
}

TEST_F(Vector3Test, XCoordinateValue)
{
    const float x = 20.0f;
    const float y = 30.0f;
    const float z = 40.0f;

    auto vector = Vector3 { x, y, z };

    // vector3 is equal to (20.0, 30.0, 40.0)
    EXPECT_TRUE(x == vector.x);
}

TEST_F(Vector3Test, YCoordinateValue)
{
    const float x = 20.0f;
    const float y = 30.0f;
    const float z = 40.0f;

    auto vector = Vector3 { x, y, z };

    // vector3 is equal to (20.0, 30.0, 40.0)
    EXPECT_TRUE(y == vector.y);
}

TEST_F(Vector3Test, ZCoordinateValue)
{
    float x = 20.0f;
    float y = 30.0f;
    float z = 40.0f;

    auto vector = Vector3 { x, y, z };

    // vector3 is equal to (20.0, 30.0, 40.0)
    EXPECT_TRUE(z == vector.z);
}

TEST_F(Vector3Test, Length)
{
    auto vector = Vector3 { 20.0f, 30.0f, 40.0f };

    // length is approximately equal to 53.8516
    EXPECT_TRUE(53.8516464f == vector.length());
}

TEST_F(Vector3Test, LengthSquared)
{
    auto vector = Vector3 { 20.0f, 30.0f, 40.0f };

    // length is approximately equal to 2900
    EXPECT_TRUE(2900.0f == vector.length_squared());
}

TEST_F(Vector3Test, Negation)
{
    auto actual = Vector3::negate({ 20.0f, 30.0f, 40.0f });

    // vector Result is equal to (-20, -30, -40)
    EXPECT_TRUE(-20.0f == actual.x);
    EXPECT_TRUE(-30.0f == actual.y);
    EXPECT_TRUE(-40.0f == actual.z);
}

TEST_F(Vector3Test, Normalization)
{
    auto actual = Vector3::normalize({ 20.0f, 30.0f, 40.0f });

    // vector Result is equal to (0.37139, 0.55709, 0.74278)
    EXPECT_TRUE(0.3713907f   == actual.x);
    EXPECT_TRUE(0.557086051f == actual.y);
    EXPECT_TRUE(0.742781401f == actual.z);
}

TEST_F(Vector3Test, Cross)
{
    auto crossProduct = Vector3::cross({ 20.0f, 30.0f, 40.0f }, { 45.0f, 70.0f, 80.0f });

    // crossProduct is equal to (-400, 200, 50)
    EXPECT_TRUE(-400.0f == crossProduct.x);
    EXPECT_TRUE(200.0f  == crossProduct.y);
    EXPECT_TRUE(50.0f   == crossProduct.z);
}

TEST_F(Vector3Test, DotProduct)
{
    auto dotProduct = Vector3::dot({20.0f, 30.0f, 40.0f} , { 45.0f, 70.0f, 80.0f });

    EXPECT_TRUE(6200.0f == dotProduct);
}

TEST_F(Vector3Test, AngleBetween)
{
    auto angle = Vector3::angle_between({ 20.0f, 30.0f, 40.0f }, { 45.0f, 70.0f, 80.0f });

    // angleBetween is approximately equal to 4.15128803
    EXPECT_TRUE(0.0724536479f == angle.value());
}

TEST_F(Vector3Test, Addition)
{
    auto vector1 = Vector3 { 20.0f, 30.0f, 40.0f };
    auto vector2 = Vector3 { 45.0f, 70.0f, 80.0f };
    auto result  = vector1 + vector2;

    // vectorResult is equal to (65, 100, 120)
    EXPECT_TRUE(65.0f  == result.x);
    EXPECT_TRUE(100.0f == result.y);
    EXPECT_TRUE(120.0f == result.z);
}

TEST_F(Vector3Test, Subtraction)
{
    auto vector1 = Vector3 { 20.0f, 30.0f, 40.0f };
    auto vector2 = Vector3 { 45.0f, 70.0f, 80.0f };
    auto result  = vector1 - vector2;

    // vector Result is equal to (-25, -40, -40)
    EXPECT_TRUE(-25.0f == result.x);
    EXPECT_TRUE(-40.0f == result.y);
    EXPECT_TRUE(-40.0f == result.z);
}

TEST_F(Vector3Test, Multiplication)
{
    auto vector1 = Vector3 { 20.0f, 30.0f, 40.0f };
    auto vector2 = Vector3 { 45.0f, 70.0f, 80.0f };
    auto result  = vector1 * vector2;

    // vector Result is equal to (800, 2100, 3200)
    EXPECT_TRUE(900.0f  == result.x);
    EXPECT_TRUE(2100.0f == result.y);
    EXPECT_TRUE(3200.0f == result.z);
}

TEST_F(Vector3Test, ScalarMultiplication)
{
    auto vector = Vector3 { 20.0f, 30.0f, 40.0f };
    auto result = vector * 75.0f;

    // vector Result is equal to (1500, 2250, 3000)
    EXPECT_TRUE(1500.0f == result.x);
    EXPECT_TRUE(2250.0f == result.y);
    EXPECT_TRUE(3000.0f == result.z);
}

TEST_F(Vector3Test, AdditionAssignment)
{
    auto vector1 = Vector3 { 20.0f, 30.0f, 40.0f };
    auto vector2 = Vector3 { 45.0f, 70.0f, 80.0f };

    vector2 += vector1;

    // vector Result is equal to (65, 100, 120)
    EXPECT_TRUE(65.0f  == vector2.x);
    EXPECT_TRUE(100.0f == vector2.y);
    EXPECT_TRUE(120.0f == vector2.z);
}

TEST_F(Vector3Test, SubtractionAssignment)
{
    auto vector1 = Vector3 { 20.0f, 30.0f, 40.0f };
    auto vector2 = Vector3 { 45.0f, 70.0f, 80.0f };

    vector2 -= vector1;

    // vector Result is equal to (25, 40, 40)
    EXPECT_TRUE(25.0f == vector2.x);
    EXPECT_TRUE(40.0f == vector2.y);
    EXPECT_TRUE(40.0f == vector2.z);
}

TEST_F(Vector3Test, MultplicationAssignment)
{
    auto vector1 = Vector3 { 20.0f, 30.0f, 40.0f };
    auto vector2 = Vector3 { 45.0f, 70.0f, 80.0f };

    vector2 *= vector1;

    // vector Result is equal to (800, 2100, 3200)
    EXPECT_TRUE(900.0f  == vector2.x);
    EXPECT_TRUE(2100.0f == vector2.y);
    EXPECT_TRUE(3200.0f == vector2.z);
}

TEST_F(Vector3Test, ScalarMultplicationAssignment)
{
    auto vector = Vector3 { 20.0f, 30.0f, 40.0f };

    vector *= 75.0f;

    // vector Result is equal to (1500, 2250, 3000)
    EXPECT_TRUE(1500.0f == vector.x);
    EXPECT_TRUE(2250.0f == vector.y);
    EXPECT_TRUE(3000.0f == vector.z);
}

TEST_F(Vector3Test, MatrixMultiplication)
{
    auto vector = Vector3 { 20.0f, 30.0f, 40.0f };
    auto matrix = Matrix  { 10.0f, 10.0f, 10.0f, 0.0f
                          , 20.0f, 20.0f, 20.0f, 0.0f
                          , 30.0f, 30.0f, 30.0f, 0.0f
                          , 5.0f , 10.0f, 15.0f, 1.0f };

    auto vectorResult = (vector * matrix);

    // vector Result is equal to (2005, 2010, 2015)
    EXPECT_TRUE(2005.0f == vectorResult.x);
    EXPECT_TRUE(2010.0f == vectorResult.y);
    EXPECT_TRUE(2015.0f == vectorResult.z);
}

TEST_F(Vector3Test, Transform)
{
    auto vector = Vector3 { 20.0f, 30.0f, 40.0f };
    auto matrix = Matrix  { 10.0f, 10.0f, 10.0f, 0.0f
                          , 20.0f, 20.0f, 20.0f, 0.0f
                          , 30.0f, 30.0f, 30.0f, 0.0f
                          , 5.0f , 10.0f, 15.0f, 1.0f };

    auto result = Vector3::transform(vector, matrix);

    // vector Result is equal to (2005, 2010, 2015)
    EXPECT_TRUE(2005.0f == result.x);
    EXPECT_TRUE(2010.0f == result.y);
    EXPECT_TRUE(2015.0f == result.z);
}

TEST_F(Vector3Test, TransformNormal)
{
    auto vector = Vector3 { 20.0f, 30.0f, 40.0f };
    auto matrix = Matrix  { 10.0f, 10.0f, 10.0f, 0.0f
                          , 20.0f, 20.0f, 20.0f, 0.0f
                          , 30.0f, 30.0f, 30.0f, 0.0f
                          , 5.0f , 10.0f, 15.0f, 1.0f };

    auto result = Vector3::transform_normal(vector, matrix);

    // vector Result is equal to (2000, 2000, 2000)
    EXPECT_TRUE(2000.0f == result.x);
    EXPECT_TRUE(2000.0f == result.y);
    EXPECT_TRUE(2000.0f == result.z);
}

TEST_F(Vector3Test, Lerp)
{
    auto vector1 = Vector3 { 5.0f, 10.0f, 50.0f };
    auto vector2 = Vector3 { 0.0f, -20.0f, 100.0f };
    auto result  = Vector3::lerp(vector1, vector2, 0.4f);

    EXPECT_TRUE(3.0f  == result.x);
    EXPECT_TRUE(-2.0f == result.y);
    EXPECT_TRUE(70.0f == result.z);
}

// A test for Cross (Vector3f, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Cross1)
{
    auto a        = Vector3 { 1.0f, 0.0f, 0.0f };
    auto b        = Vector3 { 0.0f, 1.0f, 0.0f };
    auto expected = Vector3 { 0.0f, 0.0f, 1.0f };
    auto actual   = Vector3::cross(a, b);

    EXPECT_TRUE(expected == actual);
}

// A test for Cross (Vector3f, Vector3f)
// Cross test of the same vector
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, CrossWithSameVector)
{
    auto a        = Vector3 { 0.0f, 1.0f, 0.0f };
    auto b        = Vector3 { 0.0f, 1.0f, 0.0f };
    auto expected = Vector3 { 0.0f, 0.0f, 0.0f };
    auto actual   = Vector3::cross(a, b);

    EXPECT_TRUE(expected == actual);
}

// A test for Distance (Vector3f, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Distance)
{
    auto a = Vector3 { 1.0f, 2.0f, 3.0f };
    auto b = Vector3 { 4.0f, 5.0f, 6.0f };

    auto expected = std::sqrt(27.0f);
    auto actual   = Vector3::distance(a, b);

    EXPECT_TRUE(expected == actual);
}

// A test for Distance (Vector3f, Vector3f)
// Distance from the same point
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, DistanceFromTheSamePoint)
{
    auto a = Vector3 { 1.051f, 2.05f, 3.478f };
    auto b = Vector3 { Vector2 { 1.051f, 0.0f }, 1.0f };

    b.y = 2.05f;
    b.z = 3.478f;

    auto actual = Vector3::distance(a, b);

    EXPECT_TRUE(0.0f == actual);
}

// A test for DistanceSquared (Vector3f, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, DistanceSquared)
{
    auto a = Vector3 { 1.0f, 2.0f, 3.0f };
    auto b = Vector3 { 4.0f, 5.0f, 6.0f };

    auto expected = 27.0f;
    auto actual   = Vector3::distance_squared(a, b);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Dot (Vector3f, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Dot)
{
    auto a = Vector3 { 1.0f, 2.0f, 3.0f };
    auto b = Vector3 { 4.0f, 5.0f, 6.0f };

    auto expected = 32.0f;
    auto actual   = Vector3::dot(a, b);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Dot (Vector3f, Vector3f)
// Dot test for perpendicular vector
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, DotForPerpendicularVector)
{
    auto a = Vector3 { 1.55f, 1.55f, 1 };
    auto b = Vector3 { 2.5f, 3, 1.5f };
    auto c = Vector3::cross(a, b);

    auto expected = 0.0f;
    auto actual1  = Vector3::dot(a, c);
    auto actual2  = Vector3::dot(b, c);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual1));
    EXPECT_TRUE(EqualityHelper::Equal(expected, actual2));
}

// A test for Length ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Length2)
{
    auto a        = Vector2 { 1.0f, 2.0f };
    auto z        = 3.0f;
    auto target   = Vector3 { a, z };
    auto expected = std::sqrt(14.0f);
    auto actual   = target.length();

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Length ()
// Length test where length is zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, LengthZero)
{
    Vector3 target;
    auto    expected = 0.0f;
    auto    actual   = target.length();

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for LengthSquared ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, LengthSquared2)
{
    auto a        = Vector2 { 1.0f, 2.0f };
    auto z        = 3.0f;
    auto target   = Vector3 { a, z };
    auto expected = 14.0f;
    auto actual   = target.length_squared();

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Min (Vector3f, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Min)
{
    auto a        = Vector3 { -1.0f, 4.0f, -3.0f };
    auto b        = Vector3 { 2.0f , 1.0f, -1.0f };
    auto expected = Vector3 { -1.0f, 1.0f, -3.0f };
    auto actual   = Vector3::min(a, b);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Max (Vector3f, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Max)
{
    auto a        = Vector3 { -1.0f, 4.0f, -3.0f };
    auto b        = Vector3 { 2.0f , 1.0f, -1.0f };
    auto expected = Vector3 { 2.0f , 4.0f, -1.0f };
    auto actual   = Vector3::max(a, b);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, MinMaxCodeCoverage)
{
    auto    min = Vector3::zero;
    auto    max = Vector3::one;
    Vector3 actual;

    // Min.
    actual = Vector3::min(min, max);

    EXPECT_TRUE(actual == min);

    actual = Vector3::min(max, min);

    EXPECT_TRUE(actual == min);

    // Max.
    actual = Vector3::max(min, max);

    EXPECT_TRUE(actual == max);

    actual = Vector3::max(max, min);

    EXPECT_TRUE(actual == max);
}

// A test for Lerp (Vector3f, Vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Lerp1)
{
    auto a = Vector3 { 1.0f, 2.0f, 3.0f };
    auto b = Vector3 { 4.0f, 5.0f, 6.0f };
    auto t = 0.5f;

    auto expected = Vector3 { 2.5f, 3.5f, 4.5f };
    auto actual   = Vector3::lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Vector3f, Vector3f, float)
// Lerp test with factor zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, LerpWithFactorZero)
{
    auto a = Vector3 { 1.0f, 2.0f, 3.0f };
    auto b = Vector3 { 4.0f, 5.0f, 6.0f };
    auto t = 0.0f;

    auto expected = Vector3 { 1.0f, 2.0f, 3.0f };
    auto actual   = Vector3::lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Vector3f, Vector3f, float)
// Lerp test with factor one
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, LerpWithFactorOne)
{
    auto a = Vector3 { 1.0f, 2.0f, 3.0f };
    auto b = Vector3 { 4.0f, 5.0f, 6.0f };
    auto t = 1.0f;

    auto expected = Vector3 { 4.0f, 5.0f, 6.0f };
    auto actual   = Vector3::lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Vector3f, Vector3f, float)
// Lerp test with factor > 1
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, LerpWithFactorGreaterThanOne)
{
    auto a = Vector3 { 0.0f, 0.0f, 0.0f };
    auto b = Vector3 { 4.0f, 5.0f, 6.0f };
    auto t = 2.0f;

    auto expected = Vector3 { 8.0f, 10.0f, 12.0f };
    auto actual   = Vector3::lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Vector3f, Vector3f, float)
// Lerp test with factor < 0
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, LerpWithFactorLessThanZero)
{
    auto a = Vector3 { 0.0f, 0.0f, 0.0f };
    auto b = Vector3 { 4.0f, 5.0f, 6.0f };
    auto t = -2.0f;

    auto expected = Vector3 { -8.0f, -10.0f, -12.0f };
    auto actual   = Vector3::lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Vector3f, Vector3f, float)
// Lerp test from the same point
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, LerpFromTheSamePoint)
{
    auto a = Vector3 { 1.68f, 2.34f, 5.43f };
    auto b = a;
    auto t = 0.18f;

    auto expected = Vector3 { 1.68f, 2.34f, 5.43f };
    auto actual   = Vector3::lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Reflect (Vector3f, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Reflect)
{
    auto a = Vector3::normalize({ 1.0f, 1.0f, 1.0f });

    // Reflect on XZ plane.
    auto n        = Vector3 { 0.0f, 1.0f, 0.0f };
    auto expected = Vector3 { a.x, -a.y, a.z };
    auto actual   = Vector3::reflect(a, n);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Reflect on XY plane.
    n        = Vector3 { 0.0f, 0.0f, 1.0f };
    expected = Vector3(a.x, a.y, -a.z);
    actual   = Vector3::reflect(a, n);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Reflect on YZ plane.
    n        = Vector3 { 1.0f, 0.0f, 0.0f };
    expected = Vector3 { -a.x, a.y, a.z };
    actual   = Vector3::reflect(a, n);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Reflect (Vector3f, Vector3f)
// Reflection when normal and source are the same
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, ReflectWhenNormalAndSourceAreTheSame)
{
    auto n = Vector3 { 0.45f, 1.28f, 0.86f };

    n = Vector3::normalize(n);

    auto a = n;

    auto expected = -n;
    auto actual   = Vector3::reflect(a, n);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Reflect (Vector3f, Vector3f)
// Reflection when normal and source are negation
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, ReflectWhenNormalAndSourceAreNegation)
{
    auto n = Vector3 { 0.45f, 1.28f, 0.86f };

    n = Vector3::normalize(n);

    auto a = -n;

    auto expected = n;
    auto actual   = Vector3::reflect(a, n);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Reflect (Vector3f, Vector3f)
// Reflection when normal and source are perpendicular (a dot n = 0)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, ReflectWhenNormalAndSourceArePerpendicular)
{
    auto n    = Vector3 { 0.45f, 1.28f, 0.86f };
    auto temp = Vector3 { 1.28f, 0.45f, 0.01f };

    // find a perpendicular vector of n
    auto a = Vector3::cross(temp, n);

    auto expected = a;
    auto actual   = Vector3::reflect(a, n);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform(Vector3f, Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Transform1)
{
    auto v = Vector3 { 1.0f, 2.0f, 3.0f };
    auto m = Matrix::create_rotation_x(SceneR::Math::to_radians(30.0f))
           * Matrix::create_rotation_y(SceneR::Math::to_radians(30.0f))
           * Matrix::create_rotation_z(SceneR::Math::to_radians(30.0f));

    m.m41 = 10.0f;
    m.m42 = 20.0f;
    m.m43 = 30.0f;

    auto expected = Vector3 { 12.191987f, 21.533493f, 32.616024f };
    auto actual   = Vector3::transform(v, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for clamp (Vector3f, Vector3f, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Clamp)
{
    auto a   = Vector3 { 0.5f, 0.3f, 0.33f };
    auto min = Vector3 { 0.0f, 0.1f, 0.13f };
    auto max = Vector3 { 1.0f, 1.1f, 1.13f };

    // Normal case.
    // Case N1: specfied value is in the range.
    auto expected = Vector3 { 0.5f, 0.3f, 0.33f };
    auto actual   = Vector3::clamp(a, min, max);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Normal case.
    // Case N2: specfied value is bigger than max value.
    a        = Vector3 { 2.0f, 3.0f, 4.0f };
    expected = max;
    actual   = Vector3::clamp(a, min, max);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Case N3: specfied value is smaller than max value.
    a        = Vector3 { -2.0f, -3.0f, -4.0f };
    expected = min;
    actual   = Vector3::clamp(a, min, max);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Case N4: combination case.
    a        = Vector3 {   -2.0f,  0.5f,    4.0f };
    expected = Vector3 { min.x, a.y, max.z };
    actual   = Vector3::clamp(a, min, max);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // User specfied min value is bigger than max value.
    max = Vector3 { 0.0f, 0.1f, 0.13f };
    min = Vector3 { 1.0f, 1.1f, 1.13f };

    // Case W1: specfied value is in the range.
    a        = Vector3 { 0.5f, 0.3f, 0.33f };
    expected = min;
    actual   = Vector3::clamp(a, min, max);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Normal case.
    // Case W2: specfied value is bigger than max and min value.
    a        = Vector3 { 2.0f, 3.0f, 4.0f };
    expected = min;
    actual   = Vector3::clamp(a, min, max);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Case W3: specfied value is smaller than min and max value.
    a        = Vector3 { -2.0f, -3.0f, -4.0f };
    expected = min;
    actual   = Vector3::clamp(a, min, max);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for TransformNormal (Vector3f, Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, TransformNormal1)
{
    auto v = Vector3 { 1.0f, 2.0f, 3.0f };
    auto m = Matrix::create_rotation_x(SceneR::Math::to_radians(30.0f))
           * Matrix::create_rotation_y(SceneR::Math::to_radians(30.0f))
           * Matrix::create_rotation_z(SceneR::Math::to_radians(30.0f));

    m.m41 = 10.0f;
    m.m42 = 20.0f;
    m.m43 = 30.0f;

    auto expected = Vector3 { 2.19198728f, 1.53349364f, 2.61602545f };
    auto actual   = Vector3::transform_normal(v, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector3f, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, TransformByQuaternion)
{
    auto v = Vector3 { 1.0f, 2.0f, 3.0f };
    auto m = Matrix::create_rotation_x(SceneR::Math::to_radians(30.0f))
           * Matrix::create_rotation_y(SceneR::Math::to_radians(30.0f))
           * Matrix::create_rotation_z(SceneR::Math::to_radians(30.0f));
    auto q = Quaternion::create_from_rotation_matrix(m);

    auto expected = Vector3::transform(v, m);
    auto actual   = Vector3::transform(v, q);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector3f, Quaternion)
// Transform vector3 with zero quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, TransformByZeroQuaternion)
{
    auto v        = Vector3 { 1.0f, 2.0f, 3.0f };
    auto q        = Quaternion {};
    auto expected = v;
    auto actual   = Vector3::transform(v, q);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Transform (Vector3f, Quaternion)
// Transform vector3 with identity quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, TransformByIdentityQuaternion)
{
    auto v        = Vector3 { 1.0f, 2.0f, 3.0f };
    auto q        = Quaternion::identity;
    auto expected = v;

    auto actual = Vector3::transform(v, q);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Normalize (Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Normalize)
{
    auto a        = Vector3 { 1.0f, 2.0f, 3.0f };
    auto expected = Vector3 { 0.26726124191242438468455348087975f
                            , 0.53452248382484876936910696175951f
                            , 0.80178372573727315405366044263926f };

    auto actual = Vector3::normalize(a);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Normalize (Vector3f)
// Normalize vector of length one
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, NormalizeVectorOfLengthOne)
{
    auto a = Vector3 { 1.0f, 0.0f, 0.0f };

    auto expected = Vector3 { 1.0f, 0.0f, 0.0f };
    auto actual   = Vector3::normalize(a);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Normalize (Vector3f)
// Normalize vector of length zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, NormalizeVectorOfLengthZero)
{
    auto a      = Vector3 { 0.0f, 0.0f, 0.0f };
    auto actual = Vector3::normalize(a);

    EXPECT_TRUE(SceneR::Math::is_nan(actual.x)
             && SceneR::Math::is_nan(actual.y)
             && SceneR::Math::is_nan(actual.z));
}

// A test for operator - (Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, UnaryNegation)
{
    auto a        = Vector3 {  1.0f,  2.0f,  3.0f };
    auto expected = Vector3 { -1.0f, -2.0f, -3.0f };
    auto actual   = -a;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, UnaryNegationWithSpecialValues)
{
    auto a = -Vector3 { SceneR::Math::nan, SceneR::Math::positive_infinity, SceneR::Math::negative_infinity};
    auto b = -Vector3 { 0.0f, 0.0f, 0.0f };

    EXPECT_TRUE(SceneR::Math::is_nan(a.x));
    EXPECT_TRUE(SceneR::Math::is_negative_infinity(a.y));
    EXPECT_TRUE(SceneR::Math::is_positive_infinity(a.z));
    EXPECT_TRUE(0.0f == b.x);
    EXPECT_TRUE(0.0f == b.y);
    EXPECT_TRUE(0.0f == b.z);
}

// A test for operator - (Vector3f, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Subtraction1)
{
    auto a        = Vector3 { 4.0f, 2.0f, 3.0f };
    auto b        = Vector3 { 1.0f, 5.0f, 7.0f };
    auto expected = Vector3 { 3.0f, -3.0f, -4.0f };
    auto actual   = a - b;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator * (Vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, ScalarMultiplyOperator)
{
    auto a        = Vector3 { 1.0f, 2.0f, 3.0f };
    auto factor   = 2.0f;
    auto expected = Vector3 { 2.0f, 4.0f, 6.0f };
    auto actual   = a * factor;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator * (Vector3f, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, VectorMultiplyOperator)
{
    auto a        = Vector3 { 1.0f,  2.0f,  3.0f };
    auto b        = Vector3 { 4.0f,  5.0f,  6.0f };
    auto expected = Vector3 { 4.0f, 10.0f, 18.0f };
    auto actual   = a * b;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator / (Vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, ScalarDivisionOperator)
{
    auto a        = Vector3 { 1.0f, 2.0f, 3.0f };
    auto div      = 2.0f;
    auto expected = Vector3 { 0.5f, 1.0f, 1.5f };
    auto actual   = a / div;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator / (Vector3f, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, VectorDivisionOperator)
{
    auto a        = Vector3 { 4.0f, 2.0f, 3.0f };
    auto b        = Vector3 { 1.0f, 5.0f, 6.0f };
    auto expected = Vector3 { 4.0f, 0.4f, 0.5f };
    auto actual   = a / b;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator / (Vector3f, float)
// Divide by zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, ScalarDivisionByZero)
{
    auto a      = Vector3 { -2.0f, 3.0f, SceneR::Math::max_value};
    auto div    = 0.0f;
    auto actual = a / div;

    EXPECT_TRUE(SceneR::Math::is_negative_infinity(actual.x));
    EXPECT_TRUE(SceneR::Math::is_positive_infinity(actual.y));
    EXPECT_TRUE(SceneR::Math::is_positive_infinity(actual.z));
}

// A test for operator / (Vector3f, Vector3f)
// Divide by zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, VectorDivisionByZero)
{
    auto a      = Vector3 { 0.047f, -3.0f, SceneR::Math::negative_infinity};
    auto b      = Vector3 { };
    auto actual = a / b;

    EXPECT_TRUE(SceneR::Math::is_positive_infinity(actual.x));
    EXPECT_TRUE(SceneR::Math::is_negative_infinity(actual.y));
    EXPECT_TRUE(SceneR::Math::is_negative_infinity(actual.z));
}

// A test for operator + (Vector3f, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Addition1)
{
    auto a = Vector3 { 1.0f, 2.0f, 3.0f };
    auto b = Vector3 { 4.0f, 5.0f, 6.0f };

    auto expected = Vector3 { 5.0f, 7.0f, 9.0f };
    auto actual   = a + b;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Vector3f (float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Constructor)
{
    auto x      = 1.0f;
    auto y      = 2.0f;
    auto z      = 3.0f;
    auto target = Vector3 { x, y, z };

    EXPECT_TRUE(EqualityHelper::Equal(target.x, x)
             && EqualityHelper::Equal(target.y, y)
             && EqualityHelper::Equal(target.z, z));
}

// A test for Vector3f (Vector2f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Constructor1)
{
    auto a      = Vector2 { 1.0f, 2.0f };
    auto z      = 3.0f;
    auto target = Vector3 { a, z };

    EXPECT_TRUE(EqualityHelper::Equal(target.x, a.x)
             && EqualityHelper::Equal(target.y, a.y)
             && EqualityHelper::Equal(target.z, z));
}

// A test for Vector3f ()
// Constructor with no parameter
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Constructor2)
{
    auto a = Vector3 { };

    EXPECT_TRUE(a.x == 0.0f);
    EXPECT_TRUE(a.y == 0.0f);
    EXPECT_TRUE(a.z == 0.0f);
}

// A test for Vector2f (float, float)
// Constructor with special floating values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, ConstructorWithSpecialFloatValues)
{
    auto target = Vector3 { SceneR::Math::nan
                          , SceneR::Math::max_value
                          , SceneR::Math::positive_infinity};

    EXPECT_TRUE(SceneR::Math::is_nan(target.x));
    EXPECT_TRUE(SceneR::Math::max_value == target.y);
    EXPECT_TRUE(SceneR::Math::is_positive_infinity(target.z));
}

// A test for negate (Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Negate)
{
    auto a        = Vector3 { 1.0f, 2.0f, 3.0f };
    auto expected = Vector3 { -1.0f, -2.0f, -3.0f };
    auto actual   = Vector3::negate(a);

    EXPECT_TRUE(expected == actual);
}

// A test for operator != (Vector3f, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Inequality)
{
    auto a = Vector3 { 1.0f, 2.0f, 3.0f };
    auto b = Vector3 { 1.0f, 2.0f, 3.0f };

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

// A test for operator == (Vector3f, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Equality)
{
    auto a = Vector3 { 1.0f, 2.0f, 3.0f };
    auto b = Vector3 { 1.0f, 2.0f, 3.0f };

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

// A test for One
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, VectorOne)
{
    auto val = Vector3 { 1.0f, 1.0f, 1.0f };

    EXPECT_TRUE(val == Vector3::one);
}

// A test for UnitX
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, UnitX)
{
    auto val = Vector3 { 1.0f, 0.0f, 0.0f };

    EXPECT_TRUE(val == Vector3::unit_x);
}

// A test for UnitY
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, UnitY)
{
    auto val = Vector3 { 0.0f, 1.0f, 0.0f };

    EXPECT_TRUE(val == Vector3::unit_y);
}

// A test for UnitZ
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, UnitZ)
{
    auto val = Vector3 { 0.0f, 0.0f, 1.0f };

    EXPECT_TRUE(val == Vector3::unit_z);
}

// A test for Zero
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, VectorZero)
{
    auto val = Vector3 { 0.0f, 0.0f, 0.0f };

    EXPECT_TRUE(val == Vector3::zero);
}

// A test for Vector3f (float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Constructor4)
{
    auto value    = 1.0f;
    auto target   = Vector3 { value };
    auto expected = Vector3 { value, value, value };

    EXPECT_TRUE(expected == target);

    value    = 2.0f;
    target   = Vector3 { value };
    expected = Vector3 { value, value, value };

    EXPECT_TRUE(expected == target);
}

// A test for Vector3f comparison involving NaN values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, EqualsNaN)
{
    auto a = Vector3 { SceneR::Math::nan, 0, 0 };
    auto b = Vector3 { 0, SceneR::Math::nan, 0 };
    auto c = Vector3 { 0, 0, SceneR::Math::nan};

    EXPECT_FALSE(a == Vector3::zero);
    EXPECT_FALSE(b == Vector3::zero);
    EXPECT_FALSE(c == Vector3::zero);

    EXPECT_TRUE(a != Vector3::zero);
    EXPECT_TRUE(b != Vector3::zero);
    EXPECT_TRUE(c != Vector3::zero);
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Abs)
{
    auto v1 = Vector3 { -2.5f, 2.0f, 0.5f };
    auto v3 = Vector3::abs({ 0.0f, SceneR::Math::negative_infinity, SceneR::Math::nan});
    auto v  = Vector3::abs(v1);

    EXPECT_TRUE(2.5f == v.x);
    EXPECT_TRUE(2.0f == v.y);
    EXPECT_TRUE(0.5f == v.z);
    EXPECT_TRUE(0.0f == v3.x);
    EXPECT_TRUE(SceneR::Math::positive_infinity == v3.y);
    EXPECT_TRUE(SceneR::Math::is_nan(v3.z));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Sqrt)
{
    auto a = Vector3 { -2.5f, 2.0f, 0.5f };
    auto b = Vector3 { 5.5f, 4.5f, 16.5f };

    EXPECT_TRUE(2 == (std::int32_t)Vector3::square_root(b).x);
    EXPECT_TRUE(2 == (std::int32_t)Vector3::square_root(b).y);
    EXPECT_TRUE(4 == (std::int32_t)Vector3::square_root(b).z);
    EXPECT_TRUE(SceneR::Math::is_nan(Vector3::square_root(a).x));
}

// A test to make sure these types are blittable directly into GPU buffer memory layouts
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Sizeof)
{
    EXPECT_TRUE(12 == sizeof(Vector3));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, SetFields)
{
    auto v3 = Vector3 { 4.0f, 5.0f, 6.0f };

    v3.x = 1.0f;
    v3.y = 2.0f;
    v3.z = 3.0f;

    EXPECT_TRUE(1.0f == v3.x);
    EXPECT_TRUE(2.0f == v3.y);
    EXPECT_TRUE(3.0f == v3.z);

    auto v4 = v3;

    v4.y = 0.5f;
    v4.z = 2.2f;

    EXPECT_TRUE(1.0f == v4.x);
    EXPECT_TRUE(0.5f == v4.y);
    EXPECT_TRUE(2.2f == v4.z);
    EXPECT_TRUE(2.0f == v3.y);

    auto before = Vector3 { 1.0f, 2.0f, 3.0f };
    auto after  = before;

    after.x = 500.0f;

    EXPECT_FALSE(before == after);
}
