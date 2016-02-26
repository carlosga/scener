// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/math/BoundingFrustrum.hpp"

#include "scener/math/BoundingBox.hpp"
#include "scener/math/matrix.hpp"
#include "scener/math/plane.hpp"
#include "scener/math/Ray.hpp"
#include "scener/math/plane_intersection_type.hpp"

namespace scener { namespace math {

BoundingFrustrum::BoundingFrustrum(const matrix4& value) noexcept
    : _bottom { 0.0f, 0.0f, 0.0f, 0.0f }
    , _far    { 0.0f, 0.0f, 0.0f, 0.0f }
    , _left   { 0.0f, 0.0f, 0.0f, 0.0f }
    , _near   { 0.0f, 0.0f, 0.0f, 0.0f }
    , _right  { 0.0f, 0.0f, 0.0f, 0.0f }
    , _top    { 0.0f, 0.0f, 0.0f, 0.0f }
    , _value  { value }
{
}

const plane_t& BoundingFrustrum::bottom() const noexcept
{
    return _bottom;
}

const plane_t& BoundingFrustrum::far() const noexcept
{
    return _far;
}

const plane_t& BoundingFrustrum::left() const noexcept
{
    return _left;
}

const matrix4& BoundingFrustrum::matrix() const noexcept
{
    return _value;
}

void BoundingFrustrum::matrix(const matrix4& matrix) noexcept
{
    _value = matrix;
    update_planes();
}

const plane_t& BoundingFrustrum::near() const noexcept
{
    return _near;
}

const plane_t& BoundingFrustrum::right() const noexcept
{
    return _right;
}

const plane_t& BoundingFrustrum::top() const noexcept
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

ContainmentType BoundingFrustrum::contains(const vector3& point) const noexcept
{
    throw std::runtime_error("Not implemented");
}

std::vector<vector3> BoundingFrustrum::get_corners() noexcept
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

plane_intersection_type BoundingFrustrum::intersects(const plane_t& plane) const noexcept
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

    // Left plane_t
    _left = scener::math::plane::normalize({ _value.m14 + _value.m11
                                           , _value.m24 + _value.m21
                                           , _value.m34 + _value.m31
                                           , _value.m44 + _value.m41 });

    // Right plane_t
    _right = scener::math::plane::normalize({ _value.m14 - _value.m11
                                            , _value.m24 - _value.m21
                                            , _value.m34 - _value.m31
                                            , _value.m44 - _value.m41 });

    // Top plane_t
    _top = scener::math::plane::normalize({ _value.m14 - _value.m12
                                          , _value.m24 - _value.m22
                                          , _value.m34 - _value.m32
                                          , _value.m44 - _value.m42 });

    // Bottom plane_t
    _bottom = scener::math::plane::normalize({ _value.m14 + _value.m12
                                             , _value.m24 + _value.m22
                                             , _value.m34 + _value.m32
                                             , _value.m44 + _value.m42 });

    // Near plane_t
    _near = scener::math::plane::normalize({ _value.m13, _value.m23, _value.m33, _value.m43 });


    // Far plane_t
    _far = scener::math::plane::normalize({ _value.m14 - _value.m13
                                          , _value.m24 - _value.m23
                                          , _value.m34 - _value.m33
                                          , _value.m44 - _value.m43 });
}

}}
