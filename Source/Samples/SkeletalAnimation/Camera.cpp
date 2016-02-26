// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SkeletalAnimation/Camera.hpp"

#include <SceneR/Graphics/GraphicsDevice.hpp>
#include <SceneR/Graphics/RendererWindow.hpp>
#include <SceneR/Input/Keys.hpp>
#include <SceneR/Input/Keyboard.hpp>
#include <SceneR/Input/KeyboardState.hpp>

#include "SkeletalAnimation/SampleRenderer.hpp"

namespace SkeletalAnimation {

using scener::graphics::StepTime;
using scener::input::Keys;
using scener::input::Keyboard;
using scener::input::KeyboardState;
using scener::math::degrees;
using scener::math::radians;
using scener::math::matrix4;
using scener::math::vector3;

Camera::Camera(SampleRenderer* renderer) noexcept
    : Component          { renderer }
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

void Camera::update(const StepTime& renderTime) noexcept
{
    auto currentKeyboardState = Keyboard::get_state();
    auto currentPosition      = _position;
    auto newPosition          = _position;
    auto currentRotation      = _rotation;
    auto newRotation          = _rotation;

    if (currentKeyboardState.is_key_down(Keys::D))
    {
        newPosition += { 1.0f, 0.0f, 0.0f };
    }
    if (currentKeyboardState.is_key_down(Keys::A))
    {
        newPosition += { -1.0f, 0.0f, 0.0f };
    }
    if (currentKeyboardState.is_key_down(Keys::W))
    {
        newPosition += { 0.0f, 0.0f, 1.0f };
    }
    if (currentKeyboardState.is_key_down(Keys::S))
    {
        newPosition += { 0.0f, 0.0f, -1.0f };
    }
    if (currentKeyboardState.is_key_down(Keys::Z))
    {
        newPosition += { 0.0f, 1.0f, 0.0f };
    }
    if (currentKeyboardState.is_key_down(Keys::C))
    {
        newPosition += { 0.0f, -1.0f, 0.0f };
    }

    if (currentKeyboardState.is_key_down(Keys::Q))
    {
        newRotation = currentRotation + renderTime.elapsed_render_time.total_seconds();
    }
    if (currentKeyboardState.is_key_down(Keys::E))
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

    auto aspect = _renderer->graphics_device()->viewport().aspect_ratio();

    projection = scener::math::matrix::create_perspective_field_of_view(fov, aspect, 0.1f, 1000.0f);
    view       = scener::math::matrix::create_look_at(_position, vector3::zero(), vector3::up());
}

}
