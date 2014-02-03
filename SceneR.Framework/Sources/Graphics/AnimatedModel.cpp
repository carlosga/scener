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
#include <Graphics/AnimatedModel.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/SkinningData.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

AnimatedModel::AnimatedModel(const std::shared_ptr<Model>& model)
    : model        { model }
    , skinningData { model->Skinning() }
    , player       { model->Skinning() }
{
}

AnimatedModel::~AnimatedModel()
{
}

void AnimatedModel::Play(const String& clipName)
{
    this->player.StartClip(this->skinningData->AnimationClips(clipName));
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
    this->model->CopyBoneTransformsFrom(this->player.GetSkinTransforms());
    this->model->Draw(world, view, projection);
}
