// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <AstroBoy.hpp>

#include <System/Math.hpp>
#include <Framework/RenderTime.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/Model.hpp>
#include <Framework/Renderer.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;
using namespace SceneR::Sample;

AstroBoy::AstroBoy(SceneR::Framework::Renderer& renderer)
    : DrawableComponent { renderer }
    , model             { nullptr }
    , rotation          { 0.0f }
    , world             { Matrix::Identity }
    , view              { Matrix::Identity }
    , projection        { Matrix::Identity }
{
}

AstroBoy::~AstroBoy()
{
    this->UnloadContent();
}

void AstroBoy::Update(const RenderTime& renderTime)
{
    auto aspect      = this->CurrentGraphicsDevice().Viewport().AspectRatio();
    auto newRotation = this->rotation + renderTime.ElapsedRenderTime().TotalSeconds();

    this->rotation   = Math::SmoothStep(this->rotation, newRotation, Math::PiOver4);
    this->world      = Matrix::CreateRotationX(-Math::PiOver2)
                     * Matrix::CreateRotationY(this->rotation)
                     * Matrix::CreateTranslation({ 0.0f, -3.0f, -2.0f });
    this->view       = Matrix::CreateLookAt({ 0.0f, 0.0f, 6.0f }, Vector3::Zero, Vector3::Up);
    this->projection = Matrix::CreatePerspectiveFieldOfView(Math::PiOver4, aspect, 1.0f, 100.0f);
}

void AstroBoy::Draw(const RenderTime& renderTime)
{
    this->model->Draw(this->world, this->view, this->projection);
}

void AstroBoy::LoadContent()
{
    this->model = this->renderer.Content().Load<Model>(u"AstroBoy/astroboy");
}

void AstroBoy::UnloadContent()
{
    if (this->model != nullptr)
    {
        this->model.reset();
        this->model = nullptr;
    }
}
