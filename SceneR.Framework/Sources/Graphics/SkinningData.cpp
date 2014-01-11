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

#include <Graphics/SkinningData.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

SkinningData::SkinningData()
    : animationClips(),
      bindPose(),
      inverseBindPose(),
      skeletonHierarchy()
{
}

SkinningData::SkinningData(std::map<String, AnimationClip> animationClips,
                           std::vector<Matrix>             bindPose,
                           std::vector<Matrix>             inverseBindPose,
                           std::vector<Int32>              skeletonHierarchy)
    : animationClips(animationClips),
      bindPose(bindPose),
      inverseBindPose(inverseBindPose),
      skeletonHierarchy(skeletonHierarchy)
{
}

SkinningData::SkinningData(const SkinningData& skinningData)
    : animationClips(skinningData.animationClips),
      bindPose(skinningData.bindPose),
      inverseBindPose(skinningData.inverseBindPose),
      skeletonHierarchy(skinningData.skeletonHierarchy)
{

}

SkinningData::~SkinningData()
{
}

std::map<String, AnimationClip>& SkinningData::AnimationClips()
{
    return this->animationClips;
}

std::vector<Matrix>& SkinningData::BindPose()
{
    return this->bindPose;
}

std::vector<Matrix>& SkinningData::InverseBindPose()
{
    return this->inverseBindPose;
}

std::vector<Int32>& SkinningData::SkeletonHierarchy()
{
    return this->skeletonHierarchy;
}
