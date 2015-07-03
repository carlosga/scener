// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//-------------------------------------------------------------------------------
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

SkinningData::SkinningData(const std::map<std::u16string, AnimationClip>& animationClips
                         , const std::vector<Matrix>&                     bindPose
                         , const std::vector<Matrix>&                     inverseBindPose
                         , const std::vector<UInt32>&                     skeletonHierarchy)
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

const std::map<std::u16string, AnimationClip>& SkinningData::AnimationClips() const
{
    return this->animationClips;
}

const AnimationClip& SkinningData::AnimationClips(const std::u16string& clipName)
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

const std::vector<UInt32>& SkinningData::SkeletonHierarchy() const
{
    return this->skeletonHierarchy;
}
