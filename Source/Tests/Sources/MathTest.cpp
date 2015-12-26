// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <MathTest.hpp>

#include <Math/Math.hpp>

using namespace SceneR;

TEST_F(MathHelperTest, Clamp)
{
    auto value = Math::clamp(10.0f, 0.0f, 3.0f);

    EXPECT_TRUE(3.0f == value);
}

TEST_F(MathHelperTest, Lerp)
{
    auto value1 = Math::lerp(50.0f, 100.0f, 0.5f);

    EXPECT_TRUE(75.0f == value1);

    auto value2 = Math::lerp(50.0f, 100.0f, 0.3f);

    EXPECT_TRUE(65.0f == value2);

    auto value3 = Math::lerp(10.0f, 20.0f, 0.0f);

    EXPECT_TRUE(10.0f == value3);

    auto value4 = Math::lerp(10.0f, 20.0f, 0.2f);

    EXPECT_TRUE(12.0f == value4);

    auto value5 = Math::lerp(10.0f, 20.0f, 0.5f);

    EXPECT_TRUE(15.0f == value5);

    auto value6 = Math::lerp(10.0f, 20.0f, 0.8f);

    EXPECT_TRUE(18.0f == value6);

    auto value7 = Math::lerp(10.0f, 20.0f, 1.0f);

    EXPECT_TRUE(20.0f == value7);
}
