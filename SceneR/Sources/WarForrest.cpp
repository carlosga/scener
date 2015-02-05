// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <WarForrest.hpp>

#include <Framework/MathHelper.hpp>
#include <Framework/RenderTime.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/Model.hpp>
#include <Framework/Renderer.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;
using namespace SceneR::Sample;

WarForrest::WarForrest(SceneR::Framework::Renderer& renderer)
    : DrawableComponent { renderer }
    , model             { nullptr }
    , rotation          { 0.0f }
    , world             { Matrix::Identity }
    , view              { Matrix::Identity }
    , projection        { Matrix::Identity }
{
}

WarForrest::~WarForrest()
{
    this->UnloadContent();
}

void WarForrest::Update(const RenderTime& renderTime)
{
    auto aspect      = this->CurrentGraphicsDevice().Viewport().AspectRatio();
    auto newRotation = this->rotation + renderTime.ElapsedRenderTime().TotalSeconds();

    this->rotation   = MathHelper::SmoothStep(this->rotation, newRotation, MathHelper::PiOver4);
    this->world      = Matrix::CreateRotationX(-MathHelper::PiOver2)
                     * Matrix::CreateRotationY(this->rotation)
                     * Matrix::CreateTranslation({ 300.0f, -400.0f, 0.0f });
    this->view       = Matrix::CreateLookAt({ 0.0f, 0.0f, 1200.0f }, Vector3::Zero, Vector3::Up);
    this->projection = Matrix::CreatePerspectiveFieldOfView(MathHelper::PiOver4, aspect, 1.0, 10000.0f);
}

void WarForrest::Draw(const RenderTime& renderTime)
{
    this->model->Draw(this->world, this->view, this->projection);
}

void WarForrest::LoadContent()
{
    this->model = this->renderer.Content().Load<Model>(u"WarForrestPL/WAR");
}

void WarForrest::UnloadContent()
{
    if (this->model != nullptr)
    {
        this->model.reset();
        this->model = nullptr;
    }
}
