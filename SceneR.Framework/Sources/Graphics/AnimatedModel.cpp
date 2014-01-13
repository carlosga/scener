//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------
//
// Ported from a Microsoft XNA Community Game Platform example
//-----------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#include <Framework/Matrix.hpp>
#include <Framework/RenderTime.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/SkinnedEffect.hpp>
#include <Graphics/AnimatedModel.hpp>
#include <Graphics/AnimationClip.hpp>
#include <vector>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

AnimatedModel::AnimatedModel(const std::shared_ptr<Model>& model)
    : model(model)
    , skinningData(model->Skinning())
    , player(model->Skinning())
{
}

AnimatedModel::~AnimatedModel()
{
}

void AnimatedModel::Play(const String& clipName)
{
    this->player.StartClip(this->skinningData->AnimationClips()[clipName]);
}

void AnimatedModel::PlayFirstClip()
{
    this->player.StartClip(this->skinningData->AnimationClips().begin()->second);
}

void AnimatedModel::Update(const RenderTime& renderTime)
{
    this->player.Update(renderTime.ElapsedRenderTime(), true, Matrix::Identity);
}

void AnimatedModel::Draw(const Matrix& world, const Matrix& view, const Matrix& projection)
{
    std::vector<Matrix> bones = this->player.GetSkinTransforms();

    // Render the skinned mesh.
    for (auto &mesh : this->model->Meshes())
    {
        for (auto &effect : mesh->Effects())
        {
            auto mEffect = std::dynamic_pointer_cast<SkinnedEffect>(effect);

            if (mEffect != nullptr)
            {
                mEffect->SetBoneTransforms(bones);

                mEffect->SpecularColor(Vector3(0.25f, 0.25f, 0.25f));
                mEffect->SpecularPower(16.0f);

                mEffect->World(world);
                mEffect->View(view);
                mEffect->Projection(projection);
            }
        }

        mesh->Draw();
    }
}
