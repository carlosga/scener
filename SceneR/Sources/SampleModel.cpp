// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <SampleModel.hpp>

#include <Camera.hpp>
#include <SampleRenderer.hpp>

#include <System/Math.hpp>
#include <Framework/RenderTime.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/Model.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;
using namespace SceneR::Sample;

SampleModel::SampleModel(SampleRenderer& renderer)
    : DrawableComponent { renderer }
    , model             { nullptr }
    , world             { Matrix::Identity }
{
}

void SampleModel::Initialize()
{
    // this->Enabled(false);
    // this->Visible(false);

    this->world = Matrix::CreateRotationX(-Math::PiOver2)
                * Matrix::CreateTranslation({ 0.0f, -100.0f, 0.0f })
                * Matrix::CreateScale(0.2f);

    DrawableComponent::Initialize();
}

void SampleModel::LoadContent()
{
    this->model = this->renderer.Content().Load<Model>(u"Goblin_D_Shareyko/WAR");
}

void SampleModel::UnloadContent()
{
    this->world = Matrix::Identity;
    this->model = nullptr;
}

void SampleModel::Draw(const RenderTime& renderTime)
{
    const auto camera = std::dynamic_pointer_cast<Camera>(this->renderer.Components()[0]);
    this->model->Draw(this->world, camera->View, camera->Projection);
}
