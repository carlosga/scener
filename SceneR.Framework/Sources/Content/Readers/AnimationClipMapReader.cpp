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

#include <Content/ContentReader.hpp>
#include <Content/Readers/AnimationClipMapReader.hpp>
#include <Framework/Matrix.hpp>
#include <Graphics/AnimationClip.hpp>
#include <System/Core.hpp>
#include <System/TimeSpan.hpp>
#include <map>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

AnimationClipMapReader::AnimationClipMapReader()
{
}

std::shared_ptr<void> AnimationClipMapReader::Read(ContentReader& input)
{
    auto animationClips = std::make_shared<std::map<String, AnimationClip>>();

    Int32 clipCount = input.ReadInt32();

    for (Int32 i = 0; i < clipCount; i++)
    {
        String clipName = *input.ReadObject<String>();

        animationClips->emplace(clipName, *input.ReadObject<AnimationClip>());
    }

    return animationClips;
}
