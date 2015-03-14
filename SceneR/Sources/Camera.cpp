// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Camera.hpp>

#include <SampleRenderer.hpp>

#include <System/Math.hpp>
#include <Framework/Vector3.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Sample;

Camera::Camera(SampleRenderer& renderer)
    : Component  { renderer }
    , View       { Matrix::Identity }
    , Projection { Matrix::Identity }
    , rotation   { 0 }
{
}

void Camera::Initialize()
{
    auto aspect = this->renderer.CurrentGraphicsDevice().Viewport().AspectRatio();

    this->Projection = Matrix::CreatePerspectiveFieldOfView(Math::ToRadians(27), aspect, 0.5f, 10000.0f);
}

void Camera::Update(const RenderTime& renderTime)
{
    auto newRotation = this->rotation + renderTime.ElapsedRenderTime().TotalSeconds();
    this->rotation   = Math::SmoothStep(this->rotation, newRotation, Math::PiOver4);

    // this->View = Matrix::CreateRotationY(this->rotation, { 0.0f, 0.0f, 0.0f })
    //            * Matrix::CreateLookAt({ 0.0f, 0.0f, -500.0f }, Vector3::Zero, Vector3::Up);

    this->View = Matrix::CreateLookAt({ 0.0f, 0.0f, 500.0f }, Vector3::Zero, Vector3::Up);
}
