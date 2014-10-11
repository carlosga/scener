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

#include <Content/Readers/SkinningDataReader.hpp>

#include <Graphics/SkinningData.hpp>
#include <Content/ContentManager.hpp>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

std::shared_ptr<void> SkinningDataReader::Read(ContentReader& input)
{
    // 1. Read the animation clips.
    //    Gets a collection of animation clips.
    auto animationClips = *input.ReadObject<std::map<String, AnimationClip>>();

    // 2. Read the bind pose
    //    Bindpose matrices for each bone in the skeleton, relative to the parent bone.
    auto bindPose = *input.ReadObject<std::vector<Matrix>>();

    // 3. Read the inverse bind pose
    //    Vertex to bonespace transforms for each bone in the skeleton.
    auto inverseBindPose = *input.ReadObject<std::vector<Matrix>>();

    // 4. Read the skeleton hierarchy.
    //    For each bone in the skeleton, stores the index of the parent bone.
    auto skeletonHierarchy = *input.ReadObject<std::vector<Int32>>();

    return std::make_shared<SkinningData>(animationClips, bindPose, inverseBindPose, skeletonHierarchy);
}
