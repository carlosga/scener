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
    : animationClips    ( )
    , bindPose          ( 0 )
    , inverseBindPose   ( 0 )
    , skeletonHierarchy ( 0 )
{
}

SkinningData::SkinningData(const std::map<String, AnimationClip>& animationClips
                         , const std::vector<Matrix>&            bindPose
                         , const std::vector<Matrix>&            inverseBindPose
                         , const std::vector<Int32>&             skeletonHierarchy)
    : animationClips    { animationClips }
    , bindPose          { bindPose }
    , inverseBindPose   { inverseBindPose }
    , skeletonHierarchy { skeletonHierarchy }
{
}

SkinningData::SkinningData(const SkinningData& skinningData)
    : animationClips    { skinningData.animationClips }
    , bindPose          { skinningData.bindPose }
    , inverseBindPose   { skinningData.inverseBindPose }
    , skeletonHierarchy { skinningData.skeletonHierarchy }
{

}

SkinningData::~SkinningData()
{
}

const std::map<String, AnimationClip>& SkinningData::AnimationClips() const
{
    return this->animationClips;
}

const AnimationClip& SkinningData::AnimationClips(const System::String& clipName)
{
    return this->animationClips[clipName];
}

const std::vector<Matrix>& SkinningData::BindPose() const
{
    return this->bindPose;
}

const std::vector<Matrix>& SkinningData::InverseBindPose() const
{
    return this->inverseBindPose;
}

const std::vector<Int32>& SkinningData::SkeletonHierarchy() const
{
    return this->skeletonHierarchy;
}
