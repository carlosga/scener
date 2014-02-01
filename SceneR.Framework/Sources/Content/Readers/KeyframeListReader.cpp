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
#include <Content/Readers/KeyframeListReader.hpp>
#include <Graphics/Keyframe.hpp>
#include <vector>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Graphics;

KeyframeListReader::KeyframeListReader()
{
}

std::shared_ptr<void> KeyframeListReader::Read(ContentReader& input)
{
    auto keyframes     = std::make_shared<std::vector<Keyframe>>();
    auto keyframeCount = input.ReadInt32();

    keyframes->reserve(keyframeCount);

    for (Int32 i = 0; i < keyframeCount; i++)
    {
        keyframes->push_back(*input.ReadObject<Keyframe>());
    }

    return keyframes;
}

