// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PlaneTest.hpp"

#include "EqualityHelper.hpp"

#include <SceneR/Math/Math.hpp>
#include <SceneR/Math/Plane.hpp>
#include <SceneR/Math/Quaternion.hpp>

using namespace SceneR::Math;

TEST_F(PlaneTest, TransformPlaneByQuaternion)
{
    Plane      pin(1.0f, 0.0f, 0.0f, 0.0f);
    Quaternion q    = Quaternion::create_from_axis_angle(Vector3::unit_z, SceneR::Math::pi_over_2);
    Plane      pout = Plane::transform(pin, q);

    EXPECT_TRUE(0.0f        == pout.normal.x);
    EXPECT_TRUE(0.99999994f == pout.normal.y);
    EXPECT_TRUE(0.0f        == pout.normal.z);
    EXPECT_TRUE(0.0f        == pout.d);
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
    b.normal = { 10.0f, b.normal.y, b.normal.z };

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
    b.normal = { 10.0f, b.normal.y, b.normal.z };

    expected = false;
    actual   = a == b;

    EXPECT_TRUE(expected == actual);
}

// A test for Plane (float, float, float, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, Constructor)
{
    auto  a = 1.0f;
    auto  b = 2.0f;
    auto  c = 3.0f;
    auto  d = 4.0f;
    Plane target { a, b, c, d };

    EXPECT_TRUE(target.normal.x == a
             && target.normal.y == b
             && target.normal.z == c
             && target.d == d);
}

// A test for Plane.CreateFromVertices
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, CreateFromVertices)
{
    Vector3 point1 { 0.0f, 1.0f, 1.0f };
    Vector3 point2 { 0.0f, 0.0f, 1.0f };
    Vector3 point3 { 1.0f, 0.0f, 1.0f };

    Plane target   = Plane::create_from_vertices(point1, point2, point3);
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

    Plane target   = Plane::create_from_vertices(point1, point2, point3);
    auto  invRoot2 = (1.0f / SceneR::Math::sqrt(2.0f));

    Plane expected { { invRoot2, 0, invRoot2 }, -invRoot2 };

    EXPECT_TRUE(EqualityHelper::Equal(target, expected));
}

// A test for Plane (Vector3f, float)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, ConstructorFromVector3AndScalar)
{
    Vector3 normal { 1.0f, 2.0f, 3.0f };
    auto    d = 4.0f;

    Plane target = { normal, d };

    EXPECT_TRUE(target.normal == normal && target.d == d);
}

// A test for Plane (Vector4f)
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, ConstructorFromVector4)
{
    Vector4 value { 1.0f, 2.0f, 3.0f, 4.0f };
    Plane   target { value };

    EXPECT_TRUE(target.normal.x == value.x
             && target.normal.y == value.y
             && target.normal.z == value.z
             && target.d        == value.w);
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, Dot)
{
    Plane   target { 2, 3, 4, 5 };
    Vector4 value  { 5, 4, 3, 2 };

    float expected = 10 + 12 + 12 + 10;
    float actual   = Plane::dot(target, value);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, DotCoordinate)
{
    Plane   target { 2, 3, 4, 5 };
    Vector3 value  { 5, 4, 3 };

    float expected = 10 + 12 + 12 + 5;
    float actual   = Plane::dot_coordinate(target, value);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, DotNormal)
{
    Plane   target { 2, 3, 4, 5 };
    Vector3 value  { 5, 4, 3 };

    float expected = 10 + 12 + 12;
    float actual   = Plane::dot_normal(target, value);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, Normalize)
{
    Plane target { 1, 2, 3, 4 };

    float f        = target.normal.length_squared();
    float invF     = 1.0f / SceneR::Math::sqrt(f);
    Plane expected { target.normal * invF, target.d * invF };

    auto actual = Plane::normalize(target);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));

    // normalize, normalized normal.
    actual = Plane::normalize(actual);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// Transform by matrix
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, TransformByMatrix)
{
    auto target = Plane::normalize({ 1, 2, 3, 4 });
    auto m      = Matrix::create_rotation_x(SceneR::Math::to_radians(30.0f))
                * Matrix::create_rotation_y(SceneR::Math::to_radians(30.0f))
                * Matrix::create_rotation_z(SceneR::Math::to_radians(30.0f));

    m.m41 = 10.0f;
    m.m42 = 20.0f;
    m.m43 = 30.0f;

    Plane expected;

    auto inv = Matrix::invert(m);
    auto itm = Matrix::transpose(inv);
    auto x   = target.normal.x;
    auto y   = target.normal.y;
    auto z   = target.normal.z;
    auto w   = target.d;

    expected.normal = { x * itm.m11 + y * itm.m21 + z * itm.m31 + w * itm.m41
                      , x * itm.m12 + y * itm.m22 + z * itm.m32 + w * itm.m42
                      , x * itm.m13 + y * itm.m23 + z * itm.m33 + w * itm.m43 };

    expected.d = (x * itm.m14 + y * itm.m24 + z * itm.m34 + w * itm.m44);

    auto actual = Plane::transform(target, m);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// Transform by quaternion
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, TransformByQuaternion)
{
    auto target = Plane::normalize({ 1, 2, 3, 4 });
    auto m      = Matrix::create_rotation_x(SceneR::Math::to_radians(30.0f))
                * Matrix::create_rotation_y(SceneR::Math::to_radians(30.0f))
                * Matrix::create_rotation_z(SceneR::Math::to_radians(30.0f));
    auto q      = Quaternion::create_from_rotation_matrix(m);

    Plane expected;

    auto x = target.normal.x;
    auto y = target.normal.y;
    auto z = target.normal.z;
    auto w = target.d;

    expected.normal = { x * m.m11 + y * m.m21 + z * m.m31 + w * m.m41
                      , x * m.m12 + y * m.m22 + z * m.m32 + w * m.m42
                      , x * m.m13 + y * m.m23 + z * m.m33 + w * m.m43 };

    expected.d = (x * m.m14 + y * m.m24 + z * m.m34 + w * m.m44);

    auto actual = Plane::transform(target, q);

    EXPECT_TRUE(EqualityHelper::Equal(expected, actual));
}

// A test for Plane comparison involving NaN values
// Ported from Microsoft .NET corefx System.Numerics.Vectors test suite
TEST_F(PlaneTest, EqualsNaN)
{
    Plane a = { SceneR::Math::nan, 0, 0, 0 };
    Plane b = { 0, SceneR::Math::nan, 0, 0 };
    Plane c = { 0, 0, SceneR::Math::nan, 0 };
    Plane d = { 0, 0, 0, SceneR::Math::nan};
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
