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

#include <Graphics/AnimationPlayer.hpp>
#include <Graphics/Keyframe.hpp>
#include <Graphics/SkinningData.hpp>
#include <stdexcept>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

AnimationPlayer::AnimationPlayer(const std::shared_ptr<SkinningData>& skinningData)
    : currentClipValue()
    , currentTimeValue(TimeSpan::Zero)
    , currentKeyframe(0)
    , skinningDataValue(skinningData)
    , boneTransforms(0)
    , worldTransforms(0)
    , skinTransforms(0)
{
    this->boneTransforms.resize(this->skinningDataValue->BindPose().size());
    this->worldTransforms.resize(this->skinningDataValue->BindPose().size());
    this->skinTransforms.resize(this->skinningDataValue->BindPose().size());
}

AnimationPlayer::AnimationPlayer(const AnimationPlayer& animationPlayer)
    : currentClipValue(animationPlayer.currentClipValue)
    , currentTimeValue(animationPlayer.currentTimeValue)
    , currentKeyframe(animationPlayer.currentKeyframe)
    , skinningDataValue(animationPlayer.skinningDataValue)
    , boneTransforms(animationPlayer.boneTransforms)
    , worldTransforms(animationPlayer.worldTransforms)
    , skinTransforms(animationPlayer.skinTransforms)
{
}

AnimationPlayer::~AnimationPlayer()
{
}

void AnimationPlayer::StartClip(const AnimationClip& clip)
{
    this->currentClipValue = clip;
    this->currentTimeValue = TimeSpan::Zero;
    this->currentKeyframe  = 0;

    // Initialize bone transforms to the bind pose.
    this->boneTransforms.assign(this->skinningDataValue->BindPose().begin(), this->skinningDataValue->BindPose().end());
}

void AnimationPlayer::Update(const TimeSpan& time
                           , const Boolean&  relativeToCurrentTime
                           , const Matrix&   rootTransform)
{
    this->UpdateBoneTransforms(time, relativeToCurrentTime);
    this->UpdateWorldTransforms(rootTransform);
    this->UpdateSkinTransforms();
}

void AnimationPlayer::UpdateBoneTransforms(const TimeSpan& time, const Boolean& relativeToCurrentTime)
{
    auto currentTime = TimeSpan(time);

    // Update the animation position.
    if (relativeToCurrentTime)
    {
        currentTime += this->currentTimeValue;

        // If we reached the end, loop back to the start.
        while (currentTime >= this->currentClipValue.Duration())
        {
            currentTime -= this->currentClipValue.Duration();
        }
    }

    if ((currentTime < TimeSpan::Zero) || (currentTime >= this->currentClipValue.Duration()))
    {
        throw std::runtime_error("time");
    }

    // If the position moved backwards, reset the keyframe index.
    if (currentTime < this->currentTimeValue)
    {
        this->currentKeyframe = 0;
        this->boneTransforms.assign(this->skinningDataValue->BindPose().begin(), this->skinningDataValue->BindPose().end());
    }

    this->currentTimeValue = currentTime;

    // Read keyframe matrices.
    const std::vector<Keyframe>& keyframes = this->currentClipValue.Keyframes();

    while (currentKeyframe < keyframes.size())
    {
        auto keyframe = keyframes[this->currentKeyframe];

        // Stop when we've read up to the current time position.
        if (keyframe.Time() > this->currentTimeValue)
        {
            break;
        }

        // Use this keyframe.
        this->boneTransforms[keyframe.Bone()] = keyframe.Transform();

        this->currentKeyframe++;
    }
}

void AnimationPlayer::UpdateWorldTransforms(const Matrix& rootTransform)
{
    // Root bone.
    this->worldTransforms[0] = this->boneTransforms[0] * rootTransform;

    // Child bones.
    for (Size bone = 1; bone < this->worldTransforms.size(); bone++)
    {
        Int32 parentBone = this->skinningDataValue->SkeletonHierarchy()[bone];

        this->worldTransforms[bone] = this->boneTransforms[bone] * this->worldTransforms[parentBone];
    }
}

void AnimationPlayer::UpdateSkinTransforms()
{
    for (Size bone = 0; bone < this->skinTransforms.size(); bone++)
    {
        this->skinTransforms[bone] = this->skinningDataValue->InverseBindPose()[bone] * this->worldTransforms[bone];
    }
}

const std::vector<Matrix>& AnimationPlayer::GetBoneTransforms() const
{
    return this->boneTransforms;
}

const std::vector<Matrix>& AnimationPlayer::GetWorldTransforms() const
{
    return this->worldTransforms;
}

const std::vector<Matrix>& AnimationPlayer::GetSkinTransforms() const
{
    return this->skinTransforms;
}

const AnimationClip& AnimationPlayer::CurrentClip() const
{
    return this->currentClipValue;
}

const TimeSpan& AnimationPlayer::CurrentTime() const
{
    return this->currentTimeValue;
}
