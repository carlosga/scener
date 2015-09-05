// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <QuaternionTest.hpp>

#include <EqualityHelper.hpp>

#include <System/Math.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector3.hpp>
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
    auto actual = Quaternion::Conjugate({ 5.0f, 6.0f, 7.0f, 8.0f });

    EXPECT_TRUE(-5.0f == actual.X());
    EXPECT_TRUE(-6.0f == actual.Y());
    EXPECT_TRUE(-7.0f == actual.Z());
    EXPECT_TRUE(8.0f  == actual.W());
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
    auto result = Quaternion::CreateFromAxisAngle({ 1.0f, 0.0f, 0.0f }, Math::PiOver2);

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

    auto expected = 70.0f;
    auto actual   = Quaternion::Dot(a, b);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Length ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Length)
{
    auto v        = Vector3 { 1.0f, 2.0f, 3.0f };
    auto w        = 4.0f;
    auto target   = Quaternion { v, w };
    auto expected = 5.477226f;
    auto actual   = target.Length();

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for LengthSquared ()
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, LengthSquared)
{
    auto v        = Vector3 { 1.0f, 2.0f, 3.0f };
    auto w        = 4.0f;
    auto target   = Quaternion { v, w };
    auto expected = 30.0f;
    auto actual   = target.LengthSquared();

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Quaternion, Quaternion, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Lerp)
{
    auto axis     = Vector3::Normalize({ 1.0f, 2.0f, 3.0f });
    auto a        = Quaternion::CreateFromAxisAngle(axis, Math::ToRadians(10.0f));
    auto b        = Quaternion::CreateFromAxisAngle(axis, Math::ToRadians(30.0f));
    auto t        = 0.5f;
    auto expected = Quaternion::CreateFromAxisAngle(axis, Math::ToRadians(20.0f));
    auto actual   = Quaternion::Lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Case a and b are same.
    expected = a;
    actual   = Quaternion::Lerp(a, a, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Quaternion, Quaternion, float)
// Lerp test when t = 0
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, LerpWithInterpolateZero)
{
    auto axis     = Vector3::Normalize({ 1.0f, 2.0f, 3.0f });
    auto a        = Quaternion::CreateFromAxisAngle(axis, Math::ToRadians(10.0f));
    auto b        = Quaternion::CreateFromAxisAngle(axis, Math::ToRadians(30.0f));
    auto t        = 0.0f;
    auto expected = Quaternion { a.X(), a.Y(), a.Z(), a.W() };
    auto actual   = Quaternion::Lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Quaternion, Quaternion, float)
// Lerp test when t = 1
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, LerpWithInterpolateOne)
{
    auto axis     = Vector3::Normalize({ 1.0f, 2.0f, 3.0f });
    auto a        = Quaternion::CreateFromAxisAngle(axis, Math::ToRadians(10.0f));
    auto b        = Quaternion::CreateFromAxisAngle(axis, Math::ToRadians(30.0f));
    auto t        = 1.0f;
    auto expected = Quaternion { b.X(), b.Y(), b.Z(), b.W() };
    auto actual   = Quaternion::Lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Quaternion, Quaternion, float)
// Lerp test when the two quaternions are more than 90 degree (dot product <0)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, LerpWithQuaternionsWithMoreThan90Degrees)
{
    auto axis   = Vector3::Normalize({ 1.0f, 2.0f, 3.0f });
    auto a      = Quaternion::CreateFromAxisAngle(axis, Math::ToRadians(10.0f));
    auto b      = Quaternion::Negate(a);
    auto t      = 1.0f;
    auto actual = Quaternion::Lerp(a, b, t);

    // Note that in quaternion world, Q == -Q. In the case of quaternions dot product is zero,
    // one of the quaternion will be flipped to compute the shortest distance. When t = 1, we
    // expect the result to be the same as quaternion b but flipped.
    EXPECT_TRUE(EqualityHelper::Equal(a, actual));
}

// A test for Conjugate(Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Conjugate)
{
    auto a        = Quaternion { 1, 2, 3, 4 };
    auto expected = Quaternion { -1, -2, -3, 4 };
    auto actual   = Quaternion::Conjugate(a);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Normalize (Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Normalize)
{
    auto a        = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto expected = Quaternion { 0.182574168f, 0.365148336f, 0.5477225f, 0.7302967f };
    auto actual   = Quaternion::Normalize(a);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Normalize (Quaternion)
// Normalize zero length quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, NormalizeZeroLengthQuaternion)
{
    auto a      = Quaternion { 0.0f, 0.0f, -0.0f, 0.0f };
    auto actual = Quaternion::Normalize(a);

    EXPECT_TRUE(Math::IsNaN(actual.X()));
    EXPECT_TRUE(Math::IsNaN(actual.Y()));
    EXPECT_TRUE(Math::IsNaN(actual.Z()));
    EXPECT_TRUE(Math::IsNaN(actual.W()));
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

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator * (Quaternion, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Multiply)
{
    auto a        = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto factor   = 0.5f;
    auto expected = Quaternion { 0.5f, 1.0f, 1.5f, 2.0f };
    auto actual   = a * factor;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator * (Quaternion, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Multiply1)
{
    auto a        = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b        = Quaternion { 5.0f, 6.0f, 7.0f, 8.0f };
    auto expected = Quaternion { 24.0f, 48.0f, 48.0f, -6.0f };
    auto actual   = a * b;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator / (Quaternion, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Division)
{
    auto a        = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b        = Quaternion { 5.0f, 6.0f, 7.0f, 8.0f };
    auto expected = Quaternion { -0.045977015f, -0.09195402f, -7.450581E-9f, 0.402298868f };
    auto actual   = a / b;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator + (Quaternion, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Addition)
{
    auto a        = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b        = Quaternion { 5.0f, 6.0f, 7.0f, 8.0f };
    auto expected = Quaternion { 6.0f, 8.0f, 10.0f, 12.0f };
    auto actual   = a + b;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Quaternion (float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Constructor)
{
    auto x = 1.0f;
    auto y = 2.0f;
    auto z = 3.0f;
    auto w = 4.0f;

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
    auto v      = Vector3 { 1.0f, 2.0f, 3.0f };
    auto w      = 4.0f;
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
    auto axis     = Vector3::Normalize({ 1.0f, 2.0f, 3.0f });
    auto angle    = Math::ToRadians(30.0f);
    auto expected = Quaternion(0.0691723f, 0.1383446f, 0.207516879f, 0.9659258f);
    auto actual   = Quaternion::CreateFromAxisAngle(axis, angle);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreateFromAxisAngle (Vector3f, float)
// CreateFromAxisAngle of zero vector
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, CreateFromAxisAngleOfZeroVector)
{
    auto axis   = Vector3 { };
    auto angle  = Math::ToRadians(-30.0f);
    auto cos    = Math::Cos(angle / 2.0f);
    auto actual = Quaternion::CreateFromAxisAngle(axis, angle);

    EXPECT_TRUE(0.0f == actual.X());
    EXPECT_TRUE(0.0f == actual.Y());
    EXPECT_TRUE(0.0f == actual.Z());
    EXPECT_TRUE(EqualityHelper::Equal(cos, actual.W()));
}

// A test for CreateFromAxisAngle (Vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, CreateFromAxisAngleOfAngle30And750)
{
    auto axis    = Vector3 { 1.0f, 0.0f, 0.0f };
    auto angle1  = Math::ToRadians(30.0f);
    auto angle2  = Math::ToRadians(750.0f);
    auto actual1 = Quaternion::CreateFromAxisAngle(axis, angle1);
    auto actual2 = Quaternion::CreateFromAxisAngle(axis, angle2);

    EXPECT_TRUE(EqualityHelper::Equal(actual1, actual2));
}

// A test for CreateFromAxisAngle (Vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, CreateFromAxisAngleOfAngle30And390)
{
    auto axis    = Vector3 { 1.0f, 0.0f, 0.0f };
    auto angle1  = Math::ToRadians(30.0f);
    auto angle2  = Math::ToRadians(390.0f);
    auto actual1 = Quaternion::CreateFromAxisAngle(axis, angle1);
    auto actual2 = Quaternion::CreateFromAxisAngle(axis, angle2);

    actual1.X(-actual1.X());
    actual1.W(-actual1.W());

    EXPECT_TRUE(EqualityHelper::Equal(actual1, actual2));
}

// A test for CreateFromAxisAngle (Vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, CreateFromYawPitchRoll)
{
    auto yawAngle   = Math::ToRadians(30.0f);
    auto pitchAngle = Math::ToRadians(40.0f);
    auto rollAngle  = Math::ToRadians(50.0f);

    auto yaw      = Quaternion::CreateFromAxisAngle(Vector3::UnitY, yawAngle);
    auto pitch    = Quaternion::CreateFromAxisAngle(Vector3::UnitX, pitchAngle);
    auto roll     = Quaternion::CreateFromAxisAngle(Vector3::UnitZ, rollAngle);
    auto expected = yaw * pitch * roll;
    auto actual   = Quaternion::CreateFromYawPitchRoll(yawAngle, pitchAngle, rollAngle);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// Covers more numeric rigions
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, CreateFromYawPitchRoll2)
{
    const auto step = 35.0f;

    for (float yawAngle = -720.0f; yawAngle <= 720.0f; yawAngle += step)
    {
        for (float pitchAngle = -720.0f; pitchAngle <= 720.0f; pitchAngle += step)
        {
            for (float rollAngle = -720.0f; rollAngle <= 720.0f; rollAngle += step)
            {
                auto yawRad   = Math::ToRadians(yawAngle);
                auto pitchRad = Math::ToRadians(pitchAngle);
                auto rollRad  = Math::ToRadians(rollAngle);

                auto yaw   = Quaternion::CreateFromAxisAngle(Vector3::UnitY, yawRad);
                auto pitch = Quaternion::CreateFromAxisAngle(Vector3::UnitX, pitchRad);
                auto roll  = Quaternion::CreateFromAxisAngle(Vector3::UnitZ, rollRad);

                auto expected = yaw * pitch * roll;
                auto actual   = Quaternion::CreateFromYawPitchRoll(yawRad, pitchRad, rollRad);

                EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
            }
        }
    }
}

// A test for Slerp (Quaternion, Quaternion, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Slerp)
{
    auto axis = Vector3::Normalize({ 1.0f, 2.0f, 3.0f });
    auto a    = Quaternion::CreateFromAxisAngle(axis, Math::ToRadians(10.0f));
    auto b    = Quaternion::CreateFromAxisAngle(axis, Math::ToRadians(30.0f));
    auto t    = 0.5f;

    auto expected = Quaternion::CreateFromAxisAngle(axis, Math::ToRadians(20.0f));
    auto actual   = Quaternion::Slerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Case a and b are same.
    expected = a;
    actual   = Quaternion::Slerp(a, a, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Slerp (Quaternion, Quaternion, float)
// Slerp test where t = 0
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, SlerpWithInterpolateZero)
{
    auto axis = Vector3::Normalize({ 1.0f, 2.0f, 3.0f });
    auto a    = Quaternion::CreateFromAxisAngle(axis, Math::ToRadians(10.0f));
    auto b    = Quaternion::CreateFromAxisAngle(axis, Math::ToRadians(30.0f));
    auto t    = 0.0f;

    auto expected = Quaternion { a.X(), a.Y(), a.Z(), a.W() };
    auto actual   = Quaternion::Slerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Slerp (Quaternion, Quaternion, float)
// Slerp test where t = 1
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, SlerpWithInterpolateOne)
{
    auto axis = Vector3::Normalize({ 1.0f, 2.0f, 3.0f });
    auto a    = Quaternion::CreateFromAxisAngle(axis, Math::ToRadians(10.0f));
    auto b    = Quaternion::CreateFromAxisAngle(axis, Math::ToRadians(30.0f));
    auto t    = 1.0f;

    auto expected = Quaternion { b.X(), b.Y(), b.Z(), b.W() };
    auto actual   = Quaternion::Slerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Slerp (Quaternion, Quaternion, float)
// Slerp test where dot product is < 0
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, SlerpWithDotProductLessThanZero)
{
    auto axis = Vector3::Normalize({ 1.0f, 2.0f, 3.0f });
    auto a    = Quaternion::CreateFromAxisAngle(axis, Math::ToRadians(10.0f));
    auto b    = -a;
    auto t    = 1.0f;

    auto expected = a;
    auto actual   = Quaternion::Slerp(a, b, t);

    // Note that in quaternion world, Q == -Q. In the case of quaternions dot product is zero,
    // one of the quaternion will be flipped to compute the shortest distance. When t = 1, we
    // expect the result to be the same as quaternion b but flipped.
    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Slerp (Quaternion, Quaternion, float)
// Slerp test where the quaternion is flipped
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, SlerpWithFlippedQuaternion)
{
    auto axis = Vector3::Normalize({ 1.0f, 2.0f, 3.0f });
    auto a    = Quaternion::CreateFromAxisAngle(axis, Math::ToRadians(10.0f));
    auto b    = -Quaternion::CreateFromAxisAngle(axis, Math::ToRadians(30.0f));
    auto t    = 0.0f;

    auto expected = Quaternion { a.X(), a.Y(), a.Z(), a.W() };
    auto actual   = Quaternion::Slerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for operator - (Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, UnaryNegation)
{
    auto a        = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto expected = Quaternion { -1.0f, -2.0f, -3.0f, -4.0f };
    auto actual   = -a;

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Inverse (Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Inverse)
{
    auto a        = Quaternion { 5.0f, 6.0f, 7.0f, 8.0f };
    auto expected = Quaternion { -0.0287356321f, -0.03448276f, -0.0402298868f, 0.04597701f };
    auto actual   = Quaternion::Inverse(a);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Inverse (Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, InvertZeroLengthQuaternion)
{
    auto a      = Quaternion { };
    auto actual = Quaternion::Inverse(a);

    EXPECT_TRUE(Math::IsNaN(actual.X()));
    EXPECT_TRUE(Math::IsNaN(actual.Y()));
    EXPECT_TRUE(Math::IsNaN(actual.Z()));
    EXPECT_TRUE(Math::IsNaN(actual.W()));
}

// A test for negate (Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Negate)
{
    auto a        = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto expected = Quaternion { -1.0f, -2.0f, -3.0f, -4.0f };
    auto actual   = Quaternion::Negate(a);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
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

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // make sure convert back to matrix is same as we passed matrix.
    auto m2 = Matrix::CreateFromQuaternion(actual);

    EXPECT_TRUE(EqualityHelper::Equal(matrix, m2));
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, ConvertXAxisRotationMatrix)
{
    for (float angle = 0.0f; angle < 720.0f; angle += 10.0f)
    {
        auto matrix   = Matrix::CreateRotationX(angle);
        auto expected = Quaternion::CreateFromAxisAngle(Vector3::UnitX, angle);
        auto actual   = Quaternion::CreateFromRotationMatrix(matrix);

        EXPECT_TRUE(EqualityHelper::EqualRotation(expected, actual));

        // make sure convert back to matrix is same as we passed matrix.
        auto m2 = Matrix::CreateFromQuaternion(actual);

        EXPECT_TRUE(EqualityHelper::Equal(matrix, m2));
    }
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, ConvertYAxisRotationMatrix)
{
    for (float angle = 0.0f; angle < 720.0f; angle += 10.0f)
    {
        auto matrix   = Matrix::CreateRotationY(angle);
        auto expected = Quaternion::CreateFromAxisAngle(Vector3::UnitY, angle);
        auto actual   = Quaternion::CreateFromRotationMatrix(matrix);

        EXPECT_TRUE(EqualityHelper::EqualRotation(expected, actual));

        // make sure convert back to matrix is same as we passed matrix.
        auto m2 = Matrix::CreateFromQuaternion(actual);

        EXPECT_TRUE(EqualityHelper::Equal(matrix, m2));
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

        EXPECT_TRUE(EqualityHelper::EqualRotation(expected, actual));

        // make sure convert back to matrix is same as we passed matrix.
        auto m2 = Matrix::CreateFromQuaternion(actual);

        EXPECT_TRUE(EqualityHelper::Equal(matrix, m2));
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

        EXPECT_TRUE(EqualityHelper::EqualRotation(expected, actual));

        // make sure convert back to matrix is same as we passed matrix.
        auto m2 = Matrix::CreateFromQuaternion(actual);

        EXPECT_TRUE(EqualityHelper::Equal(matrix, m2));
    }
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, FromRotationMatrixWithScaledMatrixOnXAxis)
{
    auto angle  = Math::ToRadians(180.0f);
    auto matrix = Matrix::CreateRotationY(angle)
                * Matrix::CreateRotationZ(angle);

    auto expected = Quaternion::CreateFromAxisAngle(Vector3::UnitZ, angle)
                  * Quaternion::CreateFromAxisAngle(Vector3::UnitY, angle);
    auto actual   = Quaternion::CreateFromRotationMatrix(matrix);

    EXPECT_TRUE(EqualityHelper::EqualRotation(expected, actual));

    // make sure convert back to matrix is same as we passed matrix.
    auto m2 = Matrix::CreateFromQuaternion(actual);

    EXPECT_TRUE(EqualityHelper::Equal(matrix, m2));
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, FromRotationMatrixWithScaledMatrixOnYAxis)
{
    auto angle  = Math::ToRadians(180.0f);
    auto matrix = Matrix::CreateRotationX(angle)
                * Matrix::CreateRotationZ(angle);

    auto expected = Quaternion::CreateFromAxisAngle(Vector3::UnitZ, angle)
                  * Quaternion::CreateFromAxisAngle(Vector3::UnitX, angle);
    auto actual   = Quaternion::CreateFromRotationMatrix(matrix);

    EXPECT_TRUE(EqualityHelper::EqualRotation(expected, actual));

    // make sure convert back to matrix is same as we passed matrix.
    auto m2 = Matrix::CreateFromQuaternion(actual);

    EXPECT_TRUE(EqualityHelper::Equal(matrix, m2));
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, FromRotationMatrixWithScaledMatrixOnZAxis)
{
    auto angle  = Math::ToRadians(180.0f);
    auto matrix = Matrix::CreateRotationX(angle)
                * Matrix::CreateRotationY(angle);

    auto expected = Quaternion::CreateFromAxisAngle(Vector3::UnitY, angle)
                  * Quaternion::CreateFromAxisAngle(Vector3::UnitX, angle);
    auto actual   = Quaternion::CreateFromRotationMatrix(matrix);

    EXPECT_TRUE(EqualityHelper::EqualRotation(expected, actual));

    // make sure convert back to matrix is same as we passed matrix.
    auto m2 = Matrix::CreateFromQuaternion(actual);

    EXPECT_TRUE(EqualityHelper::Equal(matrix, m2));
}

// A test for Identity
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Identity)
{
    auto actual = Quaternion { 0.0f, 0.0f, 0.0f, 1.0f };

    EXPECT_TRUE(EqualityHelper::Equal(Quaternion::Identity, actual));
}

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

// A test for Quaternion comparison involving NaN values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, EqualsNan)
{
    auto a = Quaternion { Math::NaN, 0, 0, 0 };
    auto b = Quaternion { 0, Math::NaN, 0, 0 };
    auto c = Quaternion { 0, 0, Math::NaN, 0 };
    auto d = Quaternion { 0, 0, 0, Math::NaN };
    auto z = Quaternion { 0, 0, 0, 0 };

    EXPECT_FALSE(a == z);
    EXPECT_FALSE(b == z);
    EXPECT_FALSE(c == z);
    EXPECT_FALSE(d == z);

    EXPECT_TRUE(a != z);
    EXPECT_TRUE(b != z);
    EXPECT_TRUE(c != z);
    EXPECT_TRUE(d != z);

    EXPECT_FALSE(a.IsIdentity());
    EXPECT_FALSE(b.IsIdentity());
    EXPECT_FALSE(c.IsIdentity());
    EXPECT_FALSE(d.IsIdentity());
}
