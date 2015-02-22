// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Marcus.hpp>

#include <Camera.hpp>
#include <SampleRenderer.hpp>

#include <System/Math.hpp>
#include <Framework/RenderTime.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/AnimatedModel.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;
using namespace SceneR::Sample;

Marcus::Marcus(SampleRenderer& renderer)
    : DrawableComponent { renderer }
    , animatedModel     { nullptr }
    , model             { nullptr }
    , world             { Matrix::Identity }
{
}

void Marcus::Initialize()
{
    this->world = Matrix::CreateRotationX(-Math::PiOver2)
                * Matrix::CreateTranslation({ 0.0f, -40.0f, 0.0f });

    DrawableComponent::Initialize();
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
    this->world         = Matrix::Identity;
    this->animatedModel = nullptr;
    this->model         = nullptr;
}

void Marcus::Update(const RenderTime& renderTime)
{
    this->animatedModel->Update(renderTime);
}

void Marcus::Draw(const RenderTime& renderTime)
{
    const auto camera = std::dynamic_pointer_cast<Camera>(this->renderer.Components()[0]);

    this->animatedModel->Draw(this->world, camera->View, camera->Projection);
}
