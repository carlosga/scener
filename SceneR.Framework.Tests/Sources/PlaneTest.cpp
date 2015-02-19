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

// A test for Plane (Vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, ConstructorFromVector3AndScalar)
{
    Vector3 normal { 1, 2, 3 };
    Single  d = 4;

    Plane target = { normal, d };

    EXPECT_TRUE(target.Normal() == normal && target.D() == d);
}

// A test for Plane (Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, ConstructorFromVector4)
{
    Vector4 value { 1.0f, 2.0f, 3.0f, 4.0f };
    Plane   target { value };

    EXPECT_TRUE(target.Normal().X() == value.X()
             && target.Normal().Y() == value.Y()
             && target.Normal().Z() == value.Z()
             && target.D()          == value.W());
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, Dot)
{
    Plane   target { 2, 3, 4, 5 };
    Vector4 value  { 5, 4, 3, 2 };

    Single expected = 10 + 12 + 12 + 10;
    Single actual   = Plane::Dot(target, value);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, DotCoordinate)
{
    Plane   target { 2, 3, 4, 5 };
    Vector3 value  { 5, 4, 3 };

    Single expected = 10 + 12 + 12 + 5;
    Single actual   = Plane::DotCoordinate(target, value);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, DotNormal)
{
    Plane   target { 2, 3, 4, 5 };
    Vector3 value  { 5, 4, 3 };

    Single expected = 10 + 12 + 12;
    Single actual   = Plane::DotNormal(target, value);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, Normalize)
{
    Plane target { 1, 2, 3, 4 };

    Single f        = target.Normal().LengthSquared();
    Single invF     = 1.0f / Math::Sqrt(f);
    Plane  expected { target.Normal() * invF, target.D() * invF };

    auto actual = Plane::Normalize(target);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // normalize, normalized normal.
    actual = Plane::Normalize(actual);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// Transform by matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, TransformByMatrix)
{
    auto target = Plane::Normalize({ 1, 2, 3, 4 });
    auto m      = Matrix::CreateRotationX(Math::ToRadians(30.0f))
                * Matrix::CreateRotationY(Math::ToRadians(30.0f))
                * Matrix::CreateRotationZ(Math::ToRadians(30.0f));

    m.M41(10.0f);
    m.M42(20.0f);
    m.M43(30.0f);

    Plane expected;
    auto inv = Matrix::Invert(m);
    auto itm = Matrix::Transpose(inv);

    Single x = target.Normal().X();
    Single y = target.Normal().Y();
    Single z = target.Normal().Z();
    Single w = target.D();

    expected.Normal({ x * itm.M11() + y * itm.M21() + z * itm.M31() + w * itm.M41()
                    , x * itm.M12() + y * itm.M22() + z * itm.M32() + w * itm.M42()
                    , x * itm.M13() + y * itm.M23() + z * itm.M33() + w * itm.M43() });

    expected.D(x * itm.M14() + y * itm.M24() + z * itm.M34() + w * itm.M44());

    auto actual = Plane::Transform(target, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// Transform by quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, TransformByQuaternion)
{
    auto target = Plane::Normalize({ 1, 2, 3, 4 });
    auto m      = Matrix::CreateRotationX(Math::ToRadians(30.0f))
                * Matrix::CreateRotationY(Math::ToRadians(30.0f))
                * Matrix::CreateRotationZ(Math::ToRadians(30.0f));

    m.M41(10.0f);
    m.M42(20.0f);
    m.M43(30.0f);

    auto q = Quaternion::CreateFromRotationMatrix(m);

    Plane expected;

    Single x = target.Normal().X();
    Single y = target.Normal().Y();
    Single z = target.Normal().Z();
    Single w = target.D();

    expected.Normal({ x * m.M11() + y * m.M21() + z * m.M31() + w * m.M41()
                    , x * m.M12() + y * m.M22() + z * m.M32() + w * m.M42()
                    , x * m.M13() + y * m.M23() + z * m.M33() + w * m.M43() });

    expected.D(x * m.M14() + y * m.M24() + z * m.M34() + w * m.M44());

    auto actual = Plane::Transform(target, q);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Plane comparison involving NaN values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, EqualsNaN)
{
    Plane a = { Math::NaN, 0, 0, 0 };
    Plane b = { 0, Math::NaN, 0, 0 };
    Plane c = { 0, 0, Math::NaN, 0 };
    Plane d = { 0, 0, 0, Math::NaN };
    Plane z = { 0, 0, 0, 0 };

    EXPECT_FALSE(a == z);
    EXPECT_FALSE(c == z);
    EXPECT_FALSE(d == z);
    EXPECT_FALSE(b == z);

    EXPECT_TRUE(a != z);
    EXPECT_TRUE(b != z);
    EXPECT_TRUE(c != z);
    EXPECT_TRUE(d != z);
}
