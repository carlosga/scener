// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <cmath>

#include <Vector2Test.hpp>

#include <Framework/Vector2.hpp>

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