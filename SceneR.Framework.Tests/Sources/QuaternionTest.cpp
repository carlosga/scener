// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <QuaternionTest.hpp>

#include <Framework/Quaternion.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/MathHelper.hpp>

using namespace SceneR::Framework;

TEST_F(QuaternionTest, XCoordinate)
{
    auto q = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };

    EXPECT_TRUE(1.0f == q.X());
    EXPECT_TRUE(2.0f == q.Y());
    EXPECT_TRUE(3.0f == q.Z());
    EXPECT_TRUE(4.0f == q.W());
}

TEST_F(QuaternionTest, QuaternionConjugate)
{
    auto q = Quaternion { 5.0f, 6.0f, 7.0f, 8.0f };

    q.Conjugate();

    EXPECT_TRUE(-5.0f == q.X());
    EXPECT_TRUE(-6.0f == q.Y());
    EXPECT_TRUE(-7.0f == q.Z());
    EXPECT_TRUE(8.0f  == q.W());
}

TEST_F(QuaternionTest, QuaternionLength)
{
}

TEST_F(QuaternionTest, QuaternionLengthSquared)
{
}

TEST_F(QuaternionTest, QuaternionNormalization)
{
}

TEST_F(QuaternionTest, QuaternionMultiplication)
{
    auto q1 = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto q2 = Quaternion { 5.0f, 6.0f, 7.0f, 8.0f };
    auto qr = q1 * q2;

    // quaternion Result is equal to (24, 48, 48, -6)
    EXPECT_TRUE(24.0f == qr.X());
    EXPECT_TRUE(48.0f == qr.Y());
    EXPECT_TRUE(48.0f == qr.Z());
    EXPECT_TRUE(-6.0f == qr.W());
}

TEST_F(QuaternionTest, CalculateQuaternionFromAxisAngle)
{
    auto result = Quaternion::CreateFromAxisAngle({ 1.0f, 0.0f, 0.0f }, MathHelper::PiOver2);

    // quaternion Result is equal to (0.707106769, 0, 0, 0.707106769)
    EXPECT_TRUE(0.707106769f == result.X());
    EXPECT_TRUE(0.0f         == result.Y());
    EXPECT_TRUE(0.0f         == result.Z());
    EXPECT_TRUE(0.707106769f == result.W());
}
