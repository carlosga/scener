// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "skeletalanimation/Camera.hpp"

#include <scener/graphics/GraphicsDevice.hpp>
#include <scener/graphics/RendererWindow.hpp>
#include <scener/input/keys.hpp>
#include <scener/input/keyboard.hpp>
#include <scener/input/keyboard_state.hpp>

#include "skeletalanimation/SampleRenderer.hpp"

namespace skeletal_animation {

using scener::graphics::steptime;
using scener::input::keys;
using scener::input::keyboard;
using scener::input::keyboard_state;
using scener::math::degrees;
using scener::math::radians;
using scener::math::matrix4;
using scener::math::vector3;

Camera::Camera(SampleRenderer* renderer) noexcept
    : component          { renderer }
    , view               { matrix4::identity() }
    , projection         { matrix4::identity() }
    , _position          { }
    , _rotationTransform { }
    , _rotation          { 0.0f }
    , _resize_connection { }
{
}

void Camera::initialize() noexcept
{
    _position          = { 0.0f, 0.0f, 500.0f };
    _rotation          = 0.0f;
    _rotationTransform = matrix4::identity();

    update_projection();

    _resize_connection = _renderer->window()->connect_resize([&](std::uint32_t, std::uint32_t) {
        update_projection();
    });
}

void Camera::update(const steptime& renderTime) noexcept
{
    auto currentKeyboardState = keyboard::get_state();
    auto currentPosition      = _position;
    auto newPosition          = _position;
    auto currentRotation      = _rotation;
    auto newRotation          = _rotation;

    if (currentKeyboardState.is_key_down(keys::D))
    {
        newPosition += { 1.0f, 0.0f, 0.0f };
    }
    if (currentKeyboardState.is_key_down(keys::A))
    {
        newPosition += { -1.0f, 0.0f, 0.0f };
    }
    if (currentKeyboardState.is_key_down(keys::W))
    {
        newPosition += { 0.0f, 0.0f, 1.0f };
    }
    if (currentKeyboardState.is_key_down(keys::S))
    {
        newPosition += { 0.0f, 0.0f, -1.0f };
    }
    if (currentKeyboardState.is_key_down(keys::Z))
    {
        newPosition += { 0.0f, 1.0f, 0.0f };
    }
    if (currentKeyboardState.is_key_down(keys::C))
    {
        newPosition += { 0.0f, -1.0f, 0.0f };
    }

    if (currentKeyboardState.is_key_down(keys::Q))
    {
        newRotation = currentRotation + renderTime.elapsed_render_time.total_seconds();
    }
    if (currentKeyboardState.is_key_down(keys::E))
    {
        newRotation = currentRotation - renderTime.elapsed_render_time.total_seconds();
    }

    if (currentRotation != newRotation)
    {
        _rotation = scener::math::smooth_step(currentRotation.value, newRotation.value, scener::math::pi_over_2<>);
    }

    if (currentRotation != _rotation)
    {
        _rotationTransform = scener::math::matrix::create_rotation_y(radians(_rotation), vector3::zero());
    }

    _position = scener::math::vector::lerp(currentPosition, newPosition, scener::math::pi_over_2<>);

    view = _rotationTransform * scener::math::matrix::create_look_at(_position, vector3::zero(), vector3::up());
}

void Camera::update_projection() noexcept
{
    static const radians fov = degrees(45.0f);

    auto aspect = _renderer->device()->viewport().aspect_ratio();

    projection = scener::math::matrix::create_perspective_field_of_view(fov, aspect, 0.1f, 1000.0f);
    view       = scener::math::matrix::create_look_at(_position, vector3::zero(), vector3::up());
}

}
