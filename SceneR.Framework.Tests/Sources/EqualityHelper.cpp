// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ----------------------------------------------------------------------------------------------------
// Ported from Microsoft corefx System.Numerics.Vector MathHelper class.
// ----------------------------------------------------------------------------------------------------

#include <EqualityHelper.hpp>

#include <cmath>

using namespace System;
using namespace SceneR::Framework;

// Comparison helpers with small tolerance to allow for floating point rounding during computations.
bool EqualityHelper::Equal(const Single& a, const Single& b)
{
    return (std::abs(a - b) < 1e-5);
}

bool EqualityHelper::Equal(const Vector2& a, const Vector2& b)
{
    return Equal(a.X(), b.X()) && Equal(a.Y(), b.Y());
}

bool EqualityHelper::Equal(const Vector3& a, const Vector3& b)
{
    return Equal(a.X(), b.X()) && Equal(a.Y(), b.Y()) && Equal(a.Z(), b.Z());
}

bool EqualityHelper::Equal(const Vector4& a, const Vector4& b)
{
    return Equal(a.X(), b.X()) && Equal(a.Y(), b.Y()) && Equal(a.Z(), b.Z()) && Equal(a.W(), b.W());
}

bool EqualityHelper::Equal(const Matrix& a, const Matrix& b)
{
    return
        Equal(a.M11(), b.M11()) && Equal(a.M12(), b.M12()) && Equal(a.M13(), b.M13()) && Equal(a.M14(), b.M14())
     && Equal(a.M21(), b.M21()) && Equal(a.M22(), b.M22()) && Equal(a.M23(), b.M23()) && Equal(a.M24(), b.M24())
     && Equal(a.M31(), b.M31()) && Equal(a.M32(), b.M32()) && Equal(a.M33(), b.M33()) && Equal(a.M34(), b.M34())
     && Equal(a.M41(), b.M41()) && Equal(a.M42(), b.M42()) && Equal(a.M43(), b.M43()) && Equal(a.M44(), b.M44());
}

bool EqualityHelper::Equal(const Plane& a, const Plane& b)
{
    return Equal(a.Normal(), b.Normal()) && Equal(a.D(), b.D());
}

bool EqualityHelper::Equal(const Quaternion& a, const Quaternion& b)
{
    return Equal(a.X(), b.X()) && Equal(a.Y(), b.Y()) && Equal(a.Z(), b.Z()) && Equal(a.W(), b.W());
}

bool  EqualityHelper::EqualRotation(const Quaternion& a, const Quaternion& b)
{
    return Equal(a, b) || Equal(a, -b);
}
