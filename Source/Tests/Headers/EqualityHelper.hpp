// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ----------------------------------------------------------------------------------------------------
// Ported from Microsoft corefx System.Numerics.Vectors MathHelper class.
// ----------------------------------------------------------------------------------------------------

#ifndef EQUALITYHELPER_HPP
#define	EQUALITYHELPER_HPP

#include <Math/Matrix.hpp>
#include <Math/Plane.hpp>
#include <Math/Quaternion.hpp>
#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>

class EqualityHelper
{
public:
    // Comparison helpers with small tolerance to allow for floating point rounding during computations.
    static bool Equal(const float& a, const float& b);

    static bool Equal(const SceneR::Math::Vector2& a, const SceneR::Math::Vector2& b);

    static bool Equal(const SceneR::Math::Vector3& a, const SceneR::Math::Vector3& b);

    static bool Equal(const SceneR::Math::Vector4& a, const SceneR::Math::Vector4& b);

    static bool Equal(const SceneR::Math::Matrix& a, const SceneR::Math::Matrix& b);

    static bool Equal(const SceneR::Math::Plane& a, const SceneR::Math::Plane& b);

    static bool Equal(const SceneR::Math::Quaternion& a, const SceneR::Math::Quaternion& b);

    static bool EqualRotation(const SceneR::Math::Quaternion& a, const SceneR::Math::Quaternion& b);
};

#endif	// EQUALITYHELPER_HPP
