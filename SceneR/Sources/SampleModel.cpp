// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <SampleModel.hpp>

#include <Camera.hpp>
#include <SampleRenderer.hpp>

#include <System/Math.hpp>
#include <Framework/RenderTime.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/AnimatedModel.hpp>
#include <Graphics/IEffectLights.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/AnimatedModel.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;
using namespace SceneR::Sample;

SampleModel::SampleModel(SampleRenderer& renderer)
    : DrawableComponent { renderer }
    , model             { nullptr }
    , animatedModel     { nullptr }
    , world             { Matrix::Identity }
{
}

void SampleModel::Initialize()
{
    /*
    this->world = Matrix::CreateRotationX(-Math::PiOver2)
                * Matrix::CreateTranslation({ 0.0f, -40.0f, 0.0f })
                * Matrix::CreateScale(2.0f);
    */

    this->world = Matrix::CreateTranslation({ 0.0f, -80.0f, 0.0f });

    DrawableComponent::Initialize();
}

void SampleModel::LoadContent()
{
    this->model         = this->renderer.Content().Load<Model>(u"Wild Centaur/Wild Centaur");
    // this->animatedModel = std::make_shared<AnimatedModel>(this->model);

    for (const auto& mesh : this->model->Meshes())
    {
        for (auto& effect : mesh->Effects())
        {
            auto leffect = std::dynamic_pointer_cast<IEffectLights>(effect);

            if (leffect.get() != nullptr)
            {
                leffect->EnableDefaultLighting();
            }
        }
    }

    // Start default animation clip
    // this->animatedModel->PlayFirstClip();
}

void SampleModel::UnloadContent()
{
    this->world = Matrix::Identity;
    this->model = nullptr;
}

void SampleModel::Update(const RenderTime& renderTime)
{
    // this->animatedModel->Update(renderTime);
}

void SampleModel::Draw(const RenderTime& renderTime)
{
    const auto camera = std::dynamic_pointer_cast<Camera>(this->renderer.Components()[0]);

    this->CurrentGraphicsDevice().RasterizerState().CullMode(CullMode::CullCounterClockwiseFace);

    this->model->Draw(this->world, camera->View, camera->Projection);

    // this->animatedModel->Draw(this->world, camera->View, camera->Projection);
}
