// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Marcus.hpp>

#include <Framework/MathHelper.hpp>
#include <Framework/RenderTime.hpp>
#include <Framework/Vector3.hpp>
#include <Content/ContentManager.hpp>
#include <Framework/Renderer.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;
using namespace SceneR::Sample;

Marcus::Marcus(SceneR::Framework::Renderer& renderer)
    : DrawableComponent { renderer }
    , model             { nullptr }
    , world             { Matrix::Identity }
    , view              { Matrix::Identity }
    , projection        { Matrix::Identity }
{
}

Marcus::~Marcus()
{
    this->UnloadContent();
}

void Marcus::Update(const RenderTime& renderTime)
{
    auto aspect = this->CurrentGraphicsDevice().Viewport().AspectRatio();

    this->world      = Matrix::CreateRotationX(-MathHelper::PiOver4)
                     * Matrix::CreateRotationY(MathHelper::ToRadians(150.0f))
                     * Matrix::CreateTranslation({ 0.0f, -40.0f, 100.0f });
    this->view       = Matrix::CreateLookAt({ 0.0f, 0.0f, -10.0f }, Vector3::Zero, Vector3::Up);
    this->projection = Matrix::CreatePerspectiveFieldOfView(MathHelper::PiOver4, aspect, 1.0f, 10000.0f);

    this->animatedModel->Update(renderTime);
}

void Marcus::Draw(const RenderTime& renderTime)
{
    this->animatedModel->Draw(this->world, this->view, this->projection);
}

void Marcus::LoadContent()
{
    this->model         = this->renderer.Content().Load<Model>(u"Marcus/marcus");
    this->animatedModel = std::make_shared<AnimatedModel>(this->model);

    // Start default animation clip
    this->animatedModel->PlayFirstClip();
}

void Marcus::UnloadContent()
{
    if (this->model)
    {
        this->model = nullptr;
    }
}
