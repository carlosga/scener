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

    EXPECT_TRUE(1.0f == q.x);
    EXPECT_TRUE(2.0f == q.y);
    EXPECT_TRUE(3.0f == q.z);
    EXPECT_TRUE(4.0f == q.w);
}

TEST_F(QuaternionTest, QuaternionConjugate)
{
    auto actual = Quaternion::conjugate({ 5.0f, 6.0f, 7.0f, 8.0f });

    EXPECT_TRUE(-5.0f == actual.x);
    EXPECT_TRUE(-6.0f == actual.y);
    EXPECT_TRUE(-7.0f == actual.z);
    EXPECT_TRUE(8.0f  == actual.w);
}

TEST_F(QuaternionTest, QuaternionMultiplication)
{
    auto q1 = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto q2 = Quaternion { 5.0f, 6.0f, 7.0f, 8.0f };
    auto qr = q1 * q2;

    // quaternion Result is equal to (24, 48, 48, -6)
    EXPECT_TRUE(24.0f == qr.x);
    EXPECT_TRUE(48.0f == qr.y);
    EXPECT_TRUE(48.0f == qr.z);
    EXPECT_TRUE(-6.0f == qr.w);
}

TEST_F(QuaternionTest, CalculateQuaternionFromAxisAngle)
{
    auto result = Quaternion::create_from_axis_angle({ 1.0f, 0.0f, 0.0f }, Math::pi_over_2);

    // quaternion Result is equal to (0.707106769, 0, 0, 0.707106769)
    EXPECT_TRUE(0.707106769f == result.x);
    EXPECT_TRUE(0.0f         == result.y);
    EXPECT_TRUE(0.0f         == result.z);
    EXPECT_TRUE(0.707106769f == result.w);
}

// A test for Dot (Quaternion, Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Dot)
{
    auto a = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto b = Quaternion { 5.0f, 6.0f, 7.0f, 8.0f };

    auto expected = 70.0f;
    auto actual   = Quaternion::dot(a, b);

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
    auto actual   = target.length();

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
    auto actual   = target.length_squared();

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Quaternion, Quaternion, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Lerp)
{
    auto axis     = Vector3::normalize({ 1.0f, 2.0f, 3.0f });
    auto a        = Quaternion::create_from_axis_angle(axis, Math::to_radians(10.0f));
    auto b        = Quaternion::create_from_axis_angle(axis, Math::to_radians(30.0f));
    auto t        = 0.5f;
    auto expected = Quaternion::create_from_axis_angle(axis, Math::to_radians(20.0f));
    auto actual   = Quaternion::lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Case a and b are same.
    expected = a;
    actual   = Quaternion::lerp(a, a, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Quaternion, Quaternion, float)
// Lerp test when t = 0
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, LerpWithInterpolateZero)
{
    auto axis     = Vector3::normalize({ 1.0f, 2.0f, 3.0f });
    auto a        = Quaternion::create_from_axis_angle(axis, Math::to_radians(10.0f));
    auto b        = Quaternion::create_from_axis_angle(axis, Math::to_radians(30.0f));
    auto t        = 0.0f;
    auto expected = Quaternion { a.x, a.y, a.z, a.w };
    auto actual   = Quaternion::lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Quaternion, Quaternion, float)
// Lerp test when t = 1
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, LerpWithInterpolateOne)
{
    auto axis     = Vector3::normalize({ 1.0f, 2.0f, 3.0f });
    auto a        = Quaternion::create_from_axis_angle(axis, Math::to_radians(10.0f));
    auto b        = Quaternion::create_from_axis_angle(axis, Math::to_radians(30.0f));
    auto t        = 1.0f;
    auto expected = Quaternion { b.x, b.y, b.z, b.w };
    auto actual   = Quaternion::lerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Lerp (Quaternion, Quaternion, float)
// Lerp test when the two quaternions are more than 90 degree (dot product <0)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, LerpWithQuaternionsWithMoreThan90Degrees)
{
    auto axis   = Vector3::normalize({ 1.0f, 2.0f, 3.0f });
    auto a      = Quaternion::create_from_axis_angle(axis, Math::to_radians(10.0f));
    auto b      = Quaternion::negate(a);
    auto t      = 1.0f;
    auto actual = Quaternion::lerp(a, b, t);

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
    auto actual   = Quaternion::conjugate(a);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Normalize (Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Normalize)
{
    auto a        = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto expected = Quaternion { 0.182574168f, 0.365148336f, 0.5477225f, 0.7302967f };
    auto actual   = Quaternion::normalize(a);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Normalize (Quaternion)
// Normalize zero length quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, NormalizeZeroLengthQuaternion)
{
    auto a      = Quaternion { 0.0f, 0.0f, -0.0f, 0.0f };
    auto actual = Quaternion::normalize(a);

    EXPECT_TRUE(Math::is_nan(actual.x));
    EXPECT_TRUE(Math::is_nan(actual.y));
    EXPECT_TRUE(Math::is_nan(actual.z));
    EXPECT_TRUE(Math::is_nan(actual.w));
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

    EXPECT_TRUE(x == target.x);
    EXPECT_TRUE(y == target.y);
    EXPECT_TRUE(z == target.z);
    EXPECT_TRUE(w == target.w);
}

// A test for Quaternion (Vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, ConstructorWithVector3)
{
    auto v      = Vector3 { 1.0f, 2.0f, 3.0f };
    auto w      = 4.0f;
    auto target = Quaternion { v, w };

    EXPECT_TRUE(v.x == target.x);
    EXPECT_TRUE(v.y == target.y);
    EXPECT_TRUE(v.z == target.z);
    EXPECT_TRUE(w   == target.w);
}

// A test for CreateFromAxisAngle (Vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, CreateFromAxisAngle)
{
    auto axis     = Vector3::normalize({ 1.0f, 2.0f, 3.0f });
    auto angle    = Math::to_radians(30.0f);
    auto expected = Quaternion(0.0691723f, 0.1383446f, 0.207516879f, 0.9659258f);
    auto actual   = Quaternion::create_from_axis_angle(axis, angle);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for CreateFromAxisAngle (Vector3f, float)
// CreateFromAxisAngle of zero vector
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, CreateFromAxisAngleOfZeroVector)
{
    auto axis   = Vector3 { };
    auto angle  = Math::to_radians(-30.0f);
    auto cos    = Math::cos(angle / 2.0f);
    auto actual = Quaternion::create_from_axis_angle(axis, angle);

    EXPECT_TRUE(0.0f == actual.x);
    EXPECT_TRUE(0.0f == actual.y);
    EXPECT_TRUE(0.0f == actual.z);
    EXPECT_TRUE(EqualityHelper::Equal(cos, actual.w));
}

// A test for CreateFromAxisAngle (Vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, CreateFromAxisAngleOfAngle30And750)
{
    auto axis    = Vector3 { 1.0f, 0.0f, 0.0f };
    auto angle1  = Math::to_radians(30.0f);
    auto angle2  = Math::to_radians(750.0f);
    auto actual1 = Quaternion::create_from_axis_angle(axis, angle1);
    auto actual2 = Quaternion::create_from_axis_angle(axis, angle2);

    EXPECT_TRUE(EqualityHelper::Equal(actual1, actual2));
}

// A test for CreateFromAxisAngle (Vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, CreateFromAxisAngleOfAngle30And390)
{
    auto axis    = Vector3 { 1.0f, 0.0f, 0.0f };
    auto angle1  = Math::to_radians(30.0f);
    auto angle2  = Math::to_radians(390.0f);
    auto actual1 = Quaternion::create_from_axis_angle(axis, angle1);
    auto actual2 = Quaternion::create_from_axis_angle(axis, angle2);

    actual1.x = -actual1.x;
    actual1.w = -actual1.w;

    EXPECT_TRUE(EqualityHelper::Equal(actual1, actual2));
}

// A test for CreateFromAxisAngle (Vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, CreateFromYawPitchRoll)
{
    auto yawAngle   = Math::to_radians(30.0f);
    auto pitchAngle = Math::to_radians(40.0f);
    auto rollAngle  = Math::to_radians(50.0f);

    auto yaw      = Quaternion::create_from_axis_angle(Vector3::unit_y, yawAngle);
    auto pitch    = Quaternion::create_from_axis_angle(Vector3::unit_x, pitchAngle);
    auto roll     = Quaternion::create_from_axis_angle(Vector3::unit_z, rollAngle);
    auto expected = yaw * pitch * roll;
    auto actual   = Quaternion::create_from_yaw_pitch_roll(yawAngle, pitchAngle, rollAngle);

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
                auto yawRad   = Math::to_radians(yawAngle);
                auto pitchRad = Math::to_radians(pitchAngle);
                auto rollRad  = Math::to_radians(rollAngle);

                auto yaw   = Quaternion::create_from_axis_angle(Vector3::unit_y, yawRad);
                auto pitch = Quaternion::create_from_axis_angle(Vector3::unit_x, pitchRad);
                auto roll  = Quaternion::create_from_axis_angle(Vector3::unit_z, rollRad);

                auto expected = yaw * pitch * roll;
                auto actual   = Quaternion::create_from_yaw_pitch_roll(yawRad, pitchRad, rollRad);

                EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
            }
        }
    }
}

// A test for Slerp (Quaternion, Quaternion, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Slerp)
{
    auto axis = Vector3::normalize({ 1.0f, 2.0f, 3.0f });
    auto a    = Quaternion::create_from_axis_angle(axis, Math::to_radians(10.0f));
    auto b    = Quaternion::create_from_axis_angle(axis, Math::to_radians(30.0f));
    auto t    = 0.5f;

    auto expected = Quaternion::create_from_axis_angle(axis, Math::to_radians(20.0f));
    auto actual   = Quaternion::slerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // Case a and b are same.
    expected = a;
    actual   = Quaternion::slerp(a, a, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Slerp (Quaternion, Quaternion, float)
// Slerp test where t = 0
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, SlerpWithInterpolateZero)
{
    auto axis = Vector3::normalize({ 1.0f, 2.0f, 3.0f });
    auto a    = Quaternion::create_from_axis_angle(axis, Math::to_radians(10.0f));
    auto b    = Quaternion::create_from_axis_angle(axis, Math::to_radians(30.0f));
    auto t    = 0.0f;

    auto expected = Quaternion { a.x, a.y, a.z, a.w };
    auto actual   = Quaternion::slerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Slerp (Quaternion, Quaternion, float)
// Slerp test where t = 1
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, SlerpWithInterpolateOne)
{
    auto axis = Vector3::normalize({ 1.0f, 2.0f, 3.0f });
    auto a    = Quaternion::create_from_axis_angle(axis, Math::to_radians(10.0f));
    auto b    = Quaternion::create_from_axis_angle(axis, Math::to_radians(30.0f));
    auto t    = 1.0f;

    auto expected = Quaternion { b.x, b.y, b.z, b.w };
    auto actual   = Quaternion::slerp(a, b, t);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Slerp (Quaternion, Quaternion, float)
// Slerp test where dot product is < 0
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, SlerpWithDotProductLessThanZero)
{
    auto axis = Vector3::normalize({ 1.0f, 2.0f, 3.0f });
    auto a    = Quaternion::create_from_axis_angle(axis, Math::to_radians(10.0f));
    auto b    = -a;
    auto t    = 1.0f;

    auto expected = a;
    auto actual   = Quaternion::slerp(a, b, t);

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
    auto axis = Vector3::normalize({ 1.0f, 2.0f, 3.0f });
    auto a    = Quaternion::create_from_axis_angle(axis, Math::to_radians(10.0f));
    auto b    = -Quaternion::create_from_axis_angle(axis, Math::to_radians(30.0f));
    auto t    = 0.0f;

    auto expected = Quaternion { a.x, a.y, a.z, a.w };
    auto actual   = Quaternion::slerp(a, b, t);

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
    auto actual   = Quaternion::inverse(a);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Inverse (Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, InvertZeroLengthQuaternion)
{
    auto a      = Quaternion { };
    auto actual = Quaternion::inverse(a);

    EXPECT_TRUE(Math::is_nan(actual.x));
    EXPECT_TRUE(Math::is_nan(actual.y));
    EXPECT_TRUE(Math::is_nan(actual.z));
    EXPECT_TRUE(Math::is_nan(actual.w));
}

// A test for negate (Quaternion)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, Negate)
{
    auto a        = Quaternion { 1.0f, 2.0f, 3.0f, 4.0f };
    auto expected = Quaternion { -1.0f, -2.0f, -3.0f, -4.0f };
    auto actual   = Quaternion::negate(a);

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
    b.x = 10.0f;

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
    b.x = 10.0f;

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
    auto actual   = Quaternion::create_from_rotation_matrix(matrix);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // make sure convert back to matrix is same as we passed matrix.
    auto m2 = Matrix::create_from_quaternion(actual);

    EXPECT_TRUE(EqualityHelper::Equal(matrix, m2));
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, ConvertXAxisRotationMatrix)
{
    for (float angle = 0.0f; angle < 720.0f; angle += 10.0f)
    {
        auto matrix   = Matrix::create_rotation_x(angle);
        auto expected = Quaternion::create_from_axis_angle(Vector3::unit_x, angle);
        auto actual   = Quaternion::create_from_rotation_matrix(matrix);

        EXPECT_TRUE(EqualityHelper::EqualRotation(expected, actual));

        // make sure convert back to matrix is same as we passed matrix.
        auto m2 = Matrix::create_from_quaternion(actual);

        EXPECT_TRUE(EqualityHelper::Equal(matrix, m2));
    }
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, ConvertYAxisRotationMatrix)
{
    for (float angle = 0.0f; angle < 720.0f; angle += 10.0f)
    {
        auto matrix   = Matrix::create_rotation_y(angle);
        auto expected = Quaternion::create_from_axis_angle(Vector3::unit_y, angle);
        auto actual   = Quaternion::create_from_rotation_matrix(matrix);

        EXPECT_TRUE(EqualityHelper::EqualRotation(expected, actual));

        // make sure convert back to matrix is same as we passed matrix.
        auto m2 = Matrix::create_from_quaternion(actual);

        EXPECT_TRUE(EqualityHelper::Equal(matrix, m2));
    }
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, ConvertZAxisRotationMatrix)
{
    for (float angle = 0.0f; angle < 720.0f; angle += 10.0f)
    {
        auto matrix   = Matrix::create_rotation_z(angle);
        auto expected = Quaternion::create_from_axis_angle(Vector3::unit_z, angle);
        auto actual   = Quaternion::create_from_rotation_matrix(matrix);

        EXPECT_TRUE(EqualityHelper::EqualRotation(expected, actual));

        // make sure convert back to matrix is same as we passed matrix.
        auto m2 = Matrix::create_from_quaternion(actual);

        EXPECT_TRUE(EqualityHelper::Equal(matrix, m2));
    }
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, ConvertXYZAxisRotationMatrix)
{
    for (float angle = 0.0f; angle < 720.0f; angle += 10.0f)
    {
        auto matrix   = Matrix::create_rotation_x(angle)
                      * Matrix::create_rotation_y(angle)
                      * Matrix::create_rotation_z(angle);

        auto expected = Quaternion::create_from_axis_angle(Vector3::unit_z, angle)
                      * Quaternion::create_from_axis_angle(Vector3::unit_y, angle)
                      * Quaternion::create_from_axis_angle(Vector3::unit_x, angle);

        auto actual = Quaternion::create_from_rotation_matrix(matrix);

        EXPECT_TRUE(EqualityHelper::EqualRotation(expected, actual));

        // make sure convert back to matrix is same as we passed matrix.
        auto m2 = Matrix::create_from_quaternion(actual);

        EXPECT_TRUE(EqualityHelper::Equal(matrix, m2));
    }
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, FromRotationMatrixWithScaledMatrixOnXAxis)
{
    auto angle  = Math::to_radians(180.0f);
    auto matrix = Matrix::create_rotation_y(angle)
                * Matrix::create_rotation_z(angle);

    auto expected = Quaternion::create_from_axis_angle(Vector3::unit_z, angle)
                  * Quaternion::create_from_axis_angle(Vector3::unit_y, angle);
    auto actual   = Quaternion::create_from_rotation_matrix(matrix);

    EXPECT_TRUE(EqualityHelper::EqualRotation(expected, actual));

    // make sure convert back to matrix is same as we passed matrix.
    auto m2 = Matrix::create_from_quaternion(actual);

    EXPECT_TRUE(EqualityHelper::Equal(matrix, m2));
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, FromRotationMatrixWithScaledMatrixOnYAxis)
{
    auto angle  = Math::to_radians(180.0f);
    auto matrix = Matrix::create_rotation_x(angle)
                * Matrix::create_rotation_z(angle);

    auto expected = Quaternion::create_from_axis_angle(Vector3::unit_z, angle)
                  * Quaternion::create_from_axis_angle(Vector3::unit_x, angle);
    auto actual   = Quaternion::create_from_rotation_matrix(matrix);

    EXPECT_TRUE(EqualityHelper::EqualRotation(expected, actual));

    // make sure convert back to matrix is same as we passed matrix.
    auto m2 = Matrix::create_from_quaternion(actual);

    EXPECT_TRUE(EqualityHelper::Equal(matrix, m2));
}

// A test for CreateFromRotationMatrix (Matrix4x4)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, FromRotationMatrixWithScaledMatrixOnZAxis)
{
    auto angle  = Math::to_radians(180.0f);
    auto matrix = Matrix::create_rotation_x(angle)
                * Matrix::create_rotation_y(angle);

    auto expected = Quaternion::create_from_axis_angle(Vector3::unit_y, angle)
                  * Quaternion::create_from_axis_angle(Vector3::unit_x, angle);
    auto actual   = Quaternion::create_from_rotation_matrix(matrix);

    EXPECT_TRUE(EqualityHelper::EqualRotation(expected, actual));

    // make sure convert back to matrix is same as we passed matrix.
    auto m2 = Matrix::create_from_quaternion(actual);

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
    EXPECT_TRUE (Quaternion::Identity.is_identity());
    EXPECT_TRUE (Quaternion(0, 0, 0, 1).is_identity());
    EXPECT_FALSE(Quaternion(1, 0, 0, 1).is_identity());
    EXPECT_FALSE(Quaternion(0, 1, 0, 1).is_identity());
    EXPECT_FALSE(Quaternion(0, 0, 1, 1).is_identity());
    EXPECT_FALSE(Quaternion(0, 0, 0, 0).is_identity());
}

// A test for Quaternion comparison involving NaN values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(QuaternionTest, EqualsNan)
{
    auto a = Quaternion { Math::nan, 0, 0, 0 };
    auto b = Quaternion { 0, Math::nan, 0, 0 };
    auto c = Quaternion { 0, 0, Math::nan, 0 };
    auto d = Quaternion { 0, 0, 0, Math::nan};
    auto z = Quaternion { 0, 0, 0, 0 };

    EXPECT_FALSE(a == z);
    EXPECT_FALSE(b == z);
    EXPECT_FALSE(c == z);
    EXPECT_FALSE(d == z);

    EXPECT_TRUE(a != z);
    EXPECT_TRUE(b != z);
    EXPECT_TRUE(c != z);
    EXPECT_TRUE(d != z);

    EXPECT_FALSE(a.is_identity());
    EXPECT_FALSE(b.is_identity());
    EXPECT_FALSE(c.is_identity());
    EXPECT_FALSE(d.is_identity());
}
