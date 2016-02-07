// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Math/BoundingFrustrum.hpp"

#include "SceneR/Math/BoundingBox.hpp"
#include "SceneR/Math/Ray.hpp"

namespace SceneR { namespace Math {

BoundingFrustrum::BoundingFrustrum(const Matrix& value) noexcept
    : _bottom { 0.0f, 0.0f, 0.0f, 0.0f }
    , _far    { 0.0f, 0.0f, 0.0f, 0.0f }
    , _left   { 0.0f, 0.0f, 0.0f, 0.0f }
    , _near   { 0.0f, 0.0f, 0.0f, 0.0f }
    , _right  { 0.0f, 0.0f, 0.0f, 0.0f }
    , _top    { 0.0f, 0.0f, 0.0f, 0.0f }
    , _value  { value }
{
}

const Plane& BoundingFrustrum::bottom() const noexcept
{
    return _bottom;
}

const Plane& BoundingFrustrum::far() const noexcept
{
    return _far;
}

const Plane& BoundingFrustrum::left() const noexcept
{
    return _left;
}

const Matrix& BoundingFrustrum::matrix() const noexcept
{
    return _value;
}

void BoundingFrustrum::matrix(const Matrix& matrix) noexcept
{
    _value = matrix;
    update_planes();
}

const Plane& BoundingFrustrum::near() const noexcept
{
    return _near;
}

const Plane& BoundingFrustrum::right() const noexcept
{
    return _right;
}

const Plane& BoundingFrustrum::top() const noexcept
{
    return _top;
}

ContainmentType BoundingFrustrum::contains(const BoundingBox& box) const noexcept
{
    throw std::runtime_error("Not implemented");
}

ContainmentType BoundingFrustrum::contains(const BoundingFrustrum& frustrum) const noexcept
{
    throw std::runtime_error("Not implemented");
}

ContainmentType BoundingFrustrum::contains(const BoundingSphere& sphere) const noexcept
{
    throw std::runtime_error("Not implemented");
}

ContainmentType BoundingFrustrum::contains(const Vector3& point) const noexcept
{
    throw std::runtime_error("Not implemented");
}

std::vector<Vector3> BoundingFrustrum::get_corners() noexcept
{
    throw std::runtime_error("Not implemented");
}

bool BoundingFrustrum::intersects(const BoundingBox& box) const noexcept
{
    throw std::runtime_error("Not implemented");
}

bool BoundingFrustrum::intersects(const BoundingFrustrum& frustrum) const noexcept
{
    throw std::runtime_error("Not implemented");
}

bool BoundingFrustrum::intersects(const BoundingSphere& sphere) const noexcept
{
    throw std::runtime_error("Not implemented");
}

PlaneIntersectionType BoundingFrustrum::intersects(const Plane& plane) const noexcept
{
    throw std::runtime_error("Not implemented");
}

float BoundingFrustrum::intersects(const Ray& ray) const noexcept
{
    throw std::runtime_error("Not implemented");
}

bool BoundingFrustrum::operator==(const BoundingFrustrum& frustrum) const noexcept
{
    return (_value == frustrum._value);
}

bool BoundingFrustrum::operator!=(const BoundingFrustrum& frustrum) const noexcept
{
    return !(*this == frustrum);
}

void BoundingFrustrum::update_planes() noexcept
{
    // http://www.chadvernon.com/blog/resources/directx9/frustum-culling/

    // Left plane
    _left = Plane::normalize({ _value.m14 + _value.m11
                             , _value.m24 + _value.m21
                             , _value.m34 + _value.m31
                             , _value.m44 + _value.m41 });

    // Right plane
    _right = Plane::normalize({ _value.m14 - _value.m11
                              , _value.m24 - _value.m21
                              , _value.m34 - _value.m31
                              , _value.m44 - _value.m41 });

    // Top plane
    _top = Plane::normalize({ _value.m14 - _value.m12
                            , _value.m24 - _value.m22
                            , _value.m34 - _value.m32
                            , _value.m44 - _value.m42 });

    // Bottom plane
    _bottom = Plane::normalize({ _value.m14 + _value.m12
                               , _value.m24 + _value.m22
                               , _value.m34 + _value.m32
                               , _value.m44 + _value.m42 });

    // Near plane
    _near = Plane::normalize({ _value.m13, _value.m23, _value.m33, _value.m43 });


    // Far plane
    _far = Plane::normalize({ _value.m14 - _value.m13
                            , _value.m24 - _value.m23
                            , _value.m34 - _value.m33
                            , _value.m44 - _value.m43 });
}

}}
