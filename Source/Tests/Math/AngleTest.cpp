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