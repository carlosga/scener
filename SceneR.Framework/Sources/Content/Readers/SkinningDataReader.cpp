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

#include <Content/ContentManager.hpp>
#include <Content/Readers/SkinningDataReader.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
#include <Graphics/AnimationClip.hpp>
#include <Graphics/SkinningData.hpp>
#include <System/Core.hpp>
#include <map>
#include <vector>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

SkinningDataReader::SkinningDataReader()
{
}

std::shared_ptr<void> SkinningDataReader::Read(ContentReader& input)
{
    std::map<String, AnimationClip> animationClips;
    std::vector<Matrix>             bindPose;
    std::vector<Matrix>             inverseBindPose;
    std::vector<Int32>              skeletonHierarchy;

    // 1. Read the animation clips.
    //    Gets a collection of animation clips.
    animationClips = *input.ReadObject<std::map<String, AnimationClip>>();

    // 2. Read the bind pose
    //    Bindpose matrices for each bone in the skeleton, relative to the parent bone.
    bindPose = *input.ReadObject<std::vector<Matrix>>();

    // 3. Read the inverse bind pose
    //    Vertex to bonespace transforms for each bone in the skeleton.
    inverseBindPose = *input.ReadObject<std::vector<Matrix>>();

    // 4. Read the skeleton hierarchy.
    //    For each bone in the skeleton, stores the index of the parent bone.
    skeletonHierarchy = *input.ReadObject<std::vector<Int32>>();

    return std::make_shared<SkinningData>(animationClips, bindPose, inverseBindPose, skeletonHierarchy);
}
