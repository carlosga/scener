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

using SceneR::Graphics::StepTime;
using SceneR::Input::Keys;
using SceneR::Input::Keyboard;
using SceneR::Input::KeyboardState;
using SceneR::Math::Degrees;
using SceneR::Math::Matrix;
using SceneR::Math::Vector3;

Camera::Camera(SampleRenderer* renderer) noexcept
    : Component          { renderer }
    , view               { Matrix::identity }
    , projection         { Matrix::identity }
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
    _rotationTransform = Matrix::identity;

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
        _rotation = SceneR::Math::smooth_step(currentRotation, newRotation, SceneR::Math::pi_over_2);
    }

    if (currentRotation != _rotation)
    {
        _rotationTransform = Matrix::create_rotation_y(_rotation, Vector3::zero);
    }

    _position = Vector3::lerp(currentPosition, newPosition, SceneR::Math::pi_over_2);

    view = _rotationTransform * Matrix::create_look_at(_position, Vector3::zero, Vector3::up);
}

void Camera::update_projection() noexcept
{
    auto    aspect = _renderer->graphics_device()->viewport().aspect_ratio();
    Degrees fov    = 45.0f;

    projection = Matrix::create_perspective_field_of_view(fov, aspect, 0.1f, 1000.0f);
    view       = Matrix::create_look_at(_position, Vector3::zero, Vector3::up);
}

}
