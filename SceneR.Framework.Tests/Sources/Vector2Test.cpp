// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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
