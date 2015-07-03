// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/SkinningDataReader.hpp>

#include <Content/ContentManager.hpp>
#include <Content/ContentReader.hpp>
#include <Graphics/SkinningData.hpp>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

SkinningDataReader::SkinningDataReader()
{
}

SkinningDataReader::~SkinningDataReader()
{
}

std::shared_ptr<void> SkinningDataReader::Read(ContentReader& input)
{
    // 1. Read the animation clips.
    //    Gets a collection of animation clips.
    auto animationClips = *input.ReadObject<std::map<std::u16string, AnimationClip>>();

    // 2. Read the bind pose
    //    Bindpose matrices for each bone in the skeleton, relative to the parent bone.
    auto bindPose = *input.ReadObject<std::vector<Matrix>>();

    // 3. Read the inverse bind pose
    //    Vertex to bonespace transforms for each bone in the skeleton.
    auto inverseBindPose = *input.ReadObject<std::vector<Matrix>>();

    // 4. Read the skeleton hierarchy.
    //    For each bone in the skeleton, stores the index of the parent bone.
    auto skeletonHierarchy = *input.ReadObject<std::vector<UInt32>>();

    return std::make_shared<SkinningData>(animationClips, bindPose, inverseBindPose, skeletonHierarchy);
}
