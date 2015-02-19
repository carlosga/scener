// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <PlaneTest.hpp>

#include <EqualityHelper.hpp>

#include <System/Math.hpp>
#include <Framework/Plane.hpp>
#include <Framework/Quaternion.hpp>

using namespace System;
using namespace SceneR::Framework;

TEST_F(PlaneTest, TransformPlaneByQuaternion)
{
    Plane      pin(1.0f, 0.0f, 0.0f, 0.0f);
    Quaternion q    = Quaternion::CreateFromAxisAngle(Vector3::UnitZ, Math::PiOver2);
    Plane      pout = Plane::Transform(pin, q);

    EXPECT_TRUE(0.0f        == pout.Normal().X());
    EXPECT_TRUE(0.99999994f == pout.Normal().Y());
    EXPECT_TRUE(0.0f        == pout.Normal().Z());
    EXPECT_TRUE(0.0f        == pout.D());
}

// A test to make sure these types are blittable directly into GPU buffer memory layouts
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, Sizeof)
{
    EXPECT_TRUE(16 == sizeof(Plane));
}

// A test for operator != (Plane, Plane)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, Inequality)
{
    Plane a { 1.0f, 2.0f, 3.0f, 4.0f };
    Plane b { 1.0f, 2.0f, 3.0f, 4.0f };

    // case 1: compare between same values
    bool expected = false;
    bool actual   = a != b;

    EXPECT_TRUE(expected == actual);

    // case 2: compare between different values
    b.Normal({ 10.0f, b.Normal().Y(), b.Normal().Z() });

    expected = true;
    actual   = a != b;

    EXPECT_TRUE(expected == actual);
}

// A test for operator == (Plane, Plane)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, Equality)
{
    Plane a { 1.0f, 2.0f, 3.0f, 4.0f };
    Plane b { 1.0f, 2.0f, 3.0f, 4.0f };

    // case 1: compare between same values
    bool expected = true;
    bool actual   = a == b;

    EXPECT_TRUE(expected == actual);

    // case 2: compare between different values
    b.Normal({ 10.0f, b.Normal().Y(), b.Normal().Z() });

    expected = false;
    actual   = a == b;

    EXPECT_TRUE(expected == actual);
}

// A test for Plane (float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, Constructor)
{
    Single a = 1.0f;
    Single b = 2.0f;
    Single c = 3.0f;
    Single d = 4.0f;
    Plane target { a, b, c, d };

    EXPECT_TRUE(target.Normal().X() == a
             && target.Normal().Y() == b
             && target.Normal().Z() == c
             && target.D() == d);
}

// A test for Plane.CreateFromVertices
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, CreateFromVertices)
{
    Vector3 point1 { 0.0f, 1.0f, 1.0f };
    Vector3 point2 { 0.0f, 0.0f, 1.0f };
    Vector3 point3 { 1.0f, 0.0f, 1.0f };

    Plane target   = Plane::CreateFromVertices(point1, point2, point3);
    Plane expected = {{ 0, 0, 1 }, -1.0f };

    EXPECT_TRUE(target == expected);
}

// A test for Plane.CreateFromVertices
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, CreateFromVertices2)
{
    Vector3 point1 { 0.0f, 0.0f, 1.0f };
    Vector3 point2 { 1.0f, 0.0f, 0.0f };
    Vector3 point3 { 1.0f, 1.0f, 0.0f };

    Plane  target   = Plane::CreateFromVertices(point1, point2, point3);
    Single invRoot2 = (Single)(1 / Math::Sqrt(2.0f));

    Plane expected { { invRoot2, 0, invRoot2 }, -invRoot2 };

    EXPECT_TRUE(EqualityHelper::Equal(target, expected));
}

/*
// A test for Plane (Vector3f, float)
[Fact]
public void PlaneConstructorTest3()
{
    Vector3 normal = new Vector3(1, 2, 3);
    float d = 4;

    Plane target = new Plane(normal, d);
    Assert.True(
        target.Normal == normal && target.D == d,
        "Plane.cstor did not return the expected value.");
}

// A test for Plane (Vector4f)
[Fact]
public void PlaneConstructorTest()
{
    Vector4 value = new Vector4(1.0f, 2.0f, 3.0f, 4.0f);
    Plane target = new Plane(value);

    Assert.True(
        target.Normal.X == value.X && target.Normal.Y == value.Y && target.Normal.Z == value.Z && target.D == value.W,
        "Plane.cstor did not return the expected value.");
}

[Fact]
public void PlaneDotTest()
{
    Plane target = new Plane(2, 3, 4, 5);
    Vector4 value = new Vector4(5, 4, 3, 2);

    float expected = 10 + 12 + 12 + 10;
    float actual = Plane.Dot(target, value);
    Assert.True(MathHelper.Equal(expected, actual), "Plane.Dot returns unexpected value.");
}

[Fact]
public void PlaneDotCoordinateTest()
{
    Plane target = new Plane(2, 3, 4, 5);
    Vector3 value = new Vector3(5, 4, 3);

    float expected = 10 + 12 + 12 + 5;
    float actual = Plane.DotCoordinate(target, value);
    Assert.True(MathHelper.Equal(expected, actual), "Plane.DotCoordinate returns unexpected value.");
}

[Fact]
public void PlaneDotNormalTest()
{
    Plane target = new Plane(2, 3, 4, 5);
    Vector3 value = new Vector3(5, 4, 3);

    float expected = 10 + 12 + 12;
    float actual = Plane.DotNormal(target, value);
    Assert.True(MathHelper.Equal(expected, actual), "Plane.DotCoordinate returns unexpected value.");
}

[Fact]
public void PlaneNormalizeTest()
{
    Plane target = new Plane(1, 2, 3, 4);

    float f = target.Normal.LengthSquared();
    float invF = 1.0f / (float)Math.Sqrt(f);
    Plane expected = new Plane(target.Normal * invF, target.D * invF);

    Plane actual = Plane.Normalize(target);
    Assert.True(MathHelper.Equal(expected, actual), "Plane.Normalize returns unexpected value.");

    // normalize, normalized normal.
    actual = Plane.Normalize(actual);
    Assert.True(MathHelper.Equal(expected, actual), "Plane.Normalize returns unexpected value.");
}

[Fact]
// Transform by matrix
public void PlaneTransformTest1()
{
    Plane target = new Plane(1, 2, 3, 4);
    target = Plane.Normalize(target);

    Matrix4x4 m =
        Matrix4x4.CreateRotationX(MathHelper.ToRadians(30.0f)) *
        Matrix4x4.CreateRotationY(MathHelper.ToRadians(30.0f)) *
        Matrix4x4.CreateRotationZ(MathHelper.ToRadians(30.0f));
    m.M41 = 10.0f;
    m.M42 = 20.0f;
    m.M43 = 30.0f;

    Plane expected = new Plane();
    Matrix4x4 inv;
    Matrix4x4.Invert(m, out inv);
    Matrix4x4 itm = Matrix4x4.Transpose(inv);
    float x = target.Normal.X, y = target.Normal.Y, z = target.Normal.Z, w = target.D;
    expected.Normal = new Vector3(
        x * itm.M11 + y * itm.M21 + z * itm.M31 + w * itm.M41,
        x * itm.M12 + y * itm.M22 + z * itm.M32 + w * itm.M42,
        x * itm.M13 + y * itm.M23 + z * itm.M33 + w * itm.M43);
    expected.D = x * itm.M14 + y * itm.M24 + z * itm.M34 + w * itm.M44;

    Plane actual;
    actual = Plane.Transform(target, m);
    Assert.True(MathHelper.Equal(expected, actual), "Plane.Transform did not return the expected value.");
}

[Fact]
// Transform by quaternion
public void PlaneTransformTest2()
{
    Plane target = new Plane(1, 2, 3, 4);
    target = Plane.Normalize(target);

    Matrix4x4 m =
        Matrix4x4.CreateRotationX(MathHelper.ToRadians(30.0f)) *
        Matrix4x4.CreateRotationY(MathHelper.ToRadians(30.0f)) *
        Matrix4x4.CreateRotationZ(MathHelper.ToRadians(30.0f));
    Quaternion q = Quaternion.CreateFromRotationMatrix(m);

    Plane expected = new Plane();
    float x = target.Normal.X, y = target.Normal.Y, z = target.Normal.Z, w = target.D;
    expected.Normal = new Vector3(
        x * m.M11 + y * m.M21 + z * m.M31 + w * m.M41,
        x * m.M12 + y * m.M22 + z * m.M32 + w * m.M42,
        x * m.M13 + y * m.M23 + z * m.M33 + w * m.M43);
    expected.D = x * m.M14 + y * m.M24 + z * m.M34 + w * m.M44;

    Plane actual;
    actual = Plane.Transform(target, q);
    Assert.True(MathHelper.Equal(expected, actual), "Plane.Transform did not return the expected value.");
}

// A test for Plane comparison involving NaN values
[Fact]
public void PlaneEqualsNanTest()
{
    Plane a = new Plane(float.NaN, 0, 0, 0);
    Plane b = new Plane(0, float.NaN, 0, 0);
    Plane c = new Plane(0, 0, float.NaN, 0);
    Plane d = new Plane(0, 0, 0, float.NaN);

    Assert.False(a == new Plane(0, 0, 0, 0));
    Assert.False(b == new Plane(0, 0, 0, 0));
    Assert.False(c == new Plane(0, 0, 0, 0));
    Assert.False(d == new Plane(0, 0, 0, 0));

    Assert.True(a != new Plane(0, 0, 0, 0));
    Assert.True(b != new Plane(0, 0, 0, 0));
    Assert.True(c != new Plane(0, 0, 0, 0));
    Assert.True(d != new Plane(0, 0, 0, 0));

    Assert.False(a.Equals(new Plane(0, 0, 0, 0)));
    Assert.False(b.Equals(new Plane(0, 0, 0, 0)));
    Assert.False(c.Equals(new Plane(0, 0, 0, 0)));
    Assert.False(d.Equals(new Plane(0, 0, 0, 0)));

    // Counterintuitive result - IEEE rules for NaN comparison are weird!
    Assert.False(a.Equals(a));
    Assert.False(b.Equals(b));
    Assert.False(c.Equals(c));
    Assert.False(d.Equals(d));
}

// A test to make sure the fields are laid out how we expect
[Fact]
public unsafe void PlaneFieldOffsetTest()
{
    Plane* ptr = (Plane*)0;

    EXPECT_TRUE(new IntPtr(0), new IntPtr(&ptr->Normal));
    EXPECT_TRUE(new IntPtr(12), new IntPtr(&ptr->D));
}
*/
