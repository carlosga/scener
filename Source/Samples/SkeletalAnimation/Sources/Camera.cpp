// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Camera.hpp>

#include <SampleRenderer.hpp>

#include <System/Math.hpp>
#include <Framework/Vector3.hpp>
#include <Input/Keys.hpp>
#include <Input/Keyboard.hpp>
#include <Input/KeyboardState.hpp>

namespace SceneR
{
    namespace Sample
    {
        using System::Math;
        using SceneR::Framework::Matrix;
        using SceneR::Framework::RenderTime;
        using SceneR::Framework::Vector3;
        using SceneR::Input::Keys;
        using SceneR::Input::Keyboard;
        using SceneR::Input::KeyboardState;

        Camera::Camera(SampleRenderer* renderer)
            : Component  { renderer }
            , view       { Matrix::identity }
            , projection { Matrix::identity }
        {
        }

        void Camera::initialize()
        {
            auto aspect = _renderer->graphics_device()->viewport().aspect_ratio();

            _position          = { 0.0f, 0.0f, 500.0f };
            _rotation          = 0.0f;
            _rotationTransform = Matrix::identity;

            projection = Matrix::create_perspective_field_of_view(Math::to_radians(27), aspect, 0.1f, 1000.0f);
            view       = Matrix::create_look_at(_position, Vector3::zero, Vector3::up);
        }

        void Camera::update(const RenderTime& renderTime)
        {
            auto currentKeyboardState = Keyboard::get_state();
            auto currentPosition      = _position;
            auto newPosition          = _position;
            auto currentRotation      = _rotation;
            auto newRotation          = _rotation;

            if (currentKeyboardState.is_key_down(Keys::D))
            {
                newPosition += Vector3 { 1.0f, 0.0f, 0.0f };
            }
            if (currentKeyboardState.is_key_down(Keys::A))
            {
                newPosition += Vector3 { -1.0f, 0.0f, 0.0f };
            }
            if (currentKeyboardState.is_key_down(Keys::W))
            {
                newPosition += Vector3 { 0.0f, 0.0f, 1.0f };
            }
            if (currentKeyboardState.is_key_down(Keys::S))
            {
                newPosition += Vector3 { 0.0f, 0.0f, -1.0f };
            }
            if (currentKeyboardState.is_key_down(Keys::Z))
            {
                newPosition += Vector3 { 0.0f, 1.0f, 0.0f };
            }
            if (currentKeyboardState.is_key_down(Keys::C))
            {
                newPosition += Vector3 { 0.0f, -1.0f, 0.0f };
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
                _rotation = Math::smooth_step(currentRotation, newRotation, Math::pi_over_2);
            }

            if (currentRotation != _rotation)
            {
                _rotationTransform = Matrix::create_rotation_y(_rotation, Vector3::zero);
            }

            _position = Vector3::lerp(currentPosition, newPosition, Math::pi_over_2);

            view = _rotationTransform
                 * Matrix::create_look_at(_position, Vector3::zero, Vector3::up);
        }
    }
}
