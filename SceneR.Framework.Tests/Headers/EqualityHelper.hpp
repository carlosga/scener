// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ----------------------------------------------------------------------------------------------------
// Ported from Microsoft corefx System.Numerics.Vectors MathHelper class.
// ----------------------------------------------------------------------------------------------------

#ifndef EQUALITYHELPER_HPP
#define	EQUALITYHELPER_HPP

#include <Framework/Matrix.hpp>
#include <Framework/Plane.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>

class EqualityHelper
{
public:
    // Comparison helpers with small tolerance to allow for floating point rounding during computations.
    static bool Equal(const float& a, const float& b);

    static bool Equal(const SceneR::Framework::Vector2& a, const SceneR::Framework::Vector2& b);

    static bool Equal(const SceneR::Framework::Vector3& a, const SceneR::Framework::Vector3& b);

    static bool Equal(const SceneR::Framework::Vector4& a, const SceneR::Framework::Vector4& b);

    static bool Equal(const SceneR::Framework::Matrix& a, const SceneR::Framework::Matrix& b);

    static bool Equal(const SceneR::Framework::Plane& a, const SceneR::Framework::Plane& b);

    static bool Equal(const SceneR::Framework::Quaternion& a, const SceneR::Framework::Quaternion& b);

    static bool EqualRotation(const SceneR::Framework::Quaternion& a, const SceneR::Framework::Quaternion& b);
};

#endif	// EQUALITYHELPER_HPP
