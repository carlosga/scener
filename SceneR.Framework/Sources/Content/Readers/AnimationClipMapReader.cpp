// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/AnimationClipMapReader.hpp>

#include <map>
#include <memory>

#include <System/Core.hpp>
#include <Content/ContentReader.hpp>
#include <Graphics/AnimationClip.hpp>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Graphics;

AnimationClipMapReader::AnimationClipMapReader()
{
}

AnimationClipMapReader::~AnimationClipMapReader()
{
}

std::shared_ptr<void> AnimationClipMapReader::Read(ContentReader& input)
{
    auto clipCount      = input.ReadUInt32();
    auto animationClips = std::make_shared<std::map<std::u16string, AnimationClip>>();

    for (uint32_t i = 0; i < clipCount; i++)
    {
        auto clipName = *input.ReadObject<std::u16string>();

        animationClips->emplace(clipName, *input.ReadObject<AnimationClip>());
    }

    return animationClips;
}
