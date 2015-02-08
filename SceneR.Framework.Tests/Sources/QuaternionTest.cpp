// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <QuaternionTest.hpp>

#include <cmath>

#include <Framework/Quaternion.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/MathHelper.hpp>
#include <Framework/Matrix.hpp>

using namespace System;
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

// A test for Dot (Quaternion, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Dot)
{
    auto a = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = Quaternion { 5.0f, 6.0f, 7.0f, 8.0f };

    Single expected = 70.0f;
    Single actual   = Quaternion::DotProduct(a, b);

    EXPECT_TRUE(expected == actual);
}


// A test for Length ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Length)
{
    auto   v        = Vector3 { 1.0f, 2.0f, 3.0f };
    Single w        = 4.0f;
    auto   target   = Quaternion { v, w };
    Single expected = 5.477226f;
    Single actual   = target.Length();

    EXPECT_TRUE(expected == actual);
}

// A test for LengthSquared ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, LengthSquared)
{
    auto   v        = Vector3 { 1.0f, 2.0f, 3.0f };
    Single w        = 4.0f;
    auto   target   = Quaternion { v, w };
    Single expected = 30.0f;
    Single actual   = target.LengthSquared();

    EXPECT_TRUE(expected == actual);
}

// A test for Lerp (Quaternion, Quaternion, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Lerp)
{
    auto   axis     = Vector3::Normalize({ 1.0f, 2.0f, 3.0f });
    auto   a        = Quaternion::CreateFromAxisAngle(axis, MathHelper::ToRadians(10.0f));
    auto   b        = Quaternion::CreateFromAxisAngle(axis, MathHelper::ToRadians(30.0f));
    Single t        = 0.5f;
    auto   expected = Quaternion::CreateFromAxisAngle(axis, MathHelper::ToRadians(20.0f));
    auto   actual   = Quaternion::Lerp(a, b, t);

    EXPECT_TRUE(expected == actual);

    // Case a and b are same.
    expected = a;
    actual   = Quaternion::Lerp(a, a, t);

    EXPECT_TRUE(expected == actual);
}

// A test for Lerp (Quaternion, Quaternion, float)
// Lerp test when t = 0
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, LerpWithInterpolateZero)
{
    auto   axis     = Vector3::Normalize({ 1.0f, 2.0f, 3.0f });
    auto   a        = Quaternion::CreateFromAxisAngle(axis, MathHelper::ToRadians(10.0f));
    auto   b        = Quaternion::CreateFromAxisAngle(axis, MathHelper::ToRadians(30.0f));
    Single t        = 0.0f;
    auto   expected = Quaternion { a.X(), a.Y(), a.Z(), a.W() };
    auto   actual   = Quaternion::Lerp(a, b, t);

    EXPECT_TRUE(expected == actual);
}

// A test for Lerp (Quaternion, Quaternion, float)
// Lerp test when t = 1
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, LerpWithInterpolateOne)
{
    auto   axis     = Vector3::Normalize({ 1.0f, 2.0f, 3.0f });
    auto   a        = Quaternion::CreateFromAxisAngle(axis, MathHelper::ToRadians(10.0f));
    auto   b        = Quaternion::CreateFromAxisAngle(axis, MathHelper::ToRadians(30.0f));
    Single t        = 1.0f;
    auto   expected = Quaternion { b.X(), b.Y(), b.Z(), b.W() };
    auto   actual   = Quaternion::Lerp(a, b, t);

    EXPECT_TRUE(expected == actual);
}

// A test for Lerp (Quaternion, Quaternion, float)
// Lerp test when the two quaternions are more than 90 degree (dot product <0)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, LerpWithQuaternionsWithMoreThan90Degrees)
{
    auto   axis   = Vector3::Normalize({ 1.0f, 2.0f, 3.0f });
    auto   a      = Quaternion::CreateFromAxisAngle(axis, MathHelper::ToRadians(10.0f));
    auto   b      = Quaternion::Negate(a);
    Single t      = 1.0f;
    auto   actual = Quaternion::Lerp(a, b, t);

    // Note that in quaternion world, Q == -Q. In the case of quaternions dot product is zero,
    // one of the quaternion will be flipped to compute the shortest distance. When t = 1, we
    // expect the result to be the same as quaternion b but flipped.
    EXPECT_TRUE(a == actual);
}

// A test for Conjugate(Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Conjugate)
{
    auto a        = Quaternion { 1, 2, 3, 4 };
    auto expected = Quaternion { -1, -2, -3, 4 };
    auto actual   = Quaternion::Conjugate(a);

    EXPECT_TRUE(expected == actual);
}

// A test for Normalize (Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Normalize)
{
    auto a        = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto expected = Quaternion { 0.182574168f, 0.365148336f, 0.5477225f, 0.7302967f };
    auto actual   = Quaternion::Normalize(a);

    EXPECT_TRUE(expected == actual);
}

// A test for Normalize (Quaternion)
// Normalize zero length quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, NormalizeZeroLengthQuaternion)
{
    auto a      = Quaternion { 0.0f, 0.0f, -0.0f, 0.0f };
    auto actual = Quaternion::Normalize(a);

    EXPECT_TRUE(MathHelper::IsNaN(actual.X()));
    EXPECT_TRUE(MathHelper::IsNaN(actual.Y()));
    EXPECT_TRUE(MathHelper::IsNaN(actual.Z()));
    EXPECT_TRUE(MathHelper::IsNaN(actual.W()));
}

// A test for Concatenate(Quaternion, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Concatenate)
{
//    auto b        = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
//    auto a        = Quaternion { 5.0f, 6.0f, 7.0f, 8.0f };
//    auto expected = Quaternion { 24.0f, 48.0f, 48.0f, -6.0f };
//    auto actual   = Quaternion::Concatenate(a, b);
//
//    EXPECT_TRUE(expected == actual);
}

// A test for operator - (Quaternion, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Subtraction)
{
    auto a        = Quaternion { 1.0f, 6.0f, 7.0f, 4.0f };
    auto b        = Quaternion { 5.0f, 2.0f, 3.0f, 8.0f };
    auto expected = Quaternion { -4.0f, 4.0f, 4.0f, -4.0f };
    auto actual   = a - b;

    EXPECT_TRUE(expected == actual);
}

// A test for operator * (Quaternion, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Multiply)
{
    auto   a        = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    Single factor   = 0.5f;
    auto   expected = Quaternion { 0.5f, 1.0f, 1.5f, 2.0f };
    auto   actual   = a * factor;

    EXPECT_TRUE(expected == actual);
}

// A test for operator * (Quaternion, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Multiply1)
{
    auto a        = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b        = Quaternion { 5.0f, 6.0f, 7.0f, 8.0f };
    auto expected = Quaternion { 24.0f, 48.0f, 48.0f, -6.0f };
    auto actual   = a * b;

    EXPECT_TRUE(expected == actual);
}

// A test for operator / (Quaternion, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Division)
{
    auto a        = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b        = Quaternion { 5.0f, 6.0f, 7.0f, 8.0f };
    auto expected = Quaternion { -0.045977015f, -0.09195402f, -7.450581E-9f, 0.402298868f };
    auto actual   = a / b;

    EXPECT_TRUE(expected == actual);
}

// A test for operator + (Quaternion, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Addition)
{
    auto a        = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b        = Quaternion { 5.0f, 6.0f, 7.0f, 8.0f };
    auto expected = Quaternion { 6.0f, 8.0f, 10.0f, 12.0f };
    auto actual   = a + b;

    EXPECT_TRUE(expected == actual);
}

// A test for Quaternion (float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Constructor)
{
    Single x = 1.0f;
    Single y = 2.0f;
    Single z = 3.0f;
    Single w = 4.0f;

    auto target = Quaternion { x, y, z, w };

    EXPECT_TRUE(x == target.X());
    EXPECT_TRUE(y == target.Y());
    EXPECT_TRUE(z == target.Z());
    EXPECT_TRUE(w == target.W());
}

// A test for Quaternion (Vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, ConstructorWithVector3)
{
    auto   v = Vector3 { 1.0f, 2.0f, 3.0f };
    Single w = 4.0f;

    auto target = Quaternion { v, w };

    EXPECT_TRUE(v.X() == target.X());
    EXPECT_TRUE(v.Y() == target.Y());
    EXPECT_TRUE(v.Z() == target.Z());
    EXPECT_TRUE(w     == target.W());
}

// A test for CreateFromAxisAngle (Vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, CreateFromAxisAngle)
{
    auto   axis     = Vector3::Normalize({ 1.0f, 2.0f, 3.0f });
    Single angle    = MathHelper::ToRadians(30.0f);
    auto   expected = Quaternion(0.0691723f, 0.1383446f, 0.207516879f, 0.9659258f);
    auto   actual   = Quaternion::CreateFromAxisAngle(axis, angle);

    EXPECT_TRUE(expected == actual);
}

// A test for CreateFromAxisAngle (Vector3f, float)
// CreateFromAxisAngle of zero vector
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, CreateFromAxisAngleOfZeroVector)
{
    auto   axis   = Vector3 { };
    Single angle  = MathHelper::ToRadians(-30.0f);
    Single cos    = std::cos(angle / 2.0f);
    auto   actual = Quaternion::CreateFromAxisAngle(axis, angle);

    EXPECT_TRUE(0.0f == actual.X());
    EXPECT_TRUE(0.0f == actual.Y());
    EXPECT_TRUE(0.0f == actual.Z());
    EXPECT_TRUE(cos  == actual.W());
}

// A test for CreateFromAxisAngle (Vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, CreateFromAxisAngleOfAngle30And750)
{
    auto   axis    = Vector3 { 1.0f, 0.0f, 0.0f };
    Single angle1  = MathHelper::ToRadians(30.0f);
    Single angle2  = MathHelper::ToRadians(750.0f);
    auto   actual1 = Quaternion::CreateFromAxisAngle(axis, angle1);
    auto   actual2 = Quaternion::CreateFromAxisAngle(axis, angle2);

    EXPECT_TRUE(actual1 == actual2);
}

// A test for CreateFromAxisAngle (Vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, CreateFromAxisAngleOfAngle30And390)
{
    auto   axis    = Vector3 { 1.0f, 0.0f, 0.0f };
    Single angle1  = MathHelper::ToRadians(30.0f);
    Single angle2  = MathHelper::ToRadians(390.0f);
    auto   actual1 = Quaternion::CreateFromAxisAngle(axis, angle1);
    auto   actual2 = Quaternion::CreateFromAxisAngle(axis, angle2);

    actual1.X(-actual1.X());
    actual1.W(-actual1.W());

    EXPECT_TRUE(actual1 == actual2);
}

// A test for CreateFromAxisAngle (Vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, CreateFromYawPitchRoll)
{
    Single yawAngle   = MathHelper::ToRadians(30.0f);
    Single pitchAngle = MathHelper::ToRadians(40.0f);
    Single rollAngle  = MathHelper::ToRadians(50.0f);

    auto yaw      = Quaternion::CreateFromAxisAngle(Vector3::UnitY, yawAngle);
    auto pitch    = Quaternion::CreateFromAxisAngle(Vector3::UnitX, pitchAngle);
    auto roll     = Quaternion::CreateFromAxisAngle(Vector3::UnitZ, rollAngle);
    auto expected = yaw * pitch * roll;
    auto actual   = Quaternion::CreateFromYawPitchRoll(yawAngle, pitchAngle, rollAngle);

    EXPECT_TRUE(expected == actual);
}

// Covers more numeric rigions
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, CreateFromYawPitchRoll2)
{
    const Single step = 35.0f;

    for (Single yawAngle = -720.0f; yawAngle <= 720.0f; yawAngle += step)
    {
        for (Single pitchAngle = -720.0f; pitchAngle <= 720.0f; pitchAngle += step)
        {
            for (Single rollAngle = -720.0f; rollAngle <= 720.0f; rollAngle += step)
            {
                Single yawRad   = MathHelper::ToRadians(yawAngle);
                Single pitchRad = MathHelper::ToRadians(pitchAngle);
                Single rollRad  = MathHelper::ToRadians(rollAngle);

                auto yaw   = Quaternion::CreateFromAxisAngle(Vector3::UnitY, yawRad);
                auto pitch = Quaternion::CreateFromAxisAngle(Vector3::UnitX, pitchRad);
                auto roll  = Quaternion::CreateFromAxisAngle(Vector3::UnitZ, rollRad);

                auto expected = yaw * pitch * roll;
                auto actual   = Quaternion::CreateFromYawPitchRoll(yawRad, pitchRad, rollRad);

                EXPECT_TRUE(expected == actual);
            }
        }
    }
}

// A test for Slerp (Quaternion, Quaternion, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Slerp)
{
    auto axis = Vector3::Normalize({ 1.0f, 2.0f, 3.0f });
    auto a    = Quaternion::CreateFromAxisAngle(axis, MathHelper::ToRadians(10.0f));
    auto b    = Quaternion::CreateFromAxisAngle(axis, MathHelper::ToRadians(30.0f));

    Single t = 0.5f;

    auto expected = Quaternion::CreateFromAxisAngle(axis, MathHelper::ToRadians(20.0f));
    auto actual   = Quaternion::Slerp(a, b, t);

    EXPECT_TRUE(expected == actual);

    // Case a and b are same.
    expected = a;
    actual   = Quaternion::Slerp(a, a, t);

    EXPECT_TRUE(expected == actual);
}

// A test for Slerp (Quaternion, Quaternion, float)
// Slerp test where t = 0
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, SlerpWithInterpolateZero)
{
    auto axis = Vector3::Normalize({ 1.0f, 2.0f, 3.0f });
    auto a    = Quaternion::CreateFromAxisAngle(axis, MathHelper::ToRadians(10.0f));
    auto b    = Quaternion::CreateFromAxisAngle(axis, MathHelper::ToRadians(30.0f));

    Single t = 0.0f;

    Quaternion expected = Quaternion { a.X(), a.Y(), a.Z(), a.W() };
    Quaternion actual   = Quaternion::Slerp(a, b, t);

    EXPECT_TRUE(expected == actual);
}

// A test for Slerp (Quaternion, Quaternion, float)
// Slerp test where t = 1
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, SlerpWithInterpolateOne)
{
    auto axis = Vector3::Normalize({ 1.0f, 2.0f, 3.0f });
    auto a    = Quaternion::CreateFromAxisAngle(axis, MathHelper::ToRadians(10.0f));
    auto b    = Quaternion::CreateFromAxisAngle(axis, MathHelper::ToRadians(30.0f));

    Single t = 1.0f;

    auto expected = Quaternion { b.X(), b.Y(), b.Z(), b.W() };
    auto actual   = Quaternion::Slerp(a, b, t);

    EXPECT_TRUE(expected == actual);
}

// A test for Slerp (Quaternion, Quaternion, float)
// Slerp test where dot product is < 0
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, SlerpWithDotProductLessThanZero)
{
    auto axis = Vector3::Normalize({ 1.0f, 2.0f, 3.0f });
    auto a    = Quaternion::CreateFromAxisAngle(axis, MathHelper::ToRadians(10.0f));
    auto b    = -a;

    Single t = 1.0f;

    auto expected = a;
    auto actual   = Quaternion::Slerp(a, b, t);

    // Note that in quaternion world, Q == -Q. In the case of quaternions dot product is zero,
    // one of the quaternion will be flipped to compute the shortest distance. When t = 1, we
    // expect the result to be the same as quaternion b but flipped.
    EXPECT_TRUE(expected == actual);
}

// A test for Slerp (Quaternion, Quaternion, float)
// Slerp test where the quaternion is flipped
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, SlerpWithFlippedQuaternion)
{
    auto axis = Vector3::Normalize({ 1.0f, 2.0f, 3.0f });
    auto a    = Quaternion::CreateFromAxisAngle(axis, MathHelper::ToRadians(10.0f));
    auto b    = -Quaternion::CreateFromAxisAngle(axis, MathHelper::ToRadians(30.0f));

    Single t = 0.0f;

    auto expected = Quaternion { a.X(), a.Y(), a.Z(), a.W() };
    auto actual   = Quaternion::Slerp(a, b, t);

    EXPECT_TRUE(expected == actual);
}

// A test for operator - (Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, UnaryNegation)
{
    auto a        = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto expected = Quaternion { -1.0f, -2.0f, -3.0f, -4.0f };
    auto actual   = -a;

    EXPECT_TRUE(expected == actual);
}

// A test for Inverse (Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Inverse)
{
    auto a        = Quaternion { 5.0f, 6.0f, 7.0f, 8.0f };
    auto expected = Quaternion { -0.0287356321f, -0.03448276f, -0.0402298868f, 0.04597701f };
    auto actual   = Quaternion::Inverse(a);

    EXPECT_TRUE(expected == actual);
}

// A test for Inverse (Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, InvertZeroLengthQuaternion)
{
    auto a      = Quaternion { };
    auto actual = Quaternion::Inverse(a);

    EXPECT_TRUE(MathHelper::IsNaN(actual.X()));
    EXPECT_TRUE(MathHelper::IsNaN(actual.Y()));
    EXPECT_TRUE(MathHelper::IsNaN(actual.Z()));
    EXPECT_TRUE(MathHelper::IsNaN(actual.W()));
}

// A test for Negate (Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Negate)
{
    auto a        = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto expected = Quaternion { -1.0f, -2.0f, -3.0f, -4.0f };
    auto actual   = Quaternion::Negate(a);

    EXPECT_TRUE(expected == actual);
}

// A test for operator != (Quaternion, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Inequality)
{
    auto a = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };

    // case 1: compare between same values
    bool expected = false;
    bool actual   = a != b;

    EXPECT_TRUE(expected == actual);

    // case 2: compare between different values
    b.X(10.0f);

    expected = true;
    actual   = a != b;

    EXPECT_TRUE(expected == actual);
}

// A test for operator == (Quaternion, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Equality)
{
    auto a = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };

    // case 1: compare between same values
    bool expected = true;
    bool actual   = a == b;

    EXPECT_TRUE(expected == actual);

    // case 2: compare between different values
    b.X(10.0f);

    expected = false;
    actual   = a == b;

    EXPECT_TRUE(expected == actual);
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, ConvertIdentityMatrix)
{
    auto matrix   = Matrix::Identity;
    auto expected = Quaternion { 0.0f, 0.0f, 0.0f, 1.0f };
    auto actual   = Quaternion::CreateFromRotationMatrix(matrix);

    EXPECT_TRUE(expected == actual);

    // make sure convert back to matrix is same as we passed matrix.
    auto m2 = Matrix::CreateFromQuaternion(actual);

    EXPECT_TRUE(matrix == m2);
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, ConvertXAxisRotationMatrix)
{
    for (Single angle = 0.0f; angle < 720.0f; angle += 10.0f)
    {
        auto matrix   = Matrix::CreateRotationX(angle);
        auto expected = Quaternion::CreateFromAxisAngle(Vector3::UnitX, angle);
        auto actual   = Quaternion::CreateFromRotationMatrix(matrix);

        EXPECT_TRUE(Quaternion::EqualRotation(expected, actual));

        // make sure convert back to matrix is same as we passed matrix.
        auto m2 = Matrix::CreateFromQuaternion(actual);

        EXPECT_TRUE(matrix == m2);
    }
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, ConvertYAxisRotationMatrix)
{
    for (Single angle = 0.0f; angle < 720.0f; angle += 10.0f)
    {
        auto matrix   = Matrix::CreateRotationY(angle);
        auto expected = Quaternion::CreateFromAxisAngle(Vector3::UnitY, angle);
        auto actual   = Quaternion::CreateFromRotationMatrix(matrix);

        EXPECT_TRUE(Quaternion::EqualRotation(expected, actual));

        // make sure convert back to matrix is same as we passed matrix.
        auto m2 = Matrix::CreateFromQuaternion(actual);

        EXPECT_TRUE(matrix == m2);
    }
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, ConvertZAxisRotationMatrix)
{
    for (float angle = 0.0f; angle < 720.0f; angle += 10.0f)
    {
        auto matrix   = Matrix::CreateRotationZ(angle);
        auto expected = Quaternion::CreateFromAxisAngle(Vector3::UnitZ, angle);
        auto actual   = Quaternion::CreateFromRotationMatrix(matrix);

        EXPECT_TRUE(Quaternion::EqualRotation(expected, actual));

        // make sure convert back to matrix is same as we passed matrix.
        auto m2 = Matrix::CreateFromQuaternion(actual);

        EXPECT_TRUE(matrix == m2);
    }
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, ConvertXYZAxisRotationMatrix)
{
    for (float angle = 0.0f; angle < 720.0f; angle += 10.0f)
    {
        auto matrix   = Matrix::CreateRotationX(angle)
                      * Matrix::CreateRotationY(angle)
                      * Matrix::CreateRotationZ(angle);

        auto expected = Quaternion::CreateFromAxisAngle(Vector3::UnitZ, angle)
                      * Quaternion::CreateFromAxisAngle(Vector3::UnitY, angle)
                      * Quaternion::CreateFromAxisAngle(Vector3::UnitX, angle);

        auto actual = Quaternion::CreateFromRotationMatrix(matrix);

        EXPECT_TRUE(Quaternion::EqualRotation(expected, actual));

        // make sure convert back to matrix is same as we passed matrix.
        auto m2 = Matrix::CreateFromQuaternion(actual);

        EXPECT_TRUE(matrix == m2);
    }
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, FromRotationMatrixWithScaledMatrixOnXAxis)
{
    auto angle  = MathHelper::ToRadians(180.0f);
    auto matrix = Matrix::CreateRotationY(angle)
                * Matrix::CreateRotationZ(angle);

    auto expected = Quaternion::CreateFromAxisAngle(Vector3::UnitZ, angle)
                  * Quaternion::CreateFromAxisAngle(Vector3::UnitY, angle);
    auto actual   = Quaternion::CreateFromRotationMatrix(matrix);

    EXPECT_TRUE(Quaternion::EqualRotation(expected, actual));

    // make sure convert back to matrix is same as we passed matrix.
    auto m2 = Matrix::CreateFromQuaternion(actual);

    EXPECT_TRUE(matrix == m2);
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, FromRotationMatrixWithScaledMatrixOnYAxis)
{
    Single angle  = MathHelper::ToRadians(180.0f);
    auto   matrix = Matrix::CreateRotationX(angle)
                  * Matrix::CreateRotationZ(angle);

    auto expected = Quaternion::CreateFromAxisAngle(Vector3::UnitZ, angle)
                  * Quaternion::CreateFromAxisAngle(Vector3::UnitX, angle);
    auto actual   = Quaternion::CreateFromRotationMatrix(matrix);

    EXPECT_TRUE(Quaternion::EqualRotation(expected, actual));

    // make sure convert back to matrix is same as we passed matrix.
    auto m2 = Matrix::CreateFromQuaternion(actual);

    EXPECT_TRUE(matrix == m2);
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, FromRotationMatrixWithScaledMatrixOnZAxis)
{
    auto angle  = MathHelper::ToRadians(180.0f);
    auto matrix = Matrix::CreateRotationX(angle)
                * Matrix::CreateRotationY(angle);

    auto expected = Quaternion::CreateFromAxisAngle(Vector3::UnitY, angle)
                  * Quaternion::CreateFromAxisAngle(Vector3::UnitX, angle);
    auto actual   = Quaternion::CreateFromRotationMatrix(matrix);

    EXPECT_TRUE(Quaternion::EqualRotation(expected, actual));

    // make sure convert back to matrix is same as we passed matrix.
    auto m2 = Matrix::CreateFromQuaternion(actual);

    EXPECT_TRUE(matrix == m2);
}

// A test for Identity
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Identity)
{
    auto actual = Quaternion { 0.0f, 0.0f, 0.0f, 1.0f };

    EXPECT_TRUE(Quaternion::Identity == actual);
}

// A test for
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, IsIdentity)
{
    EXPECT_TRUE (Quaternion::Identity.IsIdentity());
    EXPECT_TRUE (Quaternion(0, 0, 0, 1).IsIdentity());
    EXPECT_FALSE(Quaternion(1, 0, 0, 1).IsIdentity());
    EXPECT_FALSE(Quaternion(0, 1, 0, 1).IsIdentity());
    EXPECT_FALSE(Quaternion(0, 0, 1, 1).IsIdentity());
    EXPECT_FALSE(Quaternion(0, 0, 0, 0).IsIdentity());
}

/*

// A test for Quaternion comparison involving NaN values
[Fact]
public void QuaternionEqualsNanTest()
{
    Quaternion a = new Quaternion(float.NaN, 0, 0, 0);
    Quaternion b = new Quaternion(0, float.NaN, 0, 0);
    Quaternion c = new Quaternion(0, 0, float.NaN, 0);
    Quaternion d = new Quaternion(0, 0, 0, float.NaN);

    Assert.False(a == new Quaternion(0, 0, 0, 0));
    Assert.False(b == new Quaternion(0, 0, 0, 0));
    Assert.False(c == new Quaternion(0, 0, 0, 0));
    Assert.False(d == new Quaternion(0, 0, 0, 0));

    Assert.True(a != new Quaternion(0, 0, 0, 0));
    Assert.True(b != new Quaternion(0, 0, 0, 0));
    Assert.True(c != new Quaternion(0, 0, 0, 0));
    Assert.True(d != new Quaternion(0, 0, 0, 0));

    Assert.False(a.Equals(new Quaternion(0, 0, 0, 0)));
    Assert.False(b.Equals(new Quaternion(0, 0, 0, 0)));
    Assert.False(c.Equals(new Quaternion(0, 0, 0, 0)));
    Assert.False(d.Equals(new Quaternion(0, 0, 0, 0)));

    Assert.False(a.IsIdentity);
    Assert.False(b.IsIdentity);
    Assert.False(c.IsIdentity);
    Assert.False(d.IsIdentity);

    // Counterintuitive result - IEEE rules for NaN comparison are weird!
    Assert.False(a.Equals(a));
    Assert.False(b.Equals(b));
    Assert.False(c.Equals(c));
    Assert.False(d.Equals(d));
}

// A test to make sure these types are blittable directly into GPU buffer memory layouts
[Fact]
public unsafe void QuaternionSizeofTest()
{
    Assert.Equal(16, sizeof(Quaternion));
    Assert.Equal(32, sizeof(Quaternion_2x));
    Assert.Equal(20, sizeof(QuaternionPlusFloat));
    Assert.Equal(40, sizeof(QuaternionPlusFloat_2x));
}

[StructLayout(LayoutKind.Sequential)]
struct Quaternion_2x
{
    private Quaternion _a;
    private Quaternion _b;
}

[StructLayout(LayoutKind.Sequential)]
struct QuaternionPlusFloat
{
    private Quaternion _v;
    private float _f;
}

[StructLayout(LayoutKind.Sequential)]
struct QuaternionPlusFloat_2x
{
    private QuaternionPlusFloat _a;
    private QuaternionPlusFloat _b;
}

// A test to make sure the fields are laid out how we expect
[Fact]
public unsafe void QuaternionFieldOffsetTest()
{
    Quaternion* ptr = (Quaternion*)0;

    Assert.Equal(new IntPtr(0), new IntPtr(&ptr->X));
    Assert.Equal(new IntPtr(4), new IntPtr(&ptr->Y));
    Assert.Equal(new IntPtr(8), new IntPtr(&ptr->Z));
    Assert.Equal(new IntPtr(12), new IntPtr(&ptr->W));
}
 */