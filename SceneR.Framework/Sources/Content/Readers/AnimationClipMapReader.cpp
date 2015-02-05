// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/AnimationClipMapReader.hpp>

#include <Graphics/AnimationClip.hpp>
#include <Content/ContentReader.hpp>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

std::shared_ptr<void> AnimationClipMapReader::Read(ContentReader& input)
{
    auto animationClips = std::make_shared<std::map<String, AnimationClip>>();
    auto clipCount      = input.ReadInt32();

    for (Int32 i = 0; i < clipCount; i++)
    {
        auto clipName = *input.ReadObject<String>();

        animationClips->emplace(clipName, *input.ReadObject<AnimationClip>());
    }

    return animationClips;
}
