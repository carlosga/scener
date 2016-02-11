// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "AngleTest.hpp"

#include <SceneR/Math/Angle.hpp>

using namespace SceneR::Math;

TEST_F(AngleTest, RadiansConstructor)
{
    auto angle = Radians(1.35f);

    EXPECT_TRUE(1.35f == angle.value());
}

TEST_F(AngleTest, DegressConstructor)
{
    auto angle = Degrees(180.0f);

    EXPECT_TRUE(180.0f == angle.value());
}

TEST_F(AngleTest, ImplicitDegreesToRadiansConversions)
{
    Degrees degrees(180.0f);
    Radians radians = degrees;

    EXPECT_TRUE(180.0f        == degrees.value());
    EXPECT_TRUE(3.1415926536f == radians.value());
}

TEST_F(AngleTest, ImplicitRadiansToDegreesConversions)
{
    Radians radians(3.1415926536f);
    Degrees degrees = radians;

    EXPECT_TRUE(3.1415926536f == radians.value());
    EXPECT_TRUE(180.0f        == degrees.value());
}

TEST_F(AngleTest, EqualityTest)
{
    Radians radians(3.1415926536f);
    Degrees degrees = radians;

    EXPECT_TRUE(degrees == radians);
}

TEST_F(AngleTest, SumDegrees)
{
    Degrees deg1 = { 90.0f };
    Degrees deg2 = { 90.0f };
    Degrees sum  = deg1 + deg2;

    EXPECT_EQ(180.0f, sum.value());
}

TEST_F(AngleTest, SubtractDegrees)
{
    Degrees deg1 = { 180.0f };
    Degrees deg2 = { 90.0f };
    Degrees sub  = deg1 - deg2;

    EXPECT_EQ(90.0f, sub.value());
}

TEST_F(AngleTest, MultiplyDegreesByScalar)
{
    Degrees deg1 = { 90.0f };
    Degrees deg  = deg1 * 2;

    EXPECT_EQ(180.0f, deg.value());
}

TEST_F(AngleTest, DivideDegreesByScalar)
{
    Degrees deg1 = { 180.0f };
    Degrees deg  = deg1 / 2;

    EXPECT_EQ(90.0f, deg.value());
}
