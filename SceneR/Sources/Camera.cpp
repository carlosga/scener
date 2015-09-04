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

        Camera::Camera(SampleRenderer& renderer)
            : Component  { renderer }
            , View       { Matrix::Identity }
            , Projection { Matrix::Identity }
        {
        }

        void Camera::Initialize()
        {
            auto aspect = this->renderer.graphics_device().viewport().aspect_ratio();

            _position          = { 0.0f, 0.0f, 500.0f };
            _rotation          = 0.0f;
            _rotationTransform = Matrix::Identity;

            this->Projection = Matrix::CreatePerspectiveFieldOfView(Math::ToRadians(27), aspect, 0.5f, 10000.0f);
            this->View       = Matrix::CreateLookAt(_position, Vector3::Zero, Vector3::Up);
        }

        void Camera::Update(const RenderTime& renderTime)
        {
            auto currentKeyboardState = Keyboard::GetState();
            auto currentPosition      = _position;
            auto newPosition          = _position;
            auto currentRotation      = _rotation;
            auto newRotation          = _rotation;

            if (currentKeyboardState.IsKeyDown(Keys::D))
            {
                newPosition += Vector3 { 1.0f, 0.0f, 0.0f };
            }
            if (currentKeyboardState.IsKeyDown(Keys::A))
            {
                newPosition += Vector3 { -1.0f, 0.0f, 0.0f };
            }
            if (currentKeyboardState.IsKeyDown(Keys::W))
            {
                newPosition += Vector3 { 0.0f, 0.0f, 1.0f };
            }
            if (currentKeyboardState.IsKeyDown(Keys::S))
            {
                newPosition += Vector3 { 0.0f, 0.0f, -1.0f };
            }
            if (currentKeyboardState.IsKeyDown(Keys::Z))
            {
                newPosition += Vector3 { 0.0f, 1.0f, 0.0f };
            }
            if (currentKeyboardState.IsKeyDown(Keys::C))
            {
                newPosition += Vector3 { 0.0f, -1.0f, 0.0f };
            }

            if (currentKeyboardState.IsKeyDown(Keys::Q))
            {
                newRotation = currentRotation + renderTime.ElapsedRenderTime().TotalSeconds();
            }
            if (currentKeyboardState.IsKeyDown(Keys::E))
            {
                newRotation = currentRotation - renderTime.ElapsedRenderTime().TotalSeconds();
            }

            if (currentRotation != newRotation)
            {
                _rotation = Math::SmoothStep(currentRotation, newRotation, Math::PiOver2);
            }

            if (currentRotation != _rotation)
            {
                _rotationTransform = Matrix::CreateRotationY(_rotation, Vector3::Zero);
            }

            _position = Vector3::Lerp(currentPosition, newPosition, Math::PiOver2);

            this->View = _rotationTransform
                       * Matrix::CreateLookAt(_position, Vector3::Zero, Vector3::Up);
        }
    }
}
