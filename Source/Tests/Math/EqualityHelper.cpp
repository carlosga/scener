// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ----------------------------------------------------------------------------------------------------
// Ported from Microsoft corefx System.Numerics.Vector MathHelper class.
// ----------------------------------------------------------------------------------------------------

#include "EqualityHelper.hpp"

#include <cmath>

using namespace SceneR::Math;

// Comparison helpers with small tolerance to allow for floating point rounding during computations.
bool EqualityHelper::Equal(const float& a, const float& b)
{
    return (std::abs(a - b) < 1e-5);
}

bool EqualityHelper::Equal(const Vector2& a, const Vector2& b)
{
    return Equal(a.x, b.x) && Equal(a.y, b.y);
}

bool EqualityHelper::Equal(const Vector3& a, const Vector3& b)
{
    return Equal(a.x, b.x) && Equal(a.y, b.y) && Equal(a.z, b.z);
}

bool EqualityHelper::Equal(const Vector4& a, const Vector4& b)
{
    return Equal(a.x, b.x) && Equal(a.y, b.y) && Equal(a.z, b.z) && Equal(a.w, b.w);
}

bool EqualityHelper::Equal(const Matrix& a, const Matrix& b)
{
    return
        Equal(a.m11, b.m11) && Equal(a.m12, b.m12) && Equal(a.m13, b.m13) && Equal(a.m14, b.m14)
     && Equal(a.m21, b.m21) && Equal(a.m22, b.m22) && Equal(a.m23, b.m23) && Equal(a.m24, b.m24)
     && Equal(a.m31, b.m31) && Equal(a.m32, b.m32) && Equal(a.m33, b.m33) && Equal(a.m34, b.m34)
     && Equal(a.m41, b.m41) && Equal(a.m42, b.m42) && Equal(a.m43, b.m43) && Equal(a.m44, b.m44);
}

bool EqualityHelper::Equal(const Plane& a, const Plane& b)
{
    return Equal(a.normal, b.normal) && Equal(a.d, b.d);
}

bool EqualityHelper::Equal(const Quaternion& a, const Quaternion& b)
{
    return Equal(a.x, b.x) && Equal(a.y, b.y) && Equal(a.z, b.z) && Equal(a.w, b.w);
}

bool  EqualityHelper::EqualRotation(const Quaternion& a, const Quaternion& b)
{
    return Equal(a, b) || Equal(a, -b);
}
