// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//-----------------------------------------------------------------------------
// Ported from a Microsoft XNA Community Game Platform example
//-----------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#include <Graphics/AnimatedModel.hpp>

#include <Framework/RenderTime.hpp>
#include <Graphics/SkinningData.hpp>
#include <Graphics/Model.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

AnimatedModel::AnimatedModel(const std::shared_ptr<Model>& model)
    : model        { model }
    , skinningData { model->Skinning() }
    , player       { model->Skinning() }
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
