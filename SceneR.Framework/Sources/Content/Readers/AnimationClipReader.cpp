// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/AnimationClipReader.hpp>

#include <Graphics/AnimationClip.hpp>
#include <Content/ContentReader.hpp>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Graphics;

AnimationClipReader::AnimationClipReader()
{
}

AnimationClipReader::~AnimationClipReader()
{
}

std::shared_ptr<void> AnimationClipReader::Read(ContentReader& input)
{
    return std::make_shared<AnimationClip>(TimeSpan { input.ReadInt64() }
                                         , *input.ReadObject<std::vector<Keyframe>>());
}
