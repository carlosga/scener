// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Vector3Test.hpp>

#include <cmath>

#include <Framework/Matrix.hpp>
#include <Framework/Vector3.hpp>

using namespace System;
using namespace SceneR::Framework;

TEST_F(Vector3Test, DefaultConstructor)
{
    auto vector = Vector3 { };

    // vector3 is equal to (0.0, 0.0, 0.0)
    EXPECT_TRUE(0.0f == vector.X());
    EXPECT_TRUE(0.0f == vector.Y());
    EXPECT_TRUE(0.0f == vector.Z());
}

TEST_F(Vector3Test, IndividualCoordinatesConstructor)
{
    float x = 20.0f;
    float y = 30.0f;
    float z = 40.0f;

    auto vector3 = Vector3 { x, y, z };

    // vector3 is equal to (20.0, 30.0, 40.0)
    EXPECT_TRUE(x == vector3.X());
    EXPECT_TRUE(y == vector3.Y());
    EXPECT_TRUE(z == vector3.Z());
}

TEST_F(Vector3Test, CopyConstructor)
{
    float x = 20.0f;
    float y = 30.0f;
    float z = 40.0f;

    auto vector  = Vector3 { x, y, z };
    auto vector3 = Vector3 { vector };

    // vector3 is equal to (20.0, 30.0, 40.0)
    EXPECT_TRUE(x == vector3.X());
    EXPECT_TRUE(y == vector3.Y());
    EXPECT_TRUE(z == vector3.Z());
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
    EXPECT_TRUE(x == vector.X());
}

TEST_F(Vector3Test, YCoordinateValue)
{
    const float x = 20.0f;
    const float y = 30.0f;
    const float z = 40.0f;

    auto vector = Vector3 { x, y, z };

    // vector3 is equal to (20.0, 30.0, 40.0)
    EXPECT_TRUE(y == vector.Y());
}

TEST_F(Vector3Test, ZCoordinateValue)
{
    float x = 20.0f;
    float y = 30.0f;
    float z = 40.0f;

    auto vector = Vector3 { x, y, z };

    // vector3 is equal to (20.0, 30.0, 40.0)
    EXPECT_TRUE(z == vector.Z());
}

TEST_F(Vector3Test, Length)
{
    auto vector = Vector3 { 20.0f, 30.0f, 40.0f };

    // length is approximately equal to 53.8516
    EXPECT_TRUE(53.8516464f == vector.Length());
}

TEST_F(Vector3Test, LengthSquared)
{
    auto vector = Vector3 { 20.0f, 30.0f, 40.0f };

    // length is approximately equal to 2900
    EXPECT_TRUE(2900.0f == vector.LengthSquared());
}

TEST_F(Vector3Test, Negation)
{
    auto actual = Vector3::Negate({ 20.0f, 30.0f, 40.0f });

    // vector Result is equal to (-20, -30, -40)
    EXPECT_TRUE(-20.0f == actual.X());
    EXPECT_TRUE(-30.0f == actual.Y());
    EXPECT_TRUE(-40.0f == actual.Z());
}

TEST_F(Vector3Test, Normalization)
{
    auto actual = Vector3::Normalize({ 20.0f, 30.0f, 40.0f });

    // vector Result is equal to (0.37139, 0.55709, 0.74278)
    EXPECT_TRUE(0.3713907f   == actual.X());
    EXPECT_TRUE(0.557086051f == actual.Y());
    EXPECT_TRUE(0.742781401f == actual.Z());
}

TEST_F(Vector3Test, Cross)
{
    auto crossProduct = Vector3::Cross({ 20.0f, 30.0f, 40.0f }, { 45.0f, 70.0f, 80.0f });

    // crossProduct is equal to (-400, 200, 50)
    EXPECT_TRUE(-400.0f == crossProduct.X());
    EXPECT_TRUE(200.0f  == crossProduct.Y());
    EXPECT_TRUE(50.0f   == crossProduct.Z());
}

TEST_F(Vector3Test, DotProduct)
{
    Single dotProduct = Vector3::Dot({20.0f, 30.0f, 40.0f} , { 45.0f, 70.0f, 80.0f });

    EXPECT_TRUE(6200.0f == dotProduct);
}

TEST_F(Vector3Test, AngleBetween)
{
    Single angle = Vector3::AngleBetween({ 20.0f, 30.0f, 40.0f }, { 45.0f, 70.0f, 80.0f });

    // angleBetween is approximately equal to 4.15128803
    EXPECT_TRUE(0.0724536479f == angle);
}

TEST_F(Vector3Test, Addition)
{
    auto vector1 = Vector3 { 20.0f, 30.0f, 40.0f };
	auto vector2 = Vector3 { 45.0f, 70.0f, 80.0f };
	auto result  = vector1 + vector2;

    // vectorResult is equal to (65, 100, 120)
    EXPECT_TRUE(65.0f  == result.X());
    EXPECT_TRUE(100.0f == result.Y());
    EXPECT_TRUE(120.0f == result.Z());
}

TEST_F(Vector3Test, Subtraction)
{
    auto vector1 = Vector3 { 20.0f, 30.0f, 40.0f };
    auto vector2 = Vector3 { 45.0f, 70.0f, 80.0f };
    auto result  = vector1 - vector2;

    // vector Result is equal to (-25, -40, -40)
    EXPECT_TRUE(-25.0f == result.X());
    EXPECT_TRUE(-40.0f == result.Y());
    EXPECT_TRUE(-40.0f == result.Z());
}

TEST_F(Vector3Test, Multiplication)
{
    auto vector1 = Vector3 { 20.0f, 30.0f, 40.0f };
    auto vector2 = Vector3 { 45.0f, 70.0f, 80.0f };
    auto result  = vector1 * vector2;

    // vector Result is equal to (800, 2100, 3200)
    EXPECT_TRUE(900.0f  == result.X());
    EXPECT_TRUE(2100.0f == result.Y());
    EXPECT_TRUE(3200.0f == result.Z());
}

TEST_F(Vector3Test, ScalarMultiplication)
{
    auto vector = Vector3 { 20.0f, 30.0f, 40.0f };
    auto result = vector * 75.0f;

    // vector Result is equal to (1500, 2250, 3000)
    EXPECT_TRUE(1500.0f == result.X());
    EXPECT_TRUE(2250.0f == result.Y());
    EXPECT_TRUE(3000.0f == result.Z());
}

TEST_F(Vector3Test, AdditionAssignment)
{
    auto vector1 = Vector3 { 20.0f, 30.0f, 40.0f };
    auto vector2 = Vector3 { 45.0f, 70.0f, 80.0f };

    vector2 += vector1;

    // vector Result is equal to (65, 100, 120)
    EXPECT_TRUE(65.0f  == vector2.X());
    EXPECT_TRUE(100.0f == vector2.Y());
    EXPECT_TRUE(120.0f == vector2.Z());
}

TEST_F(Vector3Test, SubtractionAssignment)
{
    auto vector1 = Vector3 { 20.0f, 30.0f, 40.0f };
    auto vector2 = Vector3 { 45.0f, 70.0f, 80.0f };

    vector2 -= vector1;

    // vector Result is equal to (25, 40, 40)
    EXPECT_TRUE(25.0f == vector2.X());
    EXPECT_TRUE(40.0f == vector2.Y());
    EXPECT_TRUE(40.0f == vector2.Z());
}

TEST_F(Vector3Test, MultplicationAssignment)
{
    auto vector1 = Vector3 { 20.0f, 30.0f, 40.0f };
    auto vector2 = Vector3 { 45.0f, 70.0f, 80.0f };

    vector2 *= vector1;

    // vector Result is equal to (800, 2100, 3200)
    EXPECT_TRUE(900.0f  == vector2.X());
    EXPECT_TRUE(2100.0f == vector2.Y());
    EXPECT_TRUE(3200.0f == vector2.Z());
}

TEST_F(Vector3Test, ScalarMultplicationAssignment)
{
    auto vector = Vector3 { 20.0f, 30.0f, 40.0f };

    vector *= 75.0f;

    // vector Result is equal to (1500, 2250, 3000)
    EXPECT_TRUE(1500.0f == vector.X());
    EXPECT_TRUE(2250.0f == vector.Y());
    EXPECT_TRUE(3000.0f == vector.Z());
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
    EXPECT_TRUE(2005.0f == vectorResult.X());
    EXPECT_TRUE(2010.0f == vectorResult.Y());
    EXPECT_TRUE(2015.0f == vectorResult.Z());
}

TEST_F(Vector3Test, Transform)
{
    auto vector = Vector3 { 20.0f, 30.0f, 40.0f };
    auto matrix = Matrix  { 10.0f, 10.0f, 10.0f, 0.0f
                          , 20.0f, 20.0f, 20.0f, 0.0f
                          , 30.0f, 30.0f, 30.0f, 0.0f
                          , 5.0f , 10.0f, 15.0f, 1.0f };

    auto result = Vector3::Transform(vector, matrix);

    // vector Result is equal to (2005, 2010, 2015)
    EXPECT_TRUE(2005.0f == result.X());
    EXPECT_TRUE(2010.0f == result.Y());
    EXPECT_TRUE(2015.0f == result.Z());
}

TEST_F(Vector3Test, TransformNormal)
{
    auto vector = Vector3 { 20.0f, 30.0f, 40.0f };
    auto matrix = Matrix  { 10.0f, 10.0f, 10.0f, 0.0f
                          , 20.0f, 20.0f, 20.0f, 0.0f
                          , 30.0f, 30.0f, 30.0f, 0.0f
                          , 5.0f , 10.0f, 15.0f, 1.0f };

    auto result = Vector3::TransformNormal(vector, matrix);

    // vector Result is equal to (2000, 2000, 2000)
    EXPECT_TRUE(2000.0f == result.X());
    EXPECT_TRUE(2000.0f == result.Y());
    EXPECT_TRUE(2000.0f == result.Z());
}

TEST_F(Vector3Test, Lerp)
{
    auto vector1 = Vector3 { 5.0f, 10.0f, 50.0f };
    auto vector2 = Vector3 { 0.0f, -20.0f, 100.0f };
    auto result  = Vector3::Lerp(vector1, vector2, 0.4f);

    EXPECT_TRUE(3.0f  == result.X());
    EXPECT_TRUE(-2.0f == result.Y());
    EXPECT_TRUE(70.0f == result.Z());
}

// A test for Cross (Vector3f, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Cross1)
{
    auto a        = Vector3 { 1.0f, 0.0f, 0.0f };
    auto b        = Vector3 { 0.0f, 1.0f, 0.0f };
    auto expected = Vector3 { 0.0f, 0.0f, 1.0f };
    auto actual   = Vector3::Cross(a, b);

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
    auto actual   = Vector3::Cross(a, b);

    EXPECT_TRUE(expected == actual);
}

// A test for Distance (Vector3f, Vector3f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, Distance)
{
    auto a = Vector3 { 1.0f, 2.0f, 3.0f };
    auto b = Vector3 { 4.0f, 5.0f, 6.0f };

    Single expected = std::sqrt(27.0f);
    Single actual   = Vector3::Distance(a, b);

    EXPECT_TRUE(expected == actual);
}

// A test for Distance (Vector3f, Vector3f)
// Distance from the same point
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(Vector3Test, DistanceFromTheSamePoint)
{
//    auto a = Vector3 { 1.051f, 2.05f, 3.478f };
//    auto b = Vector3 { Vector2 { 1.051f, 0.0f }, 1.0f };
//
//    b.Y = 2.05f;
//    b.Z = 3.478f;
//
//    Single actual = Vector3::Distance(a, b);
//
//    EXPECT_TRUE(0.0f == actual);
}
